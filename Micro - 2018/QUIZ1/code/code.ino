#define ledStart 5
#define ledEnd 9
#define btnPin 2

#define intReduccion 100
#define minIntervalo 100
int intervalo = 1000;
unsigned long oldTime;

void setup(){
  Serial.begin(9600);
  for(int i=ledStart; i<=ledEnd; i++){
    pinMode(i,OUTPUT);
  }
  pinMode(btnPin,INPUT_PULLUP);
  Serial.println("LED OK");
  Serial.println("MITAD AQUI");
  Serial.println(((ledEnd-ledStart)/2)+ledStart);
}
void loop(){
  int i = ledStart;
  Serial.println("inicio de loop");
  while(i<=ledEnd){
    Serial.print("LED: ");
    Serial.println(i);
    digitalWrite(i, HIGH);
    smartDelay(intervalo, i);
    digitalWrite(i, LOW);
    smartDelay(intervalo,i);
    i++;
  }
}
void smartDelay(int tiempo, int ledPos){
  oldTime = millis();
  while(millis()-oldTime<=tiempo){
    if(ledPos==((ledEnd-ledStart)/2)+ledStart && !digitalRead(btnPin)){
      Serial.println("Estoy en el led de la mitad y has presionado el boton");
      if(intervalo>minIntervalo){intervalo = intervalo - intReduccion;delay(200);}
    } 
  }
}

----------------------------------------------------------


