#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


int getsw(){
  int portD = PORTD >> 8;
  portD &= 0xF;
  return portD;
}

int getbtns(){
  int portD = PORTD >> 5;
  portD &= 0x7;
  return portD;
}
