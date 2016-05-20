/*
Word clock, made by Jordy Moors (@moors7). With some great help from
Garrett Bartley (@wgbartley) and Paul Kourany (@Peekay123).
I'd appreciate it if you left this in here should you modify this code :)
Thanks!
*/

SYSTEM_MODE(SEMI_AUTOMATIC);

// This #include statement was automatically added by the Particle IDE.
#include "SparkIntervalTimer/SparkIntervalTimer.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_mfGFX/Adafruit_mfGFX.h"

// This #include statement was automatically added by the Particle IDE.
#include "RGBmatrixPanel/RGBmatrixPanel.h"

#include <math.h>

// This #include statement was automatically added by the Particle IDE.
#include "snake.h"



// =========================== Snake code =========================

void play_snake();

int length = 3;
bool update = true;
int Delay = 0;
unsigned long speed = game_speed;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
// ========================== Snake code ==========================



// ========================== MATRIX ==============================
byte matrixBuffer [3] [16] [16]; // A 3 layer display buffer for the creation of various graphical effects

boolean intro = true;            // Indicates if mode has just been entered after mode change.

unsigned long FrameTime = 0;     // Keeps track of timeing between animation frames.
unsigned int  FrameRate = 0;     // Animation frame rate.
unsigned int frameCount = 0;     // Keeps counts of the number of frames since the begining of current transition.

byte field = 1;                 // Divides frames into fields to allow traces to move at different speeds

typedef struct                  // Traces are sprite like graphical elements that can be
{ // manipulated in a variety of ways.
  boolean active;               // Active or inactive.
  int regen;                    // Frame when the trace will regenerate.
  byte xPos;                    // X position
  byte yPos;                    // Y position
  byte speed;                   // Speed
  byte length;                  // Length
  byte terminate;               // Termination point, Should be at least 8 + Length
}  trace;
trace streamerTrace[16];        // 16 traces in struct array for streamer animations
// ===========================/MATRIX=================================

int colorRandom[6][3] = {{255,0,0},{0,255,0},{0,0,255},{255,255,0},{0,255,255},{255,0,255}};

// Mode 0 = "Its MM minute(s) past/to HH"
// mode 1 = "Its HH oh 0M"
int timeMode = 0;

// displayMode
// 0 = clock
// 1 = Snake
// 2 = Matrix animation
// 3 = Digital
int displayMode = 0;

int specialModeNumber = -1;

int r = 255;
int g = 0;
int b = 0;

char pubstring[64];

char topLine[64] = {};

int8_t timeZone = -7;

unsigned long previousDisplayMillis = 0;
unsigned long delayTime = 5000;

// // allow us to use itoa() in this scope
extern char* itoa(int a, char* buffer, unsigned char radix);
void doWord(const uint8_t *w);
void blackOut();
void displayHour();
void doTime();
void displayMinute();
void mayTheForce();
void useTheForce();
void doOrDoNot();
int setMode(String command);
void lightLetter(int X, int Y, int red, int green, int blue);


/** Define RGB matrix panel GPIO pins **/
#if defined (STM32F10X_MD)  //Core
#define CLK D6
#define OE  D7
#define LAT A4
#define A   A0
#define B   A1
#define C   A2
#define D   A3
#endif

/** Define RGB matrix panel GPIO pins **/
#define CLK D6
#define OE  D7
#define LAT TX
#define A   A0
#define B   A1
#define C   A2
#define D	RX
/****************************************/


/****************************************/

//#define X_MAX 31    // Matrix X max LED coordinate (for 2 displays placed next to each other)
//#define Y_MAX 31


/***** Create RGBmatrix Panel instance *****
  Last parameter = 'true' enables double-buffering, for flicker-free,
  buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
  until the first call to swapBuffers().  This is normal. */
//RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true);
/*******************************************/



//  ======================== Snake code ========================
mysnake* temp;
mysnake snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 4]; //create snake matrix
mysnake* snakehead; //pointer to head of the snake
food apple;
food* applepointer;

Serpent Snake(&matrix);
//  ======================= /Snake code ========================



// All the word positions/lengths
//x, y, length, height
static const uint8_t wordIts[8] = {0, 0, 3, 1};
static const uint8_t wordHalf[8] = {4, 0, 4, 1};
static const uint8_t wordTwenty[8] = {10, 0, 6, 1};
static const uint8_t wordFive[8] = {1, 1, 4, 1};
static const uint8_t wordTwo[8] = {5, 1, 3, 1};
static const uint8_t wordEight[8] = {8, 1, 5, 1};
static const uint8_t wordEighteen[8] = {8, 1, 8, 1};
static const uint8_t wordOne[8] = {0, 2, 3, 1};
static const uint8_t wordThirteen[8] = {4, 2, 8, 1};
static const uint8_t wordTen[8] = {12, 2, 3, 1};
static const uint8_t wordEleven[8] = {1, 3, 6, 1};
static const uint8_t wordThree[8] = {10, 3, 5, 1};
static const uint8_t wordA[8] = {0, 4, 1, 1};
static const uint8_t wordQuarter[8] = {2, 4, 7, 1};
static const uint8_t wordTwelve[8] = {10, 4, 6, 1};
static const uint8_t wordSix[8] = {1, 5, 3, 1};
static const uint8_t wordSixteen[8] = {1, 5, 7, 1};
static const uint8_t wordFour[8] = {8, 5, 4, 1};
static const uint8_t wordFourteen[8] = {8, 5, 8, 1};
static const uint8_t wordSeven[8] = {0, 6, 5, 1};
static const uint8_t wordSeventeen[8] = {0, 6, 9, 1};
static const uint8_t wordNine[8] = {8, 6, 4, 1};
static const uint8_t wordNineteen[8] = {8, 6, 8, 1};
static const uint8_t wordMinute[8] = {1, 7, 6, 1};
static const uint8_t wordMinutes[8] = {1, 7, 7, 1};
static const uint8_t wordPast[8] = {9, 7, 4, 1};
static const uint8_t wordTo[8] = {12, 7, 2, 1};
static const uint8_t wordO[8] = {13, 7, 1, 1};
static const uint8_t wordOh[8] = {13, 7, 2, 1};
static const uint8_t wordFifty2[8] = {2, 8, 5, 1};
static const uint8_t wordTwenty2[8] = {9, 8, 6, 1};
static const uint8_t wordTwelve2[8] = {2, 9, 6, 1};
static const uint8_t wordTen2[8] = {8, 9, 3, 1};
static const uint8_t wordForty2[8] = {11, 9, 5, 1};
static const uint8_t wordThirty2[8] = {1, 10, 6, 1};
static const uint8_t wordThirteen2[8] = {7, 10, 8, 1};
static const uint8_t wordFifteen2[8] = {0, 11, 7, 1};
static const uint8_t wordThree2[8] = {10, 11, 5, 1};
static const uint8_t wordEight2[8] = {0, 12, 5, 1};
static const uint8_t wordEighteen2[8] = {0, 12, 8, 1};
static const uint8_t wordSix2[8] = {8, 12, 3, 1};
static const uint8_t wordSixteen2[8] = {8, 12, 12, 1};
static const uint8_t wordFive2[8] = {0, 13, 4, 1};
static const uint8_t wordTwo2[8] = {4, 13, 3, 1};
static const uint8_t wordOne2[8] = {6, 13, 3, 1};
static const uint8_t wordEleven2[8] = {8, 13, 6, 1};
static const uint8_t wordFour2[8] = {0, 14, 4, 1};
static const uint8_t wordFourteen2[8] = {0, 14, 8, 1};
static const uint8_t wordNine2[8] = {7, 14, 4, 1};
static const uint8_t wordNineteen2[8] = {7, 14, 8, 1};
static const uint8_t wordSeven2[8] = {0, 15, 5, 1};
static const uint8_t wordSeventeen2[8] = {0, 15, 9, 1};
static const uint8_t wordOclock[8] = {9, 15, 6, 1};
/* === May/Use the Force be with you === */
static const uint8_t wordUse[8] = {1, 4, 1, 3};
static const uint8_t wordMay[8] = {0, 3, 1, 3};
static const uint8_t wordThe[8] = {5, 1, 1, 3};
static const uint8_t wordForce[8] = {7, 0, 1, 5};
static const uint8_t wordBe[8] = {1, 8, 1, 2};
static const uint8_t wordWith[8] = {3, 9, 1, 4};
static const uint8_t wordYou[8] = {15, 13, 1, 3};
/* ===================================== */
/* === Do or do not, there is no try === */
static const uint8_t wordDo[8] = {0, 1, 1, 2};
static const uint8_t wordOr[8] = {7, 1, 1, 2};
static const uint8_t wordDo2[8] = {9, 4, 1, 2};
static const uint8_t wordNot[8] = {15, 1, 1, 3};
static const uint8_t wordThere[8] = {3, 11, 1, 5};
static const uint8_t wordIs[8] = {9, 10, 1, 2};
static const uint8_t wordNo[8] = {12, 8, 1, 2};
static const uint8_t wordTry[8] = {15, 7, 1, 3};
/* =================================== */
/* === Sith / Jedi / Yoda ============ */
static const uint8_t wordJedi[8] = {0, 7, 1, 4};
static const uint8_t wordSith[8] = {8, 7, 1, 4};
static const uint8_t wordYoda[8] = {15, 9, 1, 4};
/* =================================== */


void change_modes()
{
    int pickedColor = random(5);
    
    r = colorRandom[pickedColor][0];
    g = colorRandom[pickedColor][1];
    b = colorRandom[pickedColor][2];
    
    switch (displayMode){
        case 0:
            displayMode = 2;
            break;
        case 2:
            displayMode = 3;
            break;
        case 3:
            displayMode = 0;
            break;
        default:
            displayMode = 0;
            break;
    }
}

Timer timer(15000, change_modes);


void setup() {
    
  Particle.connect();    
    // wait for the cloud connection to be connected or timeout after 10 seconds
  if (!waitFor(Particle.connected, 10000)) {
    Time.setTime(1463662528);
    //doTime();
  }
    
  // Initialize the panel
  matrix.begin();

 
  Particle.function("text", text);                      // scroll a text over the matrix
  Particle.function("handleparams",handleParams);         // handles all parameters.
  
  // ===== Snake =====
  snakehead = &snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3];
  apple.row = 5;
  apple.column = 5;
  applepointer = &apple;
  Snake.snake_intialization(snake); //initialize snake location and direction
  // ===== Snake =====

  Time.zone(timeZone);       // Set time zone
  doTime();
  
  //uncomment this for demo mode
  timer.start();
}



void loop() {
  currentMillis = millis();

  if (specialModeNumber >= 0) {
    delayTime = 5000;
    blackOut();

    switch (specialModeNumber) {
      case 0:
        useTheForce();                      //display "use the force"
        delayTime = 2500;
        break;
      case 1:
        mayTheForce();                      // display "may the force be with you"
		delayTime = 2500;
        break;
      case 2:
        doOrDoNot();                        // display "Do ot do not, there is no try"
        delayTime = 2500;
        break;
      case 3:
        //lightLetter(14, 1, 0, 255, 0);      // light up the Ion cannon pixel
        shootCannon();
        delayTime = 18000;
        break;
      case 4:
        doWord(wordJedi);                   // display "Jedi"
		delayTime = 2500;
        break;
      case 5:
        doWord(wordSith);                   // display "Sith"
		delayTime = 2500;
        break;
      case 6:
        doWord(wordYoda);                   // display "Yoda"
		delayTime = 2500;
        break;
    }

    matrix.swapBuffers(true);
    //delay(delayTime);
    specialModeNumber = -1;
  }

  if (currentMillis - previousDisplayMillis > delayTime){
    previousDisplayMillis = currentMillis;
  
      switch (displayMode) {
        case 0:   // display the 'normal' wordclock
          doTime();
          break;
    
        case 1:   // play Snake
          if (currentMillis - previousMillis > speed) {
            // save the last time you blinked the LED
            previousMillis = currentMillis;
            update ? snake_alive() : snake_dead();
          }
          break;
    
        case 2:   // display matrix animation
          if ( currentMillis >= FrameTime + FrameRate) {  // Runs animation function every frame time
            FrameTime = currentMillis;
            streamerAnimation();                          // Just streamer traces animation, no time.
          }
          matrix.swapBuffers(true);
          break;
    
        case 3:   // Show time in digital fashion
          printTimeBig();
          break;
    
        default:  // default to normal wordclock
          doTime();
          break;
      }
      delayTime = 0;
   }
}


void scrollBigMessage(char *m, int timeDelay = 50) {
  matrix.setTextSize(2);
  matrix.setTextWrap(false);
  
  matrix.setTextColor(matrix.Color333(r,g,b));

  int l = (strlen(m) * -12) - 32;

  for (int i = 32; i > l; i -= 2) {
    matrix.fillScreen(0);
    matrix.swapBuffers(true);
    matrix.setCursor(i, 8);

    matrix.print(m);
    matrix.swapBuffers(false);
    delay(timeDelay);
    Particle.process();
  }
}


int text(String command) {
  command.toCharArray(topLine, 64);

  scrollBigMessage(topLine);
  return 0;
}

// this function automagically gets called upon a matching POST request
int handleParams(String command)
{
  //look for the matching argument <-- max of 64 characters long
  int p = 0;
  while (p<(int)command.length()) {
    int i = command.indexOf(',',p);
    if (i<0) i = command.length();
    int j = command.indexOf('=',p);
    if (j<0) break;
    String key = command.substring(p,j).toUpperCase();
    String value = command.substring(j+1,i);
    int val = value.toInt();
    
    
    // Modes
    if (key=="SETTIMEMODE")         // 0 - 1
      timeMode = val;
    else if (key=="SPECIALS")       // 0 - 6
      specialModeNumber = val;
    else if (key=="DISPLAYMODE")    // 0 - 3
      displayMode = val;
    
    // text color
    else if (key=="R")              // 0 - 255
      r = val;
    else if (key=="G")
      g = val;
    else if (key=="B")
      b = val;    
    
    // Snake    
    else if (key=="DIRECTION")
      Snake.set_new_direction(val); // 0 - 3
    else if (key=="SNAKESPEED")     // 50 - 250
      speed = val;
    
    else if (key=="SYSRESET")       // instant
      System.reset();
      
    else if (key=="MATRIXSPEED")
      FrameRate = val;

    p = i+1;
  }
  return 1;
}

void shootCannon(){
  
  // X - X      - X -      - - -
  // - - -  ->  X - X  ->  - X -
  // X - X      - X -      - - -
  
  
  Particle.publish("shoot");
  for (int i = 0; i < 38; i++){
      blackOut();
      lightLetter(13, 0, 0, 255, 0);    // light up the top left
      lightLetter(15, 0, 0, 255, 0);    // top right
      lightLetter(13, 2, 0, 255, 0);
      lightLetter(15, 2, 0, 255, 0);
      matrix.swapBuffers(true);
      delay(100);
      blackOut();
      lightLetter(14, 0, 0, 255, 0);    
      lightLetter(14, 2, 0, 255, 0);    
      lightLetter(13, 1, 0, 255, 0);
      lightLetter(15, 1, 0, 255, 0);
      matrix.swapBuffers(true);
      delay(100);
  }
  blackOut();
  lightLetter(14, 1, 0, 255, 0);
  matrix.swapBuffers(true);
  delay(100);
  blackOut();
  lightLetter(14, 1, 0, 255, 0);
  matrix.swapBuffers(true);
  delay(100);
  blackOut();
  for (int i = 0; i < 15; i++){
      blackOut();
      lightLetter(13, 0, 0, 255, 0);    // light up the top left
      lightLetter(15, 0, 0, 255, 0);    // top right
      lightLetter(13, 2, 0, 255, 0);
      lightLetter(15, 2, 0, 255, 0);
      matrix.swapBuffers(true);
      delay(50);
      blackOut();
      lightLetter(14, 0, 0, 255, 0);    
      lightLetter(14, 2, 0, 255, 0);    
      lightLetter(13, 1, 0, 255, 0);
      lightLetter(15, 1, 0, 255, 0);
      matrix.swapBuffers(true);
      delay(50);
  }
  blackOut();
  lightLetter(14, 1, 0, 255, 0);
  matrix.swapBuffers(true);
  delay(500);
  blackOut();
  matrix.swapBuffers(true);
  delay(100);
  lightLetter(14, 1, 0, 255, 0);
  matrix.swapBuffers(true);
  delay(500);
  blackOut();
  matrix.swapBuffers(true);
  delay(100);
  lightLetter(14, 1, 0, 255, 0);
  matrix.swapBuffers(true);
  delay(3000);
  blackOut();
  
  delay(500);
}


void doTime() {
    blackOut();

    doWord(wordIts);
    displayHour();
    displayMinute();
    matrix.swapBuffers(true);
    delay(1000);
}

void printTimeBig() {
  blackOut();
  matrix.setTextSize(2);

  matrix.setCursor(2 * 3, 0);
  matrix.setTextColor(matrix.Color333(0, 7, 0));
  switch (Time.hour()) {
    case 0:
      matrix.print("00");
      break;
    case 1:
      matrix.print("01");
      break;
    case 2:
      matrix.print("02");
      break;
    case 3:
      matrix.print("03");
      break;
    case 4:
      matrix.print("04");
      break;
    case 5:
      matrix.print("05");
      break;
    case 6:
      matrix.print("06");
      break;
    case 7:
      matrix.print("07");
      break;
    case 8:
      matrix.print("08");
      break;
    case 9:
      matrix.print("09");
      break;
    default:
      matrix.print(Time.hour());
  }

  matrix.setCursor(2 * 3, 2 * 8);
  matrix.setTextColor(matrix.Color333(0, 7, 7));
  switch (Time.minute()) {
    case 0:
      matrix.print("00");
      break;
    case 1:
      matrix.print("01");
      break;
    case 2:
      matrix.print("02");
      break;
    case 3:
      matrix.print("03");
      break;
    case 4:
      matrix.print("04");
      break;
    case 5:
      matrix.print("05");
      break;
    case 6:
      matrix.print("06");
      break;
    case 7:
      matrix.print("07");
      break;
    case 8:
      matrix.print("08");
      break;
    case 9:
      matrix.print("09");
      break;
    default:
      matrix.print(Time.minute());
  }
  matrix.swapBuffers(true);
  delay(1000);
}

//Display functions

void blackOut() {
  matrix.fillScreen(matrix.Color444(0, 0, 0));
}

void useTheForce() {
  doWord(wordUse);
  doWord(wordThe);
  doWord(wordForce);
}

void mayTheForce() {
  doWord(wordMay);
  doWord(wordThe);
  doWord(wordForce);
  doWord(wordBe);
  doWord(wordWith);
  doWord(wordYou);
}

void doOrDoNot() {
  doWord(wordDo);
  doWord(wordOr);
  doWord(wordDo2);
  doWord(wordNot);
  doWord(wordThere);
  doWord(wordIs);
  doWord(wordNo);
  doWord(wordTry);
}


void lightLetter(int X, int Y, int red = r, int green = g, int blue = b) {
  X *= 2;
  Y *= 2;
  matrix.drawPixel(X       , Y      , matrix.Color333(red, green, blue));
  matrix.drawPixel(X + 1   , Y      , matrix.Color333(red, green, blue));
  matrix.drawPixel(X       , Y + 1  , matrix.Color333(red, green, blue));
  matrix.drawPixel(X + 1   , Y + 1  , matrix.Color333(red, green, blue));
}

//(un)set Words
void doWord(const uint8_t *w) {
  int X = 0;
  int Y = 0;

  //finish loop per vertical row
  for (int i = 0; i < w[3]; i++) {
    //finish loops horizontally
    for (int j = 0; j < w[2]; j++) {
      X = (w[0] + j);
      Y = (w[1] + i);
      lightLetter(X, Y);
    }
  }
}

//set hours/minutes
void displayHour() {
  int h = Time.hourFormat12();
  int m = Time.minute();

  if (timeMode == 0) {
    if (m != 0 && m <= 30) {
      doWord(wordPast);
    }
    else if (m > 30) {
      h++;

      if (h == 13) {
        h = 1;
      }

      doWord(wordTo);
    }

    // hour
    switch (h) {
      case 1:
        (m != 0) ? doWord(wordOne2) : doWord(wordOne);
        break;
      case 2:
        (m != 0) ? doWord(wordTwo2) : doWord(wordTwo);
        break;
      case 3:
        (m != 0) ? doWord(wordThree2) : doWord(wordThree);
        break;
      case 4:
        (m != 0) ? doWord(wordFour2) : doWord(wordFour);
        break;
      case 5:
        (m != 0) ? doWord(wordFive2) : doWord(wordFive);
        break;
      case 6:
        (m != 0) ? doWord(wordSix2) : doWord(wordSix);
        break;
      case 7:
        (m != 0) ? doWord(wordSeven2) : doWord(wordSeven);
        break;
      case 8:
        (m != 0) ? doWord(wordEight2) : doWord(wordEight);
        break;
      case 9:
        (m != 0) ? doWord(wordNine2) : doWord(wordNine);
        break;
      case 10:
        (m != 0) ? doWord(wordTen2) : doWord(wordTen);
        break;
      case 11:
        (m != 0) ? doWord(wordEleven2) : doWord(wordEleven);
        break;
      case 12:
        (m != 0) ? doWord(wordTwelve2) : doWord(wordTwelve);
        break;
    }
  }

  else if (timeMode == 1) {
    switch (h) {
      case 1:
        doWord(wordOne);
        break;
      case 2:
        doWord(wordTwo);
        break;
      case 3:
        doWord(wordThree);
        break;
      case 4:
        doWord(wordFour);
        break;
      case 5:
        doWord(wordFive);
        break;
      case 6:
        doWord(wordSix);
        break;
      case 7:
        doWord(wordSeven);
        break;
      case 8:
        doWord(wordEight);
        break;
      case 9:
        doWord(wordNine);
        break;
      case 10:
        doWord(wordTen);
        break;
      case 11:
        doWord(wordEleven);
        break;
      case 12:
        doWord(wordTwelve);
        break;
    }
  }
}

void displayMinute() {
  int m = Time.minute();

  if (timeMode == 0) {
    switch (m) {
      case 0:
        doWord(wordOclock);
        break;
      case 1:
        doWord(wordOne);
        doWord(wordMinute);
        break;
      case 2:
        doWord(wordTwo);
        break;
      case 3:
        doWord(wordThree);
        break;
      case 4:
        doWord(wordFour);
        break;
      case 5:
        doWord(wordFive);
        break;
      case 6:
        doWord(wordSix);
        break;
      case 7:
        doWord(wordSeven);
        break;
      case 8:
        doWord(wordEight);
        break;
      case 9:
        doWord(wordNine);
        break;
      case 10:
        doWord(wordTen);
        break;
      case 11:
        doWord(wordEleven);
        break;
      case 12:
        doWord(wordTwelve);
        break;
      case 13:
        doWord(wordThirteen);
        break;
      case 14:
        doWord(wordFourteen);
        break;
      case 15:
        doWord(wordA);
        doWord(wordQuarter);
        break;
      case 16:
        doWord(wordSixteen);
        break;
      case 17:
        doWord(wordSeventeen);
        break;
      case 18:
        doWord(wordEighteen);
        break;
      case 19:
        doWord(wordNineteen);
        break;
      case 20:
        doWord(wordTwenty);
        break;
      case 21:
        doWord(wordTwenty);
        doWord(wordOne);
        break;
      case 22:
        doWord(wordTwenty);
        doWord(wordTwo);
        break;
      case 23:
        doWord(wordTwenty);
        doWord(wordThree);
        break;
      case 24:
        doWord(wordTwenty);
        doWord(wordFour);
        break;
      case 25:
        doWord(wordTwenty);
        doWord(wordFive);
        break;
      case 26:
        doWord(wordTwenty);
        doWord(wordSix);
        break;
      case 27:
        doWord(wordTwenty);
        doWord(wordEight);
        break;
      case 28:
        doWord(wordTwenty);
        doWord(wordEight);
        break;
      case 29:
        doWord(wordTwenty);
        doWord(wordNine);
        break;
      case 30:
        doWord(wordHalf);
        break;
      case 31:
        doWord(wordTwenty);
        doWord(wordNine);
        break;
      case 32:
        doWord(wordTwenty);
        doWord(wordEight);
        break;
      case 33:
        doWord(wordTwenty);
        doWord(wordSeven);
        break;
      case 34:
        doWord(wordTwenty);
        doWord(wordSix);
        break;
      case 35:
        doWord(wordTwenty);
        doWord(wordFive);
        break;
      case 36:
        doWord(wordTwenty);
        doWord(wordFour);
        break;
      case 37:
        doWord(wordTwenty);
        doWord(wordThree);
        break;
      case 38:
        doWord(wordTwenty);
        doWord(wordTwo);
        break;
      case 39:
        doWord(wordTwenty);
        doWord(wordOne);
        break;
      case 40:
        doWord(wordTwenty);
        break;
      case 41:
        doWord(wordNineteen);
        break;
      case 42:
        doWord(wordEighteen);
        break;
      case 43:
        doWord(wordSeventeen);
        break;
      case 44:
        doWord(wordSixteen);
        break;
      case 45:
        doWord(wordA);
        doWord(wordQuarter);
        break;
      case 46:
        doWord(wordFourteen);
        break;
      case 47:
        doWord(wordThirteen);
        break;
      case 48:
        doWord(wordTwelve);
        break;
      case 49:
        doWord(wordEleven);
        break;
      case 50:
        doWord(wordTen);
        break;
      case 51:
        doWord(wordNine);
        break;
      case 52:
        doWord(wordEight);
        break;
      case 53:
        doWord(wordSeven);
        break;
      case 54:
        doWord(wordSix);
        break;
      case 55:
        doWord(wordFive);
        break;
      case 56:
        doWord(wordFour);
        break;
      case 57:
        doWord(wordThree);
        break;
      case 58:
        doWord(wordTwo);
        break;
      case 59:
        doWord(wordOne);
        doWord(wordMinute);
        break;
    }
    if (m != 0 && m != 1 && m != 15 && m != 30 && m != 45 && m != 59) {
      doWord(wordMinutes);
    }
  }
  else if (timeMode == 1) {
    switch (m) {
      case 0:
        doWord(wordOclock);
        break;
      case 1:
        doWord(wordO);
        doWord(wordOne2);
        break;
      case 2:
        doWord(wordO);
        doWord(wordTwo2);
        break;
      case 3:
        doWord(wordO);
        doWord(wordThree2);
        break;
      case 4:
        doWord(wordO);
        doWord(wordFour2);
        break;
      case 5:
        doWord(wordO);
        doWord(wordFive2);
        break;
      case 6:
        doWord(wordO);
        doWord(wordSix2);
        break;
      case 7:
        doWord(wordO);
        doWord(wordSeven2);
        break;
      case 8:
        doWord(wordO);
        doWord(wordEight2);
        break;
      case 9:
        doWord(wordO);
        doWord(wordNine2);
        break;
      case 10:
        doWord(wordTen2);
        break;
      case 11:
        doWord(wordEleven2);
        break;
      case 12:
        doWord(wordTwelve2);
        break;
      case 13:
        doWord(wordThirteen2);
        break;
      case 14:
        doWord(wordFourteen2);
        break;
      case 15:
        doWord(wordFifteen2);
        break;
      case 16:
        doWord(wordSixteen2);
        break;
      case 17:
        doWord(wordSeventeen2);
        break;
      case 18:
        doWord(wordEighteen2);
        break;
      case 19:
        doWord(wordNineteen2);
        break;
      case 20:
        doWord(wordTwenty2);
        break;
      case 21:
        doWord(wordTwenty2);
        doWord(wordOne2);
        break;
      case 22:
        doWord(wordTwenty2);
        doWord(wordTwo2);
        break;
      case 23:
        doWord(wordTwenty2);
        doWord(wordThree2);
        break;
      case 24:
        doWord(wordTwenty2);
        doWord(wordFour2);
        break;
      case 25:
        doWord(wordTwenty2);
        doWord(wordFive2);
        break;
      case 26:
        doWord(wordTwenty2);
        doWord(wordSix2);
        break;
      case 27:
        doWord(wordTwenty2);
        doWord(wordEight2);
        break;
      case 28:
        doWord(wordTwenty2);
        doWord(wordEight2);
        break;
      case 29:
        doWord(wordTwenty2);
        doWord(wordNine2);
        break;
      case 30:
        doWord(wordThirty2);
        break;
      case 31:
        doWord(wordThirty2);
        doWord(wordOne2);
        break;
      case 32:
        doWord(wordThirty2);
        doWord(wordTwo2);
        break;
      case 33:
        doWord(wordThirty2);
        doWord(wordThree2);
        break;
      case 34:
        doWord(wordThirty2);
        doWord(wordFour2);
        break;
      case 35:
        doWord(wordThirty2);
        doWord(wordFive2);
        break;
      case 36:
        doWord(wordThirty2);
        doWord(wordSix2);
        break;
      case 37:
        doWord(wordThirty2);
        doWord(wordSeven2);
        break;
      case 38:
        doWord(wordThirty2);
        doWord(wordEight2);
        break;
      case 39:
        doWord(wordThirty2);
        doWord(wordNine2);
        break;
      case 40:
        doWord(wordForty2);
        break;
      case 41:
        doWord(wordForty2);
        doWord(wordOne2);
        break;
      case 42:
        doWord(wordForty2);
        doWord(wordTwo2);
        break;
      case 43:
        doWord(wordForty2);
        doWord(wordThree2);
        break;
      case 44:
        doWord(wordForty2);
        doWord(wordFour2);
        break;
      case 45:
        doWord(wordForty2);
        doWord(wordFive2);
        break;
      case 46:
        doWord(wordForty2);
        doWord(wordSix2);
        break;
      case 47:
        doWord(wordForty2);
        doWord(wordSeven2);
        break;
      case 48:
        doWord(wordForty2);
        doWord(wordEight2);
        break;
      case 49:
        doWord(wordForty2);
        doWord(wordNine2);
        break;
      case 50:
        doWord(wordFifty2);
        break;
      case 51:
        doWord(wordFifty2);
        doWord(wordOne2);
        break;
      case 52:
        doWord(wordFifty2);
        doWord(wordTwo2);
        break;
      case 53:
        doWord(wordFifty2);
        doWord(wordThree2);
        break;
      case 54:
        doWord(wordFifty2);
        doWord(wordFour2);
        break;
      case 55:
        doWord(wordFifty2);
        doWord(wordFive2);
        break;
      case 56:
        doWord(wordFifty2);
        doWord(wordSix2);
        break;
      case 57:
        doWord(wordFifty2);
        doWord(wordSeven2);
        break;
      case 58:
        doWord(wordFifty2);
        doWord(wordEight2);
        break;
      case 59:
        doWord(wordFifty2);
        doWord(wordNine2);
        break;
    }
  };
}





// ========== Snake ==========

void snake_alive() {
  Snake.clear_matrix();
  Snake.create_border();
  Snake.light_bit(apple.row, apple.column, 2);
  Snake.update_body(snake, length);
  Snake.show_body(snake, length); //switch on body leds at led matrix
  Snake.adapt_body(snake, length); //update body direction
  /**********check change at snake direction & update snake head direction***********/
  Snake.change_direction(snakehead);
  /**********check change at snake direction& update snake head direction***********/

  if ((snakehead->srow == apple.row) && (snakehead->scolumn == apple.column)) {
    Snake.happy_meal(&snake[(ledmatrix_length * ledmatrix_width) - (ledmatrix_length * 2) - (ledmatrix_width * 2) + 3 - length + 1]);
    length++;
    Snake.renew_apple(applepointer, snakehead); //update apple location
    int sounds[] = {22,23,24,25,26};
    Particle.publish("musicPick", String(sounds[random(0,5)]));
  }
  while (Snake.check_collision(applepointer, snakehead)) { //check if apple location is proper
    temp--;
    //matrix.drawRect(18, 0, 2, 2, matrix.Color333(0, 255, 0)); // For debugging purposes
    Snake.renew_apple(applepointer, temp);
  }
  temp = snakehead;
  Snake.update_head(snakehead); //update head location
  Snake.light_bit(snakehead -> srow, snakehead -> scolumn, 1); //switch on snake head LED
  if ((snakehead -> srow == 0) || (snakehead -> srow == ledmatrix_length - 1) || (snakehead -> scolumn == 0) || (snakehead -> scolumn == ledmatrix_width - 1) || Snake.body_crash(snakehead)) { //check for game over
    update = false;
  }
  Particle.process();
  matrix.swapBuffers(true);
}

void snake_dead() {
  Delay++;
  if (Delay == 2) {
    length = 0;
    Snake.clear(snake); //remove snake directions and locations

    int sounds[] = {3,5,9,11,12,20,27,28,34};
    Particle.publish("musicPick", String(sounds[random(0,9)]));
    
    String topLineText = "GAME OVER!";
    topLineText.toCharArray(topLine, 64);

    scrollBigMessage(topLine, 30);

  }
  else if (Delay == 4) {
    Snake.snake_intialization(snake); //initialize snake location and direction
    Snake.renew_apple(applepointer, snakehead); //change apple location
    while (apple.row == snakehead -> srow) { //keep apple and snake at different rows
      Snake.renew_apple(applepointer, snakehead);
    }
    length = 3;
    Delay = 0;
    update = true; //start new game
    int sounds[] = {13,14,15,16,17,18,19,21,29,30,31,33,36};
    Particle.publish("musicPick", String(sounds[random(0,13)]));
  }
  Particle.process();
}

// ========== Snake ==========








   /*****************************************************************
   *                  Matrix Clock Animations                       *
   *                          V0.1                                  *
   *                                                                *
   *                      By Dan J Hamer                            *
   *                          2014                                  *
   *                   http://carbonfrog.com                        *
   *                                                                *
   *        This work is licensed under a Creative Commons          *
   *        Attribution-ShareAlike 4.0 International License.       *
   *        http://creativecommons.org/licenses/by-sa/4.0/          *
   *****************************************************************/

/*
  // ============================================================================

  byte matrixBuffer [3] [16] [16]; // A 3 layer display buffer for the creation of various graphical effects


  boolean intro = true;            // Indicates if mode has just been entered after mode change.

  unsigned long FrameTime = 0;     // Keeps track of timeing between animation frames.
  unsigned int  FrameRate = 0;     // Animation frame rate.
  unsigned int frameCount = 0;     // Keeps counts of the number of frames since the begining of current transition.

  byte field = 1;                 // Divides frames into fields to allow traces to move at different speeds

  typedef struct                  // Traces are sprite like graphical elements that can be
  {                               // manipulated in a variety of ways.
  boolean active;               // Active or inactive.
  int regen;                    // Frame when the trace will regenerate.
  byte xPos;                    // X position
  byte yPos;                    // Y position
  byte speed;                   // Speed
  byte length;                  // Length
  byte terminate;               // Termination point, Should be at least 8 + Length
  }  trace;
  trace streamerTrace[16];        // 16 traces in struct array for streamer animations

  // ==============================================================================
*/


void blankLayer( byte layer )      // Blanks a layer in the display buffer
{ // layers 0 to 2 (3 layers)
  int x, y;                        // Loop counters
  for (x = 0; x < 16; x++)         // 'X' loop, columns.
  {
    for (y = 0; y < 16; y++)        // 'Y' loop, pixels in current column.
    {
      matrixBuffer [layer] [y] [x] = 0;
    }                              // Set all dots to 0.
  }
  return;                           // Return to calling function.
}

void initialiseStreamerTraces()                       // Initalises the traces (struct) for streamers.
{ // Loop counter
  for (int i = 0; i < 16; i++ )
  {
    streamerTrace[i].active = false;                 // Set trace as inactive.
    streamerTrace[i].regen = random(10, 150);        // Generate a random frame number for trace start.
  }
  return;
}

void streamerAnimation()
{
  if ( intro ) {                     // Runs once at intro.
    FrameRate = 20;                  // Set frame rate
    intro = false;                   // Trun off intro as animation is now active
    frameCount = 0;                  // Reset frame count.
    initialiseStreamerTraces();      // Initialises traces
  }
  frameCount++;                      // Increment frame count.
  blankLayer(2);                     // clears the buffer ready to generate the next frame
  drawTraces( 2, field, 150, 0);     // Draw current frame of traces to a buffer layer based on
  // speed, then terminate finished traces and regenerate new traces.
  field++;                           // Increment field counter,
  if ( field >= 7) {                 // when field counter reaches 7,
    field = 1;                       // reset to 1.
  }
  copyLayer(2);                      // Copies Buffer layer 2 to display
  return;                            // Return to main program loop.
}

void clipDraw(byte buf, byte cdy, byte cdx, byte shade)
{ // constrains array dimentions to with in limits, if outside limits it dosn't draw them to buffer.
  if ( (cdy >= 0 && cdy <= 15 ) && ( cdx >= 0 && cdx <= 15))
  {
    matrixBuffer [buf] [cdy] [cdx] = shade;
  }
  return;
}

void copyLayer(byte layer)      // Copies Buffer layer to display
{ // Loop counters
  blackOut();
  for (int y = 0; y < 16; y++)      // 'X' loop, columns.
  {
    for (int x = 0; x < 16; x++)     // 'Y' loop, pixels in current column.
    {
      if (matrixBuffer [layer][y][x] != 0) {
        lightLetter(x, y);
      }
      // myMatrix.matrix [r] [e] = matrixBuffer [layer] [r] [e]; ///                       <<<<<=========================
    }                           // Copy pixel from buffer layer to matrix display.
  }
  return;
}

void drawTraces( byte dtLayer, byte dtField, unsigned int dtSwell, boolean dtRunoff)
{ // Renders frame of traces to buffer, terimnates and generates random
  // parameters for new traces.
  byte g;                            // Loop counter.
  byte  dtXpos, dtYpos;              // Trace 'X' and 'Y' coordinates temporary value holders.

  for ( g = 0 ; g < 16 ; g++ )      // Note: this loop is for 16 of trace generations Not 16 of 'x' coorinates.
  { // Draw current traces to buffer layer 1.
    if ( streamerTrace[g].active == true)
    { // If curret trace is active,
      dtYpos = streamerTrace[g].yPos;    // Copy 'Y' position,
      dtXpos = streamerTrace[g].xPos;    // and 'X' position to temporary holders for manipulation.
      switch (streamerTrace[g].length)   // Switch case based on current traces length.
      {
        case 3:                            //clipDraw constrains array dimentions to with in limits,
          //if outside limits it dosn't draw them to buffer.
          //clipDraw(Layer, y pos, x pos, shade)
          clipDraw(dtLayer, dtYpos, dtXpos, 5);    // Head, this pixle actualy affects the wiping/pasting
          dtYpos--;                                // in mergeLayers hense a value of 5.
          clipDraw(dtLayer, dtYpos, dtXpos, 2);    // Body
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 1);    // Tail
          break;

        case 4:
          clipDraw(dtLayer, dtYpos, dtXpos, 5);    // Head, this pixle actualy affects the wiping/pasting
          dtYpos--;                                // in mergeLayers hense a value of 5.
          clipDraw(dtLayer, dtYpos, dtXpos, 4);    // Head
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 2);    // Body
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 1);    // Tail
          break;

        case 5:
          clipDraw(dtLayer, dtYpos, dtXpos, 5);    // Head, this pixle actualy affects the wiping/pasting
          dtYpos--;                                // in mergeLayers hense a value of 5.
          clipDraw(dtLayer, dtYpos, dtXpos, 4);    // Head
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 2);    // Body
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 2);    // Body
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 1);    // Tail
          break;

        case 6:
          clipDraw(dtLayer, dtYpos, dtXpos, 5);    // Head, this pixle actualy affects the wiping/pasting
          dtYpos--;                                // in mergeLayers hense a value of 5.
          clipDraw(dtLayer, dtYpos, dtXpos, 4);    // Head
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 2);    // Body
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 2);    // Body
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 1);    // Tail
          dtYpos--;
          clipDraw(dtLayer, dtYpos, dtXpos, 1);    // Tail
          break;
      }


      // Move traces. ! Field and speed ready for next frame.

      switch (streamerTrace[g].speed)      // Evaluates the speed
      {
        case 1:                             // Speed 1 (slowest) increments y in ever 3 fields
          if ( dtField == 3 || dtField == 6 )
          {
            streamerTrace[g].yPos++;         // Increment position in 'y'.
          }
          break;

        case 2:                              // Speed 2 (middle) increments y in every other field
          if ( dtField == 2 || dtField == 4 || dtField == 6 )
          {
            streamerTrace[g].yPos++;         // Increment position in 'y'.
          }
          break;
          /*
            case 3:                              // Speed 3 (fastest) increments y in every field
            streamerTrace[g].yPos++;                    // Increment position in 'y'.
            break;
          */

      }
    }

    if ( streamerTrace[g].active == false && dtRunoff == 0 ) // New Trace regeneration but not during runoff
    {
      if ( streamerTrace[g].regen <= frameCount)       // Check thet it is the right frame or later
      { // for regeneration.
        streamerTrace[g].active = true;                // Activate trace.
        streamerTrace[g].xPos = g;                     // give trace same x as trace number ( this helps to get an evenspread).
        streamerTrace[g].yPos = 0;                     // Reset 'Y' position.
        streamerTrace[g].speed = random(1, 3);         // Assign a random speed
        streamerTrace[g].length = random(3, 6);        // Assign a random length
        streamerTrace[g].terminate = ( 16 + streamerTrace[g].length );  // Calculate termination point.rTerminate
      }
    }

    if ( streamerTrace[g].yPos == streamerTrace[g].terminate )  // When the trace reaches its termination point.
    {
      if (dtRunoff == 0)                                 // If not yet in runoff stage,
      { // create a new random regeneration frame
        streamerTrace[g].regen = random(frameCount, (frameCount + dtSwell) );
      }                                                // calculate based on current frame and swell size.
      streamerTrace[g].active = false;                 // Deactivate trace.

      streamerTrace[g].yPos = 0;                       // Reset starting point.
    }
  }
  return;
}





