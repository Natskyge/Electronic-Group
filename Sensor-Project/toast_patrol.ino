//Definitions for simplicity
#define STOP 0
#define START 1
#define FORWARD 2
#define BACKWARD 3

//Pin variables
const int buttonPin = 2;
const int inputPin1 = 3;
const int inputPin2 = 4;
const int voltagePin = A0;

const int SH_CP_clockPin0 = 5;
const int ST_CP_latchPin0 = 6;
const int DS_dataPin0 = 7;
const int SH_CP_clockPin1 = 8;
const int ST_CP_latchPin1 = 9;
const int DS_dataPin1 = 10;

//Control variables
bool buttonValue = LOW;
bool prevButtonValue = LOW;
bool stateSwitch = true;
int currentDir = STOP;
int sensorVal = 0;
float amps = 0.0;
int iterations = 0;
bool toastGood = false;
int upperToastBound = 439;
int lowerToastBound = 363;

// data vi sender
byte nop=B11111111;

//bit på glad smiley
byte silg0=B11000011;
byte silg1=B10001001;
byte silg2=B00100100;
byte silg3=B00000100;

byte sur0=B11000011;
byte sur1=B10000001;
byte sur2=B00100100;
byte sur3=B00010000;


byte rike0=B10000001;
byte rike1=B01000010;
byte rike2=B00100100;
byte rike3=B00011000;

byte rike[4]= {rike0,rike1,rike2,rike3};
byte gladsmil[4]={silg0,silg1,silg2,silg3};
byte sur[4]={sur0,sur1,sur2,sur3};

//Debug values
bool runGoing = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  pinMode (SH_CP_clockPin0,OUTPUT);
  pinMode (ST_CP_latchPin0,OUTPUT);
  pinMode (DS_dataPin0,OUTPUT);
  pinMode (SH_CP_clockPin1,OUTPUT);
  pinMode (ST_CP_latchPin1,OUTPUT);
  pinMode (DS_dataPin1,OUTPUT);
  displayBlank();
  Serial.begin(9600);
}

//Contols motor action
void controlMotor(int dirc) {
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

void judgeToast(int iterations) {
  if (lowerToastBound < iterations && iterations < upperToastBound) {
    toastGood = true;
  } else {
    toastGood = false;
  }
}

void sursmil(){
    for (int i=0; i<=3; i++){
    digitalWrite (ST_CP_latchPin1,LOW);
    digitalWrite (ST_CP_latchPin0,LOW); 
    shiftOut(DS_dataPin1,SH_CP_clockPin1,LSBFIRST,nop); 
    shiftOut(DS_dataPin1,SH_CP_clockPin1,LSBFIRST,sur[i]);
    shiftOut(DS_dataPin0,SH_CP_clockPin0,LSBFIRST,rike[i]);
    digitalWrite (ST_CP_latchPin1,HIGH);  
    digitalWrite (ST_CP_latchPin0,HIGH);
    }
}

void smilglad(){
    for (int i=0; i<=3; i++){
    digitalWrite (ST_CP_latchPin1,LOW);
    digitalWrite (ST_CP_latchPin0,LOW); 
    shiftOut(DS_dataPin1,SH_CP_clockPin1,LSBFIRST,gladsmil[i]);
    shiftOut(DS_dataPin1,SH_CP_clockPin1,LSBFIRST,nop); 
    shiftOut(DS_dataPin0,SH_CP_clockPin0,LSBFIRST,rike[i]);
    digitalWrite (ST_CP_latchPin1,HIGH);  
    digitalWrite (ST_CP_latchPin0,HIGH);
  }
}

void displayBlank(){
    for (int i=0; i<=3; i++){
    digitalWrite (ST_CP_latchPin1,LOW);
    digitalWrite (ST_CP_latchPin0,LOW); 
    shiftOut(DS_dataPin1,SH_CP_clockPin1,LSBFIRST,nop);
    shiftOut(DS_dataPin1,SH_CP_clockPin1,LSBFIRST,nop); 
    shiftOut(DS_dataPin0,SH_CP_clockPin0,LSBFIRST,nop);
    digitalWrite (ST_CP_latchPin1,HIGH);  
    digitalWrite (ST_CP_latchPin0,HIGH);
  }
}

void loop() {
  judgeToast(iterations);


  //Acts if button pressed
  buttonValue = digitalRead(buttonPin);
  if (prevButtonValue == LOW && buttonValue == HIGH) {
    switch (currentDir){
      //Starts test
      case STOP:  
        displayBlank();
        currentDir = FORWARD;
        stateSwitch = true;
        runGoing = true;
        break;
      //Aborts test
      case FORWARD:  
        currentDir = BACKWARD;
        stateSwitch = true;
        break;
      default:
        //NOTHING!
        break;
    }
  }

  //Calculates amps from sensor input 
  sensorVal = analogRead(voltagePin);
  amps = sensorVal*(5.0/1023.0); //input volt = motor-amps

  if (amps > 2.5) {
    ++iterations;
  }

  if(runGoing == true){
    Serial.println(iterations);
  }


  //Acts on pressure
  if (amps > 4.5) {
    switch (currentDir){
      case FORWARD:
        judgeToast(iterations);
        
        if (toastGood==true){
          smilglad();
        } else {
          sursmil();
        }
        currentDir = BACKWARD;
        stateSwitch = true;
        runGoing = false;
        break;
      case BACKWARD:
        iterations = 0;
        currentDir = STOP;
        stateSwitch = true;
        break;
      default:
        break;
    }
  }

  if (stateSwitch == true){
    controlMotor(currentDir);
    stateSwitch = false;
    delay(500);
  }

  prevButtonValue = buttonValue;
  delay(1);
}
