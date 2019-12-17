#ifndef LC_WIFI
#define LC_WIFI

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include <Ticker.h>

#include "lc_gpio.h"

WiFiManager wifiManager;
Ticker ticker;

void configModeCallback(WiFiManager *manager);
void tick();

void InitWifi()
{
  // So we can do something when config mode is entered
  wifiManager.setAPCallback(configModeCallback);
  
  // Put some safeties around this (if(!autoconnect), do something)
  wifiManager.autoConnect("SkynetLED");
}

void configModeCallback(WiFiManager *manager) {
  Serial.println("Configuring access to the network...");
  Serial.println("Use SSID " + manager->getConfigPortalSSID());
  Serial.println("And use IP address " + WiFi.softAPIP());
  
  // Now do something with the LEDs here
  ticker.attach(0.5, tick);
}

void tick() {
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

#endif
