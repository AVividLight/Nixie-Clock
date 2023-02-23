#include "Arduino.h"
#include "HardwareSerial.h"

#include "RTClib.h"

#include "Definitions.h"
#include "LED.h"


static RTC_DS3231 sysClock;
static unsigned long int clockDeviationAmount = 0;
static LED *leds = new LED[41]; //23:05 => [3][10][1][10][10] => 34


void loop() {
	Serial.print(sysClock.now().hour());
	Serial.print(':');
	Serial.print(sysClock.now().minute());
	Serial.print(':');
	Serial.println(sysClock.now().second());
	delay(1000);
}


void calibrateRTC() {
	sysClock.adjust(DateTime(F(__DATE__), F(__TIME__)));
}



bool timeDesynced() {
	clockDeviationAmount = abs((signed long long) sysClock.now().unixtime() - DateTime(F(__DATE__), F(__TIME__)).unixtime());
	return (clockDeviationAmount > CALIBRATION_MAX_ERROR);
}


void setup() {
	short int errorCode = ErrorCode::NO_ERROR;

	if(!sysClock.begin()) {
		errorCode = ErrorCode::RTC_NOT_FOUND;
	} else {
		if(timeDesynced()) {
			errorCode = ErrorCode::TIME_DESYNCED;
			calibrateRTC();
		}
	}

	Serial.begin(BAUD_RATE);
	while (!Serial) {
		delay(250);
	}

	switch(errorCode) {
	case ErrorCode::NO_ERROR:
		Serial.print(sysClock.now().hour());
		Serial.print(':');
		Serial.print(sysClock.now().minute());
		Serial.print(':');
		Serial.print(sysClock.now().second());
		break;

	case ErrorCode::RTC_NOT_FOUND:
		Serial.println("Could not connect to RTC");
		Serial.flush();
		abort();
		break;

	case ErrorCode::TIME_DESYNCED:
		Serial.print("Time is desynced by ");
		Serial.print(clockDeviationAmount);
		Serial.println(" seconds.");
		break;

	default:
		break;
	}
}
