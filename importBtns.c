#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getBoardBtns(){
  int portD = PORTD >> 5;
  portD &= 0x7;
  return portD;
}

int *getPlayBtns() {
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

  // Pin 29
  int playButton7 = PORTE >> 3;
  playButton7 &= 0x1;

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