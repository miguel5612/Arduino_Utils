#define interruptPin 2
unsigned long firstMeasure = 0;
unsigned long endMeasure = 0;
unsigned long result = 0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), Down2up, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void Down2up(){
  noInterrupts();
  firstMeasure = millis();
  interrupts();
  attachInterrupt(digitalPinToInterrupt(interruptPin), Up2Down, FALLING);
}
void Up2Down()
{
  noInterrupts();
  endMeasure = millis();
  Serial.print("Pulse width: ");
  result = endMeasure-firstMeasure;
  Serial.println(String(result));
  interrupts();
  attachInterrupt(digitalPinToInterrupt(interruptPin), Down2up, RISING);
  delay(200);
}

