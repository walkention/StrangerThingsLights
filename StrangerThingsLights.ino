#include <FastLED.h>

#define DATA_PIN 6  //this is the data pin connected to the LED strip.  If using WS2801 you also need a clock pin
#define NUM_LEDS 100 //change this for the number of LEDs in the strip
#define COLOR_ORDER RGB
#define DEFAULT_BRIGHTNESS 10
#define DEFAULT_COLOR "Christmas"

//CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;


void setup(){
  randomSeed(analogRead(0));
  FastLED.addLeds<WS2811, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS); //setting up the FastLED
  //Serial.begin(9600);
  //Set overall brightness
  //FastLED.setBrightness(70);
  allOff(true);
 }

void loop(){
  FastLED.clear();
  //Calibrate the letters
  /*allOn(DEFAULT_BRIGHTNESS, DEFAULT_COLOR, true);
  printWord("abcdefghijklmnopqrstuvwxyz", 26, DEFAULT_COLOR);*/
  //Run routine
  allOn(DEFAULT_BRIGHTNESS, DEFAULT_COLOR, true);
  delay(random(10000,50000));
  int runEvent = random(1,12);
  switch(runEvent){
    case 1:
      allOff(true);
      printWord("help me", 7, DEFAULT_COLOR);
      delay(1000);
      break;
    case 2:
      allOff(true);
      showWord("ECE", 3, "Red");
      delay(1000);
      break;
    case 3:
      allOff(true);
      showWord("ITS",3,"Blue");
      delay(1000);
      break;
    case 4:
      rainbowDance(10, DEFAULT_BRIGHTNESS);
      break;
    case 5:
      for(int i = 0; i < NUM_LEDS; i++){
        int randLED = random(0, NUM_LEDS - 1);
        flicker(randLED, "Christmas");
        setLEDColorBright(randLED, DEFAULT_BRIGHTNESS, DEFAULT_COLOR, true);
      }
      break;
    case 6:
      lightChaseFwd(DEFAULT_COLOR, 10);
      delay(1000);
      break;
    case 7:
      meetInTheMiddle(DEFAULT_COLOR, 10);
      delay(1000);
      break;
    case 8:
      allOff(true);
      showWord("GO",2,"Red");
      delay(1000);
      break;
    case 9:
      glowup("Christmas");
      glowdown("Christmas");
      break;
    case 10:
      glowup("Christmas");
      glowdown("Christmas");
      delay(200);
      glowup("Red");
      glowdown("Red");
      delay(200);
      glowup("Red");
      glowdown("Red");
      delay(200);
      glowup("Red");
      glowdown("Red");
      delay(1000);
      break;
    case 11:
      lightChaseRev(DEFAULT_COLOR, 10);
      delay(1000);
      break;
    case 12:
      leaveFromTheMiddle(DEFAULT_COLOR, 10);
      delay(1000);
      break;
    default:
      allOff(true);
  }
}

void fadeByPercent(int ledNum, int brightness, bool runShow) {
    if(brightness > 100){
      brightness = 100;
    }
    if(brightness < 0) {
      brightness = 0;
    }
    int fadeLevel = (int) 2.56 * brightness;
    leds[ledNum].nscale8(fadeLevel);
    if(runShow){
      FastLED.show();
    }
}

void setLEDColorBright(int ledNum, int brightness, char color[], bool runShow){
    if (strcmp(color, "Red") == 0){
      leds[ledNum] = CRGB::Red;
    } else if(strcmp(color, "DarkOrange") == 0){
      leds[ledNum] = CRGB::DarkOrange;
    } else if(strcmp(color, "Blue") == 0){
      leds[ledNum] = CRGB::Blue;
    } else if(strcmp(color, "Purple") == 0){
      leds[ledNum] = CRGB::Purple;
    } else if(strcmp(color, "Green") == 0){
      leds[ledNum] = CRGB::Green;
    } else if(strcmp(color, "Yellow") == 0){
      leds[ledNum] = CRGB::Yellow;
    } else if(strcmp(color, "White") == 0){
      leds[ledNum] = CRGB::White;
    } else if(strcmp(color, "Halloween") == 0){
      switch (ledNum % 2) {
        case 0:
          leds[ledNum] = CRGB(175, 0, 255); //Purple
          break;
        case 1:
          leds[ledNum] = CRGB(255, 30, 0); //Orange
          break;
      }
    } else if(strcmp(color, "RedGreen") == 0){
      switch (ledNum % 2) {
        case 0:
          leds[ledNum] = CRGB::Red;
          break;
        case 1:
          leds[ledNum] = CRGB::Green;
          break;
      }
    } else {
      switch (ledNum % 5) {
        case 0:
          leds[ledNum] = CRGB::Blue;
          break;
        case 1:
          leds[ledNum] = CRGB::Green;
          break;
        case 2:
          leds[ledNum] = CRGB::Yellow;
          break;
        case 3:
          leds[ledNum] = CRGB(255, 30, 0); //Orange
          break;
        case 4:
          leds[ledNum] = CRGB::Red;
          break;
        default:
          leds[ledNum] = CRGB(255,255,255); //white To determine if there is a problem
          break;
      }
    }
    fadeByPercent(ledNum, brightness, false);
    if(runShow){
      FastLED.show();
    }
}

void printWord(char newWord[], int charLen, char color[]){
  allOff(true);
  int ledNum = 0;
  for (int i = 0; i <= charLen - 1; i++) {
    if(newWord[i] != ' '){
      ledNum = getLEDLetter(newWord[i]);
      if(ledNum >= 0){
        flicker(ledNum, color);
        for(int bright = 0; bright <= 100; bright++){
          setLEDColorBright(ledNum, bright, color, false);
          if(bright > 50){
            FastLED.delay(random(15,20));
          }
          FastLED.show();
        }
        for(int bright = 100; bright >= 0; bright--){
          setLEDColorBright(ledNum, bright, color, false);
          if(bright > 75){
            FastLED.delay(random(10,15));
          }
          FastLED.show();
        }
      }
      delay(200);
    } else {
      delay(800);
    }
    
  }
}

void showWord(char newWord[], int charLen, char color[]){
  allOff(true);
  int ledNum = 0;
  for (int i = 0; i <= charLen - 1; i++) {
      ledNum = getLEDLetter(newWord[i]);
      flicker(ledNum, color);
  }
  for(int bright = 0; bright <= 100; bright++){
    int ledNum = 0;
    for (int i = 0; i <= charLen - 1; i++) {
      ledNum = getLEDLetter(newWord[i]);
      if(ledNum >= 0){
        setLEDColorBright(ledNum, bright, color, false);
        if(bright > 50){
          FastLED.delay(random(2,5));
        }
        FastLED.show();
      }
    }
  }
  for(int bright = 100; bright >= 0; bright--){
    int ledNum = 0;
    for (int i = 0; i <= charLen - 1; i++) {
      ledNum = getLEDLetter(newWord[i]);
      if(ledNum > 0){
        setLEDColorBright(ledNum, bright, color, false);
        if(bright > 75){
          FastLED.delay(random(10,15));
        }
        FastLED.show();
      }
    }
  }
}

void flicker(int ledNum, char color[]){
  int flickerCount = random(1,5);
  for(int i = 0; i < flickerCount; i++){
    setLEDColorBright(ledNum, random(75, 100), color, true);
    FastLED.delay(random(15,20));
    setLEDColorBright(ledNum, 0, color, true);
    FastLED.delay(random(15,20));
  }
}

void lightChaseFwd(char color[], int travelDelay){
  for (int i = 1; i < NUM_LEDS; i++) {
    setLEDColorBright(i, 100, color, true);
    FastLED.delay(travelDelay);
    setLEDColorBright(i, 0, color, true);
    FastLED.delay(travelDelay);
  }
}

void lightChaseRev(char color[], int travelDelay) {
  for (int i = NUM_LEDS; i >= 0; i--) {
    setLEDColorBright(i, 100, color, true);
    FastLED.delay(travelDelay);
    setLEDColorBright(i, 0, color, true);
    FastLED.delay(travelDelay);
  }
}

void meetInTheMiddle(char color[], int travelDelay) {
  for (int i = 0; i < NUM_LEDS/2; i++) {
    setLEDColorBright(i, 100, color, false);
    setLEDColorBright(NUM_LEDS - i, 100, color, false);
    FastLED.show();
    FastLED.delay(travelDelay);
    setLEDColorBright(i, 0, color, false);
    setLEDColorBright(NUM_LEDS - i, 0, color, false);
    FastLED.show();
    FastLED.delay(travelDelay);
  }
}

void leaveFromTheMiddle(char color[], int travelDelay) {
  for (int i = NUM_LEDS/2; i >= 0; i--) {
    setLEDColorBright(i, 100, color, false);
    setLEDColorBright(NUM_LEDS - i, 100, color, false);
    FastLED.show();
    FastLED.delay(travelDelay);
    setLEDColorBright(i, 0, color, false);
    setLEDColorBright(NUM_LEDS - i, 0, color, false);
    FastLED.show();
    FastLED.delay(travelDelay);
  }
}

void allOn(int brightness, char color[], bool runShow) {
  for (int i = 0; i < NUM_LEDS; i++) {
    setLEDColorBright(i, brightness, color, false);
  }
  if(runShow){
    FastLED.show();
  }
}

void allOff(bool runShow) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  if(runShow){
    FastLED.show();
  }
}

int getLEDLetter(char letter){
  int ledNum;
  switch (letter) {
      case 'a':
      case 'A':
        ledNum = 49;
        break;
      case 'b':
      case 'B':
        ledNum = 48;
        break;
      case 'c':
      case 'C':
        ledNum = 46;
        break;
      case 'd':
      case 'D':
        ledNum = 45;
        break;
      case 'e':
      case 'E':
        ledNum = 43;
        break;
      case 'f':
      case 'F':
        ledNum = 41;
        break;
      case 'g':
      case 'G':
        ledNum = 39;
        break;
      case 'h':
      case 'H':
        ledNum = 36;
        break;
      case 'i':
      case 'I':
        ledNum = 35;
        break;
      case 'j':
      case 'J':
        ledNum = 32;
        break;
      case 'k':
      case 'K':
        ledNum = 30;
        break;
      case 'l':
      case 'L':
        ledNum = 28;
        break;
      case 'm':
      case 'M':
        ledNum = 26;
        break;
      case 'n':
      case 'N':
        ledNum = 23;
        break;
      case 'o':
      case 'O':
        ledNum = 65;
        break;
      case 'p':
      case 'P':
        ledNum = 67;
        break;
      case 'q':
      case 'Q':
        ledNum = 69;
        break;
      case 'r':
      case 'R':
        ledNum = 71;
        break;
      case 's':
      case 'S':
        ledNum = 74;
        break;
      case 't':
      case 'T':
        ledNum = 76;
        break;
      case 'u':
      case 'U':
        ledNum = 78;
        break;
      case 'v':
      case 'V':
        ledNum = 80;
        break;
      case 'w':
      case 'W':
        ledNum = 82;
        break;
      case 'x':
      case 'X':
        ledNum = 84;
        break;
      case 'y':
      case 'Y':
        ledNum = 87;
        break;
      case 'z':
      case 'Z':
        ledNum = 90;
        break;
      default:
        ledNum = -1;
        break;
    }
    return ledNum;
}

void halloweenLights() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if((i % 2) == 0) {
      leds[i] = CRGB (249,40,0);
      FastLED.show();
    } else {
      leds[i] = CRGB::Purple;
      FastLED.show();
    }
  }
}

void rainbowDance(int seconds, int brightness) {
  for(int i = 0; i < (seconds*210); i++){
    static uint8_t hue=0;
    leds.fill_rainbow(hue++);
    for(int x = 0; x < NUM_LEDS; x++){
      fadeByPercent(x, brightness, false);
    }
    FastLED.show();
  }
}

void glowup(char color[]) {
  FastLED.clear();
  //Setting i determines your lowest power value. the second condition determines the max value and the y determines your step
  for( int i = 0; i <= 100; i++ ) {  
      for(int x = 0; x < NUM_LEDS; x++){
          setLEDColorBright(x, i, color, false);
      } 
      FastLED.show();
      delay(5); 
    }
}


void glowdown(char color[]) {
  //Same thing as glowup, except in reverse
  for (int i = 255; i >= 0; i--){
      for(int x = 0; x < NUM_LEDS; x++){
          setLEDColorBright(x, i, color, false);
      }
      FastLED.show();
      delay(5); 
    }      
}
