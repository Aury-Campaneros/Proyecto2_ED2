//****************************************************************
// UVG Proyecto 2 - ED2
// Campaneros 211054
// ESP32
//****************************************************************
//****************************************************************
// Librerías
//****************************************************************
#include <Arduino.h>
//****************************************************************
// Definición de etiquetas
//****************************************************************
#define RXp2 16 //Pines para la comunicación serial 2
#define TXp2 17 //Pines para la comunicación serial 2
//****************************************************************
// Prototipos de funciones
//****************************************************************

//****************************************************************
// Variables Globales
//****************************************************************
volatile int sensor=0;  //Lectura del sensor
float temp=0;  //guarda la conversión del sensor de temperatura
int solicitar=0;

//****************************************************************
// ISR: Interrupciones
//****************************************************************
// void IRAM_ATTR ISR(){
//
//}
//****************************************************************
// Configuración
//****************************************************************
void setup()
{
  Serial.begin(115200);
  Serial2.begin(9600); //PASAR DE 9600 A 115200 para comunicación UART2
  //Declaración de Entradas
  pinMode(34, INPUT); //Entrada del sensor
}
//****************************************************************
// Loop Principal
//****************************************************************
void loop()
{
  //Parte 1 - Comunicación con el Sensor y el ESP32
   sensor=analogRead(34);   //lectura del sensor
   temp = ((sensor*3.3/4096)*(1/0.1))+20;   //conversicón de temp.
   //Parte 2 - Comunicación UART Compu y Tiva
   //Recibir datos
   if(Serial2.available()>0){
    solicitar =Serial2.parseInt();
  }
  //Transmitir datos
  if(solicitar==1){
    Serial.println(temp);
    Serial2.print(temp);
    Serial2.print('\n');
  }
  if(solicitar==0){
    Serial.println(0);
    Serial2.print("");
    Serial2.print('\n');
  }
  
}
//****************************************************************
// Funciones
//****************************************************************
