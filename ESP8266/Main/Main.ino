//Library files
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include "DHT.h"

//Local files
#include "HallSensor/HallSensor.h"

//HALL SENSOR SET UP
const int HALLPIN = 1; //#define HALPIN D6

//OLED DISPLAY SET UP
#define OLED_RESET LED_BUILTIN //4

//DHT SETUP
#define DHTPIN D5 
#define DHTTYPE DHT22   // DHT 11

//ROTARY ENCODER SET UP
#define REAPIN D0
#define REBPIN D8

//Globals
bool MAGNET = false;
float HIC = 0;
float HIF = 0;
float HUMIDITY = 0;

//ENCODER STUFF
bool AFLAG = false;
bool BFLAG = false;
volatile byte COUNT = 0;

//HALL SENSOR
HallSensor HALLSENSOR(HALLPIN, 3);

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(OLED_RESET);

void setup() {  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  Serial.begin(9600);
  pinMode(HALLPIN, INPUT);
  
  dht.begin();

  pinMode(REAPIN, INPUT_PULLUP);
  pinMode(REBPIN, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(REAPIN),rotaryInterrupt,FALLING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(digitalPinToInterrupt(REAPIN),rotaryInterrupt,FALLING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
}

void loop() {
  //Gather temperature data from DHT22
  temperature();
  //Calculate the windspeed based on RPM
  //windSpeed();

  //Calculate wind direction  
  
 draw();
}

void rotaryInterrupt() {
  //unsigned char result = ROTARY.process();
  COUNT++;
  Serial.println(COUNT);
  //RIGHT
//  if(digitalRead(REBPIN) == HIGH && digitalRead(REAPIN) == LOW   && !AFLAG){
//    BFLAG = true;
//      COUNT++;
//    }
  
}



void temperature(){
    // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  HUMIDITY = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(HUMIDITY) || isnan(t) || isnan(f)) {
   // Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute Fahrenheit
  HIF = dht.computeHeatIndex(f, HUMIDITY);
  // Compute Celsius
  HIC = dht.computeHeatIndex(t, HUMIDITY, false);
  } 

void windSpeed(){
    //Wind speed stuff
  MAGNET = digitalRead(HALLPIN) == HIGH;
  }

//This code is initialized at the end of the frame
void draw(){ 
  display.clearDisplay(); 
  drawText(0,0,WHITE,2, false, "*C:" + String(HALLSENSOR.magnetDetected()) + "("+ String(digitalRead(REAPIN)) + String(digitalRead(REBPIN)) + ")");
  drawText(0,30, WHITE, 3, false, String(HIC));
  display.display();    
  }

//X+Y Coordinates, color, size, text wrap, text string
void drawText(uint16_t x, uint16_t y, uint16_t c, uint16_t s, bool w, String t){
    display.setCursor(x,y);
    display.setTextColor(c);
    display.setTextSize(s);
    display.setTextWrap(w);
    display.print(t);
}

void displayCelcius(){
  
  
  }
