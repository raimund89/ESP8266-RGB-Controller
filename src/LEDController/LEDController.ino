#include "lc_serial.h"
#include "lc_colors.h"
#include "lc_gpio.h"
#include "lc_wifi.h"
#include "lc_ota.h"
#include "lc_webserver.h"
#include "lc_programs.h"

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
