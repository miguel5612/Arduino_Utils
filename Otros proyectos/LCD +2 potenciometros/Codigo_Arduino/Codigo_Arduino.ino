// Programacion V2. Contador 0-60 y lector A/D de 2 canales.

//Librerias utilizadas

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//Lista de entradas

#define EntradaAnalogica1 A0
#define EntradaAnalogica2 A1
#define pulsadorResetContador A3
#define pulsadorCambioModo A2 //pulsador para cambiar entre el modo contador al modo ADC
#define led 2

boolean contAnalog = false; // 0 --> contador (diapositiva 1)
          // 1 --> Analog digital (diapositiva 2)
int contadorMillis = 0;
unsigned long tiempoInicial = 0; // <-- aqui guardamos el valor de millis
unsigned long tiempoTranscurrido = 0;
double tiempoEnPantalla = 0; //Tiempo que se muestra en la lcd

int contadorDelay = 0; // --> mS
int contadorTemporalMilisegundos = 0;
String oldV1, oldV2;
int oldMsg1, oldMsg2;

const int timeSpan = 13; //100 mS de span (separacion) entre delay


//configuracion de parametros de la pantalla
LiquidCrystal_I2C lcd(0x3F, 16, 2);


void setup(){
  //Inicializacion del puerto serie, pantalla
  
  Serial.begin(9600);
    lcd.begin();
  
  //Se declaran las entradas del arduino
  
  pinMode(EntradaAnalogica1,INPUT_PULLUP);
  pinMode(EntradaAnalogica2,INPUT_PULLUP);
  pinMode(pulsadorResetContador,INPUT_PULLUP);
  pinMode(pulsadorCambioModo,INPUT_PULLUP);

  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);

  printMsg("Cronometro","Nombre");
  delay(500);
}

void loop(){
  readBtn(); //Leer los pulsadores
  if(!contAnalog){
    //contadorMillisFuncion();
    
    if( contadorDelayFuncion() ||     contadorMillisFuncion()){
      printMsgLong("Delay: ",contadorDelay," S","Milis: ",(int)tiempoEnPantalla," S");  
    }  

  }else{
   	digitalWrite(led,analogoDigital());
  }
}

// Funciones comunes...
boolean analogoDigital(){
	int lectura1 = analogRead(EntradaAnalogica1);
	int lectura2 = analogRead(EntradaAnalogica2);
	float voltage1 = lectura1 * (5.0 / 1023.0);
	float voltage2 = lectura2 * (5.0 / 1023.0);
	String linea1 = "";
	String linea2 = "";
	bool ledStauts = false;
	if(voltage1>0 && voltage1<=2)
	{
		linea1 = "In1: Baja senal.";
		ledStauts = true;
	}
	else if(voltage1>2 && voltage1<=4)
	{
		linea1 = "In1: Ok.";
	}
	else if(voltage1>4 && voltage1<=5)
	{
		linea1 = "In1: Alta senal.";
	}


	if(voltage2>0 && voltage2<=2)
	{
		linea2 = "In2: Alerta.";
	}
	else if(voltage2>2 && voltage2<=4)
	{
		linea2 = "In2: Ok.";
	}
	else if(voltage2>4 && voltage2<=5)
	{
		linea2 = "In2: detener.";
		ledStauts = true;
	}

	if(oldV1!=linea1 or oldV2!=linea2)
	{
		printMsg(linea1,linea2);		
	}

	oldV1 = linea1;
	oldV2 = linea2;

	return ledStauts;
}
boolean contadorDelayFuncion(){
  if(contadorDelay<60){
    if(contadorTemporalMilisegundos<1000){
      delay(timeSpan); //timespan --> mS
      contadorTemporalMilisegundos = contadorTemporalMilisegundos + timeSpan;
      return false;
    }else if(contadorTemporalMilisegundos>=1000){
      contadorTemporalMilisegundos = 0;
      contadorDelay = contadorDelay + 1;
      return true;
    }
  }
}
boolean contadorMillisFuncion(){
  //contador usando milis();
  if(tiempoInicial == 0){
    tiempoInicial = millis();
    return false;
  }else if(tiempoEnPantalla<60){
    tiempoTranscurrido = (millis()-tiempoInicial);
    if(tiempoTranscurrido >=1000 && tiempoEnPantalla<60){
      tiempoEnPantalla = tiempoEnPantalla + tiempoTranscurrido/1000;
      tiempoInicial = millis();
      return true;
    }
  }
}
void readBtn(){
	Serial.print(".");
    if(!digitalRead(pulsadorResetContador)){
    	initializarVariables();// inicializcion
    	Serial.println(".");
    	// vuelve al contador;
    }
    else if(!digitalRead(pulsadorCambioModo )){
    	Serial.println(".");
    	contAnalog = !contAnalog; //Cambio de modo
    	initializarVariables(); //inicializacion
    	delay(300);
    }
}
void initializarVariables(){
    tiempoEnPantalla = 0;
    tiempoTranscurrido = 0;
    tiempoEnPantalla = 0;
    contadorDelay = 0;
    tiempoInicial = 0;
    contadorDelay = 0;
	oldMsg1 = "";
	oldMsg2 = "";
	oldV1 = "";
	oldV2 = "";
}
String printMsgLong(String msgLn1Part1,int msgLn1Part2,String msgLn1Part3,String msgLn2Part1,int msgLn2Part2,String msgLn2Part3){
  //Esta funcion imprime un mensaje en el puerto serie
  lcd.setCursor(0,0);
  if(oldMsg1!=msgLn1Part2)
  {
  lcd.print(msgLn1Part1);
  lcd.print(msgLn1Part2);
  lcd.print(msgLn1Part3);
  }
  lcd.setCursor(0,1);
  if(oldMsg2!=msgLn2Part2)
  {
  lcd.print(msgLn2Part1);
  lcd.print(msgLn2Part2);
  lcd.print(msgLn2Part3);
  }
  oldMsg1 = msgLn1Part2;
  oldMsg2 = msgLn2Part2;
  return "";
}
String printMsg(String msgLn1,String msgLn2){
  //Esta funcion imprime un mensaje en el puerto serie
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(msgLn1);
  lcd.setCursor(0,1);
  lcd.print(msgLn2);
  return "";
}