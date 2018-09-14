
//Bluetooth Values
#include <SoftwareSerial.h>

int bluetoothTx=2;
int bluetoothRx=3;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

char data;

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
int torqueValue = 300;

//Canon value
int canonPin=5;

//Gear value
int gear;

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
      //NOTHING!
      break;
  }
  delay(10);
}


//Directional movement functions
void turnLeft(void) {
  controlWheel(RIGHT, FORWARD, gear);
  controlWheel(LEFT, FORWARD, 0);
}

void turnRight(void) {
  controlWheel(LEFT, FORWARD, gear);
  controlWheel(RIGHT, FORWARD, 0);
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

//void shoot(void){
//  digitalWrite(canonPin,HIGH);
//  delay(100);
//  digitalWrite(canonPin,LOW);
//  data=NULL;
//}


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

  if(bluetooth.available()){
    
    data = bluetooth.read();
    Serial.println(data);
    
    if(data=='E'){
      digitalWrite(canonPin,HIGH);
      delay(100);
      digitalWrite(canonPin,LOW);
    }
   
  }
   
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
      break;
      
  }
  
}
