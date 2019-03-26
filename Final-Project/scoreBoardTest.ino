// --- Definitions ---
// Pins
const int counterOutputPin = 8;
const int inputPinCifre1 = A0;
const int inputPinCifre2 = A1;

// Arrays for decoding voltage level to a number
// First two classifies the voltage level to 10 discrete steps found mathmatically
// Second takes has the coresponding number at index equally to the steps
int decodeArrayDigit1[10] = {72, 164, 222, 355, 449, 535, 635, 702, 852, 1024};
int decodeArrayDigit2[10] = {72, 164, 222, 355, 459, 535, 635, 702, 852, 1024};
int decodeArrayVal[10] = {0, 8, 4, 2, 1, 6, 9, 5, 3, 7};

// --- Functions ---
void setup() {
  pinMode(counterOutputPin, OUTPUT);
  pinMode(inputPinCifre1, INPUT);
  pinMode(inputPinCifre2, INPUT);
  Serial.begin(9600);
}

void incrementCurrentScore(void) {
  // Count advances on low to hight transistion
  digitalWrite(counterOutputPin, LOW);
  digitalWrite(counterOutputPin, HIGH);
  digitalWrite(counterOutputPin, LOW);
  return;
}

int decodeDigit(int digitNum, int digitVal) {
  // Find the digit we are reading
  if (digitNum == 1) {
    // Count steps into voltage array
    int stepsIn = 0;
    while (decodeArrayDigit1[stepsIn] < digitVal) {
      ++stepsIn;
    }

    return decodeArrayVal[stepsIn];
  } else if (digitNum == 2) {
    int stepsIn = 0;
    while (decodeArrayDigit2[stepsIn] < digitVal) {
      ++stepsIn;
    }

    // Return digit value
    return decodeArrayVal[stepsIn];
  }
}

int getCurrentScore(void) {
  // Measure, decode and add in the obvious way
  int cifre1Val = analogRead(inputPinCifre1);
  int cifre2Val = analogRead(inputPinCifre2);

  int cifre1 = decodeDigit(1,cifre1Val);
  int cifre2 = decodeDigit(2,cifre2Val);

  return cifre1 + 10*cifre2;
}

void loop() {
  Serial.println(getCurrentScore());
  delay(2000);
}
