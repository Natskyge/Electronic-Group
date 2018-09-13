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

int leftDistance = 4;
int midLeftDistance = 1;
int midRightDistance = -1;
int rightDistance = -4;

int blackWhiteSwitch = 300;

float timeStep = 0.005; // Seconds

float sumError = 0;

float cycleCount = 0;

float errorTerm = 0;

float prevError = 0;

float controlVar = 0;

int maxSpeed = 170;

float K_p = 200; //180
float K_i = 15; // 15
float K_d = 30; // 30

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
  int leftValue = sensorRead(sensorLeft);
  int midLeftValue = sensorRead(sensorMidLeft);
  int midRightValue = sensorRead(sensorMidRight);
  int rightValue = sensorRead(sensorRight);
  
  float procesVar = 0.25*(leftDistance*leftValue+midLeftDistance*midLeftValue+midRightDistance*midRightValue+rightDistance*rightValue);
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

void loop() {
  errorTerm = error();
  cycleCount = cycleCount + 1;

  controlVar = K_p*errorTerm + K_i*integrateError(errorTerm) + K_d*diffError(errorTerm,prevError);

  controlWheel(LEFT,FORWARD,speedLimiter(maxSpeed+controlVar));
  controlWheel(RIGHT,FORWARD,speedLimiter(maxSpeed-controlVar));

  Serial.println(controlVar);

  prevError = errorTerm;
  delay(timeStep*1000);
}
