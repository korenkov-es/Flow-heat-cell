//#define PID_INTEGRAL_WINDOW 50
#include "GyverPID.h"

#define SETPOINT 5.0


#include <microDS18B20.h>

float temp = 0;

MicroDS18B20<A4> sensor;

char cool = 0;

void setup() {
  Serial.begin(9600);

  pinMode(9, OUTPUT);

  digitalWrite(9, HIGH);
  delay(500);
}

void loop() {

  sensor.requestTemp();
  delay(1000);
  if(sensor.readTemp()){
  temp = sensor.getTemp();
  }else{
    Serial.println("ERROR");
  }



  if (temp - SETPOINT > 0){
    digitalWrite(9, HIGH);
  }else{
    digitalWrite(9, LOW);
  }
  
  Serial.println(temp);
  


  
 
  
}
