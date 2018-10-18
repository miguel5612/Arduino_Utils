#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

//Variables empleadas para leer el teclado
int rowCounter =0,columnCounter =0,foundColumn = 0,keyValue = 0, noKey = 0,debounce = 100, keyNum, menu=0, counter1 = 0, counter2 = 0,velocidad;
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
const int led[] = {0,30,31,32,33,34,35,36,8};

#define exitKey "Esc"
#define clearKey "*"
#define changeClaveKey "F1"
#define interruptPin 2

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.print("INIT SYSTEM");
  lcd.backlight();
  pinMode(interruptPin, INPUT_PULLUP);
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
  
  pinMode(10, OUTPUT);
 

  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11) | _BV(WGM10);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11) | _BV(CS10);
  
  OCR1AH = 0;
  OCR1AL = 250;
  
  OCR1BH = 0;
  OCR1BL = 30;
  
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
          lcd.setCursor(0,1);
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
    while(counter1<3){
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
    delay(1500);
    counter1 = 0; clave = ""; readKey = false; 
    lcd.clear();
    lcd.print("Escriba la clave:");
    lcd.setCursor(0,1);
    return true;
  }
  return false;
}
void programa2(){
  readKeyboard();
  if(newKey()){
      convertKey();
      validateExit(keyString);
      if(validateChangeClave(keyString)) return;
      if(validateClear(keyString)) return;
      clave+=keyString;
      lcd.print(keyString);
      counter1++;
      readKey = false;  
      delay(100);
  }
  if(counter1>=3){
    lcd.clear();
    if(getPass() == clave){
      Serial.println("Acceso concedido");
      digitalWrite(led[1],HIGH);
      digitalWrite(led[8],LOW);
      lcd.print("CLAVE CORRECTA!!");
      delay(2000);
      digitalWrite(led[1],LOW);
    }else{
      Serial.println("Acceso denegado");
      digitalWrite(led[1],LOW);
      digitalWrite(led[8],HIGH);
      lcd.print("CLAVE INCORRECTA!!");
      delay(5000);
      digitalWrite(led[8],LOW);
    }
    counter1 = 0;
    clave = "";
    lcd.clear();
    lcd.print("Digite la clave");
    lcd.setCursor(0,1);
  }
}
void programa3(){
  lcd.print("Introduzca la velocidad");
  lcd.setCursor(0,1);
  lcd.print("v = ");
  String veloString = "";
  while(keyString!=exitKey){
      readKeyboard();
      if(newKey()){
        convertKey();
        veloString += keyString;
        Serial.print("veloString: ");
        Serial.println(veloString);
        Serial.print("veloInt: ");
        Serial.println(veloString.toInt()>=255);
        Serial.print("Condicional: ");
        Serial.println(veloString.toInt());
        readKey = false;
        if(veloString.toInt()<=255){
          lcd.print(keyString);
          delay(100);
        }else{
          lcd.clear();
          lcd.print("Introduzca la velocidad");
          lcd.setCursor(0,1);
          lcd.print("v = ");
          veloString = keyString;
          lcd.print(keyString);
          delay(100);
        }
      }else{
          velocidad = veloString.toInt();
          analogWrite(led[8],velocidad);           
        
      }
  }
}
void programa4(){
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
void programa5(){
  counter1 = 0;
  while(counter1<=8){
    readKeyboard();
    if(newKey()){
      convertKey();
      validateExit(keyString);
      readKey = false;
    }
    attachInterrupt(digitalPinToInterrupt(interruptPin), changeLed, CHANGE);
    digitalWrite(led[counter1],HIGH);
    delay(500);
    digitalWrite(led[counter1],LOW);
    delay(500);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Secuencia");
    lcd.setCursor(0,1);
    lcd.print("X=");
    lcd.print(counter1);
    counter1++;
  }
}
void changeLed(){
  digitalWrite(led[counter1+1],!digitalRead(led[counter1+1]));
  counter1++;
  delay(50);
}
void programa6(){
  lcd.clear();
  lcd.print("OutputPin(10)");
  delay(1000);
   readKeyboard();
    if(newKey()){
      convertKey();
      validateExit(keyString);
      readKey = false;
    }

}
void programa7(){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Retardo 1s");
  lcd.setCursor(0,1);
  lcd.print("s = ");
  while(counter1<10){
    readKeyboard();
    if(newKey()){
      convertKey();
      validateExit(keyString);
      readKey = false;
    }
    retardoUnSegundo();
    lcd.print(counter1);
    counter1++;
  }
  counter1 = 0;
}
void retardoUnSegundo(){
  unsigned long tiempo = millis();
  while(millis()-tiempo<1000){
    Serial.println("no hago nada");
    delay(50);
  }
}
void programa8(){
  unsigned long oldMillis = millis();
  float m = 0;
  while(counter1<=60){
      readKeyboard();
      if(newKey()){
        convertKey();
        validateExit(keyString);
        readKey = false;
      }
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("contador 0-60");
      lcd.setCursor(0,1);
     lcd.print("t = ");
     lcd.print(counter1);
     lcd.print(" m= ");
     m = millis()-oldMillis;
     lcd.print(m/1000,2);
     delay(1000); 
     counter1++;
  }  
  counter1=0;
}
void programa9(){
  //Celular de segunda generacion
  const string uno[] = {"a", "b", "c"};
  const string dos[] = {"d", "e", "f"};
  const string tres[] = {"g", "h", "i"};
  const string cuatro[] = {"j", "k", "l"};
  const string cinco[] = {"m", "n", "o"};
  const string seis[] = {"p", "q", "r"};
  const string siete[] = {"s", "t", "v"};
  const string ocho[] = {"w", "x", "y"};
  const string nueve[] = {"z", "Z", "A"};
  
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
