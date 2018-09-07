#include<LiquidCrystal.h> //Library for LCD


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
#define okChar '#'
#define timeDelay 200
#define address 0
#define interruptPin 19
#define startLed 30
#define endLed 37

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);// LCD pins at which it is attached to the Arduino

unsigned long prevMillis = 0;
byte iRow = 0, iCol = 0;
const byte countRows = 4;
const byte countColumns = 3; 
const byte rowsPins[countRows] = {F1, F2, F3, F4};
const byte columnsPins[countColumns] = {C1, C2, C3}; 
char keys[countRows][countColumns] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
int countPrinted = 0, countX, menu=1;
bool direccion =  true, bandera=false;

// Iniciar valores
void setup()
{
   Serial.begin(9600);
   lcd.begin(16, 2);
   for (byte c = 0; c < countColumns; c++)
   {
      pinMode(columnsPins[c], INPUT_PULLUP);
   }
   for (byte r = 0; r < countRows; r++)
   {
      pinMode(rowsPins[r], OUTPUT);
      digitalWrite(rowsPins[r], HIGH);
   }
   for (byte r = startLed; r <= endLed; r++)
   {
      pinMode(r, OUTPUT);
      digitalWrite(r, LOW);
   }
   pinMode(interruptPin, INPUT_PULLUP);
   pinMode(btnUp,INPUT_PULLUP);
   pinMode(btnSet,INPUT_PULLUP);

  menuPpal();

}
 
void loop()
{
 switch(menu){
    case 1:
      ejemplo1();
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
void ejemplo3(){
   pinMode(9, OUTPUT); // OUT Timer 1
   pinMode(10,OUTPUT); // Out Timer 2
   TCCR1A=0;//reset the register
   TCCR1B=0;//reset the register
   TCNT1=0;
   TCCR1A=0b01010011;//COM1A0,COM1B0 are 1, COM1A1, COM1B1 are 0
   //also WGM11, WGM10 are 1
   TCCR1B=0b00010001;//WGM13 is 1 and WGM12 is 0 with no prescaler CS10 is 1
   OCR1A=4000;// compare value
}
void ejemplo2(){
  attachInterrupt(digitalPinToInterrupt(interruptPin), changeLed, LOW );
}
void changeLed(){
  Serial.println("change led");
  for (byte r = startLed; r <= endLed; r++)
   {
     if(digitalRead(r) == !direccion){
        digitalWrite(r,direccion);
        return;
     }
   }
   direccion = !direccion;
   changeLed();
   return;
   Serial.println("change led");
  
}


void ejemplo1(){
  if (millis() - prevMillis > timeDelay)   // Espera no bloqueante
   {
      if(countPrinted>=32){ countPrinted = 0; }
      if(countX == 16){ countX = 0; }
      prevMillis == millis();
      if (readKeypad())   // Detección de tecla pulsada
      {
         if(countPrinted >= 16){
            lcd.setCursor(countX,1);
            
         }else{
            lcd.setCursor(countX,0);     
         }
         lcd.print(keys[iRow][iCol]);   // Mostrar tecla
         countX ++;countPrinted++;         
         Serial.print("printed: ");
         Serial.println(countPrinted);
         Serial.print("countX:");
         Serial.println(countX);
         
         delay(timeDelay);
      }
   }
}

bool readKeypad()
{
   bool rst = false;
   
   // Barrer todas las filas
   for (byte r = 0; r < countRows; r++)
   {
      pinMode(rowsPins[r], OUTPUT);
      digitalWrite(rowsPins[r], LOW);      // Poner en LOW fila
 
      // Comprobar la fila
      for (byte c = 0; c < countColumns; c++)
      {
         if (digitalRead(columnsPins[c]) == LOW)   // Pulsacion detectada
         {
            iRow = r;
            iCol = c;
            rst = true;
         }
      }
      
      pinMode(rowsPins[r], HIGH);         // Ponen en HIGH fila
      digitalWrite(rowsPins[r], INPUT_PULLUP);   // Poner en alta impedancia
   }
   return rst;
}
 
