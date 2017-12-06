int waveC4[157];
int waveD4[140];
int waveE4[125];
int waveF4[118];
int waveG4[105];
int waveA4[93];
int waveB4[83];

#define PI 3.14159265358979323846

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
    waveA4[i] = 127 * sin(sum);
    sum = sum + (PI / 92); // array.length - 1
  }

  // Make B = 493,88 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 83; i++) {
    waveB4[i] = 127 * sin(sum);
    sum = sum + (PI / 82);
  }

  // Make G = 391,995 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 105; i++)
  {
    waveG4[i] = 127 * sin(sum);
    sum = sum + (PI / 104);
  }

  // Make F = 349,228 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 118; i++)
  {
    waveF4[i] = 127 * sin(sum);
    sum = sum + (PI / 117);
  }

  // Make E = 329,628 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 125; i++)
  {
    waveE4[i] = 127 * sin(sum);
    sum = sum + (PI / 124);
  }

  // Make D = 293,665 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 140; i++)
  {
    waveD4[i] = 127 * sin(sum);
    sum = sum + (PI / 139);
  }

  // Make C = 261,63 Hz
  i = 0;
  sum = 0.0;
  for (i = 0; i < 157; i++) {
    waveC4[i] = 127 * sin(sum);
    sum = sum + (PI / 156);
  }

}

int getAValue(int sample) {
  int index = sample % 93;
  return waveA4[index];
}

int getGValue(int sample) {
  int index = sample % 105;
  return waveG4[index];
}

int getFValue(int sample) {
  int index = sample % 118;
  return waveF4[index];
}

int getEValue(int sample) {
  int index = sample % 125;
  return waveE4[index];
}

int getDValue(int sample) {
  int index = sample % 140;
  return waveD4[index];
}

int getCValue(int sample) {
  int index = sample % 157;
  return waveC4[index];
}

int getBValue(int sample) {
  int index = sample % 83;
  return waveB4[index];
}
