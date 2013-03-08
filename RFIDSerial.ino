// This line defines a "Uart" object to access the serial port
HardwareSerial Uart = HardwareSerial();

void setup() {
    Serial.begin(9600);
    Uart.begin(9600);
}

boolean ignoreNextPacket = false;
int lastReceivedPacket = -1;
int bufferSize = 0;

void loop() {


    if (Uart.available() > 0) {
        int rfidByte = Uart.read();

        if (rfidByte == 240) {
            // ignore next packet
            ignoreNextPacket = true;
        } else {
            if (ignoreNextPacket) {
                // compare the first packet and this "ignored" packet to see if they match
                // if they don't, the second one will likely be "correct"
                int correctPacket = -1;
                if (rfidByte == lastReceivedPacket) {
                    correctPacket = lastReceivedPacket;
                } else {
                    // packet mismatch, ignore the first one
                    correctPacket = rfidByte;
                }

                // output to console
                if (convertPacketToUsableDigit(correctPacket) != -4) {
                    Serial.print(convertPacketToUsableDigit(correctPacket), DEC);
                    bufferSize++;
                } else {
                    // finished reading the RFID card

                    // check if printing empty buffer - cancel if so
                    if (bufferSize != 0) {
                        Serial.println("");
                    }

                    // technically if the buffer size doesn't match the RFID reader's output length then something is wrong
                    lastReceivedPacket = -1;
                    ignoreNextPacket = false;
                    bufferSize = 0;
                }


                // reset ignore
                ignoreNextPacket = false;
            } else {
                lastReceivedPacket = rfidByte;
            }

        }

    }
}

int convertPacketToUsableDigit(int packetByte) {
    // TODO: digits 4,7,8 are not implemented! 
    int lookupTable[] = {
        69, 22, 158, 38, -1, 174, 182, -2, -3, 70
    };
    for (int i = 0; i < 10; i++) {
        if (lookupTable[i] == packetByte) {
            return i;
        }
    }
    // return -4 when it isn't within 0-9
    return -4;
}
