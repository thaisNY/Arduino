// C++ code
//

#include <Servo.h>
Servo placa;
int graus;
void setup()
{
  Serial.begin(9600);
  placa.attach(3);
}

void loop()
{
  graus = map(analogRead(A5),0,1023,0,180);
  Serial.println(graus);
  delay(500);
  placa.write(graus);
}

//Link do Tinkercard
//https://www.tinkercad.com/things/ffQbYqZpwSo-controle-de-porta/editel