#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Variables empleadas para leer el teclado
int rowCounter =0,columnCounter =0,foundColumn = 0,keyValue = 0, noKey = 0,debounce = 100, keyNum, menu=0, counter1 = 0, counter2 = 0,velocidad, posX = 0, posY = 0;
boolean foundCol = false, readKey = false,numericValue = false, estado, condition = false;
String keyString, clave, keyPressed;


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

const String cero[] = {"0", "+"};
const String uno[] = {".", ",", ":","1"};
const String dos[] = {"a", "b", "c","2"};
const String tres[] = {"d", "e", "f","3"};
const String cuatro[] = {"g", "h", "i","4"};
const String cinco[] = {"j", "k", "l","5"};
const String seis[] = {"m", "n", "o","6"};
const String siete[] = {"p", "q", "r","7"};
const String ocho[] = {"s", "t", "v","8"};
const String nueve[] = {"w", "x", "y","9"};

String palabraIn[32];
#define exitKey "Esc"
#define clearKey "*"
#define changeClaveKey "F1"
#define interruptPin 2

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.print("INIT SYSTEM");
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
  
  lcd.clear();
  lcd.cursor();
}
void loop()
{
  unsigned long oldTime;
  int pos = 0;
  readKeyboard();
  if(newKey()){
      Serial.println("Primera pulsasion");
      convertKey();
      keyPressed = keyString;
      Serial.print("key p: ");
      Serial.println(keyString);
      if(specialK(keyString))
      {
        Serial.println("is not special key");
        //Si no es una tecla especial
        //Activo la condicion, si vuelve a presionar la misma letra cambiare.
        condition = true;
        //Ubico el cursor en la posicion deseada      
        lcd.setCursor(posX,posY);
        //Imprimo en la pantalla la primera letra
        lcd.print(getNumber(keyString.toInt(),pos));
        //Guardo la letra impresa
        saveAndCompare(getNumber(keyString.toInt(),pos),posX, posY);
        readKey = false;
        delay(300);
        //Tiempo de espera! importante 2s
        unsigned long oldM = millis();
        while(condition & millis() - oldM <= 2000){
          readKeyboard();
          if(newKey())
          {
            convertKey();
            if(keyString == keyPressed)
            {
              Serial.print("pos: ");
              Serial.println(pos);
              pos++;
              lcd.setCursor(posX,posY);
              lcd.print(getNumber(keyString.toInt(),pos));
              saveAndCompare(getNumber(keyString.toInt(),pos),posX, posY);
              delay(300);
            }
            else
            {
              condition = false;
            }
          }
        }
        posX++;
      }
      else
      {
        lcd.setCursor(posX,posY);
        readKey = false;
        condition = false;
      }  
      Serial.println("posX ha aumentado");
  }
  if(posX>=15) {posY++;posX=0;}
  if(posY>=2){posX = 0; posY = 0;}
}
//Funciones para la lectura del teclado
void saveAndCompare(String letter, int posInX, int posInY){
  if(posInY!=0){posInX = posInX + 16;}
  palabraIn[posInX] = letter;
  String palabra;
  for(int i=0;i<=posInX;i++){
    palabra+=palabraIn[i];
  }
  Serial.print("palabra: ");Serial.println(palabra);
  if(palabra.indexOf("clc") > 0){lcd.clear();posX = 0; posY = 0;}
  
}
void printWord(String word){
   //Ubico el cursor en la posicion deseada      
    lcd.setCursor(posX,posY);
    //Imprimo en la pantalla la primera letra
    lcd.print(word);
    //Guardo la letra impresa
    saveAndCompare(word,posX, posY);
}
boolean specialK(String key)
{
  if(key == "Left Arrow")
  {
    if(posX > 0 ) posX -= 1;
    return false;
  }
  else if(key == "Right Arrow")
  {
    if(posX < 16 ) posX += 1;
    return false;
  }
  else if(key == "Up Arrow")
  {
    if(posY == 1 ) posY -= 1;
    return false;
  }
  else if(key == "Down Arrow")
  {
    if(posY == 0 ) posY += 1;
    return false;
  }
  else if(key == "F1")
  {
    posX = 0;posY = 0; lcd.clear();
    printWord("Miguel Califa");
    posX = 16;
    readKey = false;
    return false;
  }
  else if(key == "F2")
  {
    posX = 0;posY = 0; lcd.clear();
    printWord("Andres Martinez");
    posX = 16;
    readKey = false;
    return false;
  }
  else if(key == "*")
  {
    printWord("*");
    posX += 1;
    readKey = false;
    return false;
  }
  else if(key == "#")
  {
    printWord("#");
    posX += 1;
    readKey = false;
    return false;
  }
  else if(key == "Esc")
  {
    lcd.clear();
    posX = 0;
    posY = 0;
    readKey = false;
    return false;
  }
  else if(key == "Ent")
  {
    lcd.clear();
    posX = 0;
    posY = 0;
    printWord("Enviando");
    posY = 1;
    posX = 3;
    printWord("Mensaje");
    posX = 16;
    delay(500);
    lcd.clear();
    posX = 0;
    posY = 0;
    readKey = false;
    return false;
  }
  else
  {
    return true;
  }
}
String getNumber(int numIn, int pos){
  if(pos>=4){pos = pos/3;}
  switch(numIn){
    case 0:
      return cero[pos];
    case 1:
      return uno[pos];
      break;
    case 2:
      return dos[pos];
      break;
      
    case 3:
      return tres[pos];
      break;
      
    case 4:
      return cuatro[pos];
      break;
      
    case 5:
      return cinco[pos];
      break;
      
    case 6:
      return seis[pos];
      break;
      
    case 7:
      return siete[pos];
      break;
      
    case 8:
      return ocho[pos];
      break;
      
    case 9:
      return nueve[pos];
      break;
  }
}

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


