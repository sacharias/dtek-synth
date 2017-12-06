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

void setupPlayButtons() {
  TRISDSET = 0xFFFF;
  TRISFSET = 0x8;
}

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

void initLamps() {
  // Setup Output Led Lamps
  TRISECLR = 0x0001;
  TRISECLR = 0x0002;
  TRISECLR = 0x0004;

  // Setup - LED Matrix
  char normalOperation[] = {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  spiTransferDuo(normalOperation, normalOperation);

  char scanlimit[] = {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1};
  spiTransferDuo(scanlimit, scanlimit);

  char intensity[] = {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};
  spiTransferDuo(intensity, intensity);

  // Reset - turn off all lights
  char matrix[] = { 
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  };
  setLedMatrix(matrix);
}

void waveShow() {
  while (1) {
    int del = 150000;
    char matrix[128];
    int i;
    for (i = 0; i < 128; i++) {
      matrix[i] = 1;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 16; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 32; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 48; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 64; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 80; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 96; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 112; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);

    quicksleep(del);
      for (i = 0; i < 128; i++) {
      matrix[i] = 0;
    }
    setLedMatrix(matrix);
  }
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
