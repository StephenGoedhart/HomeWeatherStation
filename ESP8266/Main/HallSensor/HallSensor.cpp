#include "Arduino.h"
#include "HallSensor.h"

HallSensor::HallSensor(const int pin, int wicks) {
	pinMode(pin, INPUT);
	this->pin = pin;
	this->wicks = wicks;
}

void HallSensor::Loop() {
	//TO DO:
	//INCREMENT TIMER
	timer++;

	//DETECT MAGNET
	//CALCULATE THE TIME DIFFERENCE (NEW TIME - CURRENT TIME
	if (timer != 0 && digitalRead(pin) == HIGH) {
		rpmValue = (timer) * wicks;
		timer = 0;
	}
}

bool HallSensor::magnetDetected() {
	return digitalRead(pin) == HIGH;
}
