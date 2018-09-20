//#include<LiquidCrystal.h> //Library for LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define btnUp 10
#define btnSet 11 
#define LED1 12
#define LED2 13
#define LED3 9
#define timeDelay 200

//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// LCD pins at which it is attached to the Arduino
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

bool bandera = false, bandera2 = false;
String movStr = "";
int menuEx = 1;
int menu = 1;
 
void setup() //method used to run the source for the one time onlys
{
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);    
    //lcd.begin(16, 2);//LCD order i.e. 16 columns & 2 rows
  
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);

    pinMode(btnUp,INPUT_PULLUP);
    pinMode(btnSet,INPUT_PULLUP);
    menuPpal();
}
void loop() //method to run the source code repeatedly 
{
  switch(menu){
    case 1:
      ejemplo1();
      movStr = "";
      break;
    case 2:
      ejemplo2();
      bandera2 = true;
      break;
    case 3:
      ejemplo3();
      break;
  }
}
void menuPpal(){
  lcd.setCursor(0,0);//setting cursor on LCD
  lcd.print("Seleccione ejemplo");//prints on LCD  
  lcd.setCursor(0,1);//setting cursor on LCD  
  lcd.print("x=");//prints on LCD
  lcd.print(menu);
    
  while(!bandera){
    if(!digitalRead(btnUp)) {
      if(menu>2){
        menu = 1;
      }else{
        menu++;
      }
      delay(timeDelay);
      lcd.setCursor(0,1);//setting cursor on LCD  
      lcd.print("x=");//prints on LCD
      lcd.print(menu);
    }else if(!digitalRead(btnSet)){
      bandera = true;
    }
  }
  bandera = false;
  lcd.clear();
  delay(500);
}
void ejemplo1(){
  movStr = "Hola";
  for(int i=0;i<16;i++){
    lcd.setCursor(0,0);//setting cursor on LCD
    lcd.print(movStr);//prints on LCD
    movStr = " "+movStr;  
    lcd.setCursor(0,1);//setting cursor on LCD
    lcd.print("x=");//prints on LCD
    lcd.print(i);
    delay(1000);//delay of 1 sec
  }
}
void ejemplo2(){
  if(bandera2){   
  lcd.setCursor(0,0);//setting cursor on LCD
  lcd.clear();
  switch(menuEx){
          case 1:
            lcd.print("Target: LED_1");
            lcd.setCursor(0,1);
            lcd.print("Estado=");
            lcd.print(digitalRead(LED1));
            break;
          case 2:
            lcd.print("Target: LED_2");
            lcd.setCursor(0,1);
            lcd.print("Estado=");
            lcd.print(digitalRead(LED2));
            break;
           case 3:
             lcd.print("Target: LED_3");
            lcd.setCursor(0,1);
            lcd.print("Estado=");
            lcd.print(digitalRead(LED3));
             break;
    }
    bandera2 = false;
  }
    if(!digitalRead(btnUp)) {
      bandera2 = true;
      if(menuEx>2){
        menuEx = 1;
      }else{
        menuEx++;
      }
      delay(timeDelay*2);
    }else if(!digitalRead(btnSet)){
        switch(menuEx){
      case 1:
        digitalWrite(LED1,!digitalRead(LED1));
        break;
      case 2:
        digitalWrite(LED2,!digitalRead(LED2));
        break;
      case 3:
        digitalWrite(LED3,!digitalRead(LED3));
        break;
    }
    bandera2 = true;
    delay(timeDelay*2); 
    }
    
}
void ejemplo3(){
  int numAleatorio = random(1,10);
  lcd.clear();
  lcd.setCursor(0,0);//setting cursor on LCD
  lcd.print("Num (1-10)");
  lcd.setCursor(0,1);//setting cursor on LCD
  lcd.print("X=");
  lcd.print(menuEx);
  while(!bandera){
    if(!digitalRead(btnUp)) {
      if(menuEx>9){
        menuEx = 0;
      }else{
        menuEx++;
      }
      delay(timeDelay);
      lcd.setCursor(0,1);//setting cursor on LCD
      lcd.print("X=");
      lcd.print(menuEx);
    }else if(!digitalRead(btnSet)){
      bandera = true;
      delay(timeDelay);
    }
  }
  while(bandera){
    if(numAleatorio == menuEx){
      lcd.clear();
      lcd.setCursor(0,0);//setting cursor on LCD
      lcd.print(" GANASTE!!!! ");  
    }else{
      lcd.clear();
      lcd.setCursor(0,0);//setting cursor on LCD
      lcd.print(" PERDISTE ");
      lcd.setCursor(0,1);//setting cursor on LCD
      lcd.print("numeroMaquina=");
      lcd.print(numAleatorio);  
    }
    if(!digitalRead(btnUp)){
      bandera = false;
      menuEx = 1;   
      return;
    }
    delay(timeDelay);
  }
  
}

