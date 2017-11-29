#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include "generateSound.h"

double count = 0.0;
int debug_value = 0;
int sample = 0;
int sampleMax = 411090;
int waveType = 0; // 0 = sine, 1 = triangle, 2 = square
int octave = 4; // Standard = 4, Range: 2 - 4

//int duration = 41109;

// Connect to 34 on chipkit
void setupPlayButtons() {
  TRISDSET = 0xFFFF; // Sätter första till input
  TRISFSET = 0x8; // prova med 8
}

int* getPlayButtons() {
  // Pin 5
  int playButton1 = PORTD >> 1;
  playButton1 &= 0x1;

  // Pin 6
  int playButton2 = PORTD >> 2;
  playButton2 &= 0x1;

  // Pin 7
  int playButton3 = PORTD >> 9;
  playButton3 &= 0x1;

  // Pin 8
  int playButton4 = PORTD >> 10;
  playButton4 &= 0x1;

  // Pin 9
  int playButton5 = PORTD >> 3;
  playButton5 &= 0x1;

  // Pin 2
  int playButton6 = PORTD >> 8;
  playButton6 &= 0x1;

  // Guide till problem:
  // PORTF >> 2 är alltid på.
  

  // Fungerar inte än
  // Pin 1
  // int playButton7 = PORTF >> 2;
  // playButton7 &= 0x1;
  int playButton7 = 0;


  int playButtonsValue = 0;
  playButtonsValue = playButton1 << 6 ;
  playButtonsValue |= playButton2 << 5;
  playButtonsValue |= playButton3 << 4;
  playButtonsValue |= playButton4 << 3;
  playButtonsValue |= playButton5 << 2;
  playButtonsValue |= playButton6 << 1;
  playButtonsValue |= playButton7;

  return playButtonsValue;
}


/* Interrupt Service Routine */
void user_isr()
{
  int n = 0;
  int value = 0;
  int playButtonsValue = getPlayButtons();

  // C finns inte än.
  if (playButtonsValue & 0x40) {
      value += getCValue(sample);
      n++;
  }
  if (playButtonsValue & 0x20) {
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

  // B finns inte än.
  // if (playButtonsValue & 0x1) {
  //   value += getBValue(sample);
  //   n++;
  // }

  if (n == 0) {
    OC1RS = 0;
  } else {
    OC1RS = ( value / n ) + 127;
  }

  sample++;
  if (sample >= sampleMax) { sample = 0; }

  //clear interrupt flag
  IFS(0) = 0x0000;
}

// volatile int *triseAdress = 0xbf886100; //

/* Lab-specific initialization goes here */
void labinit()
{
  // *triseAdress &= ~0xFF;
  // TRISD |= 0xFE0; // toggle switches

  // set priority
  IPC(2) = 0x1c;
  //clear interrupt flag
  IFSCLR(0) = 0x0100;
  // enable interrupt timer
  IECSET(0) = 0x0100;

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
}

/* This function is called repetitively from the main program */
void labwork()
{
  int portD = getPlayButtons();
  // int p = PORTD >> 9;
  display_debug(&portD);
}
