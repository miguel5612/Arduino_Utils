#include <LiquidCrystal.h>
#include <TimerOne.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int count_1,count_2=0;
void setup() {
  pinMode(22,INPUT);
  Timer1.initialize(1000000);
  Timer1.start();
  Timer1.attachInterrupt(conteo_int);
  pinMode(21,INPUT);
  lcd.begin(16,2);
  lcd.clear();
}

void loop() {
  if(count_1<60){count_1++;}
  lcd.setCursor(0,0);
  lcd.print(' ');
  lcd.setCursor(0,0);
  lcd.print(String(count_1));
  delay(1000);
}

void conteo_int(){
  if(count_2<60){count_2++;}
  lcd.setCursor(0,1);
  lcd.print(' ');
  lcd.setCursor(0,1);
  lcd.print(String(count_2));
  }

void reinicio(){
  while(digitalRead(21)==1){
    lcd.clear();
    count_1=0;
    count_2=0;}
  }
