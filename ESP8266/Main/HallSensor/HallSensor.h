/*
 * Hall Sensor based wind speed Manager
 */

#ifndef HallSensor_h
#define HallSensor_h

class HallSensor{    
  public: 
    enum type {rpm, kph, mps, mph, fps};    
    HallSensor(const int pin, int wicks);
    void Setup();
    void Loop();
    float getSpeed(type type);
	bool magnetDetected();

  private:
	int pin;
	int wicks;
	float timer = 0;
	float rpmValue = 0; 
};

#endif
