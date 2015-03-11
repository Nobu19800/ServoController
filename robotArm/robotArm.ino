#include <ctype.h>
#include <string.h>
#include <Wire.h>
#include <Servo.h>



int angle[6] = {-1,-1,-1,-1,-1,-1};
int pin[6] = {3,5,6,9,10,11};
Servo servoList[6];


void receiveEvent(int howMany) 
{
     while(Wire.available()) {
         byte num = Wire.read();
         for(int i=0;i < num;i++)
         {
           byte dt = Wire.read();
            
            int a = (int)dt;
            
            if(angle[i] != a)
            {
                angle[i] = a;
                servoList[i].write(angle[i]);
            }
            
         }
        
         
   }
}

void requestEvent() 
{

}


void setup()
{
     //Serial.begin(9600);
     Wire.begin(0x8);
     Wire.onRequest(requestEvent);
     Wire.onReceive(receiveEvent);
     
     for(int i=0;i < 6;i++)
     {
       servoList[i].attach(pin[i]);
     }
}


void loop()
{
}
