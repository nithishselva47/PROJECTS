#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int relay = 5;
int irPin1=4;
int irPin2=3;
int count=0;
boolean state1 = true;
boolean state2 = true;
boolean insideState = false;
boolean outsideIr=false;
boolean isPeopleExiting=false;
int i=1;

void setup() {
mySerial.begin(9600); 
Serial.begin(9600);
pinMode(irPin1, INPUT);
pinMode(irPin2, INPUT);
pinMode(relay, OUTPUT);
lcd.begin(16, 2);
}
void loop() {  
    if (!digitalRead(irPin1) && i==1 && state1){
        outsideIr=true;
        delay(100);
        i++;
        state1 = false;
    }
    else if (!digitalRead(irPin2) && i==2 &&   state2){
        lcd.setCursor(0,0);
        lcd.print("    Entering    ");
        lcd.setCursor(0,1);
        lcd.print("inside the room");
        delay(3000);
        outsideIr=true;
        delay(100);
        i = 1 ;
        count++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" No. of people ");
        lcd.setCursor(0,1);
        lcd.print("  inside room:  ");
        delay(3000);
        lcd.clear();
        lcd.print(count);
        state2 = false;
    }
    else if (!digitalRead(irPin2) && i==1 && state2 ){
        outsideIr=true;
        delay(100);
        i = 2 ;
        state2 = false;
    }
    else if (!digitalRead(irPin1) && i==2 && state1 ){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Exit from room");
        delay(3000);
        outsideIr=true;
        delay(100);
        count--;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" No. of people ");
        lcd.setCursor(0,1);
        lcd.print("   inside room:  ");
        delay(3000);
        lcd.clear();
        lcd.print(count);
        i = 1;
        state1 = false;
    }  
    if (digitalRead(irPin1)){
        state1 = true;
    }
    if (digitalRead(irPin2)){
        state2 = true;
    }
    if(count>=1){
        digitalWrite(relay,LOW);
    }
    else{
        digitalWrite(relay,HIGH);
    }
    if(count>=15){
        delay(1000); 
        Serial.println("AT+CMGF=1"); 
        delay(1000);
        Serial.println("AT+CMGS=\"+919488448059\"\r"); 
        delay(1000);    
        Serial.println("The count is above 15");
        delay(100);
        Serial.println((char)26);
        delay(1000);
    }
    else{
      Serial.println("Below 15");
      delay(1000);
    }
}
