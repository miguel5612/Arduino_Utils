int cuadro=0;
int fila=1;
int vel=200;

#include <Key.h>
#include <Keypad.h>
#include <Wire.h>
const byte ROWS = 4; //cuatro filas, definidas dependiendo del teclado
const byte COLS = 4; //cuatro columnas, definidas dependiendo del teclado


char hexaKeys[ROWS][COLS] {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
 };
byte rowPins[ROWS] = {2,3,4,5}; //pines asignados a las filas del teclado
byte colPins[COLS] = {6,7,8,9}; //pines asignados a las columnas del teclado


//inicializar una instancia d la clase New Keypad
Keypad custonKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

byte letra[8] = { B00111, B00101, B00111, B00000, B00000, B00000, B00000, B00000 }; 
int a=0;
void setup(){
  pinMode(10,OUTPUT);
  Serial.begin(9600);
}

void loop(){
 
  char tecla = custonKeypad.getKey();
  if(tecla=='1'|| a==1){
    digitalWrite(10,HIGH);
   delayMicroseconds(111); 
   digitalWrite(10,LOW);
   delayMicroseconds(889); 
   Serial.print("uno");
   a=1;
  }
  if(tecla=='2'||a==2){
  digitalWrite(10,HIGH);
   delayMicroseconds(444); 
   digitalWrite(10,LOW); 
   delayMicroseconds(556); 
   a=2;
  }
  if(tecla=='3'|| a==3){
    digitalWrite(10,HIGH);
   delayMicroseconds(777); 
   digitalWrite(10,LOW);
   delayMicroseconds(223); 
   a=3;
  }
  if(tecla=='4'|| a==4){
    digitalWrite(10,HIGH);
   delayMicroseconds(222); 
   digitalWrite(10,LOW);
   delayMicroseconds(778); 
   a=4;
  }
  if(tecla=='5'||a==5){
    digitalWrite(10,HIGH);
   delayMicroseconds(555); 
   digitalWrite(10,LOW);
   delayMicroseconds(445); 
   a=5;
  }
  if(tecla=='6'|| a==6){
    digitalWrite(10,HIGH);
   delayMicroseconds(888); 
   digitalWrite(10,LOW);
   delayMicroseconds(112); 
   a=6;
  }
  if(tecla=='7'||a==7){
   digitalWrite(10,HIGH);
   delayMicroseconds(333); 
   digitalWrite(10,LOW); 
   delayMicroseconds(667);
   a=7; 
  }
  if(tecla=='8'||a==8){
   digitalWrite(10,HIGH);
   delayMicroseconds(666); 
   digitalWrite(10,LOW); 
   delayMicroseconds(334); 
   a=8;
  }
  if(tecla=='9'||a==9){
   digitalWrite(10,HIGH);
   delayMicroseconds(999); 
   digitalWrite(10,LOW);
   delayMicroseconds(1); 
   a=9; 
  }
  
}




