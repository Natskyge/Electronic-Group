const int buttonPin = 2;
bool buttonState = LOW;
int start = 0;
 

void setup() {
  // put your setup code here, to run once:
pinMode(buttonPin, INPUT);
Serial.begin(9600);
}


void loop() {
buttonState = digitalRead(buttonPin);
if (buttonState == HIGH){
  start = 1;
  } else { start =0;}

Serial.println(start);
}
