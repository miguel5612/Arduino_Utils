#include<LiquidCrystal.h> //Library for LCD
#include <Keypad.h>
#include <EEPROM.h>

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
#define motorPin 8
#define delChar '*'
#define okChar '#'
#define timeDelay 200
#define address 0




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
String movStr = "", password,inPassword, velocidadStr;
int menuEx = 1;
int menu = 1,velocidad;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() //method used to run the source for the one time onlys
{
    Serial.begin(9600);    
    lcd.begin(16, 2);//LCD order i.e. 16 columns & 2 rows
    
    pinMode(btnUp,INPUT_PULLUP);
    pinMode(btnSet,INPUT_PULLUP);
    pinMode(motorPin,OUTPUT);
    digitalWrite(motorPin,LOW);
    lcd.print("ALLL OK");
    delay(1000);
    lcd.clear();
    password = EEPROM.read(address);
    
    velocidad = 0;
    velocidadStr = "";
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
  inPassword = "";
  char key = keypad.getKey();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press #");
  if(key == delChar){
    key = keypad.getKey();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("** Nueva clave **");
    lcd.setCursor(0,1);
    lcd.print("N=");
    password = "";
    while(key!=delChar){
      key = keypad.getKey();      
      if(key!=NO_KEY){
       lcd.print(key);
       password+=key;  
      }
    }
    EEPROM.write(address,password.toInt());
  }if(key == okChar){
    key = keypad.getKey();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("** Escriba clave # **");
    lcd.setCursor(0,1);
    lcd.print("N=");
    while(key!=okChar){
      key = keypad.getKey();      
      if(key!=NO_KEY){
       lcd.print(key); 
       inPassword+=key;  
      }
    }
    if(inPassword == password){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ingreso exitoso");
    }else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ingreso fallido");  
    }
  }
}
void ejemplo3(){
    char key = keypad.getKey();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Write");
  lcd.setCursor(0,1);
  lcd.print("V= ");
  lcd.print(velocidad);
  if(key!=NO_KEY){
       lcd.print(key); 
       velocidadStr+=key;  
       velocidad = velocidadStr.toInt();
       if(velocidad>255){
          velocidad = 0;
          velocidadStr = "";
          lcd.clear();
       }
  }
  analogWrite(motorPin, velocidad);  
}

