#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#define PI 3.14159265358979323846

int timeoutcount = 0;
int debug_value = 0;
int sample = 0;
int on = 0;

int waveA [94]; // 440 Hz
int waveG [105]; // 391,995 Hz

double sin(double x) {
	int n = 1;
	double sin = x, t = x;
	while (!(t >= -0.0000000001 && t <= 0.000000001)) {
		t = (-t) * (x * x) / ((2 * n + 1) * (2 * n));
		sin = sin + t;
		n++;
	}
	return sin;
}

/* Interrupt Service Routine */
void user_isr() {

  // if(timeoutcount >= 41109){
  //   // Gör någonting varje sekund
  //
  //   int tempVal = waveA[sample] + 127;
  //   sample++;
  //   if (sample >= 92) {
  //     sample = 0;
  //   }
  //
  //   timeoutcount = 0;
  //   display_debug(&sample);
  //   debug_value++;
  // }
  // timeoutcount++;

  // Gör någonting varje 24,325 mikrosekund
  int tempVal = waveA[sample] + 127;
  OC1RS = tempVal;

  sample++;

  if (sample >= 93) {
    sample = 0;
  }



  // F4 SQUARE WAVE
  // if ( (sample % 59) == 0) {
  //   if (on) {
  //     OC1RS = 0;
  //     on = 0;
  //   } else {
  //     OC1RS = 256;
  //     on = 1;
  //   }
  // }
  // sample ++;

  //clear interrupt flag
  IFS(0) = 0x0000;
}

volatile int *triseAdress = 0xbf886100; //

/* Lab-specific initialization goes here */
void labinit() {
    *triseAdress &= ~0xFF;
    TRISD |= 0xFE0; // toggle switches

    // set priority
    IPC(2) = 0x1c;
    //clear interrupt flag
    IFSCLR(0) = 0x0100;
    // enable interrupt timer
    IECSET(0) = 0x0100;

    //Timer 2 Setup
    T2CONSET = 0x00; // 1:1 Prescaling
    PR2 = 1946;
    TMR2 = 0; // Clear the timer register
    T2CONSET = 0x8000; // Start timer 2

    // Timer 3 and PWM
    OC1CON = 0x0000; // Turn off OC1
    OC1R = 0; // 256 är max
    OC1RS = 0; // Set dutycycle between 0 and PR3
    OC1CON = 0x000E; // Set Timer 3 as output compare and PWM Mode

    T3CONSET = 0x00; // 1:1 Prescaling
    PR3 = 256; // 8-bit depth
    T3CONSET = 0x8000; // Start timer 3
    OC1CONSET = 0x8000; // Start PWM

    // Make waveX arrays
    // sample rate: 41109

    // Make waveG
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < 105; i++){
      waveG[i] = 127 * sin(sum);
      sum = sum + (PI / 104);
    }

    // Make waveA
    i = 0;
    sum = 0.0;
    for (i = 0; i < 94; i++){
      waveA[i] = 127 * sin(sum);
      sum = sum + (PI / 93);
    }

    enable_interrupt();
}

/* This function is called repetitively from the main program */
void labwork() {
  // Gör ingenting här.
}
