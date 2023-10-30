//****************************************************************
// UVG Proyecto 2 - ED2
// Campaneros 211054
//Tiva C
//****************************************************************
//****************************************************************
// Librerías
//****************************************************************
#include <Arduino.h>
#include <SPI.h>
#include <SD.h> 
#include "pitches.h"
//****************************************************************
// Definición de etiquetas
//****************************************************************
#define push1 23 //cambiar por 31 Preguntar el valor del sensor
#define push2 22 //cambiar por 17
#define chipSelect 5 //CS de la SD
#define NOTE_C4_1 260
#define buzzerPin 40 //pin del Buzzer
//#define RXp2 33 //Pines para la comunicación serial 2
//#define TXp2 32 //Pines para la comunicación serial 2
//****************************************************************
// Prototipos de funciones
//****************************************************************
void melodiaMedicion(void);
void melodiaAlmacenar(void);
void escribirSD(int almacenarSensor);
//****************************************************************
// Variables Globales
//****************************************************************
int solicitarAnterior=0; //Variable para antirevote del push1
int almacenarAnterior=0; //Variable para antirevote del push2
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
  //Declaración de Entradas
  pinMode(push1, INPUT);
  //declaración de salidas
  pinMode(buzzerPin, OUTPUT);
  pinMode(chipSelect, OUTPUT);

  //Iniciación de la comunicación serial
  Serial.begin(115200) //Comunicación UART0
  Serial2.begin(115200); //comunicación UART2
  Serial.println("Almacenamiento SD");
  Serial.println("Inicializando la tarjeta SD. . .");
  if(!SD.begin(chipSelect)){   // Inicializar la SD 
    Serial.println("¡Inicialización fallida!");
    return;
  }
  Serial.println("Inicialización realizada.");
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
    Serial2.print(comSerial);
    Serial2.print('\n');
    melodiaMedicion();
  }
  solicitarAnterior=solicitar;
  delay(20);
  if(solicitar==0 && solicitarAnterior==0){
    comSerial=0;
    Serial2.print(comSerial);
    Serial2.print('\n');
  }
  solicitarAnterior=solicitar;
  delay(20);

  //Recibir datos el valor de la temp
  if(Serial.available()>0){
    recibir =Serial2.parseInt();
  }

  //Parte 4 - Almacenamiento de la SD
  volatile int almacenar = digitalRead(push2);
  if(almacenar==1 && almacenarAnterior==0){
    escribirSD("/medicion_temp.txt");
    melodiaAlmacenar();
  }
  almacenarAnterior=almacenar;
  delay(20);
}
  
//****************************************************************
// Función para configurar módulo PWM
//****************************************************************
//Función para la parte 4
void escribirSD(int almacenarSensor) // Función para escribir en un archivo de la SD
{
  int comandos=0;
  Serial.println("*******Almacenando la medición del sensor*******");
   comandos += recibir + "\n"; // // Añade un salto de línea después de cada línea ingresada
  //Escribe la información en un nuevo archivo
  myFile2 = SD.open(almacenarSensor, FILE_WRITE);
  if(myFile2){
    
    myFile2.println(comandos);
    //Cerrar el archivo
    myFile2.close();
    Serial.println("Medición Almacenada con Exito");
  }
  else{
    //Si no se puede guardar la imagen, imprima un error
    Serial.print("Error al tratar de almacenar su medición");
  }
}


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
