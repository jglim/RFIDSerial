RFIDSerial
=========

Get usable serial data from your cheap RFID readers!

  - Uses Teensy 2.0 (since there is a USB serial *and* a hardware serial)
  - Reads and converts raw data into the card's 10 digit ID
  - Outputs the data into the serial (separated by newlines)
  
I recently bought one of those affordable (~US$10) chinese RFID readers. Unfortunately the device only outputs to USB (appears as a keyboard). I wanted the output via the serial port as it was inconvenient that the RFID reader hijacks your keyboard everytime a card is scanned, hence I created this project.

Using a logic analyser, I noticed that the pin labeled TX sends a serial output ``(bit rate: 9600)`` when a card is scanned. The format is as follows

``[card digit] [240] [card digit] ``
repeated 10 times

I am not sure what the format for encoding the number is. However, since the character space should only span [0-9], I chose to decode it via a lookup table. 
Please note that this table is incomplete - help would be appreciated! (see caveats)

How to use
-----------

Your RFID reader must be similar or exactly the same as mine - [this was the one I purchased.](http://www.aliexpress.com/snapshot/211636793.html)
On the board, there should be a few test points. The one we are interested in is the serial TX (refer to image)

![RFID Board](https://raw.github.com/jglim/RFIDSerial/master/Images/rfid1.png)

1. Connect the TX pin from the reader to the RX pin of your Teensy (Pin 7/D2)
2. Connect the RFID board's ground to your Teensy's ground
3. Upload the sketch using Teensyduino

To prevent keystrokes being sent to the computer while supplying power, I believe it is possible to tape the USB data lines, leaving only 5V and GND

Caveats
--------------
* The first digit is occassionally not sent (check whether the output's ``length == 10``)
* The digits ``4,7,8`` are not implemented! It would be great if someone has a RFID card with those digits and can help add them!


License
-

MIT
