#include "sensors.h"
#include "config.h"
#include "state.h"

float rataMV(int pin, int n) {
  long total = 0;
  for (int i = 0; i < n; i++) total += analogReadMilliVolts(pin);
  return total / (float)n;
}

void handleBattery() {
  float vb = rataMV(BAT_VOLT, 64)   / 1000.0 * DIV_BAT;
  float vs = rataMV(SOLAR_VOLT, 64) / 1000.0 * DIV_SOLAR;
  if (vb < 0.5) vb = 0;
  if (vs < 0.5) vs = 0;

  if (!voltInit) { batVolt = vb; solVolt = vs; voltInit = true; }
  else {
    batVolt += 0.2 * (vb - batVolt);   // haluskan supaya tidak naik-turun
    solVolt += 0.2 * (vs - solVolt);
  }
}