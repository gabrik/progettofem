#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>

Servo myservo;
int pos = 0;
const int btBoud = 115200;
const int pinBtTx = 11;
const int pinBtRx = 10;
const int pinLed = 13;


const int pinLCDRx = 13;
const int pinLCDTx = 12;

SoftwareSerial bt(pinBtRx, pinBtTx);
SoftwareSerial lcd(pinLCDRx, pinLCDTx);


void setup()
{

  Serial.begin(9600);
  //while (!Serial);
  Serial.println("serial open");


  lcd.begin(9600);
  while (!lcd);
  
  
  lcd.write(19);
  lcd.write(12);
  
  
  Serial.println("lcd open");
  lcd.write(12);
  lcd.print("lcd open");

  delay(1000);


  bt.begin(9600);
  while (!bt);
  Serial.println("bt open");
  lcd.write(12);
  lcd.print("bt open");

  delay(1000);
  lcd.write(12);
  lcd.print("ready");
  
  delay(500);
  lcd.write(12);
  

  pinMode(pinLed, OUTPUT);
  myservo.attach(8);

}

void loop()
{

  
  
  
  
  if (bt.available()) {
    char c = (char)bt.read();
    Serial.println(c);
    lcd.write(12);

    //per i ladri cosi' entrano piu' facilmente
    /*if(c=='R'){
      setup();
    }*/


    if (c == '1') {

      
      lcd.print("Aperto ");
      lcd.print(c);
      for (pos = 0; pos <= 175; pos++) {
        myservo.write(pos);
      }
      digitalWrite(pinLed, HIGH);
    }


    if (c == '0') {
      lcd.print("Chiuso ");
      lcd.print(c);
      for (pos = 175; pos >= 0; pos--) {
        myservo.write(pos);
      }
      digitalWrite(pinLed, LOW);
    }
  }

}
