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


int sensorRead(int sensorPin){
  sensorData = analogRead(sensorPin);
  if(sensorData <= blackWhiteSwitch){
    return B1;
  }
  else{
    return B0;
  }
}

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
midLeftValue = sensorRead(sensorMidLeft);
midRightValue = sensorRead(sensorMidRight);

leftValue = sensorRead(sensorLeft);
rightValue = sensorRead(sensorRight);

midValues = (midLeftValue<<1) + midRightValue;

switch(midValues){

  case B11:
    //move forward
    break;

  case B10:
    //Move left 
    break;

  case B01:
    //Move Right
    break;

  case B00:
    //Panic mode
    sideValues = (leftValue<<1) + rightValue;  

    switch(sideValues){
            case B11:
              //lol idk
              break;

            case B10:
              //lol idk
              break;

            case B01:
              //lol idk
              break;

            case B00:
              //MEGAPANIC
              break;

            default:
              break;
         
    }
    break;
  
  default: 
    break; 
  }
}













