#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include "generateSound.h"


//the opcodes for the MAX7221 and MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

double count = 0.0;
int debug_value = 0;
int sample = 0;
int sampleMax = 411090;

//int duration = 41109;


void setCs(int high){
  if(high){
    // Sätt cs till HIGH
    PORTESET = 0x0004;
  } else {
    // Sätt cs till LOW
    PORTECLR = 0x0004;
  }
}

void setData(int high){
  if(high){
    // Sätt data till HIGH
    PORTESET = 0x0002;
  } else {
    // Sätt DATA till LOW
    PORTECLR = 0x0002;
  }
}

void setClk(int high){
  if(high){
    // Sätt clk till HIGH
    PORTESET = 0x0001;
  } else {
    // Sätt clk till LOW
    PORTECLR = 0x0001;
  }
}

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
  // if (playButtonsValue & 0x40) {
  //     value += getCValue(sample);
  //     n++;
  // }
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

void spiTransfer(char data[]) {
    //Create an array with the data to shift out
    // [0, 0, 0, 0, 1, 1, 1, 1]
    setCs(0);

    int i;
    for (i = 0; i < 16; i++){
      setClk(0);
      setData(data[i]);
      quicksleep(80);
      setClk(1);
      quicksleep(80);
    }

    setCs(1);
    setClk(0);
    quicksleep(80);


}

void shutdownLamps(int address, int down){
  if(down){
    //spiTransfer(address, OP_SHUTDOWN,(char)0);
  }
}

void deployMatrice(char *matrice){
  int x = 16;
  int y = 8;

  // first row second led
  char digit0[] = {0,0,0,0, 0,0,0,1, 0,0,0,0 ,0,0,0,0 };
  int i = 0;
  for(i =0; i < y; i++){
    digit0[8 + i] = matrice[i + 8];
  }
  spiTransfer(digit0);

  // first row first led
  for(i =0; i < y; i++){
    digit0[8 + i] = matrice[i];
  }
  spiTransfer(digit0);

  // second row second led
  char digit1[] = {0,0,0,0, 0,0,1,0, 0,0,0,0 ,0,0,0,0 };
  for(i =0; i < y; i++){
    digit1[8 + i] = matrice[16 + i + 8];
  }
  spiTransfer(digit1);

  // second row first led
  for(i =0; i < y; i++){
    digit1[8 + i] = matrice[16 + i];
  }
  spiTransfer(digit1);

  // third row second led
  char digit2[] = {0,0,0,0, 0,0,1,1, 0,0,0,0 ,0,0,0,0 };
  for(i =0; i < y; i++){
    digit2[8 + i] = matrice[32 + i + 8];
  }
  spiTransfer(digit2);

  // third row first led
  for(i =0; i < y; i++){
    digit2[8 + i] = matrice[32 + i];
  }
  spiTransfer(digit2);

  // fourth row second led
  char digit3[] = {0,0,0,0, 0,1,0,0, 0,0,0,0 ,1,0,0,0 };
  for(i =0; i < y; i++){
    digit3[8 + i] = matrice[48 + i + 8];
  }
  spiTransfer(digit3);

  // fourth row first led
  for(i =0; i < y; i++){
    digit3[8 + i] = matrice[48 + i];
  }
  spiTransfer(digit3);

  // fifth row second led
  char digit4[] = {0,0,0,0, 0,1,0,1, 0,0,0,0 ,0,0,0,0 };
  for(i =0; i < y; i++){
    digit4[8 + i] = matrice[64 + i + 8];
  }
  spiTransfer(digit4);

  // fifth row first led
  for(i =0; i < y; i++){
    digit4[8 + i] = matrice[64 + i];
  }
  spiTransfer(digit4);

  // 6 row second led
  char digit5[] = {0,0,0,0, 0,1,1,0, 0,0,1,0 ,0,0,0,0 };
  for(i =0; i < y; i++){
    digit5[8 + i] = matrice[80 + i + 8];
  }
  spiTransfer(digit5);

  // 6 row first led
  for(i =0; i < y; i++){
    digit5[8 + i] = matrice[80 + i];
  }
  spiTransfer(digit5);

  // 7 row second led
  char digit6[] = {0,0,0,0, 0,1,1,1, 0,0,0,0 ,0,0,0,0 };
  for(i =0; i < y; i++){
    digit6[8 + i] = matrice[96 + i + 8];
  }
  spiTransfer(digit6);

  // 7 row first led
  for(i =0; i < y; i++){
    digit6[8 + i] = matrice[96 + i];
  }
  spiTransfer(digit6);

  // 8 row second led
  char digit7[] = {0,0,0,0, 1,0,0,0, 1,0,0,0 ,0,0,0,0 };
  for(i =0; i < y; i++){
    digit7[8 + i] = matrice[112 + i + 8];
  }
  spiTransfer(digit7);

  // 7 row first led
  for(i =0; i < y; i++){
    digit7[8 + i] = matrice[112 + i];
  }
  spiTransfer(digit7);

}


void test(){
  char twoDim[8][16];

  int y = 8;
  int x = 16;
  int i = 0;
  for(i = 0; i < y; y++){
    int j = 0;
    for(j = 0; j < x; j++){
      twoDim[i][j] = 0;
    }
  }

  deployMatrice(twoDim);

  // 0000 0000 0000 0000
  // 0000 0000 0000 0000
  // 0000 0000 0000 0000
  // 0000 0000 0000 0000
  // 0000 0000 0000 0000
  // 0000 0000 0000 0000
  // 0000 0000 0000 0000
  // 0000 0000 0000 0000

}


void initLamps(){
  // Sätt upp output på ledlamporna
  TRISECLR = 0x0001;
  TRISECLR = 0x0002;
  TRISECLR = 0x0004;
  //int dataarray = {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1};
//  spiTransfer(dataarray);
  char normalOperation[] = {0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1};
  spiTransfer(normalOperation);

  char scanlimit[] = {0,0,0,0, 1,0,1,1, 0,0,0,0 ,0,1,1,1};
  spiTransfer(scanlimit);

  char intensity[] = {0,0,0,0, 1,0,1,0, 0,0,0,0 ,0,0,0,1};
  spiTransfer(intensity);

  test();
  // char digit0[] = {0,0,0,0, 0,0,0,1, 0,0,0,0 ,0,0,0,1 };
  // spiTransfer(digit0);
  //
  // char digit1[] = {0,0,0,0, 0,0,1,0, 0,0,0,0 ,0,0,1,0 };
  // spiTransfer(digit1);
  //
  // char digit2[] = {0,0,0,0, 0,0,1,1, 0,0,0,0 ,0,1,0,0 };
  // spiTransfer(digit2);
  //
  // char digit3[] = {0,0,0,0, 0,1,0,0, 0,0,0,0 ,1,0,0,0 };
  // spiTransfer(digit3);
  //
  // char digit4[] = {0,0,0,0, 0,1,0,1, 0,0,0,1 ,0,0,0,0 };
  // spiTransfer(digit4);
  //
  // char digit5[] = {0,0,0,0, 0,1,1,0, 0,0,1,0 ,0,0,0,0 };
  // spiTransfer(digit5);
  //
  // char digit6[] = {0,0,0,0, 0,1,1,1, 0,1,0,0 ,0,0,0,0 };
  // spiTransfer(digit6);
  //
  // char digit7[] = {0,0,0,0, 1,0,0,0, 1,0,0,0 ,0,0,0,0 };
  // spiTransfer(digit7);
  // spiTransfer(digit7);
}






// volatile int *triseAdress = 0xbf886100; //

/* Lab-specific initialization goes here */
void labinit()
{
  // *triseAdress &= ~0xFF;
  // TRISD |= 0xFE0; // toggle switches

  initLamps();
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


}
