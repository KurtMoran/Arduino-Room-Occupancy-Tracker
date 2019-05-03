#include <Ultrasonic.h>
#include <EEPROM.h>

int pos = 0;
int piezoPin=13;
int finalpos=0;
int countL=0;
int initialpos=0;
int distL=0;
int distR=0;
int countR=0;
int tonePin=9;
int personCount=0;
int EEPROMSIZE=1024;
const unsigned long period=120000;
unsigned long currentMillis=0;
unsigned long startMillis=0;
int addr=0;
byte value;
/*
 * Pass as a parameter the trigger and echo pin, respectively,
 * or only the signal pin (for sensors 3 pins), like:
  Ultrasonic ultrasonic(13); */
 ////////////////////////you may need to switch the two numbers below////////////////////////
Ultrasonic ultrasonicL(8, 7); // (trigger, echo)
Ultrasonic ultrasonicR(6, 5);
void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(tonePin, OUTPUT);
startMillis = millis();
}

void loop() {
    // Pass INC as a parameter to get the distance in inches
    while(true){
      //tone(tonePin, 440, 100);
      currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
      if (currentMillis - startMillis >= period)  //test whether the period has elapsed
      {
         EEPROM.write(addr, personCount);
         
         Serial.print("The number of people in the room at minute " );
         Serial.print(currentMillis/60000);
         Serial.print(" changed from ");
         Serial.print(value, DEC);
         value = EEPROM.read(addr);
         Serial.print(" to ");
         Serial.print(value, DEC);
         Serial.println();
         addr+=1; 
         startMillis = currentMillis;  //IMPORTANT to save the start time of the current state.
      }
      distL= ultrasonicL.distanceRead();
      distR= ultrasonicR.distanceRead();
      delay(20);
      if(distL<100 and distL!=0){
        countL+=1;
        delay(500);
        Serial.println("countL went up to");
        Serial.println(countL);
    }
    if(distR<100 and distR!=0){
        countR+=1;
        delay(500);
        Serial.println("countR went up to");
        Serial.println(countR);
    }
    if(distL>100 or distL==0){
      countL=0;
      //Serial.println("count was reset");
    }
    if(distR>100 or distR==0){
      countR=0;
      //Serial.println("count was reset");
    }

    if(countL>countR){
      personCount+=1;
      Serial.println("Number of people in the room is ");
      Serial.print(personCount);
      tone(tonePin, 440, 100);
      delay(1500);
      countL=0;
      countR=0;
      break;
    }
    if(countL<countR){
      personCount-=1;
      Serial.println("Number of people in the room is ");
      Serial.print(personCount);
      tone(tonePin, 800, 100);
      delay(1500);
      countR=0;
      countL=0;
      break;
    }
    /*if(count==1){
      personCount+=1;
      Serial.println("Number of people in the room is ");
      Serial.print(personCount);
      tone(tonePin, 440, 100);
      delay(1000);
      count=0;
      break;
    }*/
    }
    
}  
