#include "state.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;
bool rtcOk = false;
bool uiActive = false;       // true jika LCD sedang dipakai (bangun karena tombol / power on)

Mode lastDisplayedMode = (Mode)-1;
RTC_DATA_ATTR Mode currentMode = AUTO;
RTC_DATA_ATTR bool relayState  = false;
RTC_DATA_ATTR uint32_t nextCheckUnix = 0;   // jadwal cek LDR berikutnya (waktu RTC)

int currentMenu = 0;       // 0 = Mode, 1 = Sensor LDR, 2 = Status Relay

// ================== VARIABEL LAINNYA ==================
int intensity;
int settings;

bool isSleeping = false;

String intensityProgress;
String settingsLevel;

int lastIntensity = -1, lastSettings = -1;
int lastDisplayedMenu = -1;
int lastDisplayedSettings = -1;
int lastDisplayedIntensity = -1;


unsigned long lastButtonTime = 0;
bool pressed = false;

// const unsigned long SCREEN_TIMEOUT = 15000; // tanpa aktivitas selama ini -> deep sleep (1s = 1000)

// Menu otomatis pindah ke SET saat potensiometer diputar, lalu kembali
bool potMenuActive = false;
int lastMenu = 0;
unsigned long lastPotChange = 0;


float batVolt = 0, solVolt = 0;
bool voltInit = false;