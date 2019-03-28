#include <LiquidCrystal.h>
int maxLenString = 20;
int nameLen = 4;
int maxScoreBoardLen = 4;
char *strn = "Ayy LMAO";


const int rs = 1, en = 2, d4 = 10, d5 = 11, d6 =12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

typedef struct HighScore {
  char *initialer;
  int score;
} HighScore;

HighScore scoreBoard[4];

HighScore HighScoreNew(char* initialer, int score) {
  HighScore newHigh;
  newHigh.initialer = initialer;
  newHigh.score = score;
  return newHigh;
}

void initScoreBoard(HighScore *scoreBoard, int len) {
  HighScore tempScore = HighScoreNew("NaN",0);
  for (int i = 0; i < len; ++i) {
    scoreBoard[i] = tempScore;
  }
}

HighScore* updateScoreBoard(HighScore *scoreBoard, int len, HighScore hiScore) {
  for (int i = len-1; 0 <= i; --i) {
    // Shift forward, highest at first index.
    if (scoreBoard[i].score <= hiScore.score && i < len-1) {
      scoreBoard[i+1] = scoreBoard[i];
    }
  }

  for (int j = 0; j < len; ++j) {
    if (hiScore.score >= scoreBoard[j].score) {
      scoreBoard[j] = hiScore;
      break;
    }
  }

  return scoreBoard;
}

void printScoreBoard(HighScore *scoreBoard, int len) {
  if (len > maxScoreBoardLen) {
    printString(0,0,"ERROR: To long",15);
    return;
  }

  for (int i = 0; i < len; ++i) {
    printString(i,0,scoreBoard[i].initialer,nameLen);
    printString(i,nameLen,": ",2);
    printInteger(i,nameLen+2,scoreBoard[i].score);
  }
}

void printString(int line, int start, char *string, int len) {
  lcd.setCursor(start,line);
  
  if (len-start > maxLenString) {
    lcd.print("String to long.");
    return;
  }

  lcd.print(string);
}

void printInteger(int line, int start, int integer) {
  lcd.setCursor(start,line);
  lcd.print(integer);
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  initScoreBoard(scoreBoard,4);
  printScoreBoard(scoreBoard,4);
  delay(5000);
  HighScore hiBob = HighScoreNew("Bobb",69);
  updateScoreBoard(scoreBoard,4,hiBob);
  printScoreBoard(scoreBoard,4);
  delay(5000);
  HighScore hiBill = HighScoreNew("Bill",3);
  updateScoreBoard(scoreBoard,4,hiBill);
  printScoreBoard(scoreBoard,4);
  delay(5000);
  HighScore hiMunk = HighScoreNew("munk",420);
  updateScoreBoard(scoreBoard,4,hiMunk);
  printScoreBoard(scoreBoard,4);
  delay(5000);
  HighScore hiCrab = HighScoreNew("Crab",-100);
  updateScoreBoard(scoreBoard,4,hiCrab);
  printScoreBoard(scoreBoard,4);
}

void loop() {
  printScoreBoard(scoreBoard,4);
}
