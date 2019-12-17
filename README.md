# ESP8266 RGB(W) Controller
This firmware has been written for an ESP8285-based Magic Home RGBW LED Controller (specifically [this one](https://nl.aliexpress.com/item/32579734729.html)), but it should work with any of the ESP8266 or ESP8285 based RGB(W) LED controllers. Although controlling the white channel is implemented, this can be ignored and always set to zero when using an RGB controller without white channel.

## Some notes on hardware
In case of the Magic Home or similar devices, the hardware part should already have been dealt with, and these devices can usually handle more than a 100W output power. If you're making the hardware yourself, note that the Espressif devices typically cannot handle more than 10 mA over their output pins. To control LEDs - and especially LED strips - you should use a MOSFET (most devices use N-type, but whatever works in your case) to switch higher currents. In any case I would say this is recommended practice to avoid accidentally damaging the ESP chip.

Also note, I'm not responsible in any way for whatever you're doing with this software. I just wrote it and would like to share it with the world, but be responsible and think about what you're doing. Most of the LED strips and LED controllers can handle high currents at pretty high voltages, which can result in all kinds of damage to you or your surroundings. Anyway, just wanted to say that :)

## Functionality
- [x] WiFi access through [WiFiManager](https://github.com/tzapu/WiFiManager) for easy configuration
- [x] ArduinoOTA for easy updating
- [x] Websocket communication using [WebSocketsServer](https://github.com/Links2004/arduinoWebSockets)
- [ ] Built-in color sequence programs
- [ ] Persistent color setting after power cycle
- [ ] Settings page (for hostname, websocket port, reset wifi, etc.)
- [ ] Scripting custom color sequence programs
- [ ] Test support for ESP32
- [ ] Color sequences to indicate status
- [ ] IR remote support
- [ ] Structuring code (separate GPIO, color and programs)

## Installing
The code is written using the Arduino IDE, and that is the easiest way to compile and upload the code. For instructions on how to add the Espressif boards to the Arduino IDE, take a look at https://github.com/esp8266/Arduino. Also, you will need two libraries, WiFiManager (by **tzapu**) and WebSockets (by **Markus Sattler**). Both can be installed from the Library Manager in the Arduino IDE (Menu Sketch -> Include Library -> Manage Libraries).

After that, download this repository in a separate folder and open the .ino file in the Arduino IDE. If your Espressif device is not yet configured to use ArduinoOTA, you need to upload the program once using an UART device. The board type needs to be set to either 'Generic ESP8266 Module' or 'Generic ESP8285 Module'. The program currently is about 350kB in size.

- **For the ESP8285 module.** Set the flash size to 1MB, with at least 350kB of OTA size. When scripting is added to the functionality, more FS-size will mean more space for scripts.
- **For the ESP8266 module.** Set the flash size to anything larger than or equal to 1MB, and an OTA size of at least 350kB.

## Usage
To test the device you can use the [Simple WebSocket Client](https://chrome.google.com/webstore/detail/simple-websocket-client/pfdhoblngboilpfeibdedpjgfnlcodoo) for Chrome/Chromium. All communication through the websocket is text-based. The following commands can be sent:

Command | Explanation
------------ | -------------
#RRGGBBWW | Sends a color to the device in hexadecimal form in the range 0x00-0xFF for each color red (RR), green (GG), blue (BB) and white (WW). *Note:  you need to send the entire number. Sending for example 0xFFFF will result in red and green set to zero.* The device broadcasts the new color, in this same format, to all connected clients.
c | Request for the current color. Uses the format #RRGGBBWW.
pXX | Starts the program indicated by the hexadecimal number XX. If XX equals 0, any currently running program is stopped. Hence, the device supports a maximum of 255 programs. The device broadcasts the number of the new program, in the same format, to all connected clients.
r | Requests the currently running program. The code of the current program is returned in hexadecimal number. Zero is returned if no program is running.
