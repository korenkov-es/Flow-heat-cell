
#include "GyverPID.h"
GyverPID regulator(2, 0, 0, 1000);

#define SETPOINT 50.0


#include <microDS18B20.h>

MicroDS18B20<A5> sensor1;


void setup() {
  Serial.begin(9600);
  
  regulator.setDirection(NORMAL); // направление регулирования (NORMAL/REVERSE). ПО УМОЛЧАНИЮ СТОИТ NORMAL
  regulator.setLimits(0, 255);    // пределы (ставим для 8 битного ШИМ). ПО УМОЛЧАНИЮ СТОЯТ 0 И 255
  regulator.setpoint = SETPOINT;
  delay(500);
}

void loop() {
  static uint32_t tmr = millis();
  static bool flag;

  sensor1.requestTemp();
  delay(750);


  regulator.input = sensor1.getTemp();
  regulator.getResultTimer();
  analogWrite(3, regulator.output);
  
  Serial.print(regulator.input);
  Serial.print(' ' );
  Serial.println(regulator.output);
  
}
