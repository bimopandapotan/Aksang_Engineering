#include "schedule.h"
#include "config.h"

// ================== FUNGSI JADWAL ==================
bool dalamRange(int menit) {
  return (menit >= PAGI_START && menit < PAGI_END) ||
         (menit >= SORE_START && menit < SORE_END);
}

// Detik dari 'now' sampai awal range berikutnya (pagi/sore)
uint32_t detikKeRangeBerikutnya(DateTime now) {
  int startList[2] = { PAGI_START, SORE_START };
  uint32_t nowUnix = now.unixtime();
  uint32_t terdekat = 0xFFFFFFFF;

  for (int i = 0; i < 2; i++) {
    DateTime s(now.year(), now.month(), now.day(),
               startList[i] / 60, startList[i] % 60, 0);
    uint32_t su = s.unixtime();
    if (su <= nowUnix) su += 24UL * 3600;   // pakai besok
    if (su < terdekat) terdekat = su;
  }
  return terdekat - nowUnix;
}

// Waktu (unix) pengecekan LDR berikutnya
uint32_t hitungNextCheck(DateTime now) {
  uint32_t nowUnix = now.unixtime();
  int menit = now.hour() * 60 + now.minute();
  bool inRange = dalamRange(menit);
  uint32_t interval = inRange ? INTERVAL_RANGE : INTERVAL_NORMAL;
  uint32_t next = nowUnix + interval;

  // Di luar range: jangan sampai melewati awal range berikutnya
  if (!inRange) {
    uint32_t keRange = detikKeRangeBerikutnya(now);
    if (keRange < interval) next = nowUnix + keRange;
  }
  return next;
}