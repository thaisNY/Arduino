#include <Servo.h>

#include <IRremote.h>

#include <Adafruit_NeoPixel.h>

#include <LiquidCrystal.h>

#define PIN            6
#define NUMPIXELS      12
#define SERVO A2
Servo s;
int pos = 0;
LiquidCrystal LCD(A4,A5,A3,4,3,2);
//Controle remoto
IRrecv irrecv(5);
decode_results results;

int SensorTempPino=0;
unsigned long tempo = 0;
float distancia = 0;

int LED_Ver = 7;
int LED_Vrd = 8;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
   s.attach(SERVO);
   Serial.begin(9600);
   s.write(0); // Inicia motor posição zero
  // Define a quantidade de colunas e linhas do LCD
	LCD.begin(16,2);
   //Sensor de distancia
   pinMode(LED_Vrd, OUTPUT); //LED verde
   pinMode(LED_Ver, OUTPUT); //LED vermelho
   pinMode(9, INPUT); //ECHO
   pinMode(12, OUTPUT); //TRIGGER
   pinMode(A1, INPUT); //Force sensor
   irrecv.enableIRIn(); //Controle Remoto
   //NeoPixel
   pixels.begin(); // This initializes the NeoPixel library.
   pixels.setBrightness(100); // 100/255 brightness (about 40%)
   pixels.show();             // Initialize all pixels to 'off'
   Serial.begin(9600);
  
}

void loop()
{
    //Armazena em results quando um código válido é recebido
    if(irrecv.decode(&results)){
      irrecv.resume(); //Recebe o próximo valor
    }

    //Botão 1 -> Liga os 12 LEDs em AZUL
    if(results.value == 0xFD08F7){
      //Estrutura para ligar os LEDs do neopixel
      //O FOR passa por cada LED mandando ele acender
      for(int i=0;i<=12;i++){
        //Coloca a cor nos LEDs
        pixels.setPixelColor(i, 0, 0, 255);
        pixels.show();
        //Delay para cada LED acender
        delay(10);
      }
    }

    //Botão 2 -> Liga os 12 LEDs em AMARELO 
    if(results.value == 0xFD8877){
      //Estrutura para ligar os LEDs do neopixel
      //O FOR passa por cada LED mandando ele acender
      for(int i=0;i<=12;i++){
        //Coloca a cor nos LEDs
        pixels.setPixelColor(i, 255, 255, 0);
        pixels.show();
        //Delay para cada LED acender
        delay(10);
      }
    }
   
   //Botão 8 -> Liga os 3 LEDs em AMARELO e 3 VERDE e 3 MAGENTA
   // e 3 AZUL
   if(results.value == 0xFD9867){
    //Estrutura para ligar os LEDs do neopixel
    //O FOR passa por cada LED mandando ele acender
      for(int i=0;i<=2;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 255, 255, 0);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }
     for(int i=3;i<=5;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 0, 255, 0);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }
     for(int i=6;i<=8;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 255, 0, 255);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }

     for(int i=9;i<=12;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 0, 0, 255);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }

    }

   //Botão 9 -> Liga os 2 LEDs em AMARELO e 2 VERDE e 2 MAGENTA
   // e 2 AZUL e 2 VERMELHO e 2 CIANO
   if(results.value == 0xFD58A7){
    //Estrutura para ligar os LEDs do neopixel
    //O FOR passa por cada LED mandando ele acender
      for(int i=0;i<=2;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 255, 255, 0);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }
     for(int i=2;i<=4;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 0, 255, 0);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }
     for(int i=4;i<=6;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 255, 0, 255);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }

     for(int i=6;i<=8;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 0, 0, 255);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }

     for(int i=8;i<=10;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 255, 0, 0);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }
     for(int i=10;i<=12;i++){
          //Coloca a cor nos LEDs
          pixels.setPixelColor(i, 0, 255, 255);
          pixels.show();
          //Delay para cada LED acender
          delay(10);
      }

    } 



    //Botão POWER -> Desliga o Neopixel
    if(results.value == 0xFD00FF){
      for(int i=0;i<=12;i++){
      pixels.setPixelColor(i, 0, 0, 0);
      pixels.show();
      delay(10);
      }
    }
    proximidade();

      float Temp = 0;
      Temp = medirTemperatura();
      if (Temp > 35){
          LCD.clear();
          delay(1000);
          LCD.print("Infectado");
          delay(1000);
          for(pos = 90; pos >= 0; pos--)
          {
           	s.write(pos);
            delay(15);
          }
       }
       if (Temp <= 35){

          for(pos = 0; pos < 90; pos++){
            s.write(pos);
            delay(15);
          }
       }
      //sensor de forca
      Serial.println(analogRead(A1));
      if(analogRead(A1) > 219){
          LCD.clear();
          delay(1000);
          LCD.print("ABRINDO");
          delay(1000);
      }
}
   
float medirTemperatura(){
	
  	// Faz a leitura da tensao no Sensor de Temperatura
  	float SensorTempTensao=analogRead(SensorTempPino);

  	// Converte a tensao lida
	float Tensao=SensorTempTensao*5/1024;

  	// Converte a tensao lida em Graus Celsius
	int TemperaturaC= round((Tensao-0.5)*100);
  
  	LCD.clear();
  
  	LCD.print("Temperatura:");
  
  	// Muda o cursor para a primeira coluna e segunda linha do LCD
  	LCD.setCursor(0,1);
	
  	// Imprime a temperatura em Graus Celsius
	LCD.print(TemperaturaC);
  
  	LCD.write(B10110010);
  
  	LCD.print(" C");
  	
  	// Aguarda 1 segundo
  	delay(1000);
  	return  TemperaturaC;
}

void proximidade(){
  //Acionando o TRIGGER
  digitalWrite(12,HIGH);
  delayMicroseconds(10);
  digitalWrite(12,LOW);
  
  //Calculo da distancia usando a função pulseIn();
  tempo = pulseIn(9, HIGH, 20588);
  distancia = tempo/58.0;
  Serial.println(distancia);
  
  //Se tiver algo no alcance do sensor
  if(distancia <= 40.20){
    digitalWrite(LED_Ver, HIGH);
    digitalWrite(LED_Vrd, LOW);
    
  }
  else{
    digitalWrite(LED_Ver, LOW);
    digitalWrite(LED_Vrd, HIGH);
    
  }
}

//LINK DO PROJETO NO TINKERCARD
//https://www.tinkercad.com/things/45S3dtAhj2g-2unidadefinalv2/editel