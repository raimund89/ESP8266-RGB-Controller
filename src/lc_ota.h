#ifndef LC_OTA
#define LC_OTA

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void InitOTA()
{
  ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname("Skynet LED Controller");

  ArduinoOTA.onStart([]() {
    Serial.println("Skynet update started.");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("Skynet update ended.");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress/(total/100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);

    if(error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });

  ArduinoOTA.begin();
  Serial.println("Skynet LED Controller ready to receive updates.");
  Serial.println("Update address: " + WiFi.localIP());
}

void HandleOTA() {
  ArduinoOTA.handle();
}

#endif
