//****************************************************************
// UVG Proyecto 2 - ED2
// Campaneros 211054
//Tiva C
//****************************************************************
//****************************************************************
// Librerías
//****************************************************************
#include <Arduino.h>
#include "pitches.h"
//****************************************************************
// Definición de etiquetas
//****************************************************************
#define push1 23 //cambiar por 31 Preguntar el valor del sensor
#define push2 22 //cambiar por 17
#define NOTE_C4_1 260
#define buzzerPin 40 //pin del Buzzer
//#define RXp2 33 //Pines para la comunicación serial 2
//#define TXp2 32 //Pines para la comunicación serial 2
//****************************************************************
// Prototipos de funciones
//****************************************************************
void melodiaMedicion(void);
void melodiaAlmacenar(void);
//****************************************************************
// Variables Globales
//****************************************************************
int solicitarAnterior=0; //Variable para antirevote del push1
int comSerial=0;
int recibir=0;           //Recibe el valor de la temp

int melody[] = {         //melodia para cuando se realiza una medición
   NOTE_C4_1,NOTE_C4, NOTE_D4, NOTE_C4};
int noteDurations[] = { //Duración de la melodía1 
  4, 4, 2, 2};
int melody2[] = {         //melodia para cuando se guarda en la SD
   NOTE_AS4,NOTE_A4,NOTE_F4,NOTE_G4};
int noteDurations2[] = { //Duración de la melodía2
  4, 2, 2,2};
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
  //declaración de salidas
  pinMode(buzzerPin, OUTPUT);
  
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
    Serial.print(comSerial);
    Serial.print('\n');
    melodiaMedicion();
  }
  solicitarAnterior=solicitar;
  delay(20);
  if(solicitar==0 && solicitarAnterior==0){
    comSerial=0;
    Serial.print(comSerial);
    Serial.print('\n');
  }
  solicitarAnterior=solicitar;
  delay(20);

  //Recibir datos el valor de la temp
  if(Serial.available()>0){
    recibir =Serial.parseInt();
  }
  
}
  
//****************************************************************
// Función para configurar módulo PWM
//****************************************************************
//Parte 5 - Indicador Auditivo
void melodiaMedicion(void) //Función para el indicador auditivo de la medición del sensor
{
  for (int thisNote = 0; thisNote < 4; thisNote++) {
    int noteDuration = 1000/noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration + 50;     //delay between pulse
    delay(pauseBetweenNotes);
    noTone(buzzerPin);         // stop the tone playing
  }
}
void melodiaAlmacenar(void) //Función para el indicador auditivo para el almacenamiento en la SD
{
  for (int thisNote1 = 0; thisNote1 < 4; thisNote1++) {
    int noteDuration1 = 1000/noteDurations2[thisNote1];
    tone(buzzerPin, melody2[thisNote1],noteDuration1);
    int pauseBetweenNotes1 = noteDuration1 + 50;     //delay between pulse
    delay(pauseBetweenNotes1);
    noTone(buzzerPin);         // stop the tone playing
  }
}
