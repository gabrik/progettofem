    #include <SoftwareSerial.h>
 
 
    
    
    const int btBoud = 115200;
    const int pinBtTx = 11;
    const int pinBtRx = 10;
    const int pinLed = 13;
    
    SofwareSerial bt(pinBtRx,pinBtTx);
    
    
    void setup()  
    {  
         
     Serial.begin(9600);
     while(!Serial);
     
     bt.begin(9600);
     while(!bt);
      
     pinMode(pinLed,OUTPUT);
    
    }  
      
    void loop() 
    {  
     if(bt.available()){
       char c = (char)bt.read();
       if(c=='H')
         digitalWrite(pinLed,HIGH);
       if(c=='L')
         digitalWrite(pinLed,LOW);
     } 
       
    }  
