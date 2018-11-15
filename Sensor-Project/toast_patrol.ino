#define FORWARD 1
#define BACKWARD 2
#define STOP 3

const int buttonPin = 2;
const int inputPin1 = 3;
const int inputPin2 = 4;
bool buttonState = LOW;
bool prevButtonState = LOW;
int currentDir = STOP;
int start = 0;

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
      break;
    case BACKWARD:
      digitalWrite(inputPin1, HIGH);
      digitalWrite(inputPin2, LOW);
      break;
    case STOP:
      digitalWrite(inputPin1, LOW);
      digitalWrite(inputPin2, LOW);
      break;
    default:
      // NOTHING!
      break;
  }
}


void loop() {
  buttonState = digitalRead(buttonPin);
  controlStab(currentDir);
  if (prevButtonState == LOW && buttonState == HIGH) {
    switch (currentDir) {
      case STOP:
        currentDir = FORWARD;
        break;
      case FORWARD:
        currentDir = BACKWARD;
        break;
      case BACKWARD:
        currentDir = STOP;
        break;
      default:
        // NOTHING!
        break;
    }
  }
  
  prevButtonState = buttonState;
  Serial.println(start);
  delay(100);
}