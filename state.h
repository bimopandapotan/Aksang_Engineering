#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

extern LiquidCrystal_I2C lcd;
extern RTC_DS3231 rtc;
extern bool rtcOk;
extern bool uiActive;

enum Mode { AUTO, MANUAL_ON, MANUAL_OFF };
extern Mode lastDisplayedMode;
extern Mode currentMode;
extern bool relayState;
extern uint32_t nextCheckUnix;

extern int currentMenu;

extern int intensity;
extern int settings;

extern bool isSleeping;

extern String intensityProgress;
extern String settingsLevel;

extern int lastIntensity, lastSettings;
extern int lastDisplayedMenu;
extern int lastDisplayedSettings;
extern int lastDisplayedIntensity;

extern unsigned long lastButtonTime;
extern bool pressed;

extern bool potMenuActive;
extern int lastMenu;
extern unsigned long lastPotChange;

extern float batVolt, solVolt;
extern bool voltInit;