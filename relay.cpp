#include "relay.h"
#include "config.h"
#include "state.h"

int relayLevel(bool on) {
  return on ? (RELAY_ACTIVE_LOW ? LOW : HIGH)
            : (RELAY_ACTIVE_LOW ? HIGH : LOW);
}

// ================== LOGIKA RELAY (tanpa LCD, aman dipanggil saat bangun dari timer) ==================
void controlRelay() {
  int ldrValue = analogRead(LDR_PIN);   // 0 - 1023
  int potValue = analogRead(POT_PIN);   // 0 - 1023
  // Serial.println(potValue);

  switch (currentMode) {
    case AUTO:
      if (!relayState && intensity < settings) {
        relayState = true;       // gelap -> nyala
      } else if (relayState && intensity > settings) {
        relayState = false;  // nyala -> gelap (hysteresis)
      }
      break;
    case MANUAL_ON:
      relayState = true;
      break;
    case MANUAL_OFF:
      relayState = false;
      break;
  }

  digitalWrite(RELAY_PIN, relayLevel(relayState));
}

