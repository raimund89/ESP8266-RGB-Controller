#include "lc_serial.h"
#include "lc_settings.h"
#include "lc_colors.h"
#include "lc_gpio.h"
#include "lc_wifi.h"
#include "lc_ota.h"
#include "lc_webserver.h"
#include "lc_programs.h"

// Very important part to do: don't read color from the analogRead. Save the current color, then use that to set the current color. Can use analogRead to confirm correct writing...

void setup() {
  InitSerial();
  LoadSettings();
  InitGPIO();
  InitWifi();
  InitOTA();
  delay(1000);
  InitWebserver();
}

void loop() {
  HandleOTA();
  HandleSocket();
}
