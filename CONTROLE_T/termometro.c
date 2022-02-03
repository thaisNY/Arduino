int vm1 = 13;
int vm2 = 12;
int vm3 = 11;
int vm4 = 10;
int vm5 = 9;

int t = 0;

void setup() {
    Serial.begin(9600);

    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(A5, INPUT);
}

void loop () {
 	t = map(((analogRead(A5) - 20) * 3.04), 0 , 1023 , -40 , 125);
    if (t == - 40) {
      digitalWrite(vm1, LOW);
      digitalWrite(vm2, LOW);
      digitalWrite(vm3, LOW);
      digitalWrite(vm4, LOW);
      digitalWrite(vm5, LOW);
    }
    if (t > - 40 && t < 125){
      digitalWrite(vm1, HIGH);
      digitalWrite(vm2, HIGH);
      digitalWrite(vm3, HIGH);
      digitalWrite(vm4, LOW);
      digitalWrite(vm5, LOW);
    }
    if (t >= 125){
      digitalWrite(vm1, HIGH);
      digitalWrite(vm2, HIGH);
      digitalWrite(vm3, HIGH);
      digitalWrite(vm4, HIGH);
      digitalWrite(vm5, HIGH);
    }
  	
  	Serial.println(t);
	delay(1000);
}

//Link do Tinkercard
//https://www.tinkercad.com/things/2obWCRD6R42-termometro2/editel