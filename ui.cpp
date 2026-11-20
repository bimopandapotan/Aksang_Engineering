#include "ui.h"
#include "config.h"
#include "state.h"

const char* modeText[] = { "AUTO", "MANUAL ON", "MANUAL OFF" };

String makeProgressBar(int boxes) {
  boxes = constrain(boxes, 0, 9);

  String text = "";

  for (int i = 0; i < boxes; i++) {
    text += '|';
  }

  while (text.length() < 9) {
    text += ' ';
  }

  return text;
}

// Hitung bar LDR & SET sekali di awal (tanpa memicu pindah menu)
void initBars() {
  int ldrValue = analogRead(LDR_PIN);
  intensity = -map(ldrValue, 823, 1024, -9, 0);
  lastIntensity = intensity;
  intensityProgress = makeProgressBar(intensity);

  int potValue = analogRead(POT_PIN);
  settings = -map(potValue/2, 256, 512, -9, 0);
  lastSettings = settings;
  settingsLevel = makeProgressBar(settings);

}

void wakeScreen() {
  isSleeping = false;
  lastButtonTime = millis();

  lcd.display();
  lcd.backlight();
  lcd.clear();

  // Paksa displayMenu() menggambar ulang teks
  lastDisplayedMenu = -1;
  lastDisplayedSettings = -1;
  lastDisplayedIntensity = -1;
  lastDisplayedMode = (Mode)-1;
}

// ================== TAMPILAN LCD ==================

void displayMenu() {
  bool menuChanged = currentMenu != lastDisplayedMenu;

  switch (currentMenu) {
    case 0:
      if (menuChanged || currentMode != lastDisplayedMode) {
        lcd.setCursor(0, 0);
        lcd.print("Mode Lampu:     ");

        lcd.setCursor(0, 1);
        lcd.print(modeText[currentMode]);
        lcd.print("          ");

        lastDisplayedMode = currentMode;
      }
      break;

    case 1:
      if (menuChanged ||
          settings != lastDisplayedSettings ||
          intensity != lastDisplayedIntensity) {

        lcd.setCursor(0, 0);
        lcd.print("SET: ");
        lcd.print(settingsLevel);

        lcd.setCursor(0, 1);
        lcd.print("LDR: ");
        lcd.print(intensityProgress);

        lastDisplayedSettings = settings;
        lastDisplayedIntensity = intensity;
      }
      break;

    case 2:
      // Biarkan tampilan tegangan menggunakan
      // mekanisme pembaruan yang sudah ada.
      lcd.setCursor(0, 0);
      lcd.print("VBAT: ");
      lcd.print(batVolt, 2);
      lcd.print("V    ");

      lcd.setCursor(0, 1);
      lcd.print("VSOL: ");
      lcd.print(solVolt, 2);
      lcd.print("V    ");
      break;
  }

  lastDisplayedMenu = currentMenu;
}