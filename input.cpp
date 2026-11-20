#include "input.h"
#include "config.h"
#include "state.h"
#include "ui.h"

void handleButtons() {
  if (pressed) {
    if (digitalRead(BTN_LEFT) == HIGH &&
        digitalRead(BTN_RIGHT) == HIGH &&
        digitalRead(BTN_SELECT) == HIGH) {
      pressed = false;
    }
    return;
  }

  bool left   = digitalRead(BTN_LEFT) == LOW;
  bool right  = digitalRead(BTN_RIGHT) == LOW;
  bool select = digitalRead(BTN_SELECT) == LOW;

  // Tidak ada tombol yang ditekan
  if (!left && !right && !select) return;

  // Jika LCD mati, tombol hanya untuk membangunkan
  if (isSleeping) {
    wakeScreen();

    // Tunggu tombol dilepas agar tidak dianggap sebagai
    // aksi tombol pada pemanggilan loop berikutnya
    pressed = true;

    return;
  }

  // Mulai dari sini, tombol menjalankan aksi normal
  lastButtonTime = millis();
  pressed = true;

  if (left) {
    potMenuActive = false;

    currentMenu--;
    if (currentMenu < 0) {
      currentMenu = TOTAL_MENU - 1;
    }

    lcd.clear();
    lastDisplayedMenu = -1;
  }

  if (right) {
    potMenuActive = false;

    currentMenu++;
    if (currentMenu >= TOTAL_MENU) {
      currentMenu = 0;
    }

    lcd.clear();
    lastDisplayedMenu = -1;
  }

  if (select && currentMenu == 0) {
    currentMode = (Mode)((currentMode + 1) % 3);
  }
}

void handlePotMenu() {
  int ldrValue = analogRead(LDR_PIN);
  intensity = -map(ldrValue, 723, 1023, -9, 0);

  if (lastIntensity != intensity) {
    lastIntensity = intensity;
    intensityProgress = makeProgressBar(intensity);
  }

  int potValue = analogRead(POT_PIN);
  settings = -map(potValue, 523, 1023, -9, 0);

  int delta = settings - lastSettings;

  if (lastSettings != settings) {
  int delta = settings - lastSettings;

  lastSettings = settings;
  settingsLevel = makeProgressBar(settings);

  if (abs(delta) >= 1) {
    if (isSleeping) {
      wakeScreen();
      currentMenu = 1;
      potMenuActive = false;
    } else {
      if (!potMenuActive) {
        lastMenu = currentMenu;
        potMenuActive = true;
      }

      if (currentMenu != 1) {
        currentMenu = 1;
        lcd.clear();
        lastDisplayedMenu = -1;
      }

      lastButtonTime = millis();
    }

    lastPotChange = millis();
  }
}

  // Kembali ke menu sebelumnya setelah 5 detik
  if (potMenuActive &&
      millis() - lastPotChange >= PotSetMenuChangeTimer) {
    potMenuActive = false;
    currentMenu = lastMenu;
    lcd.clear();
  }
}