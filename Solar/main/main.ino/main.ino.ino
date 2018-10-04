#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(2);
  servo1.write(0);
  
  servo2.attach(2);
  servo2.write(0);
  
  delay(2000);



}

void loop() {
  // put your main code here, to run repeatedly:
    servo1.write(90);
        servo2.write(90);
  delay(2000);
  servo1.write(0);
    servo1.write(0);
  delay(2000);



}
