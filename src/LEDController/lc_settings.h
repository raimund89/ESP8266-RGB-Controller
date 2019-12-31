#ifndef LC_SETTINGS
#define LC_SETTINGS

#include "lc_colors.h"

struct {
  int port;
  int pin_r;
  int pin_g;
  int pin_b;
  int pin_w;
  int pin_ir;
  Color currentColor;
} settings;

void LoadSettings() {
  
}

#endif
