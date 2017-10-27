#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#define PI 3.14159265358979323846

double count = 0.0;
int debug_value = 0;
int sample = 0;

//int duration = 41109;
int duration = 20555;

int waveA[93];
int waveG[105];
int waveF[118];
int waveE[125];
int waveD[140];

double sin(double x)
{
  int n = 1;
  double sin = x, t = x;
  while (!(t >= -0.0000000001 && t <= 0.000000001))
  {
    t = (-t) * (x * x) / ((2 * n + 1) * (2 * n));
    sin = sin + t;
    n++;
  }
  return sin;
}

void generateSinWaves(void)
{
  // Make waveX arrays
  // sample rate: 41109

  // Make A = 440 Hz
  int i = 0;
  double sum = 0.0;
  for (i = 0; i < 93; i++)
  {
    waveA[i] = 127 * sin(sum);
    sum = sum + (PI / 92); // array.length - 1
  }

  // Make G = 391,995 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 105; i++)
  {
    waveG[i] = 127 * sin(sum);
    sum = sum + (PI / 104);
  }

  // Make F = 349,228 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 118; i++)
  {
    waveF[i] = 127 * sin(sum);
    sum = sum + (PI / 117);
  }

  // Make E = 329,628 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 125; i++)
  {
    waveE[i] = 127 * sin(sum);
    sum = sum + (PI / 124);
  }

  // Make D = 293,665 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 140; i++)
  {
    waveD[i] = 127 * sin(sum);
    sum = sum + (PI / 139);
  }
}

/* Interrupt Service Routine */
void user_isr()
{

  // Gör någonting varje 24,325 mikrosekund

  if (count < duration * 2)
  {
    OC1RS = waveA[sample] + 127;
    sample++;
    if (sample > 92)
    {
      sample = 0;
    }
  }
  else if (count < duration * 3)
  {
    OC1RS = waveG[sample] + 127;
    sample++;
    if (sample > 104)
    {
      sample = 0;
    }
  }
  else if (count < duration * 4)
  {
    OC1RS = waveF[sample] + 127;
    sample++;
    if (sample > 117)
    {
      sample = 0;
    }
  }
  else if (count < duration * 5)
  {
    OC1RS = waveE[sample] + 127;
    sample++;
    if (sample > 124)
    {
      sample = 0;
    }
  }
  else if (count < duration * 6)
  {
    OC1RS = waveD[sample] + 127;
    sample++;
    if (sample > 139)
    {
      sample = 0;
    }
  }
  else if (count < duration * 7)
  {
  }
  else if (count < duration * 8)
  {
    OC1RS = waveD[sample] + 127;
    sample++;
    if (sample > 139)
    {
      sample = 0;
    }
  }
  else if (count < duration * 9)
  {
  }
  else if (count < duration * 10)
  {
    OC1RS = waveD[sample] + 127;
    sample++;
    if (sample > 139)
    {
      sample = 0;
    }
  }

  count++;

  // Färdig
  // OC1RS = waveD[sample] + 127;
  // sample++;
  // if (sample > 139)
  // {
  //   sample = 0;
  // }

  // Färdig
  // OC1RS = waveE[sample] + 127;
  // sample++;
  // if (sample > 124)
  // {
  //   sample = 0;
  // }

  // Färdig
  // OC1RS = waveF[sample] + 127;
  // sample++;
  // if (sample > 117)
  // {
  //   sample = 0;
  // }

  // Färdig
  // OC1RS = waveG[sample] + 127;
  // sample++;
  // if (sample > 104)
  // {
  //   sample = 0;
  // }

  // Färdig
  // OC1RS = waveA[sample] + 127;
  // sample++;
  // if (sample > 92)
  // {
  //   sample = 0;
  // }

  //clear interrupt flag
  IFS(0) = 0x0000;
}

volatile int *triseAdress = 0xbf886100; //

/* Lab-specific initialization goes here */
void labinit()
{
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
}

/* This function is called repetitively from the main program */
void labwork()
{
  // Gör ingenting här.
}
