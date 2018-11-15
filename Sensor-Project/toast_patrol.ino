const int buttonPin = 2;
const int inputPin1 = 3;
const int inputPin2 = 4;
bool buttonState = LOW;
int start = 0;

#define FORWARD 1
#define BACKWARD 2
#define STOP 3
 

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  Serial.begin(9600);
}

void controlStab(int dirc) {
  switch (dirc) {
    case FORWARD:
      digitalWrite(inputPin1, LOW);
      digitalWrite(inputPin2, HIGH);
    case BACKWARD:
      digitalWrite(inputPin1, HIGH);
      digitalWrite(inputPin2, LOW);
    case STOP:
      digitalWrite(inputPin1, LOW);
      digitalWrite(inputPin2, LOW);
    default:
      // NOTHING
      break;
  }
}


void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH){
    start = 1;
  } else { start =0;}

  Serial.println(start);
}
