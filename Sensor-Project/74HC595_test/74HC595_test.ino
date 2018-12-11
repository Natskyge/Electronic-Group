int clockPin = 5;
int latchPin = 6;
int dataPin = 7; 
// data er det vi sander 
byte data=B00110101;

void setup() {
 pinMode (clockPin,OUTPUT)
 pinMode (latchPin,OUTPUT)
 pinMode (dataPin,OUTPUT)
  

}

void loop() {
//sander den dater vi skal seder til 74HC595
digitalWrite (latchpin LOW)
shiftOut(dataPin,clockPin,MSBFIRST,data);
digitalWrite (latchpin HIGH)



}
