#include "Arduino.h"
#include "HardwareSerial.h"

#include "RTClib.h"


#define MAXIMUM_INPUT_TIME_LENGTH 5
#define SDA_PIN 4
#define SCL_PIN 5

static unsigned short int seconds = 0;
static unsigned char minute = 0;
static unsigned char hour = 0;

static unsigned short cycleDelay = 0;

static RTC_DS3231 sysClock;


void calculateCycleDelay() {
	unsigned int startTime = millis();
	loop();
	unsigned int cycleDuration = millis() - startTime;
	
	cycleDelay = (1000 - cycleDuration);
}

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
	return;
	seconds += 1;
	delay(cycleDelay);

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
}

void pollRTC() {
	if(sysClock.lostPower()) {
		Serial.println("Power failure detected- recalibration necessary");
	} else {
		DateTime now = sysClock.now();
		Serial.print("now(): ");
		Serial.print(now.hour());
		Serial.print(":");
		Serial.println(now.minute());
	}
}

double currentTemp() {
	return sysClock.getTemperature() * (9.0/5.0) + 32;
}

void calibrateRTC() {
	sysClock.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void setup() {
	bool error = false;

	Serial.begin(9600);
	while (!Serial) {
		delay(250);
	}

	if(!sysClock.begin()) {
		Serial.println("Could not connect to RTC");
		error = true;
	}

	if(!error) {
		//calibrateRTC();
		pollRTC ();
		Serial.print("Current temp: ");
		Serial.println(currentTemp());
	}

	//pinMode(LED_BUILTIN, OUTPUT);

	//askAndAssignTime();
	//calculateCycleDelay();
}
