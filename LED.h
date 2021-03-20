#ifndef LED_H
#define LED_H

class LED {
	public:
	LED();
	LED(const unsigned short int, const unsigned short int, const unsigned short int);
	~LED();

	void setColor(const unsigned short int, const unsigned short int, const unsigned short int);

	private:
	unsigned short int redPin;
	unsigned short int greenPin;
	unsigned short int bluePin;

	unsigned short int redValue;
	unsigned short int greenValue;
	unsigned short int blueValue;
};

#endif