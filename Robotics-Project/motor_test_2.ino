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

void loop() {
  forward();
  delay(2000);
  turnLeft();
  delay(2000);
  forward();
  delay(2000);
  turnRight();
  delay(2000);
}

void controlWheel(int side, int dirc, int spd) {
  delay(10);
  // Select wheel
  int pinA, pinB, pinPWM;
  if (side == RIGHT) {
    pinA = pinRightA;
    pinB = pinRightB;
    pinPWM = pinRightPWM;
  } else if (side == LEFT) {
    pinA = pinLeftA;
    pinB = pinLeftB;
    pinPWM = pinLeftPWM;
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

void turnLeft(void) {
  controlWheel(RIGHT, FORWARD, 255);
  controlWheel(LEFT, FORWARD, 0);
}

void turnRight(void) {
  controlWheel(LEFT, FORWARD, 255);
  controlWheel(RIGHT, FORWARD, 0);
}

void forward(void) {
  controlWheel(LEFT, FORWARD, 255);
  controlWheel(RIGHT, FORWARD, 255);
}
