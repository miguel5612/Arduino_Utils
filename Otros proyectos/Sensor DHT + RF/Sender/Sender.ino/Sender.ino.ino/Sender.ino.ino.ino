#include "DHT.h" 
#define DHTPIN 2 
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE); 

String mensaje = "";

void setup() {
//inicializacion del puerto serie
  Serial.begin(9600); //Se inicia la comunicación serial 
  Serial2.begin(9600); // Puerto de envio del modulo :p
//inicializacion del DHT
  dht.begin(); //Se inicia el sensor
}

void loop(){
  int h = dht.readHumidity(); //se lee la humedad
  int t= dht.readTemperature(); // se lee la temperatura
  enviarMensajeRF(t,h);
  // se imprime las variables de temperatura y humedad
  enviarMensajeSerialArduino(t,h);  
  delay(1000); 
  //con un retraso de 1 segundo
}
void enviarMensajeSerialArduino(int temperatura, int humedad){
  Serial.print("Hum:"); 
  Serial.println((int)humedad); 
  Serial.print("  Tem:"); 
  Serial.println((int)temperatura); 
}
void enviarMensajeRF(int temperatura, int humedad)
{
mensaje = "";
//Aqui se envia el mensaje 
// TTTHHH --> Esta es la palabra que se envia
//Temperatura
if(temperatura<10)
{
  mensaje += "00"+String(temperatura);
}else if(temperatura>10 && temperatura<100){
  mensaje += "0"+String(temperatura);
}else if(temperatura>100 && temperatura<200)
{
  mensaje += String(temperatura);
}else{
  mensaje += "000";
}
//humedad
 if(humedad<10)
{
  mensaje += "00"+String(humedad);
}else if(humedad>10 && humedad<100){
  mensaje += "0"+String(humedad);
}else if(humedad>100 && humedad<200)
{
  mensaje += String(humedad);
}else{
  mensaje += "000";
}
//impresion del mensaje :P
Serial2.println(mensaje);
}

ç
