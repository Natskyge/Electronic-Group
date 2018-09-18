// Bluetooth Values
#include <SoftwareSerial.h>
int bluetoothTx=2;
int bluetoothRx=3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
char data = ' ';
bool manual = true;


// Canon value
int canonPin=5;


// Gear value
int gear = 255;


// Sensor Values
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

int extraLeftDistance = 8;
int leftDistance = 5;
int midLeftDistance = 1;
int midRightDistance = -1;
int rightDistance = -5;
int extraRightDistance = -8;
int blackWhiteSwitch = 450;


// PID Constants
float timeStep = 0.001; // Seconds
float sumError = 0;
float errorTerm = 0;
float prevError = 0;
float controlVar = 0;
int maxSpeed = 170;
float K_p = 200; // Proportional control weight
float K_i = 400; // Integral control weight
float K_d = 70;  // Differntal control weight


// Motor values
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


//------Basic control functions------//
// Sensor white/black function - 1=black 0=white
int sensorRead(int sensorPin){
  sensorData = analogRead(sensorPin);
  if(sensorData <= blackWhiteSwitch){
    return B1;
  }
  else{
    return B0;
  }
}


// Wheel rotation function
void controlWheel(int side, int dirc, int spd) {
  // Select wheel, choose adequite pins
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
    default:
     // NOTHING!
     break;
  }
}

//------Bluetooth control functions------//
// Directional movement functions
void turnLeft(void) {
  controlWheel(RIGHT, FORWARD, gear);
  controlWheel(LEFT, FORWARD, gear/2);
}

void turnRight(void) {
  controlWheel(LEFT, FORWARD, gear);
  controlWheel(RIGHT, FORWARD, gear/2);
}

void forward(void) {
  controlWheel(LEFT, FORWARD, gear);
  controlWheel(RIGHT, FORWARD, gear);
}

void backward(void) {
  controlWheel(LEFT, BACKWARD, gear);
  controlWheel(RIGHT, BACKWARD, gear);
}

void stopMovement(void) {
    controlWheel(LEFT, FORWARD, 0);
    controlWheel(RIGHT, FORWARD, 0);
}


// Checks for manual/automatic mode
bool manualCheck(char btData, bool manualBool){
  switch(btData){

    case 'M':
      return true;
      break;

    case 'A':
      return false;
      break;

    default:
      return manualBool;
      break;
  }
}


// All controlls for manual/bluetooth
void btControl(char btData){
  
  if(data=='E'){
      digitalWrite(canonPin,HIGH);
      delay(100);
      digitalWrite(canonPin,LOW);
      
  }else{
    switch (data) {
    
      case 'R':
        turnRight();
        break;
    
      case 'F':
        forward();
        break;
    
      case 'L':
        turnLeft();
        break;
    
      case 'S':
        stopMovement();
        break;
      
     case 'B':
        backward();
        break;

      // Gear functions
      case '6':
        gear=255;
        break;
      
      case '5':
        gear=200;
        break;
      
      case '4':
        gear=175;
        break;
      
      case '3':
        gear=150;
        break;
      
      case '2':
        gear=100;
        break;
      
      case '1':
        gear=50;
        break;
      
      default:
        //Nothing!
        break;
   
    }
  }    
}


//------PID control functions------//
// PID Error function
float error(void) {
  // Sensors values, 0 if white, 1 if black
  int extraLeftValue = sensorRead(sensorExtraLeft);
  int leftValue = sensorRead(sensorLeft);
  int midLeftValue = sensorRead(sensorMidLeft);
  int midRightValue = sensorRead(sensorMidRight);
  int rightValue = sensorRead(sensorRight);
  int extraRightValue = sensorRead(sensorExtraRight);

  //Calculations for error/unballance
  float procesVar = 0.16*(extraLeftDistance*extraLeftValue + leftDistance*leftValue + midLeftDistance*midLeftValue + midRightDistance*midRightValue + rightDistance*rightValue + extraRightDistance*extraRightValue);
  float setPoint = 0;
  return setPoint - procesVar;  // Calculates diffrence from setPoint, IE how unballanced the car is
}

// Differntiate error function
float diffError(float error, float prevError) {
  // Discreet differntiation, indicates chang in the course
  return (error-prevError)/(timeStep);
}

// Integrate error function
float integrateError(float error) {
  // Riemann sum integration, increases intensity of control the longer it doesn't work.
  sumError = sumError + error*timeStep;
  return sumError;
}

// Wheel control function, negative spd = drives backwards
void wheel(int side, int spd) {
  int truSpd = 0;
  // Wheel turning backwards
  if (spd < 0) {
    truSpd = -spd;
    if (truSpd > maxSpeed) {
      truSpd = maxSpeed; // Speed to high
    }
    controlWheel(side,BACKWARD,truSpd);
  // Wheel turning forwards
  } else {
    truSpd = spd;
    if (truSpd > maxSpeed) {
      truSpd = maxSpeed; // Speed to high
    }
    controlWheel(side,FORWARD,truSpd);
  }
}


void setup() {
  pinMode(pinLeftA, OUTPUT);
  pinMode(pinLeftB, OUTPUT);
  pinMode(pinLeftPWM, OUTPUT);
  pinMode(pinRightA, OUTPUT);
  pinMode(pinRightB, OUTPUT);
  pinMode(pinRightPWM, OUTPUT);

  pinMode(canonPin,OUTPUT);
  
  Serial.begin(9600);
  bluetooth.begin(115200);
}


void loop() {
  // Connect to bluetooth
  if(bluetooth.available()){
    data = bluetooth.read();
  }

  // Checks if manual is on
  manual = manualCheck(data, manual);
  if (manual == true) {
    btControl(data);
    sumError = 0; // Resets PID control loop
  } else {
    errorTerm = error();

    // controlVar is half the difference between the power on the two motors, negative included
    controlVar = K_p*errorTerm + K_i*integrateError(errorTerm) + K_d*diffError(errorTerm,prevError);

    wheel(LEFT,maxSpeed+controlVar);
    wheel(RIGHT,maxSpeed-controlVar);

    prevError = errorTerm; // For differential
  }
  delay(timeStep*1000); // Necessary for integral and derivative
}
