#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void setCs(int high) {
  if (high) {
    PORTESET = 0x0004; // CS HIGH
  } else {
    PORTECLR = 0x0004; // CS LOW
  }
}

void setData(int high) {
  if (high) {
    PORTESET = 0x0002; // DATA HIGH
  } else {
    PORTECLR = 0x0002; // DATA LOW
  }
}

void setClk(int high) {
  if (high) {
    PORTESET = 0x0001; // CLK HIGH
  } else {
    PORTECLR = 0x0001; // CLK LOW
  }
}

void spiTransferDuo(char data1[], char data2[]) {
  int sleepTime = 40;
  setCs(0);

  int i;
  for (i = 0; i < 16; i++) {
    setClk(0);
    setData(data2[i]);
    quicksleep(sleepTime);
    setClk(1);
    quicksleep(sleepTime);
  }

  i = 0;
  for (i = 0; i < 16; i++) {
    setClk(0);
    setData(data1[i]);
    quicksleep(sleepTime);
    setClk(1);
    quicksleep(sleepTime);
  }

  setCs(1);
  setClk(0);
  quicksleep(sleepTime);
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