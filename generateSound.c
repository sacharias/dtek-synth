
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
//
// int* getWaveA(void) {
//   return waveA;
// }
//
// int* getWaveG(void) {
//   return waveG;
// }
//
// int* getWaveF(void) {
//   return waveF;
// }
//
// int* getWaveE(void) {
//   return waveE;
// }
//
// int* getWaveD(void) {
//   return waveD;
// }
