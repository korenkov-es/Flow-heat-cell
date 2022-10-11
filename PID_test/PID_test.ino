//#define PID_INTEGRAL_WINDOW 50
#include "GyverPID.h"
//GyverPID regulator(20, 0.3, 750, 1500);
//GyverPID regulator(15, 1, 100, 1500); Выходит на колебания 78-82 градуса
GyverPID regulator(15, 0.3, 100, 1500);
#define SETPOINT 80.0


#include <microDS18B20.h>
MicroDS18B20<A4> sensor2;
MicroDS18B20<A5> sensor1;


void setup() {
  Serial.begin(9600);
  Serial.println("Middle Temp, Edge Temp, Power");
  
  regulator.setDirection(NORMAL); // направление регулирования (NORMAL/REVERSE). ПО УМОЛЧАНИЮ СТОИТ NORMAL
  regulator.setLimits(0, 255);    // пределы (ставим для 8 битного ШИМ). ПО УМОЛЧАНИЮ СТОЯТ 0 И 255
  regulator.setpoint = SETPOINT;
  
  pinMode(3, OUTPUT);
  delay(500);
}

void loop() {
  
  sensor1.requestTemp();
  sensor2.requestTemp();
  delay(1000);


  regulator.input = sensor1.getTemp();

  
  regulator.getResultTimer();
  regulator.integral = constrain(regulator.integral, 0, 30);
  
   if(abs(-regulator.input + SETPOINT) <=2 ){
    analogWrite(3, regulator.output + 10);//Если сделать +30, то держится температура 84 градуса
  }else{
    analogWrite(3, regulator.output);
  }


  if (sensor1.readTemp()) {
	  Serial.print(sensor1.getTemp());
  }
  else {
	  Serial.print("Error Middle");
  }
  Serial.print(' ');

  if (sensor2.readTemp()) {
	  Serial.print(sensor2.getTemp());
  }
  else {
	  Serial.print("Error Edge");
  }
  Serial.print(' ');

  Serial.println(regulator.output
  
  );
  
}
