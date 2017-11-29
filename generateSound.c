int waveA[93];
int waveG[105];
int waveF[118];
int waveE[125];
int waveD[140];

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


int getAValue(int sample) {
  int index = sample % 93;
  return waveA[index];
}

int getGValue(int sample) {
  int index = sample % 105;
  return waveG[index];
}

int getFValue(int sample) {
  int index = sample % 118;
  return waveF[index];
}

int getEValue(int sample) {
  int index = sample % 125;
  return waveE[index];
}

int getDValue(int sample) {
  int index = sample % 140;
  return waveD[index];
}
