// C++ code
//
#define vm 13
#define am 12
#define vd 11
int tempoVm = 6000;
int tempoAm = 2000;
int tempoVd = 4000;
void setup()
{
  pinMode(vm, OUTPUT);
  pinMode(am, OUTPUT);
  pinMode(vd, OUTPUT);
}

void loop()
{
  digitalWrite(vm, HIGH); // liga led vm
  delay(tempoVm); //espera tempo vm 6s
  digitalWrite(vm, LOW); //desliga vm
  digitalWrite(vd, HIGH); // liga led vd
  delay(tempoVd); //espera tempo vd 4s
  digitalWrite(vd, LOW); //desliga vd
  digitalWrite(am, HIGH); // liga led am
  delay(tempoAm); //espera tempo am 2s
  digitalWrite(am, LOW); //desliga am
 
}
//Link do Tinkercard
//https://www.tinkercad.com/things/3PGZ0SWYKyV-semaforo/editel