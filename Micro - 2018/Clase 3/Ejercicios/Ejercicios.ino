
#include<LiquidCrystal.h> //Library for LCD
#define btnUp 7
#define btnSet 6 
#define LED1 8
#define LED2 9
#define LED3 10
#define timeDelay 200



LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// LCD pins at which it is attached to the Arduino

bool bandera = false;
String movStr = "";
int menuEx = 1;
int menu = 1;
 
void setup() //method used to run the source for the one time onlys
{
    Serial.begin(9600);
    
    lcd.begin(16, 2);//LCD order i.e. 16 columns & 2 rows
  
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
  lcd.setCursor(0,0);//setting cursor on LCD
  lcd.clear();
  switch(menuEx){
    case 1:
      lcd.print("Target: LED_1");
      delay(timeDelay);
      break;
    case 2:
      lcd.print("Target: LED_2");
      delay(timeDelay);
      break;
     case 3:
       lcd.print("Target: LED_3");
       delay(timeDelay);
       break;
  }
  if(!bandera){
    if(!digitalRead(btnUp)) {
      if(menuEx>3){
        menuEx = 0;
      }else{
        menuEx++;
      }
    }else if(!digitalRead(btnSet)){
      bandera = true;
    }
  }
  if(bandera){
    switch(menuEx){
      case 1:
        digitalWrite(LED1,HIGH);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        break;
      case 2:
        digitalWrite(LED2,HIGH);
        digitalWrite(LED1,LOW);
        digitalWrite(LED3,LOW);
        break;
      case 3:
        digitalWrite(LED3,HIGH);
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        break;
    }
  }
}
void ejemplo3(){
  int numAleatorio = random(1,20);
  lcd.clear();
  lcd.setCursor(0,0);//setting cursor on LCD
  lcd.print("Num (1-20)");
  while(!bandera){
    if(!digitalRead(btnUp)) {
      if(menuEx>20){
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
    delay(timeDelay);
  }
  
}

