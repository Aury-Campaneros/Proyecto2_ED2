//****************************************************************
// UVG Proyecto 2 - ED2
// Campaneros 211054
//Tiva C
//****************************************************************
//****************************************************************
// Librerías
//****************************************************************
#include <SPI.h>
#include <SD.h> 
//****************************************************************
// Definición de etiquetas
//****************************************************************
#define push1 31 //cambiar por 31 Preguntar el valor del sensor
#define push2 PF_0 //cambiar por 17
#define chipSelect PA_3 //CS de la SD
//#define NOTE_C4_1 260
//#define buzzerPin 40 //pin del Buzzer
//#define RXp2 33 //Pines para la comunicación serial 2
//#define TXp2 32 //Pines para la comunicación serial 2
//****************************************************************
// Prototipos de funciones
//****************************************************************
//void melodiaMedicion(void);
//void melodiaAlmacenar(void);

//****************************************************************
// Variables Globales
//****************************************************************
int solicitarAnterior=0; //Variable para antirevote del push1
int almacenarAnterior=0; //Variable para antirevote del push2
int comSerial=0; 
float recibir =0.00; //Recibe el valor de la temp


/*int melody[] = {         //melodia para cuando se realiza una medición
   NOTE_C4_1,NOTE_C4, NOTE_D4, NOTE_C4};
int noteDurations[] = { //Duración de la melodía1 
  4, 4, 2, 2};
int melody2[] = {         //melodia para cuando se guarda en la SD
   NOTE_AS4,NOTE_A4,NOTE_F4,NOTE_G4};
int noteDurations2[] = { //Duración de la melodía2
  4, 2, 2,2};*/
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
  SPI.setModule(0);
  Serial.begin(115200);
  Serial2.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.print("Iniciando SD");
  if (!SD.begin(chipSelect)) {
    Serial.println("Fallo al iniciar la SD");
    // don't do anything more:
    return;
  }
  Serial.println("Iniciación Exitosa de la SD");
  //Declaración de Entradas
  pinMode(push1, INPUT_PULLUP);
  pinMode(push2, INPUT_PULLUP);
}

//****************************************************************
// Loop Principal
//****************************************************************
void loop()
{
  //Parte 2 - Solicitar el valor del sensor
  //Transmición de datos
  volatile int solicitar = digitalRead(push1);
  volatile int almacenar = digitalRead(push2);
  if(solicitar==0 && solicitarAnterior==0){
    comSerial=1;
    Serial2.print(comSerial);
    Serial2.print('\n');
    //melodiaMedicion();
  }
  solicitarAnterior=solicitar;
  delay(20);
  if(solicitar==1 && almacenar==1 && solicitarAnterior==0){
    comSerial=0;
    Serial2.print(comSerial);
    Serial2.print('\n');
  }
  solicitarAnterior=solicitar;
  delay(20);

  //Recibir datos el valor de la temp
  if(Serial2.available()>0){
    recibir =Serial2.parseFloat();
  }
  

  //Parte 4 - Almacenamiento de la SD
  if(almacenar==0 && solicitar==1 && almacenarAnterior==0){
     File dataFile = SD.open("datalog.txt", FILE_WRITE);
     // escribir en el archivo del SD
     if (dataFile) {
      dataFile.println(recibir);
      dataFile.close();
      // mostrar en el monitor serial:
      Serial.println(recibir);
     }
     // Si el archivo no esta abierto mostrar un error
     else {
      Serial.println("Error al abrir el archivo datalog.txt");
      }
   }
  almacenarAnterior=almacenar;
  delay(20);
}
  
//****************************************************************
// Funciones
//****************************************************************


/*/Parte 5 - Indicador Auditivo
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
}*/
