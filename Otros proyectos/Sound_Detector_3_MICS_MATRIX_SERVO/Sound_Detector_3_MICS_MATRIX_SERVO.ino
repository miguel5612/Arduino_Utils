//Circuito detector de sonido
// V1.0
// Este circuito detecta de donde proviene el sonido con 3 sensores de audio y con un servomotor indica de donde provino el ultimo audio escuchado.
// Conectar los 3 sensores a los pines A0, A1, A2 y el servo motor en el pin 2.
// Se puede conectar una matrix 8x8 a los pines 11,12,13 para visualizar graficamente el punto.

//emtradas de audio a 90 grados de separacion cada una

#include "LedControl.h"
#include "binary.h"
#include <Servo.h>

int mic1 = A1;
int mic2 = A2;
int mic3 = A0;

//diferencia a la que se considera un cambio en los sensores de audio

#define diferencia 10

// Incremento en grados del servomotor

#define servoIncremento 10

//Salida del servomotor

#define servo 2

//Matrix led

#define din 13
#define cs 12
#define clk 11

// Tiempo de refresco

#define delayTime 2000

// Codigo en binario ejemplo

// happy face
byte hf[8]= {B00111100,B01000010,B10100101,B10000001,B10100101,B10011001,B01000010,B00111100};

byte binarios[8] = {1,2,4,8,16,32,64,128};
// Matrix LCD 8x8 library
                       //Din,CS,CLK
LedControl lc=LedControl(13,11,12,1);

//Servo motor

Servo myservo;  // create servo object to control a servo


int micData = 0,mic1Read = 0, mic2Read = 0, mic3Read = 0;
int row = 4, col = 4; //ubicacion del led que esta encendido
int pos = 0; //posicion del servo

void setup() {
  
  //Servo motor

    myservo.attach(servo);  // attaches the servo on pin 9 to the servo object
    myservo.write(0);              // tell servo to go to position in variable 'pos'
    
  //puerto serie
  
  Serial.begin(9600);

  //Pantalla
   lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,8);
  // Clear the display
  lc.clearDisplay(0); 

  caraFeliz();
  
  // put your setup code here, to run once:
  pinMode(mic1Read,INPUT_PULLUP);
  pinMode(mic2Read,INPUT_PULLUP);
  pinMode(mic3Read,INPUT_PULLUP);

  delay(delayTime);
}

void loop() {
  serialMSG(); //Aqui se envia por puerto serie las lecturas y se almacenan en las variables
  readMics(); // Esta funcion lee los microfonos y guarda en las variables la ubicacion del cursor
  refrescarMatriz(); //Aqui se mueve el punto
  refrescarServo(); //Aqui se ubica el servo
  delay(delayTime/50);
  // put your main code here, to run repeatedly:

}
void refrescarServo()
{
  if(pos>180){pos =0 ;} //cuando hay un error en la variable
  myservo.write(pos);
  Serial.print("POSICION: ");
  Serial.println(pos);
}
void readMics()
{
  /*
  Serial.println("MICRREAD");
  Serial.print(mic1Read);
  Serial.println("  ");
  Serial.print(mic2Read);
  Serial.println("  ");
  Serial.print(mic3Read);
  Serial.println("  ");
  */
  
  if((abs(mic1Read-mic2Read)<= diferencia && (abs(mic1Read-mic2Read)>0)) && (abs(mic1Read-mic3Read)<=diferencia && abs(mic1Read-mic3Read)>0)){
    //el punto sube
    if(pos>=90){pos=100;} //en caso que el servo este lejos}
    if(pos>0){pos-= servoIncremento;} //El sonido proviene del sensor 1
    row++;
    Serial.println("MIC1----------------");
    if(row>=8){row = 0;}    
  }
  if((abs(mic2Read-mic3Read)<=diferencia && abs(mic2Read-mic3Read)>0) && (abs((mic2Read-mic1Read)<=diferencia) && abs((mic2Read-mic1Read))>0)){
    //el punto baja
    if(pos<=90){pos=80;} //en caso que el servo este lejos}
    if(pos<90){pos+= servoIncremento;} //El sonido proviene del sensor 2
    col++;
    Serial.println("MIC2---------------");
    if(col>=8){col = 0;}    
  }
  if((abs(mic3Read-mic1Read)<=diferencia && abs(mic3Read-mic1Read)>0) && (abs(mic3Read-mic2Read)<=diferencia && abs(mic3Read-mic2Read) >0)){
    //el punto va a la izquierda
    if(pos<=90){pos=100;} //en caso que el servo este lejos}
    if(pos<90){pos+=servoIncremento*2;} // El sonido proviene del sensor 3
    else if(pos<180){pos+=servoIncremento;} // El sonido proviene del sensor 3
    row-=1;
    Serial.println("MIC3---------------");
    if(row<=0){row = 8;}    
  }
}
void refrescarMatriz()
{
  Serial.print("COL: ");
  Serial.println(col);
  Serial.print("ROW: ");
  Serial.println(row);
  lc.clearDisplay(0);
  lc.setRow(0,col,binarios[row]);
}
void caraFeliz()
{
    // Display happy face
  lc.setRow(0,0,hf[0]);
  lc.setRow(0,1,hf[1]);
  lc.setRow(0,2,hf[2]);
  lc.setRow(0,3,hf[3]);
  lc.setRow(0,4,hf[4]);
  lc.setRow(0,5,hf[5]);
  lc.setRow(0,6,hf[6]);
  lc.setRow(0,7,hf[7]);
}
void serialMSG()
{
  Serial.println("--------------------");
  mic1Read = readSerial(mic1);
  mic2Read = readSerial(mic2);
  mic3Read = readSerial(mic3);
  Serial.println("--------------------");
  
}

int readSerial(int pin)
{
  Serial.print("Leyendo el pin: ");
  Serial.print(pin);
  Serial.print("  Valor: ");
  micData = analogRead(pin);
  Serial.println(micData);
  return micData;
}

