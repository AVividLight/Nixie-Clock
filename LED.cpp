#include "LED.h"


LED::LED() {
	redPin = -1;
	greenPin = -1;
	bluePin = -1;

	redValue = 255;
	greenValue = 255;
	blueValue = 255;
}


LED::LED(const unsigned short int rP, const unsigned short int gP, const unsigned short int bP) {
	redPin = rP;
	greenPin = gP;
	bluePin = bP;

	redValue = 255;
	greenValue = 255;
	blueValue = 255;
}


LED::~LED() {

}


void LED::setColor(const unsigned short int red, const unsigned short int green, const unsigned short int blue) {
	redValue = red;
	greenValue = green;
	blueValue = blue;
}