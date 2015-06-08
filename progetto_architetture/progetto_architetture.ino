#include <SoftwareSerial.h>
#include <Servo.h>
#include <LiquidCrystal.h>


//per richieste http
#include <Bridge.h>
#include <HttpClient.h>

//formato della richiesta json
//{"id":3,"door":"Garage Door","who":"Salvatore","time":"2015-06-04T11:54:21.861436574+02:00"}


Servo myservo;
int pos = 0;
const int btBoud = 115200;
const int pinBtTx = 11;
const int pinBtRx = 10;
int x=A5;
int cont=0;
char c;

const int pinLCDRx = 13;
const int pinLCDTx = 12;


int state=0;

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
  lcd.print("starting bridge");
  Bridge.begin();
  lcd.write(12);
  lcd.print("bridge ready");

  delay(1000);
  lcd.write(12);
  lcd.print("ready");

  delay(500);
  lcd.write(12);


  //pinMode(pinLed, OUTPUT);
  myservo.attach(8);

  pinMode(x, INPUT);



}

void loop()
{

  //Serial.println(myservo.read());
  HttpClient client;
  //Serial.println(state);
 Serial.println(analogRead(x));

  if (analogRead(x)>450 && state==0) {
       if(cont==0){
      lcd.write(12);
      lcd.print("Accesso illecito!!!");
      Serial.println("Accesso illecito");
       String postData = "{\"door\":\"Garage Door\",\"who\":\"Ladro\",\"id_house\":1}";
      String httpDest = "http://54.154.114.53/api/alarm/new";
      String httpBody = "req=" + postData;
      client.post(httpDest, httpBody);
      delay(4000);
      lcd.write(12);
    }else{
      lcd.write(12);
    }
    cont=1;
    }
      

  if (bt.available()) {
     c = (char)bt.read();
    Serial.println(c);
    lcd.write(12);

    //per i ladri cosi' entrano piu' facilmente
    /*if(c=='R'){
      setup();
    }*/



    if (c == '1') {
      cont=0;
      state = 1;
      lcd.print("Aperto ");
      lcd.print(c);
      for (pos = 0; pos <= 175; pos++) {
        myservo.write(pos);
      }


      delay(1000);
      lcd.write(12);

      // Make a HTTP request:
      //client.get("http://54.154.114.53/api/access/new");
      String postData = "{\"door\":\"Garage Door\",\"who\":\"Salvatore\",\"id_house\":1}";
      String httpDest = "http://54.154.114.53/api/access/new";
      String httpBody = "req=" + postData;
      client.post(httpDest, httpBody);
      while (client.available()) {
        char cc = client.read();
        lcd.print(cc);
      }

      delay(2000);
      lcd.write(12);

      delay(2000);
      lcd.write(12);
      lcd.print("Ingresso registrato sul server");

      delay(2000);
      lcd.write(12);

      //Serial.print(c);
    }






    if (c == '0') {
      cont=0;
      lcd.print("Chiuso ");
      lcd.print(c);
      for (pos = 175; pos >= 0; pos--) {
        myservo.write(pos);
      }
      state = 0;




      delay(1000);
      lcd.write(12);

       String postData = "{\"door\":\"Garage Door\",\"who\":\"Salvatore\",\"id_house\":1}";
      String httpDest = "http://54.154.114.53/api/exit/new";
      String httpBody = "req=" + postData;
      client.post(httpDest, httpBody);

      while (client.available()) {
        char cc = client.read();
        lcd.print(cc);
      }

      delay(2000);
      lcd.write(12);

      delay(1000);
      lcd.write(12);
      lcd.print("Uscita registrata sul server");

      delay(2000);
      lcd.write(12);


    }
  }

}
