#pragma once
#include <Arduino.h>

// ================== KONFIGURASI PIN (ESP32) ==================
const int LDR_PIN     = 34;  // ADC1_CH6, input-only
const int RELAY_PIN   = 26;  // RTC GPIO -> bisa di-hold saat deep sleep
const int BTN_LEFT    = 27;
const int BTN_SELECT  = 14;  // RTC GPIO -> juga dipakai membangunkan dari deep sleep
const int BTN_RIGHT   = 13;
const int POT_PIN     = 32;

// BATTERY PINS
const int BAT_VOLT    = 33;
const int SOLAR_VOLT  = 25;
// BATTERY AMPERE USES SDA N SCL

const int SDA_PIN     = 21;  // RX2 -> SDA (LCD + DS3231)
const int SCL_PIN     = 22;  // TX2 -> SCL (LCD + DS3231)

const bool RELAY_ACTIVE_LOW = true; // ubah false jika modul relay Active HIGH

// ================== JADWAL DEEP SLEEP (dari kode 2) ==================
// Dua range waktu (menit sejak tengah malam)
const int PAGI_START  = 5 * 60;    // 05:00
const int PAGI_END    = 7 * 60;    // 07:00
const int SORE_START  = 17 * 60;   // 17:00
const int SORE_END    = 21 * 60;   // 19:00

// Interval cek LDR (detik). Nilai di bawah adalah nilai uji coba.
// Untuk pemakaian sebenarnya: INTERVAL_NORMAL = 60*60, INTERVAL_RANGE = 10*60
const uint32_t INTERVAL_NORMAL = 60 * 60;  // di luar range
const uint32_t INTERVAL_RANGE  = 10 * 60;  // di dalam range

const int TOTAL_MENU = 3;

const unsigned long SCREEN_TIMEOUT = 15000; // tanpa aktivitas selama ini -> deep sleep (1s = 1000)

const unsigned long PotSetMenuChangeTimer = 5000; // ms

// ===== KONFIGURASI TEGANGAN =====
const float DIV_BAT   = 5.42;    // kalibrasi dengan multimeter
const float DIV_SOLAR = 5.42;    // kalibrasi terpisah