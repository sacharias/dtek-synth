#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include "generateSound.h"

int sample = 0;
int sampleMax = 411090;

/* 
 * 0 = PLAY
 * 1 = WAVE
 * 2 = DECAY 
 */
int mode = 0;

/* Interrupt Service Routine */
void user_isr() {
  int n = 0;
  int value = 0;
  int playButtonsValue = getPlayBtns();

  if (playButtonsValue & 0x40) {
      value += getCValue(sample);
      n++;
  }

  if (playButtonsValue & 0x20) {
    PORTESET = 0x2;
    value += getDValue(sample);
    n++;
  }

  if (playButtonsValue & 0x10) {
    value += getEValue(sample);
    n++;
  }

  if (playButtonsValue & 0x8) {
    value += getFValue(sample);
    n++;
  }

  if (playButtonsValue & 0x4) {
    value += getGValue(sample);
    n++;
  }

  if (playButtonsValue & 0x2) {
    value += getAValue(sample);
    n++;
  }

  if (playButtonsValue & 0x1) {
    value += getBValue(sample);
    n++;
  }

  if (n == 0) {
    OC1RS = 0;
  } else {
    OC1RS = (value / n) + 127;
  }

  sample++;
  if (sample >= sampleMax) {
    sample = 0;
  }
  //clear interrupt flag
  IFS(0) = 0x0000;
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
  generateSinWaves();
  setupPlayButtons();

  initLamps();

  // waveShow();
}

/* This function is called repetitively from the main program */
void labwork() {
  int portD = getPlayBtns();
  int portD2 = getBoardBtns();
  display_debug(&portD2);
}
