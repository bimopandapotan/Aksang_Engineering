#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include <config.h>
#include <state.h>
#include <sensors.h>
#include <relay.h>
#include <schedule.h>
#include <input.h>
#include <ui.h>
#include <power.h>

const char box = '|';

// ================== SETUP ==================
void setup() {
  Serial.begin(9600);
  analogReadResolution(10);

  pinMode(RELAY_PIN, OUTPUT);
  relayState = false;
  digitalWrite(RELAY_PIN, relayLevel(false));   // power on: relay OFF

  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);

  Wire.begin(SDA_PIN, SCL_PIN);

  rtcOk = rtc.begin();
  if (!rtcOk) {
    Serial.println("RTC tidak terdeteksi");
  } else if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  nextCheckUnix = 0;

  uiActive = true;
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistem Lampu");
  lcd.setCursor(0, 1);
  lcd.print("Otomatis Siap");
  delay(1500);
  lcd.clear();

  initBars();
  lastButtonTime = millis();
}


void loop() {
  handleButtons();
  handlePotMenu();
  handleBattery();
  checkScreenTimeout();
  controlRelay();

  if (!isSleeping) {
    displayMenu();
  }

  delay(100);
}