#include "Arduino.h"
#include "HardwareSerial.h"

#include "RTClib.h"

static RTC_DS3231 sysClock;
const short CALIBRATION_BAND = 10;


void loop() {
	
}

void calibrateRTC() {
	sysClock.adjust(DateTime(F(__DATE__), F(__TIME__)));
}



bool timeDesynced() {
	return (abs((signed long long) sysClock.now().unixtime() - DateTime(F(__DATE__), F(__TIME__)).unixtime()) > CALIBRATION_BAND);
}

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		delay(50);
	}

	if(!sysClock.begin()) {
		Serial.println("Could not connect to RTC");
		Serial.flush();
		abort();
	}

	if(timeDesynced()) {
		Serial.print("Time is desynced.");
		calibrateRTC();
	}
}
