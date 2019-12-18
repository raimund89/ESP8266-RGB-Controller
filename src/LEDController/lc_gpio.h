#ifndef LC_GPIO
#define LC_GPIO

#include "lc_colors.h"
#include "lc_programs.h"

// Pin definitions on an ESP8285 Magic Home type LED controller
#define PWM_GREEN 5
#define PWM_RED   12
#define PWM_BLUE  13
#define PWM_WHITE 15

void SetColor(Color c);
Color GetColor();

void InitGPIO()
{
  pinMode(PWM_GREEN, OUTPUT);
  pinMode(PWM_RED, OUTPUT);
  pinMode(PWM_BLUE, OUTPUT);
  pinMode(PWM_WHITE, OUTPUT);

  // Avoid any *4 or /4, just change the analog range
  analogWriteRange(255);

  // By default, turn on at half the power
  Program_CycleColors(0.1);
}

void SetColor(Color c) {
  analogWrite(PWM_RED, c.r);
  analogWrite(PWM_GREEN, c.g);
  analogWrite(PWM_BLUE, c.b);
  analogWrite(PWM_WHITE, c.w);
}

// In this case, the value of a long is used, where each byte is the color value.
// Using a long means 64-bit. This is too much (32-bit is sufficient), but could
// be used later for additional settings, or increasing the resolution to 10-bit.
void SetColorHex(unsigned long c) {
  analogWrite(PWM_RED, c >> 24);
  analogWrite(PWM_GREEN, (c & 0x00FF0000L) >> 16);
  analogWrite(PWM_BLUE, (c & 0x0000FF00L) >> 8);
  analogWrite(PWM_WHITE, (c & 0x000000FFL));
}

Color GetColor() {
  Color c;
  c.r = analogRead(PWM_RED);
  c.g = analogRead(PWM_GREEN);
  c.b = analogRead(PWM_BLUE);
  c.w = analogRead(PWM_WHITE);

  return c;
}

unsigned long GetColorHex() {
  unsigned long c = 0;
  c += analogRead(PWM_RED) << 24;
  c += analogRead(PWM_GREEN) << 16;
  c += analogRead(PWM_BLUE) << 8;
  c += analogRead(PWM_WHITE);

  return c;
}

#endif
