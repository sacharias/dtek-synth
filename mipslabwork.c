#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include "generateSound.h"

//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP 0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE 9
#define OP_INTENSITY 10
#define OP_SCANLIMIT 11
#define OP_SHUTDOWN 12
#define OP_DISPLAYTEST 15

double count = 0.0;
int debug_value = 0;
int sample = 0;
int sampleMax = 411090;

int globalCounter = 0;
int currentState = 0;
//int duration = 41109;

void setCs(int high) {
  if (high) {
    // Sätt cs till HIGH
    PORTESET = 0x0004;
  } else {
    // Sätt cs till LOW
    PORTECLR = 0x0004;
  }
}

void setData(int high) {
  if (high) {
    // Sätt data till HIGH
    PORTESET = 0x0002;
  } else {
    // Sätt DATA till LOW
    PORTECLR = 0x0002;
  }
}

void setClk(int high) {
  if (high) {
    // Sätt clk till HIGH
    PORTESET = 0x0001;
  } else {
    // Sätt clk till LOW
    PORTECLR = 0x0001;
  }
}

// Connect to 34 on chipkit
void setupPlayButtons()
{
  TRISDSET = 0xFFFF; // Sätter första till input
  TRISFSET = 0x8;    // prova med 8
}

int *getPlayButtons()
{
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

  // Fungerar inte än
  // Pin 1
  // int playButton7 = PORTF >> 2;
  // playButton7 &= 0x1;
  int playButton7 = 0;

  int playButtonsValue = 0;
  playButtonsValue = playButton1 << 6;
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
  // if (playButtonsValue & 0x40) {
  //     value += getCValue(sample);
  //     n++;
  // }
  if (playButtonsValue & 0x20)
  {
    PORTESET = 0x2;
    value += getDValue(sample);
    n++;
  }

  if (playButtonsValue & 0x10)
  {
    value += getEValue(sample);
    n++;
  }

  if (playButtonsValue & 0x8)
  {
    value += getFValue(sample);
    n++;
  }

  if (playButtonsValue & 0x4)
  {
    value += getGValue(sample);
    n++;
  }

  if (playButtonsValue & 0x2)
  {
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
    OC1RS = (value / n) + 127;
  }

  sample++;
  if (sample >= sampleMax) {
    sample = 0;
  }
  //clear interrupt flag
  IFS(0) = 0x0000;
}

void spiTransferDuo(char data1[], char data2[]) {
  setCs(0);

  int i;
  for (i = 0; i < 16; i++) {
    setClk(0);
    setData(data2[i]);
    quicksleep(80);
    setClk(1);
    quicksleep(80);
  }

  i = 0;
  for (i = 0; i < 16; i++) {
    setClk(0);
    setData(data1[i]);
    quicksleep(80);
    setClk(1);
    quicksleep(80);
  }

  setCs(1);
  setClk(0);
  quicksleep(80);
}

void setLedMatrixHelper(char m[], int b1[], int b2[], char dCode[]) {
  char OneCol0[] = {
    dCode[0], dCode[1], dCode[2], dCode[3], dCode[4], dCode[5], dCode[6], dCode[7], 
    m[b1[0]], m[b1[1]], m[b1[2]], m[b1[3]], m[b1[4]], m[b1[5]], m[b1[6]], m[b1[7]]
  };
  char TwoCol0[] = {
    dCode[0], dCode[1], dCode[2], dCode[3], dCode[4], dCode[5], dCode[6], dCode[7], 
    m[b2[0]], m[b2[1]], m[b2[2]], m[b2[3]], m[b2[4]], m[b2[5]], m[b2[6]], m[b2[7]]
  };
  spiTransferDuo(OneCol0, TwoCol0);
}

void setLedMatrix(char m[]) { 
  int b1[] = {112, 96, 80, 64, 48, 32, 16, 0};
  int b2[] = {120, 104, 88, 72, 56, 40, 24, 8};

  char digit0[] = {0, 0, 0, 0, 0, 0, 0, 1};
  char digit1[] = {0, 0, 0, 0, 0, 0, 1, 0};
  char digit2[] = {0, 0, 0, 0, 0, 0, 1, 1};
  char digit3[] = {0, 0, 0, 0, 0, 1, 0, 0};
  char digit4[] = {0, 0, 0, 0, 0, 1, 0, 1};
  char digit5[] = {0, 0, 0, 0, 0, 1, 1, 0};
  char digit6[] = {0, 0, 0, 0, 0, 1, 1, 1};
  char digit7[] = {0, 0, 0, 0, 1, 0, 0, 0};

  setLedMatrixHelper(m, b1, b2, digit0);

  int i;
  for (i = 0; i < 8; i++) {
    b1[i] = b1[i] + 1;
    b2[i] = b2[i] + 1;
  }
  setLedMatrixHelper(m, b1, b2, digit1);

  for (i = 0; i < 8; i++) {
    b1[i] = b1[i] + 1;
    b2[i] = b2[i] + 1;
  }
  setLedMatrixHelper(m, b1, b2, digit2);

  for (i = 0; i < 8; i++) {
    b1[i] = b1[i] + 1;
    b2[i] = b2[i] + 1;
  }
  setLedMatrixHelper(m, b1, b2, digit3);

  for (i = 0; i < 8; i++) {
    b1[i] = b1[i] + 1;
    b2[i] = b2[i] + 1;
  }
  setLedMatrixHelper(m, b1, b2, digit4);

  for (i = 0; i < 8; i++) {
    b1[i] = b1[i] + 1;
    b2[i] = b2[i] + 1;
  }
  setLedMatrixHelper(m, b1, b2, digit5);

  for (i = 0; i < 8; i++) {
    b1[i] = b1[i] + 1;
    b2[i] = b2[i] + 1;
  }
  setLedMatrixHelper(m, b1, b2, digit6);

  for (i = 0; i < 8; i++) {
    b1[i] = b1[i] + 1;
    b2[i] = b2[i] + 1;
  }
  setLedMatrixHelper(m, b1, b2, digit7);
}

void initLamps() {
  // Sätt upp output på ledlamporna
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
  char zeros[] = { 
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                  };
  setLedMatrix(zeros);
}

void fallingStock() {
  int fillFrom = 0;
  int i;
  for (i = 0; i < 8; i++) {
    char matrix[128];
    int j;
    for (j = fillFrom; j < 16; i++) {
      matrix[j] = 1;
    }
    setLedMatrix(matrix);
    quicksleep(1000000);
    fillFrom += 16;
    }

}
  // char matrix[] = { 
  //                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
  //                 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  //                 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
  //                 };
  // setLedMatrix(matrix);
  
  // char matrix2[] = { 
  //                 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
  //                 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
  //                 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  //                 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
  // };
  // setLedMatrix(matrix2);

/* Lab-specific initialization goes here */
void labinit() {
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

  initLamps();

  // char matrix[128] = { 
  //                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
  //                 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0,
  //                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1,
  //                 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
  //                 };
  // setLedMatrix(matrix);

  fallingStock();
}

/* This function is called repetitively from the main program */
void labwork() {
  int portD = getPlayButtons();
}
