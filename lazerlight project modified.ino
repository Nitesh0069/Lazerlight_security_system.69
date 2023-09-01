/* CODE WRITEN BY NITESH KUMAR TIME :27 DAYS
   This program here is for laser light security system completed at 25 - nov - 2022, for ST.Claret 2nd puc
   JUST STARTED ON 25-5-2023
   this is 28-7-2023 where some coments where done again at the time of of display of the program*/



#include <SoftwareSerial.h>
SoftwareSerial MyBlue(4,3);// RX | TX
int flag = 0; // its is a variable that takes boolean variables ie. true ot fales | 0 or 1
int ldrPin = 7;// Digital reciver from LDR 1 module 
int ldrPin2 = 6; //Digital reciver from LDR 2 module
int buzz1 = 13; //Buzzer 1 which responed based on LDR's signal
int buzz2 = 12; //Buzzer  which responds based on smoke module 
int laserPin = 5; // lasermodule which can be operated by using bluetooth application 
int p =9000; // delay using millis
int p1 = 900;// delay using millis
//int p2 = 9900;// delay using millis
int smokeA0= A0; //Analog singnal from smoke module
int sensorThres = 300; // Sensi of Somke Module Can be adjusted according the size of room. use of smoke sencor is recomended only if its used in room.
unsigned long timenow = 0; //counts the time in milliseconds from the time the program in ON
const unsigned buzzon = 350; // by using millis we are giving delay to buzz1 at startup to avoid over laping of the sound


void setup()
 {
  pinMode(laserPin,OUTPUT); // this section if pintype input or output
  pinMode(buzz1,OUTPUT);
  pinMode(buzz2,OUTPUT);

  pinMode(smokeA0,INPUT);
  pinMode(ldrPin,INPUT);
  digitalWrite(laserPin,HIGH);
  Serial.begin(9600);// its is a bit rate at which Arduino talks to PC | phone | other PROGRAMABLE devicies
  Serial.println("Ready to recive Comands\nType 'A' and 'B' to on and off the laser");
  MyBlue.begin(38400); // its is a bit rate at which HC 05 talks to PC | phone | other BLUETOOTH devicies
  MyBlue.println("Ready to recive Comands\nType 'A' and 'B' to on and off the laser");
} 


  void loop()
 {   
    
  
        if (MyBlue.available()) // to check availability of bluethooth module.          /* THIS SET OF CODE HERE IT CONTROL LASER ON AND OF BY SENDING 'A' TO AND 'B' TO OFF USING HC 05 MODULE*/
             flag = MyBlue.read();   //reading the input from bluetooth                                   
             if (flag == 'A') 
                 { 
                   digitalWrite(laserPin, HIGH); //default startup of lazers is on.
                   MyBlue.println("Laser ON"); //output in terminal
                 } 
        else  if (flag == 'B') 
                { 
                 digitalWrite(laserPin, LOW);//low after sending B 
                 
                 MyBlue.println("Laser OFF"); // printing low in terminal
                }
                  
   
   if ( digitalRead(ldrPin) == 1)                                /*THIS HERE IS TO TRIGGER THE BUZZER 1 USING LDR1*/
      
    
     { if ( millis()> buzzon )
        
        digitalWrite(buzz1, HIGH);
        MyBlue.println("Someone is in here");

        timenow = millis();

        while (millis()< timenow + p);}
         
      
    else 
      { 
      digitalWrite (buzz1, LOW);
      } 
        


        if ( digitalRead(ldrPin2) == 1)                            /*THIS HERE IS TO TRIGGER THE BUZZER 1 USING LDR2*/
      
    
     { if ( millis()> buzzon )
        
        digitalWrite(buzz1, HIGH);
        MyBlue.println("Someone is in here");

        timenow = millis();

        while (millis()< timenow + p);}
         
      
    else 
      { 
      digitalWrite (buzz1, LOW);
      } 
           // if (flag =='N');noTone(13);{timenow = millis();  IGNORE THIS 98 AND 100 LINE SINCE I AM NOT ABLE TO FIND IT OUT found it on 28-7-2023. it was to delay the startup of smoke sensor.

           // while (millis()< timenow + p2);}
      
  



      int analogSensor = analogRead(smokeA0);           /*THIS IS SMOKE SENSOR TO AVOID SMOKE IN THE ROOM*/
      if (analogSensor > sensorThres)

             { 

              digitalWrite(buzz2, HIGH);
              MyBlue.println("Smoke Detected") ;
              
              timenow = millis();

                    while (millis()< timenow + p1);}

       else   {

               digitalWrite (buzz2, LOW);
            
              }
    
    
                         
  }
	   