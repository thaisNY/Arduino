#include <LiquidCrystal.h>

LiquidCrystal LCD(12,11,7,6,5,4);

int SensorTempPino=0;

void setup()
{
 	// Define a quantidade de colunas e linhas do LCD
	LCD.begin(16,2);
  
}

void loop()
{
  	
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
}

//Link do Tinkercard
//https://www.tinkercad.com/things/jV1UXWIGkLB-sensor-de-t-com-tela/editel