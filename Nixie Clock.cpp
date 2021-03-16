#include <stdlib.h>
#include <string.h>


#define MAXIMUM_INPUT_TIME_LENGTH 5

static unsigned short int seconds = 0;
static unsigned char minute = 0;
static unsigned char hour = 0;


void setup() {
  Serial.begin(9600);
  while(!Serial) {
	  delay(250);
  }
  pinMode(LED_BUILTIN, OUTPUT);

  askAndAssignTime();
}

// [1][2][:][3][7][\0]
//	0  1  2  3  4   5

char *inputLoop() {
	char *inputText = new char[MAXIMUM_INPUT_TIME_LENGTH];
	char *inputBuffer = new char;

	while(true) {
		if(Serial.available() >= MAXIMUM_INPUT_TIME_LENGTH) {
			for(int i = 0; i < MAXIMUM_INPUT_TIME_LENGTH; i += 1) {
				Serial.readBytes(inputBuffer, 1);
				inputText[i] = *inputBuffer;
			}
			break;
		} else {
			delay (100);
		}
	}

	inputText[MAXIMUM_INPUT_TIME_LENGTH] = '\0';

	free(inputBuffer);
	return inputText;
}

void askAndAssignTime () {
	Serial.println("Input time in format 23:12");

	char *inputTime = inputLoop();

	char *timeBuffer;
	timeBuffer = strtok(inputTime, ":");
	hour = atoi(timeBuffer);
	minute = atoi(strtok(NULL, ":"));
}

void loop() {
  seconds += 1;
  delay(1000);

  if(seconds == 60) {
	minute += 1;
	seconds -= 60;
  }

  if(minute == 60) {
	hour += 1;
	minute -= 60;
  }

  if(hour == 24) {
	hour = 0;
  }

  Serial.print("It is currently ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.println();
}