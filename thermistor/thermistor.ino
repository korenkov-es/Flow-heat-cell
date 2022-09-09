
// один датчик лучше читать без адресации, это сильно экономит память
#include <microDS18B20.h>
//#include "GyverPID.h"
//GyverPID regulator(0.1, 0.05, 0.01, 10);// коэф. П, коэф. И, коэф. Д, период дискретизации dt (мс)
MicroDS18B20<A4> sensor1;
MicroDS18B20<A5> sensor2;
const int Led = 3;
float T1 = 0;
float T2 = 0;
float Setpoint = 60;
float power = 100;


void setup() {


  
  Serial.begin(9600);
  pinMode(Led, OUTPUT);
}
void loop() { 
              // читаем с датчика температуру
  //regulator.input = T1;   // сообщаем регулятору текущую температуру

  // getResultTimer возвращает значение для управляющего устройства
  // (после вызова можно получать это значение как regulator.output)
  // обновление происходит по встроенному таймеру на millis()


  analogWrite(Led,power);
  sensor1.requestTemp();
  sensor2.requestTemp();
  

  delay(1000);
  

  if (sensor1.readTemp()){ 
    T1 = sensor1.getTemp();
  } else Serial.println("error_A4");

  if (sensor2.readTemp()){ 
    T2 = sensor2.getTemp();
    
  } else Serial.println("error_A5");

  Serial.print("Power value: ");
  Serial.println(power);
  Serial.print("Middle temp (A4): ");
  Serial.println(T1);
  
  Serial.print("Edge temp (A5): ");
  Serial.println(T2);
  Serial.println();
}
