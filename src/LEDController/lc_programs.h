#ifndef LC_PROGRAMS
#define LC_PROGRAMS

#include "lc_colors.h"
#include "lc_gpio.h"

#include <Ticker.h>

Ticker program_ticker;

void Tick_CycleColors() {
  switch(GetColorHex()){
    case 0xFF000000L:
      SetColor(COLOR_GREEN);
      break;
    case 0x00FF0000L:
      SetColor(COLOR_BLUE);
      break;
    case 0x0000FF00L:
      SetColor(COLOR_RED);
      break;
    default:
      // This will be called the first time, when the
      // LEDs are still off after GPIO initialization
      SetColor(COLOR_RED);
      break;
  }
}

void Program_CycleColors(float speed) {
  program_ticker.attach(speed, Tick_CycleColors);
}

void Program_Clear() {
  program_ticker.detach();
}

#endif
