/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
int timeoutcount = 0;
int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

volatile int *triseAdress = 0xbf886100;

/* Lab-specific initialization goes here */
void labinit()
{
    *triseAdress &= ~0xFF;
    TRISD |= 0xFE0;

    //timerstuff
    //T2CONSET = 0x70;
    //PR2 = 31250;
    //TMR2 = 0;
    //T2CONSET = 0x8000; // Start timer

}

volatile int *porteAdress = 0xbf886110;

void setupPWM(void) {
  T2CONSET = 0x70;
  PR2 = 1561;
  OC1RS = 117;
  OC1CONbits.OCM = 0b110;
  T2CONbits.ON = 1;
  OC1CONbots.ON = 1;
}

void updateDisplay(){
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  display_image(96, icon);
}

void doTimeStuff(){
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
  *porteAdress += 1;
}

/* This function is called repetitively from the main program */
void labwork( void ){
    /*
    int btnValue = getbtns();
    if(btnValue){
      int switchValue = getsw();

      if((btnValue >>2) & 1){
        int a = switchValue << 12;
        mytime &= 0x0FFF;
        mytime = a|mytime;
      }

      if((btnValue >>1) & 1){
        int a = switchValue << 8;
        mytime &= 0xF0FF;
        mytime = a|mytime;
      }

      if(btnValue & 1){
        int a = switchValue << 4;
        mytime &= 0xFF0F;
        mytime = a|mytime;

      }

      updateDisplay();

    }

    if((IFS(0) >> 8) & 1){
      IFS(0) &= 0x0FF;
      timeoutcount++;
    }

    if(timeoutcount >= 10){
      timeoutcount = 0;
      doTimeStuff();
    }
    */


}
