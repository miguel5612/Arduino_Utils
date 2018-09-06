#include<LiquidCrystal.h> //Library for LCD
#include <Keypad.h>

#define btnUp 7
#define btnSet 6
#define F1 22
#define F2 23
#define F3 24 
#define F4 25
#define C1 26
#define C2 27
#define C3 28
#define C4 29
#define delChar '*'
#define timeDelay 200




LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// LCD pins at which it is attached to the Arduino

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] =
{{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
int count, countBytes;
byte rowPins[ROWS] = {F1, F2, F3, F4};
byte colPins[COLS] = {C1, C2, C3};

bool bandera = false;
String movStr = "";
int menuEx = 1;
int menu = 1;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() //method used to run the source for the one time onlys
{
    Serial.begin(9600);
    
    lcd.begin(16, 2);//LCD order i.e. 16 columns & 2 rows
  

    pinMode(btnUp,INPUT_PULLUP);
    pinMode(btnSet,INPUT_PULLUP);
    lcd.print("ALLL OK");
    delay(1000);
    lcd.clear();
    //menuPpal();
}
void loop() //method to run the source code repeatedly 
{
  
  /*
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
  */
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
  char key = keypad.getKey();
  if(key == delChar){
    lcd.clear();
    count = 0;countBytes = 0;
    lcd.setCursor(0,0);
  }
  else if (key != NO_KEY)
  {
    count++;
    countBytes++;
    if (countBytes==17)
    {
      lcd.setCursor(0,1);
      lcd.print(key);
      countBytes = 17;
      count = 0;
    }
    else if (countBytes == 33){
      lcd.setCursor(0,0);
      lcd.print(key);
      count= 1;
      countBytes = 1;
    }else{
      lcd.print(key);
      Serial.print("Count: ");
      Serial.println(count);
      Serial.print("CountBytes: ");
      Serial.println(countBytes);
    }
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
    /*
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
    */
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

