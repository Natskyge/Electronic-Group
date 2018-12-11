//Pin Values
int SH_CP_clockPin0 = 5;
int ST_CP_latchPin0 = 6;
int DS_dataPin0 = 7;
int SH_CP_clockPin1 = 8;
int ST_CP_latchPin1 = 9;
int DS_dataPin1 = 10;

bool toastGood = false;



// data er det vi sander 
byte data=B10000001;
byte nop=B11111111;

//bit på glad smili

byte silg0=B11000011;
byte silg1=B10001001;
byte silg2=B00100100;
byte silg3=B00000100;

//byte silg0=B11111111;
//byte silg1=B11110111;
//byte silg2=B11011011;
//byte silg3=B11111011;

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
void setup() {
 pinMode (SH_CP_clockPin0,OUTPUT);
 pinMode (ST_CP_latchPin0,OUTPUT);
 pinMode (DS_dataPin0,OUTPUT);
 pinMode (SH_CP_clockPin1,OUTPUT);
 pinMode (ST_CP_latchPin1,OUTPUT);
 pinMode (DS_dataPin1,OUTPUT);
}

void loop() {
 if (toastGood==true){
  smilglad();
  } else{
    sursmil();
     }

 }
