#define A 13
#define B 12
#define C 11
#define D 10
#define E 9
#define F 8
#define G 7

#define disp1 6
#define disp2 5

#define tiempoEspera 5 // 13 milis es lo mejor para no ver el efecto
#define maxNumber 99
#define btnUp 4
#define btnSet 3

int contador = 0;
int unidades = 0;
int decenas = 0;
int menu = 1;
int fiboIndex = 0;
bool bandera = false;


const int number[11] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};
const int fibonacci[11] = {1,2,3,5,8,13,21,34,55,89,144};

void setup(){
  Serial.begin(9600);
  //configuracion de pines
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode(F,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(disp1,OUTPUT);
  pinMode(disp2,OUTPUT);


  pinMode(btnUp,INPUT_PULLUP);
  pinMode(btnSet,INPUT_PULLUP);
  publicar(0,menu);
    
}
void loop(){
  while(!bandera){
    if(!digitalRead(btnUp)){
      Serial.println("BTN UP");
      if(menu<3){
        menu++;
      }else{
        menu = 1;
      }
      publicar(0,menu);
      delay(tiempoEspera);
    }else if(!digitalRead(btnSet) & menu<=3){
      Serial.println("BTN SET");
      bandera = true;
    }    
  }
  switch(menu){
    case 1:
      contar();
    break;    
    case 2:
      contarPulsador();
    break;
    case 3: 
      fibonacciFctn();
    break;
  }
}
void fibonacciFctn(){
  Serial.println("en fibo");
  if(!digitalRead(btnUp)){
    if(fiboIndex<=11) fiboIndex++;
  }else if(!digitalRead(btnSet)){
    if(fiboIndex>0) fiboIndex-=1;
  }
  String strNumber = String(fibonacci[fiboIndex]);
  unidades = (strNumber.substring(1,2)).toInt();
  decenas = (strNumber.substring(0,1)).toInt();
  if(fibonacci[fiboIndex]<10){  unidades = fibonacci[fiboIndex]; decenas = 0; }
  smartDelay(200);
  Serial.print("Numero: ");
  Serial.println(fibonacci[fiboIndex]);
  Serial.print("unidades: ");
  Serial.println(unidades);
  Serial.print("Decena: ");
  Serial.println(decenas);
  Serial.print("fiboIndex");
  Serial.println(fiboIndex);
}
void contarPulsador(){
  if(!digitalRead(btnUp)){
    aumentarContador();
    smartDelay(1000); 
  }else{
    smartDelay(200); 
  }
}
void disminuirContador(){
  if(unidades>0){
    unidades-=1;
  }else if(decenas>0){
    decenas-=1;
    unidades = 9;
  }
}
void aumentarContador(){
  if(contador<maxNumber){
    if(unidades<9){
      Serial.println("AUMENTO UNIDADES");
      unidades++;
    }else{
        unidades = 0;
        decenas ++;
    }
    contador++;
  }
}

void contar(){
  aumentarContador();
  Serial.print("contador: ");
  Serial.println(contador);
  Serial.print("Unidades: ");
  Serial.println(unidades);
  smartDelay(1000);
}
void smartDelay(int tiempo){
  unsigned long actual = millis();
  do{
    mostrarNumero();
    delay(tiempoEspera);
  }while((millis()-actual<tiempo));
}
void mostrarNumero(){
  if(decenas == 0){
    publicar(0,unidades);
  }else{
    publicar(0,unidades);
    delay(tiempoEspera);
    publicar(1,decenas);
  }
}
void publicar(int dispSelect, int num){
  if(dispSelect!=0){
    digitalWrite(disp2, HIGH);
    digitalWrite(disp1, LOW);
  }else{
    digitalWrite(disp2, LOW);
    digitalWrite(disp1, HIGH); 
  }
  escribirEnPuerto(num);
}
void escribirEnPuerto(int x){
  int pin2, b;             

  for (pin2 = A, b = 0; pin2 >= G; pin2--, b++)
  {
    digitalWrite(pin2, !bitRead(number[x], b));

  }
}
