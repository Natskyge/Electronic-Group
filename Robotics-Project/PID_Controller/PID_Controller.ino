//Sensor Values
int sensorData;

int sensorExtraLeft = A0;
int sensorLeft = A1;
int sensorMidLeft = A2;
int sensorMidRight = A3;
int sensorRight = A4;
int sensorExtraRight = A5;

int extraLeftValue = B0;
int leftValue = B0;
int midLeftValue = B0;
int midRightValue = B0;
int rightValue = B0;
int extraRightValue = B0;

int extraLeftDistance = 8; // 7
int leftDistance = 5;
int midLeftDistance = 1;
int midRightDistance = -1;
int rightDistance = -5;
int extraRightDistance = -8;

int blackWhiteSwitch = 450; // 300, 450

float timeStep = 0.001; // 0.005 Seconds

float sumError = 0;

float cycleCount = 0;

float errorTerm = 0;

float prevError = 0;

float controlVar = 0;

int maxSpeed = 120;

float K_p = 200; // 180, 198, 158
float K_i = 400; // 15, 396, 317
float K_d = 70; // 30, 66, 52

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
}

float error(void) {
  extraLeftValue = sensorRead(sensorExtraLeft);
  leftValue = sensorRead(sensorLeft);
  midLeftValue = sensorRead(sensorMidLeft);
  midRightValue = sensorRead(sensorMidRight);
  rightValue = sensorRead(sensorRight);
  extraRightValue = sensorRead(sensorExtraRight);
  
  float procesVar = 0.16*(extraLeftDistance*extraLeftValue + leftDistance*leftValue + midLeftDistance*midLeftValue + midRightDistance*midRightValue + rightDistance*rightValue + extraRightDistance*extraRightValue);
  
  float setPoint = 0;

  return setPoint - procesVar;
}

float diffError(float error, float prevError) {
  return (error-prevError)/(timeStep);
}

float integrateError(float error) {
  sumError = sumError + error*timeStep;
  return sumError;
}

int speedLimiter(int spd) {
  if (spd < 0) {
    return 0;
  } else if (spd > maxSpeed) {
    return maxSpeed;
  } else {
    return spd;
  }
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

void wheel(int side, int spd) {
  int truSpd = 0;
  if (spd < 0) {
    truSpd = -spd;
    if (truSpd > maxSpeed) {
      truSpd = maxSpeed;
    }
    Serial.println("BACKWARD");
    controlWheel(side,BACKWARD,truSpd);
  } else {
    truSpd = spd;
    if (truSpd > maxSpeed) {
      truSpd = maxSpeed;
    }
    Serial.println("FORWARD");
    controlWheel(side,FORWARD,truSpd);
  }
}

void loop() {
  errorTerm = error();
  cycleCount = cycleCount + 1;

  controlVar = K_p*errorTerm + K_i*integrateError(errorTerm) + K_d*diffError(errorTerm,prevError);

  wheel(LEFT,maxSpeed+controlVar);
  wheel(RIGHT,maxSpeed-controlVar);

  prevError = errorTerm;
  delay(timeStep*1000);
}
