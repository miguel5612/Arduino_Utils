#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int count_1,count_2=0;
void setup() {
  Serial.begin(9600);
  pinMode(22,INPUT);
  Timer1.initialize(1000000);
  Timer1.start();
  Timer1.attachInterrupt(conteo_int);
  pinMode(21,INPUT);
  //lcd.print("ALL OK");
  //delay(1000);
  lcd.clear();
}

void loop() {
  if(count_1<60){count_1++;}
  //lcd.setCursor(0,0);
  //lcd.print(' ');
  //lcd.setCursor(0,0);
  //lcd.print(String(count_1));
  Serial.print("Delay --> ");
  Serial.println(String(count_1));
  delay(1000);
}

void conteo_int(){
  if(count_2<60){count_2++;}
  //lcd.setCursor(0,1);
  //lcd.print(' ');
  //lcd.setCursor(0,1);
  //lcd.print(String(count_2));
  Serial.print("Timer --> ");
  Serial.println(String(count_2));
  }

void reinicio(){
  while(digitalRead(21)==1){
    lcd.clear();
    count_1=0;
    count_2=0;}
  }
