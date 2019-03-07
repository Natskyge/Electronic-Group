// Definitions
#define UP 1
#define DOWN -1
#define RIGHT 1
#define LEFT -1
#define STOP 0
#define HORIZONTAL 2
#define VERTICAL 3

const int leftRightPin = A1;
const int upDownPin = A0;
int leftRightDegree;
int upDownDegree;

// Get human readable ouput from joystick
// Returns an array of two numbers, giving the direction.
// The number at index 0 is up down direction, The number
// at index 1 is left right direction
int getDirection(int axis) {
  // Get data from the axis
  int degree = 0;
  if (axis == VERTICAL) {
    degree = analogRead(upDownPin);
  } else if (axis == HORIZONTAL) {
    degree = analogRead(leftRightPin);
  }
  
  // Switch case select direction
  if (degree <= 333) {
    return axis == VERTICAL ? UP : LEFT;
  } else if (333 < degree  && degree <= 667) {
    return STOP;
  } else if (667 < degree) {
    return axis == VERTICAL ? DOWN : RIGHT;
  }

  // Shouldn't every run.
  return STOP;
}

void setup() {
  pinMode(leftRightPin, INPUT);
  pinMode(upDownPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Vertical: ");
  Serial.println(getDirection(VERTICAL));
  Serial.println("Horizontal: ");
  Serial.println(getDirection(HORIZONTAL));
  delay(200);
}
