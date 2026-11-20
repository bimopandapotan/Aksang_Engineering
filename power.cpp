#include "power.h"
#include "config.h"
#include "state.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"

const int WAKE_PINS[] = { BTN_LEFT, BTN_SELECT, BTN_RIGHT };

void goToSleep() {
  // // Pastikan tombol dilepas sebelum mengaktifkan wake-up
  // while (digitalRead(BTN_LEFT) == LOW ||
  //        digitalRead(BTN_SELECT) == LOW ||
  //        digitalRead(BTN_RIGHT) == LOW) {
  //   delay(10);
  // }

  // // Matikan LCD sebelum tidur
  // lcd.noBacklight();
  // lcd.noDisplay();

  // bool wokeByButton = false;

  // do {
  //   // Tentukan waktu tidur berdasarkan jadwal RTC
  //   uint32_t sleepSec = INTERVAL_NORMAL;

  //   if (rtcOk) {
  //     DateTime now = rtc.now();
  //     uint32_t nowUnix = now.unixtime();

  //     if (nextCheckUnix <= nowUnix) {
  //       nextCheckUnix = hitungNextCheck(now);
  //     }

  //     sleepSec = nextCheckUnix - nowUnix;
  //   }

  //   if (sleepSec < 1) {
  //     sleepSec = 1;
  //   }

  //   // Pertahankan kondisi relay selama light sleep
  //   digitalWrite(RELAY_PIN, relayLevel(relayState));
  //   gpio_hold_en((gpio_num_t)RELAY_PIN);

  //   // Tombol aktif LOW sebagai sumber wake-up
  //   for (int p : WAKE_PINS) {
  //     gpio_wakeup_enable((gpio_num_t)p, GPIO_INTR_LOW_LEVEL);
  //   }

  //   esp_sleep_enable_gpio_wakeup();
  //   esp_sleep_enable_timer_wakeup(
  //     (uint64_t)sleepSec * 1000000ULL
  //   );

  //   isSleeping = true;

  //   // ESP32 benar-benar masuk light sleep di sini
  //   esp_light_sleep_start();

  //   // Kode berlanjut setelah ESP32 bangun
  //   gpio_hold_dis((gpio_num_t)RELAY_PIN);

  //   for (int p : WAKE_PINS) {
  //     gpio_wakeup_disable((gpio_num_t)p);
  //   }

  //   esp_sleep_wakeup_cause_t cause =
  //     esp_sleep_get_wakeup_cause();

  //   if (cause == ESP_SLEEP_WAKEUP_TIMER) {
  //     // Bangun untuk mengecek kondisi LDR dan relay
  //     delay(50);
  //     controlRelay();
  //     nextCheckUnix = 0;
  //   } else {
  //     // Bangun karena tombol
  //     wokeByButton = true;
  //   }

  // } while (!wokeByButton);

  // // Nyalakan kembali antarmuka setelah tombol membangunkan ESP32
  // isSleeping = false;
  // uiActive = true;
  // pressed = true;
  // potMenuActive = false;

  // lcd.display();
  // lcd.backlight();
  // lcd.clear();

  // initBars();
  // lastButtonTime = millis();

  lcd.noBacklight();
  lcd.noDisplay();

  isSleeping = true;
}

// Tanpa aktivitas -> deep sleep (menggantikan layar mati)
void checkScreenTimeout() {
  // if (millis() - lastButtonTime >= SCREEN_TIMEOUT) {
  //   goToSleep();
  // }

  if (!isSleeping &&
      millis() - lastButtonTime >= SCREEN_TIMEOUT) {
        goToSleep();
  }
}