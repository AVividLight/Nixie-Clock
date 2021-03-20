#ifndef DEFINITIONS_H
#define DEFINITIONS_H

constexpr unsigned int BAUD_RATE = 9600;
constexpr unsigned short int CALIBRATION_MAX_ERROR = 10;

enum ErrorCode {
	NO_ERROR = 0,
	RTC_NOT_FOUND = 1,
	TIME_DESYNCED = 2
};

#endif