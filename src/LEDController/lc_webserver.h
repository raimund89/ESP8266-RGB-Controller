#ifndef LC_WEBSERVER
#define LC_WEBSERVER

#include <WebSocketsServer.h>

#include "lc_gpio.h"

/**************************************/
/* Only use broadcast functions when  */
/* the status is updated, so all      */
/* connected devices are notified of  */
/* changes. Use sendXXX() functions   */
/* only as specific responses.        */
/**************************************/

WebSocketsServer websocket = WebSocketsServer(81);

void webSocketEvent(byte num, WStype_t type, uint8_t* payload, size_t length);

void InitWebserver()
{
  websocket.begin();
  websocket.onEvent(webSocketEvent);
  Program_Clear();
}

void webSocketEvent(byte num, WStype_t type, uint8_t* payload, size_t length) {
  if(type == WStype_TEXT) {
    if(payload[0] == '#') {
      // They sent a color.
      SetColorHex(strtoull((const char*)&payload[1], NULL, 16));
      websocket.broadcastTXT(ColorToString(currentColor).c_str());
    } else if(payload[0] == 'c') {
      // They want to know the current color.
      websocket.sendTXT(num, ColorToString(currentColor).c_str());
    } else if(payload[0] == 'p') {
      // They want to set a program.

      //////// HERE CODE TO CHOOSE BETWEEN PROGRAMS //////////
    } else if(payload[0] == 'r') {
      // They want to know if a program is running

      //////// HERE CODE TO SEND WHICH PROGRAM IS RUNNING ////////
    }
  }
}

void HandleSocket(){
  websocket.loop();
}

#endif
