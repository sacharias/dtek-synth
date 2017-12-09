#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"



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
