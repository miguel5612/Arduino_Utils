/*
 
 El mensaje de la pantalla de desplazamiento debe ser enviado delimitado por paréntesis.
 Esto lo explicaremos paso a paso en el tutorial
/p para pausar el desplazamiento. El envío de nuevo se reanuda el desplazamiento.
/<Para desplazarse más rápido
/> Para desplazarse más lenta
/+ Para aumentar el nivel de brillo
/-  Para disminuir el nivel de brillo
/e  para borrar la pantalla
 
 Connexiones:
 Max 7219                 Arduino
 VCC                      +5V
 DIN                      MOSI (Pin 11)
 LOAD                     pinCS(Pin 10)
 CLK                      SCK  (Pin 13)
 GND                      Gnd
 NO OLVIDES VISITAR Y DALE ME GUSTA A: https://www.facebook.com/arduinoquindio/
*/


//Librerias utilizadas
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 10; //Pin CS  de la Matrix va al PIN 10 de ARDUINO
int numberOfHorizontalDisplays = 8;//Numero de Matrices ubicadas horizontalmente utilizadas en el letrero
int numberOfVerticalDisplays = 1;//Numero de Matrices ubicadas verticalmente utilizadas en el letrero

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);
int scrollspeed = 200; 

int spacer = 1;  // Espacio entre caracteres
int width = 5 + spacer; // Ancho de cada letra 5 pixeles
boolean inChar = false, NewData = false, pause = false;
boolean dataAvailable = false;
char inputString[512] ;
int count = 0, BTvalue = 5;


void setup() {

  matrix.setIntensity(1); //Numero que se varía pa cambiar la intensidad de los led

// Ajuste de la posicion de cada Matrix
  matrix.setPosition(0, 7, 0); 
  matrix.setPosition(1, 6, 0); 
  matrix.setPosition(2, 5, 0); 
  matrix.setPosition(3, 4, 0); 
  matrix.setPosition(4, 3, 0);
  matrix.setPosition(5, 2, 0);
  matrix.setPosition(6, 1, 0); 
  matrix.setPosition(7, 0, 0); 
 
  
  //  ...
    matrix.setRotation(0, 3);    
  matrix.setRotation(1, 3);   
  matrix.setRotation(2, 3);    
  matrix.setRotation(3, 3);   
  
  matrix.fillScreen(0);
  matrix.write();
  Serial.begin(9600); // Inicializamos la comunicación serial
  
  // Usamos la Interrupcion cero del pin D2
  //pinMode(2, INPUT);
  //digitalWrite(2, LOW);
  //attachInterrupt(0, serialInterrupt, CHANGE);
  
}

void loop(){

 if(dataAvailable){
  NewData = true;
  display_data();
 }  
 if ( Serial.available() ) {
    // read the character and do what you need 
    serialInterrupt();
    return; // just runs loop() again immediately
  }
 
}

void display_data(){
  for ( int i = 0 ; i < width * count + matrix.width() - 1 - spacer; i++ ) {

    matrix.fillScreen(0);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; 

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < count ) {
        matrix.drawChar(x, y, inputString[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }
    matrix.write(); // Enviamos el mapa de bits a las Matrices
    if(!dataAvailable){
      i = width * count + matrix.width() - 1 - spacer; 
      matrix.fillScreen(LOW);
      matrix.write();
    }
    if(NewData){
      i = 0; 
      matrix.fillScreen(LOW);
      matrix.write();
      NewData = false;
    }
    while(pause == true){
      delay(1);
    } 
    
    delay(scrollspeed);
  }
}


volatile boolean inService = false;

void serialInterrupt(){
  
  
  if (inService) return;

 
  inService = true;
  //interrupts();
  while(!Serial.available());
  while (Serial.available()) {
     char ch = Serial.read();
    
     if(ch =='('){
       count = 0;
       inChar = true;
       
       while(inChar){
         if (Serial.available()) {
           ch = Serial.read();
           if(ch == ')'){
             inChar = false;
             dataAvailable = true;
            } else{
             inputString[count] = ch;
             count++;
           }
           if(count > 0) {
             NewData = true;
           }
         }
       }
     }  
     
     if(ch =='/'){  
      
       inChar = true;
       while(inChar){
         if (Serial.available()) {
           ch = Serial.read();
           // '/+' Incrementa el brillo
           if(ch == '+'){
             if(BTvalue < 15) {
               BTvalue ++;
               matrix.setIntensity(BTvalue);
              }
             break;
           }  
           // '/-' decrementa el brillo         
           if(ch == '-'){
            if(BTvalue > 0){
             BTvalue --;
             matrix.setIntensity(BTvalue);
            }
            break;
           }    

           // '/>' baja la velocidad de las letras
           if(ch == '>'){
            
             if(scrollspeed < 500) {
               scrollspeed = scrollspeed + 50;
             }
             break;
           }  
           // '/<' sube a velocidad de las letras          
           if(ch == '<'){
            
            if(scrollspeed > 50){
             scrollspeed=scrollspeed-50;
            }
            break;
           }   

           // '/e' limpia las matrices        
           if(ch == 'e'){
            
            dataAvailable = false;
             break; 
           }
           
           // '/p' ipausa el mensaje      
           if(ch == 'p'){
            
             if(pause == false){
               pause = true;
             } 
             else {
               pause = false;
             } 
             break; 
           }
           
           else {
            
            break;  
           }
           
           
         }
       }
     }  

    
  }  
  
  inService = false;
}
