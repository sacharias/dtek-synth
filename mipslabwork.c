#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include "generateSound.h"

// Testing Variables
int count = 0;
int testVal = 0;
int updateRate = 60; // per second
int updateCount = 0;

// Global Variables
int sample = 0;
int sampleMax = 411090;
int shouldMatrixUpdate = 1; // if 1, matrix will update
/*
 * 0 = PLAY
 * 1 = WAVE
 * 2 = DECAY
 */
int mode = 0;

/*
 * 2 = Octave 2
 * 3 = Octave 3 (Standard)
 * 4 = Octave 4
 */
int octave = 4;

/*
 * 0 = Sine
 * 1 = Saw
 * 2 = Square
 */
int waveForm = 0;

void updateSound() {
  int n = 0;
  int value = 0;
  int playButtonsValue = getPlayBtns();

  if (playButtonsValue & 0x40) {
      value += getCValue(sample, octave);
      n++;
  }

  if (playButtonsValue & 0x20) {
    value += getDValue(sample, octave);
    n++;
  }

  if (playButtonsValue & 0x10) {
    value += getEValue(sample, octave);
    n++;
  }

  if (playButtonsValue & 0x8) {
    value += getFValue(sample, octave);
    n++;
  }

  if (playButtonsValue & 0x4) {
    value += getGValue(sample, octave);
    n++;
  }

  if (playButtonsValue & 0x2) {
    value += getAValue(sample, octave);
    n++;
  }

  if (playButtonsValue & 0x1) {
    value += getBValue(sample,octave);
    n++;
  }

  if (n == 0) {
    OC1RS = 0;
    shouldMatrixUpdate = 1;
  } else {
    OC1RS = (value / n) + 127;
    shouldMatrixUpdate = 0;
  }

  sample++;
  if (sample >= sampleMax) {
    sample = 0;
  }
}

/* Interrupt Service Routine */
void user_isr() {
  updateSound();

  IFS(0) = 0x0000; // Clear interrupt flag
}

void labinit() {
  IPC(2) = 0x1c; // set priority
  IFSCLR(0) = 0x0100; // clear interrupt flag
  IECSET(0) = 0x0100; // enable interrupt timer

  //Timer 2 Setup
  T2CONSET = 0x00; // 1:1 Prescaling
  PR2 = 1946;
  TMR2 = 0;          // Clear the timer register
  T2CONSET = 0x8000; // Start timer 2

  // Timer 3 and PWM
  OC1CON = 0x0000; // Turn off OC1
  OC1R = 0;        // 256 är max
  OC1RS = 0;       // Set dutycycle between 0 and PR3
  OC1CON = 0x000E; // Set Timer 3 as output compare and PWM Mode

  T3CONSET = 0x00;    // 1:1 Prescaling
  PR3 = 256;          // 8-bit depth
  T3CONSET = 0x8000;  // Start timer 3
  OC1CONSET = 0x8000; // Start PWM

  enable_interrupt();
  generateSinWaves(waveForm);
  setupPlayButtons();

  initLamps();
  // waveShow();
}

int waveIsClicked = 0;
int octaveIsClicked = 0;
/* This function is called repetitively from the main program */
void labwork() {
  int boardButtons = getBoardBtns();
  if(boardButtons & 0x4){
    if(!waveIsClicked){
      waveForm = waveForm + 1;
      if(waveForm > 2){
        waveForm = 0;
      }
      waveIsClicked = 1;
      display_debug(&waveForm);
      generateSinWaves(waveForm);

    }
  } else{
    waveIsClicked = 0;
  }

  if(boardButtons & 0x2){
     if(!octaveIsClicked){
       octave = octave + 1;
       if(octave > 4){
         octave = 2;
       }
       octaveIsClicked = 1;
       display_debug(&octave);
     }
   } else{
      octaveIsClicked = 0;
   }

   if (updateCount >= 30000) {
     if (shouldMatrixUpdate) {
       matrixNext();
     }
     updateCount = 0;
   } else {
     updateCount++;
   }

}
