//Sensor Values
int sensorData;
int sensorLeft = A0;
int sensorMidLeft = A1;
int sensorMidRight = A2;
int sensorRight = A3;
int leftValue = B0;
int midLeftValue = B0;
int midRightValue = B0;
int rightValue = B0;

int midValues = 0;
int sideValues = 0;
int blackWhiteSwitch = 300;
int degree = 0;


//Motor values
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
int torqueValue = 200;


//Sensor white/black function
int sensorRead(int sensorPin){
  sensorData = analogRead(sensorPin);
  if(sensorData <= blackWhiteSwitch){
    return B1;
  }
  else{
    return B0;
  }
}


//Wheel rotation function
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


//Directional movement functions
void turnLeft(void) {
  controlWheel(LEFT, FORWARD, 0);
  controlWheel(RIGHT, FORWARD, 200);
}

void turnRight(void) {
  controlWheel(LEFT, FORWARD, 200);
  controlWheel(RIGHT, FORWARD, 0);
}

void turnSoftLeft(void) {
  controlWheel(LEFT, FORWARD, 100);
  controlWheel(RIGHT, FORWARD, 200);
}

void turnSoftRight(void) {
  controlWheel(LEFT, FORWARD, 200);
  controlWheel(RIGHT, FORWARD, 100);
}

void turnHardLeft(void) {
  controlWheel(LEFT, BACKWARD, 200);
  controlWheel(RIGHT, FORWARD, 200);
}

void turnHardRight(void) {
  controlWheel(LEFT, FORWARD, 200);
  controlWheel(RIGHT, BACKWARD, 200);
}

void forward(void) {
  controlWheel(LEFT, FORWARD, 200);
  controlWheel(RIGHT, FORWARD, 200);
}

void backward(void) {
  controlWheel(LEFT, BACKWARD, 200);
  controlWheel(RIGHT, BACKWARD, 200);
}

void stopMovement(void) {
    controlWheel(LEFT, FORWARD, 0);
    controlWheel(RIGHT, FORWARD, 0);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(pinLeftA, OUTPUT);
  pinMode(pinLeftB, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightA, OUTPUT);
  pinMode(pinRightB, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  leftValue = sensorRead(sensorLeft);
  midLeftValue = sensorRead(sensorMidLeft);
  midRightValue = sensorRead(sensorMidRight);
  rightValue = sensorRead(sensorRight);

//  if (leftValue == 0 &&  midLeftValue == 0 && midRightValue == 0 && rightValue == 0) {
    //backward();
//  } else {
    degree = (2*leftValue) + (midLeftValue) - (midRightValue) - (2*rightValue);
    switch (degree) {
      case -3:
        turnHardRight();
        break;
      case -2:
        turnRight();
        break;
      case -1:
        turnSoftRight();
        break;
      case 0:
        forward();
        break;
      case 1:
        turnSoftLeft();
        break;
      case 2:
        turnLeft();
        break;
      case 3:
        turnHardLeft();
        break;
      default:
        stopMovement();
        break;
    
    }
    Serial.println(degree);
//  }
}













