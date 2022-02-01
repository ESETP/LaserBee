/**************************************************************************//**
 * Copyright (c) 2015 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/
///////////////////////////////////////////////////////////////////////////////
// function_generator.c
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Call Graph
//
// FunctionGenerator_main()
//  |
//  +- drawSplash()
//  |   +- getWaitJoystick()
//  |   |   +- getJoystick()
//  |
//  +- drawStaticSprites()
//  |   +- drawScreenSprite()
//  |
//  +- processInput()
//  |   +- transitionDemoWaveform()
//  |   +- transitionDemoFrequency()
//  |
//  +- drawScreen()
//  |   +- drawScreenWaveform()
//  |   +- drawScreenFrequency()
//  |       +- drawScreenText()
//  |
//  +- synchFrame()
//
// Timer4_ISR()
//
// PORTMATCH_ISR()
//

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "bsp.h"
#include "tick.h"
#include "render.h"
#include "joystick.h"
#include "thinfont.h"
#include "function_generator.h"
#include "sine.h"
#include "square.h"
#include "triangle.h"
#include "sawtooth.h"
#include "windowed_sine.h"
#include "nav_up.h"
#include "nav_down.h"
#include "nav_left.h"
#include "nav_right.h"
#include "waveform_tables.h"
#include "retargetserial.h"


///////////////////////////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////////////////////////

//pins
//uint8_t* C1 = 0x90^0x04; // you also changed the C1s farther down
SI_SBIT(C1, SFR_P1, 4);
SI_SBIT(D, SFR_P1, 5);
SI_SBIT(Ds, SFR_P1, 6);




#define NUM_KEYS 3

// Demo state variables
static DemoState currentDemoState = DEMO_SINE;
static SI_VARIABLE_SEGMENT_POINTER(currentTable, uint16_t, const SI_SEG_CODE) = sineTable; // current waveform table for DAC output
static SI_VARIABLE_SEGMENT_POINTER(currentWaveform, uint8_t, const SI_SEG_CODE) = sine_bits; // current waveform picture

// Frequency selection
#define SUPPORTED_NUM_FREQ 8
static SI_SEGMENT_VARIABLE(frequency[SUPPORTED_NUM_FREQ], uint16_t, SI_SEG_XDATA) = {
    261L,
    293L,
    311L,
    100L,
    200L,
    440L,
    1000L,
    2000L
};

// Current Frequency Selection
#define NUM_VOICES 2
#define EMPTY 255
static uint8_t currentFreqIndex[NUM_VOICES] = {EMPTY};
static uint8_t countPressed = 0;

// Phase offset (updated when frequency is changed)
static uint16_t phaseOffset[NUM_VOICES] = {0};


///////////////////////////////////////////////////////////////////////////////
// Supporting Functions
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// transitionDemoWaveform
//-----------------------------------------------------------------------------
//
// Change function/waveform.
// Left  - change function order: sine < square < triangle < sawtooth < windowed sine
// Right - change function order: sine > square > triangle > sawtooth > windowed sine
//
// dir - valid arguments are: JOYSTICK_E, JOYSTICK_W
//
static void transitionDemoWaveform(uint8_t dir)
{
  if (dir == JOYSTICK_E)
  {
    switch (currentDemoState)
    {
    case DEMO_SINE:
      currentDemoState = DEMO_SQUARE;
      currentWaveform = square_bits;
      currentTable = squareTable;
      break;

    case DEMO_SQUARE:
      currentDemoState = DEMO_TRIANGLE;
      currentWaveform = triangle_bits;
      currentTable = triangleTable;
      break;

    case DEMO_TRIANGLE:
          currentDemoState = DEMO_SAWTOOTH;
      currentWaveform = sawtooth_bits;
      currentTable = sawtoothTable;
      break;

    case DEMO_SAWTOOTH:
      currentDemoState = DEMO_WINDOWED_SINE;
      currentWaveform = windowed_sine_bits;
      currentTable = windowedSineTable;
      break;

    case DEMO_WINDOWED_SINE:
      currentDemoState = DEMO_SINE;
      currentWaveform = sine_bits;
      currentTable = sineTable;
      break;
    }
  }
  else if (dir == JOYSTICK_W)
  {
    switch (currentDemoState)
    {
    case DEMO_SINE:
      currentDemoState = DEMO_WINDOWED_SINE;
      currentWaveform = windowed_sine_bits;
      currentTable = windowedSineTable;
      break;

    case DEMO_SQUARE:
      currentDemoState = DEMO_SINE;
      currentWaveform = sine_bits;
      currentTable = sineTable;
      break;

    case DEMO_TRIANGLE:
      currentDemoState = DEMO_SQUARE;
      currentWaveform = square_bits;
      currentTable = squareTable;
      break;

    case DEMO_SAWTOOTH:
      currentDemoState = DEMO_TRIANGLE;
      currentWaveform = triangle_bits;
      currentTable = triangleTable;
      break;

    case DEMO_WINDOWED_SINE:
      currentDemoState = DEMO_SAWTOOTH;
      currentWaveform = sawtooth_bits;
      currentTable = sawtoothTable;
      break;
    }
  }
}

//-----------------------------------------------------------------------------
// getJoystick
//-----------------------------------------------------------------------------
//
// Get new ADC sample and return joystick direction. Valid return values:
//  JOYSTICK_NONE   JOYSTICK_N   JOYSTICK_S
//  JOYSTICK_C      JOYSTICK_E   JOYSTICK_W
//
static uint8_t getJoystick(void)
{
  uint32_t mv;
  uint8_t dir;

  ADC0CN0_ADBUSY = 1;
  while (!ADC0CN0_ADINT);
  ADC0CN0_ADINT = 0;

  mv = ((uint32_t)ADC0) * 3300 / 1024;

  dir = JOYSTICK_convert_mv_to_direction(mv);

  return dir;
}

//-----------------------------------------------------------------------------
// getWaitJoystick
//-----------------------------------------------------------------------------
//
// Get joystick input. If joystick was moved, wait for release. Return joystick
// direction. Valid return values:
//  JOYSTICK_NONE   JOYSTICK_N   JOYSTICK_S
//  JOYSTICK_C      JOYSTICK_E   JOYSTICK_W
//
static uint8_t getWaitJoystick(void)
{
  uint8_t dir, dirSave;

  dir = getJoystick();
  dirSave = dir;


  // wait for release then transition
  while (dir != JOYSTICK_NONE)
  {
    dir = getJoystick();
  }

  return dirSave;
}


static void clear(){
  uint8_t i;

  for (i = 0; i < NUM_VOICES; i++){
      currentFreqIndex[i] = EMPTY;
      phaseOffset[i] = 0;
  }

  countPressed = 0;
}


static void processInput(uint8_t dir)
{
  uint8_t i, j;
  uint8_t keys[NUM_KEYS];

  keys[0] = C1;
  keys[1] = D;
  keys[2] = Ds;


  if ((dir == JOYSTICK_E) || (dir == JOYSTICK_W))
    {
      transitionDemoWaveform(dir);
    }


  //check current pressed keys
    for (i = 0; i < NUM_VOICES; i++){
        if (currentFreqIndex[i] != EMPTY){
            if (keys[currentFreqIndex[i]]){
                clear();
                break;
            }
        }
    }


    if (countPressed < NUM_VOICES){
      //check each key for pressed
      for (i = 0; i < NUM_KEYS; i++){
          if (!keys[i] && countPressed < NUM_VOICES){
              uint8_t duplicate = 0;
              for (j = 0; j < NUM_VOICES; j++){
                  if (currentFreqIndex[j] == i){
                      duplicate = 1;
                  }
              }
              if (!duplicate){
                  currentFreqIndex[countPressed] = i;
                  phaseOffset[countPressed] = frequency[currentFreqIndex[countPressed]] * PHASE_PRECISION / SAMPLE_RATE_DAC;
                  countPressed++;
              }
          }
      }
    }



}


///////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
///////////////////////////////////////////////////////////////////////////////

SI_INTERRUPT_USING(TIMER4_ISR, TIMER4_IRQn, 1)
{
  static uint16_t phaseAcc[NUM_VOICES] = {0};       // Holds phase accumulator
  uint8_t i;

  SI_UU16_t temp;   // The temporary value that holds
                    // value before being written
                    // to the DAC
  
  TMR4CN0 &= ~TMR3CN0_TF3H__BMASK;    // Clear Timer4 overflow flag

  if (countPressed){
    temp.u16 = 0;
    for (i = 0; i < NUM_VOICES; i++){
        phaseAcc[i] += phaseOffset[i];            // Increment phase accumulator
        // Read the table value
        temp.u16 += currentTable[phaseAcc[i] >> 8];
    }

    temp.u16 /= countPressed;


    // Set the value of <temp> to the next output of DAC at full-scale
    // amplitude. The rails are 0x000 and 0xFFF. DAC low byte must be
    // written first.
    SFRPAGE = PG4_PAGE;


    DAC3L = DAC2L = DAC1L = DAC0L = temp.u8[LSB];
    DAC3H = DAC2H = DAC1H = DAC0H = temp.u8[MSB];
  }
}

///////////////////////////////////////////////////////////////////////////////
// Driver Function
///////////////////////////////////////////////////////////////////////////////

void FunctionGenerator_main(void)
{
  while(1)
  {
    processInput(getWaitJoystick());
  }
}
