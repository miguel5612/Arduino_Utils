#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad
int selectedMenu = 0;
int counter = 0;

LiquidCrystal_I2C lcd(0x3F, 16, 2);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("A-Write B-Game");
}

void loop() {
  reconocer();
  // put your main code here, to run repeatedly:
  if(selectedMenu!=0 && selectedMenu==1){
    writeLetters();
  }else if(selectedMenu!=0 && selectedMenu==2){
    gameRandomNumber();
  }
}
void gameRandomNumber(){  
  lcd.setCursor(0,0);
  lcd.print("Write and C for exit");
  char key = keypad.getKey();
  int numberUnit,numberDec;
  if(counter<1 and key!='C' and key){
    numberUnit = Serial.print(atoi(&key));
    Serial.println(numberUnit);
    counter+=1;
    lcd.setCursor(counter,1);
    lcd.print(key); 
    delay(500);
  }else if(counter>=1 && counter<2){
    numberDec = (int)key;
    Serial.println(numberDec);
    counter+=1;
    lcd.setCursor(counter,1);
    lcd.print(key); 
    delay(500);
  }else if(key=='C'){counter=2;Serial.println("C PRESSED");} 
  else if(counter==2){
    lcd.clear();
    int number1;
    if(counter<=1){number1 = numberUnit;}
    else{number1 = numberUnit*10+numberDec;}
    Serial.print("TU KEY:   ");
    Serial.println(key);
    Serial.print("TU NUMERO ESCRITO: ");
    Serial.println(number1);
    Serial.print("TU COUNTER");
    Serial.println(counter);
    int randomNumber = random(0,10);
    if (number1<=10 and number1 == randomNumber and counter>0){
      lcd.clear();
      lcd.print("GANASTE");
      lcd.setCursor(0,1);
      lcd.print(number1);
      counter = 0;
    }else if(counter>0){
      lcd.clear();
      lcd.print("Perdiste");
      lcd.setCursor(0,1);
      lcd.print("TU: ");
      lcd.print(number1);
      lcd.print("YO: ");
      lcd.print(randomNumber);
      counter = 0;
      delay(2000);
      lcd.clear();
    }else if(counter>2){
      counter = 0;
      lcd.clear();
      lcd.print("NUMERO INVALIDO!!!");
      delay(3000);
      lcd.clear();
      setup();
    }
  }
  
}
void writeLetters(){
  if (counter<16){
    char key = keypad.getKey();
    if(key){
      lcd.print(key);
      counter+=1;
    }
   }
   else if(counter<32){
   char key = keypad.getKey();
    if(key){
      lcd.setCursor(counter-16, 1); 
      lcd.print(key);
      counter+=1;
    }
   }else{
    counter =0 ;
    lcd.clear();
    setup();
    }
}
void reconocer (){
if(selectedMenu==0){
  char key = keypad.getKey();
  
  if (key=='A'){
    lcd.clear();
    lcd.print("A-Write");
    delay(1000);
    lcd.clear();
    selectedMenu = 1;
  }else if(key=='B'){
    lcd.clear();
    lcd.print("B-game");
   selectedMenu = 2;
   delay(1000);
   lcd.clear();
   }
  }
}
