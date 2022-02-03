#include <LiquidCrystal.h>

LiquidCrystal LCD(12,11,7,6,5,4);

int SensorTempPino=0;
int buzzer = 8; //Pino ao qual o buzzer está ligado
void setup()
{
 	// Define a quantidade de colunas e linhas do LCD
	LCD.begin(16,2);
  	pinMode(buzzer,OUTPUT);
  
}

void loop()
{
  	
// Faz a leitura da tensao no Sensor de Temperatura
	float SensorTempTensao=analogRead(SensorTempPino);

  	// Converte a tensao lida
	float Tensao=SensorTempTensao*5/1024;

  	// Converte a tensao lida em Graus Celsius
	int TemperaturaC= round((Tensao-0.5)*100); //temperatura
  
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
  	if (TemperaturaC > 36){
    	LCD.print("Infectado");
      	tone(buzzer,293);             
    	delay(200);    
    	noTone(buzzer);
    }
}
//Link do Tinkercard
//https://www.tinkercad.com/things/e69s8WZVqaW-projeto1/editel