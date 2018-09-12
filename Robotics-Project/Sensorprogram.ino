int sensorData;
int sensorLeft = A0;
String leftValue = "x";
int sensorMidLeft = A1;
String midLeftValue = "x";
int sensorMidRight = A2;
String midRightValue = "x";
int sensorRight = A3;
String rightValue = "x";

String values = "";
String midValues = "";
int blackWhiteSwitch = 300;


String sensorRead(int sensorPin){
  sensorData = analogRead(sensorPin);
  if(sensorData <= blackWhiteSwitch){
    return "b";
  }
  else{
    return "w";
  }
}

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
leftValue = sensorRead(sensorLeft);
midLeftValue = sensorRead(sensorMidLeft);
midRightValue = sensorRead(sensorMidRight);
rightValue = sensorRead(sensorRight);

midValues = midLeftValue + midRightValue;
values = leftValue + midLeftValue + midRightValue + rightValue;

Serial.println(values);

}













