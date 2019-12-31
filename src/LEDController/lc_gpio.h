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
unsigned long GetColorHex();

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

  analogWrite(PWM_RED, c.r * (2*c.l/255));
  analogWrite(PWM_GREEN, c.g * (2*c.l/255));
  analogWrite(PWM_BLUE, c.b * (2*c.l/255));
  analogWrite(PWM_WHITE, c.w);

  // TODO: Check whether the color was set right by reading it back
}

void SetColorHex(unsigned long c) {
  Color color = {(c & 0xFF00000000L) >> 32, (c & 0x00FF000000L) >> 24, (c & 0x0000FF0000L) >> 16, (c & 0x000000FF00L) >> 8, (c & 0x00000000FFL)};

  SetColor(color);
}

Color GetColor() {
  return currentColor;
}

unsigned long GetColorHex() {
  unsigned long color = (currentColor.r << 32) + (currentColor.g << 24) + (currentColor.b << 16) + (currentColor.l << 8) + (currentColor.w);
  return color;
}

#endif
