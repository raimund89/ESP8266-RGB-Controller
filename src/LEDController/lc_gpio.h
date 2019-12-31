#ifndef LC_GPIO
#define LC_GPIO

#include "lc_colors.h"
#include "lc_programs.h"

// Pin definitions on an ESP8285 Magic Home type LED controller
#define PWM_GREEN 5
#define PWM_RED   12
#define PWM_BLUE  13
#define PWM_WHITE 15

Color currentColor;

void SetColor(Color c);
Color GetColor();
unsigned long long GetColorHex();

#include <Ticker.h>

Ticker program_ticker;

void Tick_CycleColors() {
  switch(GetColorHex()){
    case 0xFF00008000L:
      SetColor(COLOR_GREEN);
      break;
    case 0x00FF008000L:
      SetColor(COLOR_BLUE);
      break;
    case 0x0000FF8000L:
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
  currentColor = c;

  // TODO: Check if all these float conversions are necessary. Slows things down maybe...
  analogWrite(PWM_RED,   float(c.r) * (2.0*float(c.l)/255.0));
  analogWrite(PWM_GREEN, float(c.g) * (2.0*float(c.l)/255.0));
  analogWrite(PWM_BLUE,  float(c.b) * (2.0*float(c.l)/255.0));
  analogWrite(PWM_WHITE, c.w);

  // TODO: Check whether the color was set right by reading it back
}

void SetColorHex(unsigned long long c) {
  Color color;
  color.r = (c & 0xFF00000000L) >> 32;
  color.g = (c & 0x00FF000000L) >> 24;
  color.b = (c & 0x0000FF0000L) >> 16;
  color.l = (c & 0x000000FF00L) >> 8;
  color.w = (c & 0x00000000FFL);

  SetColor(color);
}

Color GetColor() {
  return currentColor;
}

unsigned long long GetColorHex() {
  unsigned long long color = (currentColor.r << 32) + (currentColor.g << 24) + (currentColor.b << 16) + (currentColor.l << 8) + (currentColor.w);
  return color;
}

String ColorToString(Color c) {
  char str[11];
  sprintf(str, "#%02X%02X%02X%02X%02X", c.r, c.g, c.b, c.l, c.w);
  return str;
}

#endif
