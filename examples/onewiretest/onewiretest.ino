#include <ESP8266WiFi.h>
#include "ESPSoftwareSerial.h"

ESPSoftwareSerial swSer1;
ESPSoftwareSerial swSer2;

void setup() {
	delay(2000);
	Serial.begin(115200);
	Serial.println("\nOne Wire Half Duplex Serial Tester");
	swSer1.begin(115200, 12, 12, SWSERIAL_8N1, false, 256);
	swSer1.enableIntTx(true);
	swSer2.begin(115200, 14, 14, SWSERIAL_8N1, false, 256);
	swSer2.enableIntTx(true);
}

void loop() {
	Serial.println("\n\nTesting on swSer1");
	Serial.print("Enter something to send using swSer1.");
	checkSwSerial(&swSer1);

	Serial.println("\n\nTesting on swSer2");
	Serial.print("Enter something to send using swSer2.");
	checkSwSerial(&swSer2);

}

void checkSwSerial(ESPSoftwareSerial* ss) {
	byte ch;
	while (!Serial.available());
	ss->enableTx(true);
	while (Serial.available()) {
		ch = Serial.read();
		ss->write(ch);
	}
	ss->enableTx(false);
	// wait 1 second for the reply from SOftwareSerial if any
	delay(1000);
	if (ss->available()) {
		Serial.print("\nResult:");
		while (ss->available()) {
			ch = (byte)ss->read();
			Serial.print(ch < 0x01 ? " 0" : " ");
			Serial.print(ch, HEX);
		}
		Serial.println();
	}
}
