#define A 13
#define B 12
#define C 11
#define D 10
#define E 9
#define F 8
#define G 7

#define disp1 6
#define disp2 5

#define btn1 4
#define btn2 3
#define btn3 2

#define tiempoEspera 300 // 13 milis es lo mejor para no ver el efecto

int contador = 0;
int unidades = 0;
int decenas = 0;


const int number[11] = {0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};

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


  pinMode(btn1,OUTPUT);
  pinMode(btn2,OUTPUT);
  pinMode(btn3,OUTPUT);
}
void loop(){

    contar();
}
void contar(){
  contador++;
  Serial.print("contador: ");
  Serial.println(contador);
  Serial.print("Unidades: ");
  Serial.println(unidades);
  if(unidades<9){
    unidades++;
  }else{
      unidades = 0;
      decenas ++;
  }
  smartDelay(1000);
}
void smartDelay(int tiempo){
  int actual = millis();
  while(millis()-actual<tiempo){
    mostrarNumero();
    delay(tiempoEspera);
  }
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
