// Octave 4 arrays
int waveC4[157];
int waveD4[140];
int waveE4[125];
int waveF4[118];
int waveG4[105];
int waveA4[93];
int waveB4[83];

// octave 3 arrays
int waveC3[314];
int waveD3[280];
int waveE3[250];
int waveF3[236];
int waveG3[210];
int waveA3[186];
int waveB3[166];

// octave 2 arrays
int waveC2[79];
int waveD2[70];
int waveE2[63];
int waveF2[59];
int waveG2[53];
int waveA2[46];
int waveB2[41];

#define PI 3.14159265358979323846

// our own sinus function :)
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

// genereate a sin wave into the array 'wave'
void generateSin(int length, int* wave){
  int i = 0;
  double sum = 0.0;

  for (i = 0; i < length; i++)
  {
    wave[i] = 100 * sin(sum);
    sum = sum + (PI / (length-1)); // array.length - 1
  }
}

// Genereate a box wave into the array 'wave'
void generateBox(int length, int* wave){
  int i = 0;

  for (i = 0; i < length; i++)
  {
    if(i < length/2){
      wave[i] = 100;
    } else{
      wave[i] = -100;
    }
  }
}

// Genereate a triangle wave into the array 'wave'
void generateTriangle(int length, int* wave){
  int i = 0;
  double sum = 0;

  for (i = 0; i < length; i++)
  {
    sum += 300/length;
    wave[i] = sum;
  }
}


// Genereate sinwawes based on wavetype. 0 is sinus, 1 is box and 2 is triangle
void generateSinWaves(int waveType)
{
  // Make waveX arrays
  // sample rate: 41109

  if(waveType == 0){

      // Make A = 440 Hz
      generateSin(sizeof(waveA4)/sizeof(int), waveA4);

      // Make B = 493,88 Hz
      generateSin(sizeof(waveB4)/sizeof(int), waveB4);

      // Make G = 391,995 Hz
      generateSin(sizeof(waveG4)/sizeof(int), waveG4);

      // Make F = 349,228 Hz
      generateSin(sizeof(waveF4)/sizeof(int), waveF4);

      // Make E = 329,628 Hz
      generateSin(sizeof(waveE4)/sizeof(int), waveE4);

      // Make D = 293,665 Hz
      generateSin(sizeof(waveD4)/sizeof(int), waveD4);

      // Make C = 261,63 Hz
      generateSin(sizeof(waveC4)/sizeof(int), waveC4);


        // GENERATE A3 OSV

      // Make A = 440 Hz
      generateSin(sizeof(waveA3)/sizeof(int), waveA3);

      // Make B = 493,88 Hz
      generateSin(sizeof(waveB3)/sizeof(int), waveB3);

      // Make G = 391,995 Hz
      generateSin(sizeof(waveG3)/sizeof(int), waveG3);

      // Make F = 349,228 Hz
      generateSin(sizeof(waveF3)/sizeof(int), waveF3);

      // Make E = 329,628 Hz
      generateSin(sizeof(waveE3)/sizeof(int), waveE3);

      // Make D = 293,665 Hz
      generateSin(sizeof(waveD3)/sizeof(int), waveD3);

      // Make C = 261,63 Hz
      generateSin(sizeof(waveC3)/sizeof(int), waveC3);



      // GENERATE A2 OSV
      // Make A = 440 Hz
      generateSin(sizeof(waveA2)/sizeof(int), waveA2);

      // Make B = 493,88 Hz
      generateSin(sizeof(waveB2)/sizeof(int), waveB2);

      // Make G = 391,995 Hz
      generateSin(sizeof(waveG2)/sizeof(int), waveG2);

      // Make F = 349,228 Hz
      generateSin(sizeof(waveF2)/sizeof(int), waveF2);

      // Make E = 329,628 Hz
      generateSin(sizeof(waveE2)/sizeof(int), waveE2);

      // Make D = 293,665 Hz
      generateSin(sizeof(waveD2)/sizeof(int), waveD2);

      // Make C = 261,63 Hz
      generateSin(sizeof(waveC2)/sizeof(int), waveC2);

  } else if(waveType == 1){

    // GENERATE A4 OSV
      // Make A = 440 Hz
      generateBox(sizeof(waveA4)/sizeof(int), waveA4);

      // Make B = 493,88 H
      generateBox(sizeof(waveB4)/sizeof(int), waveB4);

      // Make G = 391,995 Hz
      generateBox(sizeof(waveG4)/sizeof(int), waveG4);

      // Make F = 349,228 Hz
      generateBox(sizeof(waveF4)/sizeof(int), waveF4);

      // Make E = 329,628 Hz
      generateBox(sizeof(waveE4)/sizeof(int), waveE4);

      // Make D = 293,665 Hz
      generateBox(sizeof(waveD4)/sizeof(int), waveD4);

      // Make C = 261,63 Hz
      generateBox(sizeof(waveC4)/sizeof(int), waveC4);


      // GENERATE A3 OSV
        // Make A = 440 Hz
        generateBox(sizeof(waveA3)/sizeof(int), waveA3);

        // Make B = 493,88 Hz
        generateBox(sizeof(waveB3)/sizeof(int),waveB3);

        // Make G = 391,995 Hz
        generateBox(sizeof(waveG3)/sizeof(int), waveG3);

        // Make F = 349,228 Hz
        generateBox(sizeof(waveF3)/sizeof(int), waveF3);

        // Make E = 329,628 Hz
        generateBox(sizeof(waveE3)/sizeof(int), waveE3);

        // Make D = 293,665 Hz
        generateBox(sizeof(waveD3)/sizeof(int), waveD3);

        // Make C = 261,63 Hz
        generateBox(sizeof(waveC3)/sizeof(int), waveC3);


        // GENERATE A2 OSV
          // Make A = 440 Hz
          generateBox(sizeof(waveA2)/sizeof(int), waveA2);

          // Make B = 493,88 Hz
          generateBox(sizeof(waveB2)/sizeof(int), waveB2);

          // Make G = 391,995 Hz
          generateBox(sizeof(waveG2)/sizeof(int), waveG2);

          // Make F = 349,228 Hz
          generateBox(sizeof(waveF2)/sizeof(int),waveF2);

          // Make E = 329,628 Hz
          generateBox(sizeof(waveE2)/sizeof(int), waveE2);

          // Make D = 293,665 Hz
          generateBox(sizeof(waveD2)/sizeof(int), waveD2);

          // Make C = 261,63 Hz
          generateBox(sizeof(waveC2)/sizeof(int), waveC2);


  } else{
      // Make A = 440 Hz
      generateTriangle(sizeof(waveA4)/sizeof(int), waveA4);

      // Make B = 493,88 Hz
      generateTriangle(sizeof(waveB4)/sizeof(int), waveB4);

      // Make G = 391,995 Hz
      generateTriangle(sizeof(waveG4)/sizeof(int), waveG4);

      // Make F = 349,228 Hz
      generateTriangle(sizeof(waveF4)/sizeof(int), waveF4);

      // Make E = 329,628 Hz
      generateTriangle(sizeof(waveE4)/sizeof(int), waveE4);

      // Make D = 293,665 Hz
      generateTriangle(sizeof(waveD4)/sizeof(int), waveD4);

      // Make C = 261,63 Hz
      generateTriangle(sizeof(waveC4)/sizeof(int), waveC4);

      // GENEREATE A3 OSV!

      // Make A = 440 Hz
      generateTriangle(sizeof(waveA3)/sizeof(int), waveA3);

      // Make B = 493,88 Hz
      generateTriangle(sizeof(waveB3)/sizeof(int), waveB3);

      // Make G = 391,995 Hz
      generateTriangle(sizeof(waveG3)/sizeof(int), waveG3);

      // Make F = 349,228 Hz
      generateTriangle(sizeof(waveF3)/sizeof(int), waveF3);

      // Make E = 329,628 Hz
      generateTriangle(sizeof(waveE3)/sizeof(int), waveE3);

      // Make D = 293,665 Hz
      generateTriangle(sizeof(waveD3)/sizeof(int), waveD3);

      // Make C = 261,63 Hz
      generateTriangle(sizeof(waveC3)/sizeof(int), waveC3);

      // GENEREATE A2 OSV!

      // Make A = 440 Hz
      generateTriangle(sizeof(waveA2)/sizeof(int), waveA2);

      // Make B = 493,88 Hz
      generateTriangle(sizeof(waveB2)/sizeof(int), waveB2);

      // Make G = 391,995 Hz
      generateTriangle(sizeof(waveG2)/sizeof(int), waveG2);

      // Make F = 349,228 Hz
      generateTriangle(sizeof(waveF2)/sizeof(int), waveF2);

      // Make E = 329,628 Hz
      generateTriangle(sizeof(waveE2)/sizeof(int), waveE2);

      // Make D = 293,665 Hz
      generateTriangle(sizeof(waveD2)/sizeof(int), waveD2);

      // Make C = 261,63 Hz
      generateTriangle(sizeof(waveC2)/sizeof(int), waveC2);
  }
}


// get value based on sample and what kind of octave(wave) (2, 3 or 4)
int getAValue(int sample, int wave) {
  if(wave == 4){
    int index = sample % (sizeof(waveA4)/sizeof(int));
    return waveA4[index];
  } else if(wave == 3){
    int index = sample % (sizeof(waveA3)/sizeof(int));
    return waveA3[index];
  } else{
    int index = sample % (sizeof(waveA2)/sizeof(int));
    return waveA2[index];
  }
}

// get value based on sample and what kind of octave(wave) (2, 3 or 4)
int getGValue(int sample, int wave) {
  if(wave == 4){
    int index = sample % (sizeof(waveG4)/sizeof(int));
    return waveG4[index];
  } else if(wave == 3){
    int index = sample % (sizeof(waveG3)/sizeof(int));
    return waveG3[index];
  } else{
    int index = sample % (sizeof(waveG2)/sizeof(int));
    return waveG2[index];
  }
}

// get value based on sample and what kind of octave(wave) (2, 3 or 4)
int getFValue(int sample, int wave) {
  if(wave == 4){
    int index = sample % (sizeof(waveF4)/sizeof(int));
    return waveF4[index];
  } else if(wave == 3){
    int index = sample % (sizeof(waveF3)/sizeof(int));
    return waveF3[index];
  } else{
    int index = sample % (sizeof(waveF2)/sizeof(int));
    return waveF2[index];
  }
}

// get value based on sample and what kind of octave(wave) (2, 3 or 4)
int getEValue(int sample, int wave) {
  if(wave == 4){
    int index = sample % (sizeof(waveE4)/sizeof(int));

    return waveE4[index];
  } else if(wave == 3){
    int index = sample % (sizeof(waveE3)/sizeof(int));
    return waveE3[index];
  } else{
    int index = sample % (sizeof(waveE2)/sizeof(int));
    return waveE2[index];
  }
}

// get value based on sample and what kind of octave(wave) (2, 3 or 4)
int getDValue(int sample, int wave) {
  if(wave == 4){
    int index = sample % (sizeof(waveD4)/sizeof(int));
    return waveD4[index];
  } else if(wave == 3){
    int index = sample % (sizeof(waveD3)/sizeof(int));
    return waveD3[index];
  } else{
    int index = sample % (sizeof(waveD2)/sizeof(int));
    return waveD2[index];
  }
}

// get value based on sample and what kind of octave(wave) (2, 3 or 4)
int getCValue(int sample, int wave) {
  if(wave == 4){
    int index = sample % (sizeof(waveC4)/sizeof(int));
    return waveC4[index];
  } else if(wave == 3){
    int index = sample % (sizeof(waveC3)/sizeof(int));
    return waveC3[index];
  } else{
    int index = sample % (sizeof(waveC2)/sizeof(int));
    return waveC2[index];
  }

}

// get value based on sample and what kind of octave(wave) (2, 3 or 4)
int getBValue(int sample, int wave) {
  if(wave == 4){
    int index = sample % (sizeof(waveB4)/sizeof(int));
    return waveB4[index];
  } else if(wave == 3){
    int index = sample % (sizeof(waveB3)/sizeof(int));
    return waveB3[index];
  } else{
    int index = sample % (sizeof(waveB2)/sizeof(int));
    return waveB2[index];
  }
}
