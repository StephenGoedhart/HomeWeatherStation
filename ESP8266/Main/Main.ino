#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include "DHT.h"

//HALL SENSOR SET UP
#define HALPIN D6

//OLED DISPLAY SET UP
#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);

//DHT SETUP
#define DHTPIN D5 
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


int HALMODE = 0;

float hic = 0;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  Serial.println("DHTxx test!");

  pinMode(HALPIN, INPUT);
  
  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");

  //Wind speed stuff
  HALMODE = digitalRead(HALPIN);

  if(HALMODE == LOW){
   Serial.println("\n MAGNET DETECTED \n");
  }
  else{
       Serial.println("\n NOTHING... \n");
  }


 draw();
}

//This code is initialized at the end of the frame
void draw(){ 
  drawText(0,0,WHITE,2, false, "'C:");
  drawText(0,30, WHITE, 3, false, String(hic));
  display.display();
  delay(2000);
  display.clearDisplay();   
  delay(500);
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
