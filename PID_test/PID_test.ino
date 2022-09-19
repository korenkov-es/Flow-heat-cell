
#include "GyverPID.h"
GyverPID regulator(10, 0, 1, 1500);

#define SETPOINT 80.0


#include <microDS18B20.h>
MicroDS18B20<A4> sensor1;
MicroDS18B20<A5> sensor2;


void setup() {
  Serial.begin(9600);
  
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
  analogWrite(3, regulator.output);


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

  Serial.println(regulator.output);
  
}
