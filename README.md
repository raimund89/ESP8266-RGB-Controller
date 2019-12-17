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
- [ ] Persistent settings (hostname, color, bit-resolution, OTA-name, scripts, pin assignments, etc.)
- [ ] Settings page (for hostname, websocket port, reset wifi, scripting, etc.)
- [ ] Scripting custom color sequence programs
- [ ] Test support for ESP32
- [ ] Color sequences to indicate status
- [ ] IR remote support (for some models)
- [ ] Structuring code (separate GPIO, color and programs)
- [ ] Support for 10-bit colors (as Espressif chips can do that). *Could do this by allocating an additional byte for each color in the upper half of the unsigned long.*

## Installing
The code is written using the Arduino IDE, and that is the easiest way to compile and upload the code. For instructions on how to add the Espressif boards to the Arduino IDE, take a look at https://github.com/esp8266/Arduino. Also, you will need two libraries, WiFiManager (by **tzapu**) and WebSockets (by **Markus Sattler**). Both can be installed from the Library Manager in the Arduino IDE (Menu Sketch -> Include Library -> Manage Libraries).

After that, download this repository in a separate folder and open the .ino file in the Arduino IDE. If your Espressif device is not yet configured to use ArduinoOTA, you need to upload the program once using an UART device. The board type needs to be set to either 'Generic ESP8266 Module' or 'Generic ESP8285 Module'. The program currently is about 350kB in size.

- **For the ESP8285 module.** Set the flash size to 1MB, with at least 350kB of OTA size. When scripting is added to the functionality, more FS-size will mean more space for scripts.
- **For the ESP8266 module.** Set the flash size to anything larger than or equal to 1MB, and an OTA size of at least 350kB.

## Usage
To test the device you can use the [Simple WebSocket Client](https://chrome.google.com/webstore/detail/simple-websocket-client/pfdhoblngboilpfeibdedpjgfnlcodoo) for Chrome/Chromium. All communication through the websocket is text-based. The following commands can be sent:

Command | Explanation
------------ | -------------
`#RRGGBBWW` | Sends a color to the device in hexadecimal form in the range 0x00-0xFF for each color red (`RR`), green (`GG`), blue (`BB`) and white (`WW`). *Note:  you need to send the entire number. Sending for example 0xFFFF will result in red and green set to zero and blue and white set to max.* The device broadcasts the new color, in the same format, to all connected clients.
`c` | Request for the current color. Returned value is in the format `#RRGGBBWW`.
`pXX` | Starts the program indicated by the hexadecimal number `XX`. If XX equals 0, any currently running program is stopped. Hence, the device supports a maximum of 255 programs. The device broadcasts the number of the new program, in the same format, to all connected clients.
`r` | Requests the currently running program. Returned value is in the format `pXX`. Zero is returned if no program is running.
`lXX` | If `XX` is `00`, this returns a comma-separated list of all the currently occupied program slots. If it is the number of an existing program, it returns the name of the program.
`xXXY...Y` | If `XX` is the number of an existing program and `Y...Y` is not given, the device returns the code of the program. If `Y...Y` is set to `0` (not `\0`!), the program is deleted. If `Y...Y` is a string of text and there is currently no program at slot `XX`, the string will be set as the new program at program number `XX`.

* If you want to turn the device off, simply send the color `#00000000` to the device.

## Examples

### Javascript
In Javascript you can use the WebSocket class. An easy example, with just a textbox for sending and a `<div>` for output, would be the following. Replace the IP-address with the address of the device, and the port to the websocket port (default is 81).

```javascript
<html>
  <body>
    <!-- message form -->
    <form name="publish">
      <input type="text" name="message">
      <input type="submit" value="Send">
    </form>

    <!-- div with messages -->
    <div id="messages"></div>

    <script type='text/javascript'>
        let socket = new WebSocket("wss://192.168.1.2:81");

        // send message from the form
        document.forms.publish.onsubmit = function() {
          let outgoingMessage = this.message.value;

          socket.send(outgoingMessage);
          return false;
        };

        // message received - show the message in div#messages
        socket.onmessage = function(event) {
          let message = event.data;

          let messageElem = document.createElement('div');
          messageElem.textContent = message;
          document.getElementById('messages').prepend(messageElem);
        }
    </script>
  </body>
</html>
```

### Android
In Android I prefer working in Kotlin, but in Java it's pretty similar. You can use the Scarlet library (from Tinder), or directly use OkHttp3.

**To be added**
