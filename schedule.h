#pragma once
#include <Arduino.h>
#include <RTClib.h>

bool dalamRange(int menit);
uint32_t detikKeRangeBerikutnya(DateTime now);
uint32_t hitungNextCheck(DateTime now);