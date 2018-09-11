int pinLeftA = 12;
int pinLeftB = 13;
int pinLeftPWM = 11;
int pinRightA = 7;
int pinRightB = 8;
int pinRightPWM = 6;
#define FORWARD 1
#define BACKWARD 2
#define STILL 3
#define LEFT 4
#define RIGHT 5

void setup() {
  pinMode(pinLeftA, OUTPUT);
  pinMode(pinLeftB, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightA, OUTPUT);
  pinMode(pinRightB, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);
  Serial.begin(9600);
}

void controlWheel(int side, int dirc, int spd) {
  int pinPWM, pinA, pinB;
  if (side == LEFT) {
    // Select pins for controlling left wheel
    pinA = pinLeftA;
    pinB = pinLeftB;
    pinPWM = pinLeftPWM;
  } else if (side == RIGHT) {
    // Select pins for controlling right wheel
    pinA = pinRightA;
    pinB = pinRightB;
    pinPWM = pinRightPWM;
  } else {
    return;
  }

  // Give commands to selected wheel
  analogWrite(pinPWM, spd);
  switch (dirc) {
    case FORWARD:
      digitalWrite(pinA, HIGH);
      digitalWrite(pinB, LOW);
      break;
    case BACKWARD:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, HIGH);
      break;
    case STILL:
      digitalWrite(pinA, LOW);
      digitalWrite(pinB, LOW);
      break;
    default:
     // NOTHING!
     break;
  }
  delay(10);
}

void loop() {
  controlWheel(LEFT,FORWARD, 255);
  // controlWheel(RIGHT,FORWARD, 255);
  delay(5000);

  controlWheel(LEFT,BACKWARD, 255);
  // controlWheel(RIGHT,BACKWARD, 255);
  delay(5000);

  controlWheel(LEFT,STILL, 255);
  // controlWheel(RIGHT,STILL, 255);
  delay(5000);
}

