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

// Pins
SI_SBIT(IN1, SFR_P1, 4);                  // P1.4 IN1
//SI_SBIT(IN2, SFR_P1, 5);                  // P1.5 IN2
//SI_SBIT(IN3, SFR_P1, 6);                  // P1.6 IN3

// Demo state variables
static DemoState currentDemoState = DEMO_SINE;
static SI_VARIABLE_SEGMENT_POINTER(currentTable, uint16_t, const SI_SEG_CODE) = sineTable; // current waveform table for DAC output
static SI_VARIABLE_SEGMENT_POINTER(currentWaveform, uint8_t, const SI_SEG_CODE) = sine_bits; // current waveform picture

// Frequency selection
#define SUPPORTED_NUM_FREQ 8
static SI_SEGMENT_VARIABLE(frequency[SUPPORTED_NUM_FREQ], uint16_t, SI_SEG_XDATA) = {
    10L,
    20L,
    50L,
    100L,
    200L,
    440L,
    1000L,
    2000L
};

// Current Frequency Selection
static uint8_t currentFreqIndex = 3;

// Phase offset (updated when frequency is changed)
static uint16_t phaseOffset1 = 100 * PHASE_PRECISION / SAMPLE_RATE_DAC;
//static uint16_t phaseOffset2 = 100 * PHASE_PRECISION / SAMPLE_RATE_DAC;
//static uint16_t new_freq = 440;

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
// transitionDemoFrequency
//-----------------------------------------------------------------------------
//
// Change frequency of the function.
// Up   - increase frequency
// Down - decrease frequency
//
// dir - valid arguments are: JOYSTICK_N, JOYSTICK_S
//
static void transitionDemoFrequency(uint8_t dir)
{
  if (dir == JOYSTICK_N)
  {
    // increase freq
    if(currentFreqIndex == SUPPORTED_NUM_FREQ-1)
    {
      currentFreqIndex = 0;
    }
    else
    {
      currentFreqIndex++;
    }
  }
  else if (dir == JOYSTICK_S)
  {
    // decrease freq
    if (currentFreqIndex == 0)
    {
      currentFreqIndex = SUPPORTED_NUM_FREQ-1;
    }
    else
    {
      currentFreqIndex--;
    }
  }

  phaseOffset1 = frequency[currentFreqIndex] * PHASE_PRECISION / SAMPLE_RATE_DAC;
  //new_freq = frequency[currentFreqIndex] * 1.26;
  //phaseOffset2 = (new_freq) * PHASE_PRECISION / SAMPLE_RATE_DAC;
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

//-----------------------------------------------------------------------------
// getJoystickDemo
//-----------------------------------------------------------------------------
//
// Get and process joystick input.
// Left/Right = change function/waveform
// Up/Down    = change frequency
//
static void processInput(uint8_t dir)
{
  // process input
  //if ((dir == JOYSTICK_E) || (dir == JOYSTICK_W))
  //{
  //  transitionDemoWaveform(dir);
  //}
  //else if ((dir == JOYSTICK_N) || (dir == JOYSTICK_S))
  //{
  //  transitionDemoFrequency(dir);
  //}

  if (IN1 == 1){
      currentFreqIndex = 0;
      phaseOffset1 = frequency[currentFreqIndex] * PHASE_PRECISION / SAMPLE_RATE_DAC;
  }
  else if (IN1 == 0){
      currentFreqIndex = 1;
      phaseOffset1 = frequency[currentFreqIndex] * PHASE_PRECISION / SAMPLE_RATE_DAC;
  }
  else{
      phaseOffset1 = 0;
      //phaseOffset2 = 0;
  }
}


///////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
///////////////////////////////////////////////////////////////////////////////

SI_INTERRUPT_USING(TIMER4_ISR, TIMER4_IRQn, 1)
{
  static uint16_t phaseAcc1 = 0;       // Holds phase accumulator
  //static uint16_t phaseAcc2 = 0;       // Holds phase accumulator

  SI_UU16_t temp;   // The temporary value that holds
                    // value before being written
                    // to the DAC
  
  TMR4CN0 &= ~TMR3CN0_TF3H__BMASK;    // Clear Timer4 overflow flag

  phaseAcc1 += phaseOffset1;            // Increment phase accumulator
  //phaseAcc2 += phaseOffset2;            // Increment phase accumulator

  // Read the table value
  temp.u16 = currentTable[phaseAcc1 >> 8];

  // Set the value of <temp> to the next output of DAC at full-scale
  // amplitude. The rails are 0x000 and 0xFFF. DAC low byte must be
  // written first.

  SFRPAGE = PG4_PAGE;

  DAC3L = DAC2L = DAC1L = DAC0L = temp.u8[LSB];
  DAC3H = DAC2H = DAC1H = DAC0H = temp.u8[MSB];
}

//-----------------------------------------------------------------------------
// PMATCH_ISR
//-----------------------------------------------------------------------------
//
// The Port Match interrupt occurs whenever (Pn & PnMASK) != (PnMAT & PnMASK).
// We must disable the interrupt and wait until the button is released in
// main, or else the interrupt will trigger multiple times.  It is generally
// not good practice to sit in an ISR for int32_t periods of time.
//
SI_INTERRUPT(PMATCH_ISR, PMATCH_IRQn)
{
  uint8_t SFRPAGE_save = SFRPAGE;

  SFRPAGE = PG2_PAGE;

  EIE1 &= ~0x02;                     // Disable Port Match interrupts to
                                     // prevent multiple interrupts from
                                     // occurring while the button is
                                     // pressed
  SFRPAGE = SFRPAGE_save;
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
