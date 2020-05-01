# Arduino HID Keyboard Using V-USB for Arduino

There was a moment when just the laptop/desktop keyboard wasn't enough and there was a deadly virus outside and to buy online was also a danger. But you like to tinker and you have lying around an Arduino Uno board, the chinese version because you like to have more boards instead of an expensive one which you can fry easily enough. 

Besides the Arduino Board, make sure you have:
- some breadboard push buttons (I used six)
- a 4x4 8 wire keypad
- an microUSB female board (you can use an USB Type A Male connector and solder the wires at the end to the corresponding pins)
- two 3V6 Zener diodes with a power of maximum 0.5W (1W will not work)
- two 68 Ohm resistors
- one 2.2 kOhm resistor
- six 10 kOhm resistors
- microUsb Male - Type A Male cable (or the alternative from above)
- USb Type B Male - USB Type A cable (to program Arduino Uno)
- many male-male dupont wires

The list is a little big, you can save "space" by having a genuine board, for which you can reprogram the USB controller (atmega 16U2). Also, I recomment to solder the components on a prototyping  (or just the USB interface with the diodes and resistors, I don't trust the breadboard and neither should you, many thing could happen when a resistor will not make contact, or a diode, which is more important, with the resistor you will lose connection, but the diode will stop reverse current, for example).

I attached an image with the connections made. Verify the connections twice before connections to a computer (my laptop said "power surge on USB port" at some point (this is what happens when the GND and VCC are reversed), which is not good if the laptop is not so expensive and the USB protections are inexistent.

Download the library from: https://code.google.com/archive/p/vusb-for-arduino/downloads, and copy the content of "libraries" folder in your Arduino IDE libraried folder. We will need only "UsbKeyboard", but in that folder you will see that "UsbDevice" and "UsbStream" are present. Also, I used the Arduino IDE version 1.0.5 (https://www.arduino.cc/en/main/OldSoftwareReleases) because I read that newer versions needs some updates for the V-USB libraries, and since the last update to this library was in 2010, I didn't even try to use a newer version of Arduino IDE. To be honest, the next time I will try to make it work with a newer versions, the 1.0.5 is horrible.

In the code you will find many comments about the implementation. The code is very simple, but I had some problems with the Keypad.h library (which you can download from https://playground.arduino.cc/Code/Keypad/#Download) because for the USBKeyboard library to work, I had to disable Timer 0 (overflow interrupt), which uses millis() counts for delay (millis() will return 0 when Timer 0 is disabled). The Keypad.cpp has a limit of how often the keypad is scanned and for this uses millis(), and since millis() return 0, the condition will never be satisfied and the scan will never happed. I commented the if statement in the getKeys() function and after this the keypad returned the key pressed without any problem. Of course there is a better fix, but I didn't want to spend more time on this.

