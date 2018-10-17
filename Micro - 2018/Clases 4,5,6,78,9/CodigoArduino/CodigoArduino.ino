#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

//Variables empleadas para leer el teclado
int rowCounter =0,columnCounter =0,foundColumn = 0,keyValue = 0, noKey = 0,debounce = 100, keyNum, menu=0, counter1 = 0, counter2 = 0;
boolean foundCol = false, readKey = false,numericValue = false, estado;
String keyString, clave;


//Conexiones entre el arduino y el teclado
const int row1 = 40;
const int row2 = 41;
const int row3 = 42;
const int row4 = 43;
const int row5 = 44;
const int colA = 48;
const int colB = 49;
const int colC = 50;
const int colD = 51;
const int led[] = {0,30,31,32,33,34,35,36,37};

#define exitKey "Esc"
#define clearKey "*"
#define changeClaveKey "F1"

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);
  pinMode(row5, OUTPUT);
  pinMode(colA, INPUT_PULLUP);
  pinMode(colB, INPUT_PULLUP);
  pinMode(colC, INPUT_PULLUP);
  pinMode(colD, INPUT_PULLUP);
  while(!Serial){};
  int i = 0;
  while(i<=8){
    pinMode(led[i],OUTPUT);
    Serial.print("testing led: ");
    Serial.print(led[i]);
    Serial.print("   i= ");
    Serial.println(i);
    for (int j=0;j<=4;j++){
      digitalWrite(led[i],!estado);
      delay(50);
      digitalWrite(led[i],!estado);
      delay(50);
    }
    digitalWrite(led[i],LOW);
    i++;
  }
  printMenu();
  
}

void loop(){
  while(menu > 0){ 
        switch(menu){
        case 1:
          programa1();
          break;  
        case 2:
          programa2();
          break;
       case 3:
          programa3();
          break;
       case 4:
          programa4();
          break;
       case 5:
          programa5();
          break;
       case 6:
          programa6();
          break;
       case 7:
          programa7();
          break;
       case 8:
          programa8();
          break;
      case 9:
          programa9();
          break;
          
        }
   }
  if(newKey()){  
    convertKey();    
    Serial.print(keyValue); 
    Serial.print("  -  ");
    Serial.println(keyString);
    Serial.print("Digit: ");
    Serial.print(keyString.toInt());
    Serial.print("   is Digit: ");
    Serial.println(keyString.toInt()<10 & menu == 0);
    if(keyString.toInt()<10 & menu == 0){ 
      switch(keyString.toInt()){
        case 1:
          readKey = false;
          lcd.clear();
          menu=1;
          break;  
        case 2:
          readKey = false;
          lcd.clear();
          lcd.print("INGRESE LA CLAVE");
          menu=2;
          break;
       case 3:
          readKey = false;
          lcd.clear();
          menu=3;
          break;
       case 4:
          readKey = false;
          lcd.clear();
          menu=1;
          break;
       case 5:
          readKey = false;
          lcd.clear();
          menu=5;
          break;
       case 6:
          readKey = false;
          lcd.clear();
          menu=6;
          break;
       case 7:
          readKey = false;
          lcd.clear();
          menu=7;
          break;
       case 8:
          readKey = false;
          lcd.clear();
          menu=8;
          break;
      case 9:
          readKey = false;
          lcd.clear();
          menu=9;
          break;
      default:
          printMenu();
          break;
          
      }
    }
    
    
    readKey = false; // reset the flag
    delay(debounce); // debounce
  }else{
    readKeyboard();
  }
  
}
String getPass(){
  return String(String(EEPROM.read(0)) + String(EEPROM.read(1)) + String(EEPROM.read(2)));
}

void validateExit(String key){
  if(key==exitKey){
    menu = 0;    
  }
}
bool validateClear(String key){
  if(key == clearKey){
    lcd.clear();
    counter1 =0;counter2=0;
    return true;
  }
  return false;
}
void programa1(){
  readKey = false;  
  readKeyboard();
  if(newKey()){
    convertKey();
    validateExit(keyString);
    if(validateClear(keyString)) return;
    if(counter1<16){
      if(counter1==0){lcd.setCursor(0,0);}
      lcd.print(keyString);
      counter1+=keyString.length();
      delay(50);
    }else if(counter2<16){
      if(counter1==16 & counter2 == 0)  lcd.setCursor(0,1);
      lcd.print(keyString);
      counter2+=keyString.length();
      delay(50);
    }else{
      counter1 =0;counter2=0;
      delay(50);
    }
    readKey = false;
  }
  
}
boolean validateChangeClave(String key){
  if(key == changeClaveKey){
    counter1 = 0;
    clave = "";
    int address = 0;
    lcd.clear();
    lcd.print("**Nueva Clave**");
    lcd.setCursor(0,1);
    while(counter1<=3){
      readKey = false;  
      readKeyboard();
      if(newKey()){
        convertKey();
        lcd.print(keyString);
        clave += keyString;
        EEPROM.write(address,keyString.toInt());
        counter1++;address++;clave="";
      }
    }
    lcd.clear();
    return true;
  }
}
void programa2(){
  readKey = false;  
  readKeyboard();
  if(counter1>=3){
    lcd.clear();
    if(getPass() == clave){
      Serial.println("Acceso concedido");
      digitalWrite(led[1],HIGH);
      digitalWrite(led[8],LOW);
      lcd.print("CLAVE CORRECTA!!");
    }else{
      Serial.println("Acceso denegado");
      digitalWrite(led[1],LOW);
      digitalWrite(led[8],HIGH);
      lcd.print("CLAVE INCORRECTA!!");
    }
    counter1 = 0;
    clave = "";
    lcd.clear();
  }else{
    if(newKey()){
    convertKey();
    validateExit(keyString);
    if(validateChangeClave(keyString)) return;
    if(validateClear(keyString)) return;
      clave+=keyString;
    }
  }
  
}
void programa3(){
  
}
void programa4(){
  
}
void programa5(){
  
}
void programa6(){
  
}
void programa7(){
  
}
void programa8(){
  
}
void programa9(){
  
}
void printMenu(){
  lcd.clear();
  lcd.print("Digite el # del programa 4-9");
}

//Funciones para la lectura del teclado
bool newKey(){
  return (readKey==true && noKey == 19);
}
void readKeyboard(){
  if(noKey == 20){ // no keys were pressed
    readKey = true;  // keyboard is ready to accept a new keypress
  }
  noKey = 0;
  for(rowCounter=row1; rowCounter<(row5 +1); rowCounter++){
    scanRow(); // switch on one row at a time
    for(columnCounter = colA; columnCounter <colD +1; columnCounter++){
      readColumn(); // read the switch pressed
      if (foundCol== true){
        keyValue =(rowCounter-row1) +5*(columnCounter - colA);
      }
    }
  }
}

void scanRow(){
  for(int j =row1; j < (row5 +1); j++){
    digitalWrite(j, HIGH);
  }
  digitalWrite(rowCounter , LOW); // switch on one row
}

void readColumn(){
  foundColumn = digitalRead(columnCounter);
  if(foundColumn == 0){
     foundCol = true;
  }
  else{
  foundCol=false;
  noKey=noKey +1; // counter for number of empty columns
  }
}

void convertKey(){
  // converts the key number to the corresponding key
  keyString ="";
  keyNum = 99;
  numericValue = false;  
  //
  switch (keyValue) {
    // column A
    case 0:
    keyString = "Left Arrow";
    break;
    case 1:
    keyString = "7";
    keyNum = 7;
    break;  
    case 2:
    keyString = "4";
    keyNum = 4;    
    break;
    case 3:
    keyString = "1";
    keyNum = 1;    
    break;
    case 4:
    keyString = "F1";
    break;
    // column B
    case 5:
    keyString = "0";
    keyNum = 0;
    break;
    case 6:
    keyString = "8";
    keyNum = 8;    
    break;  
    case 7:
    keyString = "5";
    keyNum = 5;    
    break;
    case 8:
    keyString = "2";
    keyNum = 2;    
    break;
    case 9:
    keyString = "F2";    
    break;   
    // column C
    case 10:
    keyString = "Right Arrow";
    break;
    case 11:
    keyString = "9";
    keyNum = 9;    
    break;  
    case 12:
    keyString = "6";
    keyNum = 6;    
    break;
    case 13:
    keyString = "3";
    keyNum = 3;    
    break;
    case 14:
    keyString = "#";   
    break;   
    // column D
    case 15:
    keyString = "Ent";
    break;
    case 16:
    keyString = "Esc";   
    break;  
    case 17:
    keyString = "Down Arrow";   
    break;
    case 18:
    keyString = "Up Arrow";  
    break;
    case 19:
    keyString = "*";   
    break;     
  }
  if (keyNum == 99){
      numericValue = false; // show a non numeric key pressed
  }
  else{
      numericValue = true;  // show a number key pressed
  }
}