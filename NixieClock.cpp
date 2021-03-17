#include <stdlib.h>
#include <string.h>
#include "Arduino.h"
#include "HardwareSerial.h"


#define MAXIMUM_INPUT_TIME_LENGTH 5

static unsigned short int seconds = 0;
static unsigned char minute = 0;
static unsigned char hour = 0;

static unsigned long cycleStartTime = 0;
static unsigned short cycleElapsedTime = 0;
static unsigned short cycleDelay = 0;

char *inputLoop() {
	char *inputText = new char[MAXIMUM_INPUT_TIME_LENGTH];

	while(Serial.available() < MAXIMUM_INPUT_TIME_LENGTH) {
		delay(500);
	}

	for (int i = 0; i < MAXIMUM_INPUT_TIME_LENGTH; i += 1) {
		Serial.readBytes(&inputText[i], 1);
	}
	inputText[MAXIMUM_INPUT_TIME_LENGTH] = '\0';

	return inputText;
}

void askAndAssignTime() {
	Serial.println("Input time in format 23:12");

	char *inputTime = inputLoop();

	char *timeBuffer;
	timeBuffer = strtok(inputTime, ":");
	hour = atoi(timeBuffer);
	minute = atoi(strtok(NULL, ":"));
}

/*
millis() returns the number of milliseconds passed since the Arduino board began running the current program as an unsigned long. This number will overflow (go back to zero), after approximately 50 days.
*/

void loop() {
	cycleStartTime = millis();
	delay(cycleDelay);

	seconds += 1;
	if (seconds == 60) {
		minute += 1;
		seconds -= 60;
	}

	if (minute == 60) {
		hour += 1;
		minute -= 60;
	}

	if (hour == 24) {
		hour = 0;
	}

	Serial.print("It is currently ");
	Serial.print(hour);
	Serial.print(":");
	Serial.print(minute);
	Serial.println();

	cycleElapsedTime = millis() - cycleStartTime;
	if(cycleElapsedTime > 1000) {
		cycleDelay = 0;
		Serial.println()
	} else {
		cycleDelay = 1000 - cycleElapsedTime;
	}
}

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		delay(250);
	}

	askAndAssignTime();
}
