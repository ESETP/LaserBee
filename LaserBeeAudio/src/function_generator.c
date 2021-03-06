///////////////////////////////////////////////////////////////////////////////
// function_generator.c
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "bsp.h"
#include "tick.h"
#include "function_generator.h"
#include "waveform_tables.h"



///////////////////////////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////////////////////////

//pins
SI_SBIT(C1, SFR_P2, 4);
SI_SBIT(Cs, SFR_P2, 3);
SI_SBIT(D, SFR_P2, 2);
SI_SBIT(Ds, SFR_P2, 1);
SI_SBIT(E, SFR_P2, 0);
SI_SBIT(F, SFR_P1, 7);
SI_SBIT(Fs, SFR_P1, 6);
SI_SBIT(G, SFR_P1, 5);
SI_SBIT(Gs, SFR_P1, 4);
SI_SBIT(A, SFR_P1, 3);
SI_SBIT(As, SFR_P1, 2);
SI_SBIT(H, SFR_P1, 1); // H German standard, needs to be used because B is a system macro
SI_SBIT(C2, SFR_P1, 0);


//function buttons
SI_SBIT(OCT_UP, SFR_P2, 6);
SI_SBIT(OCT_DOWN, SFR_P2, 5);
SI_SBIT(WAVE_CHANGE, SFR_P0, 7);

SI_SBIT(AMP_ON, SFR_P0, 6);


#define NUM_KEYS 13

// Demo state variables
static DemoState currentDemoState = DEMO_SQUARE;
static SI_VARIABLE_SEGMENT_POINTER(currentTable, uint16_t, const SI_SEG_CODE) = squareTable; // current waveform table for DAC output

// Frequency selection
static SI_SEGMENT_VARIABLE(fixed_frequency[NUM_KEYS], uint16_t, SI_SEG_XDATA) = {
    261L,
    277L,
    293L,
    311L,
    329L,
    349L,
    370L,
    392L,
    415L,
    440L,
    466L,
    494L,
    523L,
};

#define CENTRE_OCT 5
static uint8_t octave_loc = CENTRE_OCT;

// Frequency selection
static SI_SEGMENT_VARIABLE(frequency[NUM_KEYS], uint16_t, SI_SEG_XDATA) = {
    261L,
    277L,
    293L,
    311L,
    329L,
    349L,
    370L,
    392L,
    415L,
    440L,
    466L,
    494L,
    523L,
};

// Current Frequency Selection
#define NUM_VOICES 3
#define EMPTY 255
#define MIN_FREQ 70
#define MAX_FREQ 1000
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
//
static void transitionDemoWaveform(void)
{

    switch (currentDemoState)
    {
    case DEMO_SINE:
      currentDemoState = DEMO_SQUARE;
      currentTable = squareTable;
      break;

    case DEMO_SQUARE:
      currentDemoState = DEMO_SAWTOOTH;
      currentTable = sawtoothTable;
      break;

    case DEMO_SAWTOOTH:
      currentDemoState = DEMO_PIANO;
      currentTable = pianoTable;
      break;

    case DEMO_PIANO:
      currentDemoState = DEMO_SINE;
      currentTable = sineTable;
      break;

    }
}


//-----------------------------------------------------------------------------
// getWait
//-----------------------------------------------------------------------------
// get value of given input and wait until it is unpressed to return.
//
static void getWaitFunctions(uint8_t * out)
{

  uint8_t up, down, change;

  up = OCT_UP;
  down = OCT_DOWN;
  change = WAVE_CHANGE;

  // wait for release then return saved values
  while (!OCT_UP || !OCT_DOWN || !WAVE_CHANGE){};

  out[0] = up;
  out[1] = down;
  out[2] = change;

}

//-----------------------------------------------------------------------------
// clear
//-----------------------------------------------------------------------------
// empty the currently playing note arrays and set countPressed = 0
//
static void clear(){
  uint8_t i;

  for (i = 0; i < NUM_VOICES; i++){
      currentFreqIndex[i] = EMPTY;
      phaseOffset[i] = 0;
  }

  countPressed = 0;
  AMP_ON = 0;
}

//-----------------------------------------------------------------------------
// processInput
//-----------------------------------------------------------------------------
// main control flow of program. Handle function button presses and then add
// newly pressed keys to the array if there is space.
//
static void processInput(uint8_t *functions)
{
  uint8_t i, j;
  uint8_t keys[NUM_KEYS];

  keys[0] = C1;
  keys[1] = Cs;
  keys[2] = D;
  keys[3] = Ds;
  keys[4] = E;
  keys[5] = F;
  keys[6] = Fs;
  keys[7] = G;
  keys[8] = Gs;
  keys[9] = A;
  keys[10] = As;
  keys[11] = H;
  keys[12] = C2;

  // If change then transition waveform
  if (!functions[2])
    {
      transitionDemoWaveform();
    }

  // If oct up then shift freq * 2
  if (!functions[0] && frequency[0] < MAX_FREQ){
      octave_loc += 1;

            if (octave_loc == CENTRE_OCT){
                for (i = 0; i < NUM_KEYS; i++){
                        frequency[i] = fixed_frequency[i];
                    }
            }
            else{

              for (i = 0; i < NUM_KEYS; i++){
                        frequency[i] *= 2;
                    }
            }
  }

  // If oct down then shift freq / 2
  if (!functions[1] && frequency[NUM_KEYS-1] > MIN_FREQ){
      octave_loc -= 1;

      if (octave_loc == CENTRE_OCT){
          for (i = 0; i < NUM_KEYS; i++){
                  frequency[i] = fixed_frequency[i];
              }
      }
      else{

        for (i = 0; i < NUM_KEYS; i++){
                  frequency[i] /= 2;
              }
      }
  }

  //check current pressed keys are still pressed
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
                  AMP_ON = 1;
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

    //temp.u16 /= NUM_VOICES;


    // Set the value of <temp> to the next output of DAC at full-scale
    // amplitude. The rails are 0x000 and 0xFFF. DAC low byte must be
    // written first.
    SFRPAGE = PG4_PAGE;


    DAC0L = temp.u8[LSB];
    DAC0H = temp.u8[MSB];
  }
}

///////////////////////////////////////////////////////////////////////////////
// Driver Function
///////////////////////////////////////////////////////////////////////////////

void FunctionGenerator_main(void)
{
  while(1)
  {
      uint8_t controlButtons[3];
      getWaitFunctions(controlButtons);
      processInput(controlButtons);
  }
}
