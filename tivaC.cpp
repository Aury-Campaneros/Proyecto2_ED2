//****************************************************************
// UVG Proyecto 2 - ED2
// Campaneros 211054
//Tiva C
//****************************************************************
//****************************************************************
// Librerías
//****************************************************************
#include <Arduino.h>
//****************************************************************
// Definición de etiquetas
//****************************************************************
#define push1 3 //cambiar por 31 Preguntar el valor del sensor
//#define push2 22 //cambiar por 17
//#define RXp2 33 //Pines para la comunicación serial 2
//#define TXp2 32 //Pines para la comunicación serial 2
//****************************************************************
// Prototipos de funciones
//****************************************************************

//****************************************************************
// Variables Globales
//****************************************************************
int solicitarAnterior=0; //Variable para antirevote del push1
int comSerial=0;
int recibir=0;           //Recibe el valor de la temp
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
  //Iniciación de la comunicación serial
  //Serial.begin(115200);
  Serial.begin(9600); //comunicación UART2
  //Declaración de Entradas
  pinMode(push1, INPUT);
  
}
//****************************************************************
// Loop Principal
//****************************************************************
void loop()
{
  //Parte 2 - Solicitar el valor del sensor
  //Transmición de datos
  volatile int solicitar = digitalRead(push1);
  if(solicitar==1 && solicitarAnterior==0){
    comSerial=1;
  }
  solicitarAnterior=solicitar;
  delay(20);
  if(solicitar==0 && solicitarAnterior==0){
    comSerial=0;
  }
  solicitarAnterior=solicitar;
  delay(20);
  Serial.print(comSerial);
  Serial.print('\n');  
  delay(200); 
  
  //Recibir datos el valor de la temp
  if(Serial.available()>0){
    recibir =Serial.parseInt();
  }

}