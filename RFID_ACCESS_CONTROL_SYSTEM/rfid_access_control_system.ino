#include <Keypad.h>
#include <LiquidCrystal.h>
const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int count,temp;                            
char input[12];
char a[12]={'0','B','0','0','2','6','A','F','E','6','6','4'};
const int ROW_NUM    = 4; 
const int COLUMN_NUM = 4; 
char key;
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte pin_rows[ROW_NUM] = {2,3,4,5}; 
byte pin_column[COLUMN_NUM] ={6,7,8,9}; 
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
const String password_1 = "123A";
String input_password;
const int RELAY = 11;
const int BUZZER = 12;
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(BUZZER,OUTPUT);
  pinMode(RELAY,OUTPUT);
  input_password.reserve(32); 
}
void loop()
{ 
  digitalWrite(RELAY, HIGH);
  digitalWrite(BUZZER, HIGH);
  lcd.clear();
  lcd.print("Welcome Guys");
  delay(1000);
  if(Serial.available())
  {
    count = 0;
    temp=1;
    while(Serial.available())    
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if((input[0]==a[0])&&(input[1]==a[1])&&(input[2]==a[2])&&(input[3]==a[3])&&(input[4]==a[4])&&(input[5]==a[5])&&(input[6]==a[6])&&(input[7]==a[7])&&(input[8]==a[8])&&(input[9]==a[9])&&(input[10]==a[10])&&(input[11]==a[11]))
    {
      Serial.println("Allowed");
      lcd.clear();
      lcd.print("Allowed");
      delay(3000);
      lcd.clear();
      while(1){
        char key = keypad.getKey();
        if (key){
          Serial.print(key);
          lcd.print(key);
            if(key == '*') {
              input_password = "";
              lcd.clear(); 
              lcd.print(" ");
              Serial.println(" ");
            } 
            else if(key == '#') {
              temp++;
              if(input_password == password_1){
                Serial.println("\nThe password is correct, unlocking the door in 20 seconds");
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Password=correct");
                lcd.setCursor(0,1);
                lcd.print("unlock the door");
                digitalWrite(RELAY, LOW);
                delay(3000);
                lcd.clear();
                input_password = "";
                break;
              }
              else {
                Serial.println("\nThe password is incorrect, try again");
                lcd.clear();
                lcd.setCursor(0,0); 
                lcd.print("password=wrong");
                lcd.setCursor(0,1);
                lcd.print("Try again");
                delay(2000);
                lcd.clear();
                input_password = "";
                if(temp>3){
                  digitalWrite(BUZZER, LOW);
                  delay(2000);
                  break;
                }
              }
              input_password = "";
            } 
            else {
              input_password += key; 
            }
          }
        }
      }
      else{
        Serial.println("Not Allowed");
        lcd.clear();
        lcd.print("Not Allowed");
        delay(2000);
    }
  }
}
