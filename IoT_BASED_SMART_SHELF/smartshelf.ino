#include "HX711.h"  //You must have this library in your arduino library folder
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
#define DOUT  A0
#define CLK  A1
HX711 scale(DOUT, CLK);
const int SENSOR_PIN = 2;
const int RELAY_PIN = 4;
float calibration = -462500;
void setup() {
  mySerial.begin(9600); 
  Serial.begin(9600);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.println("HX711 Calibration");
  scale.tare();
  delay(100);
}
void loop() {
  long a = scale.get_units();
  int motion =digitalRead(SENSOR_PIN);
  scale.set_scale(calibration);
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3);
  Serial.println(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane pers
  delay(1000);
  if(a<1.000){
    delay(1000); 
    Serial.println("AT+CMGF=1"); 
    delay(1000);
    Serial.println("AT+CMGS=\"+919488448059\"\r"); 
    delay(1000);
    Serial.println("  the product is going t0 sold 100 %");
    delay(100);
    Serial.println((char)26);
    delay(1000);
  }
  else if(a>0.999 && a<2.000){
    delay(1000); 
    Serial.println("AT+CMGF=1"); 
    delay(1000);
    Serial.println("AT+CMGS=\"+919488448059\"\r"); 
    delay(1000);
    Serial.println("  the product is sold 90 %");
    delay(100);
    Serial.println((char)26);
    delay(1000);
  }
  else if(a>1.999 && a<3.000){
    delay(1000); 
    Serial.println("AT+CMGF=1"); 
    delay(1000);
    Serial.println("AT+CMGS=\"+919488448059\"\r"); 
    delay(1000);
    Serial.println("  the product is sold 70 %");
    delay(100);
    Serial.println((char)26);
    delay(1000);
  }
else if(a>2.999){
    Serial.println(" the product is high");
    delay(1000);
  }
  if(motion){
    Serial.println("Motion detected");
    digitalWrite(RELAY_PIN, LOW);
    delay(1000);
  }else{
     Serial.println("nothing moves");
     digitalWrite(RELAY_PIN,HIGH);
  }
}
