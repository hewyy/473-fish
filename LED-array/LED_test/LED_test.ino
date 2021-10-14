#include <FastLED.h>

#define DATA_PIN 6

class LED_Array {
public:
  // requires: numLEDs <= 300 
  void init(int numLEDs) {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(LEDs, numLEDs);
    currentBrightness = 80;
  }

  void off(){
    FastLED.setBrightness(0);
  }
  
  // hue , saturation, brightness
  // requires: 0 <= h, s, v <= 255
  void setHSVColor(int hue, int saturation, int brightness) {
    FastLED.showColor(CHSV(hue,saturation,brightness));
    currentBrightness = brightness;
  }

  // note: the strip uses GRB by default but CRGB() handles the conversion
  // requires: 0 <= r, g, b <= 255
  void setRGBColor(int r, int g, int b) {
    FastLED.showColor(CRGB(r,g,b));
  }
    
  // requires: 0 <= brightness <= 255
  void setBrightness(int b) {
    FastLED.setBrightness(b);
    currentBrightness = b;
//    FastLED.show();
  }

  // passes in a vector of r,g,b values and 
  // the time is the amount of time between the r,g,b value set
  // requires: 0 <= r, g, b <= 255
  void createColorCycle(int startColorVal[], int endColorVal[], int time);

  // passes in a vector of brightness values and 
  // the time is the amount of time between the r,g,b value set
  // requires: 0 <= brightness <= 255
    void changeBrightness(int brightnessValues[], int arrSize, int delayIn) {
      /* not functional - needs debugging
      for (int idx = 0; idx < arrSize; ++idx){
        int nextVal = brightnessValues[idx];
        int bDiff = currentBrightness - nextVal;
        int delayOut, bIncr;

        if (abs(bDiff) < delayIn) {
          delayOut = delayIn / bDiff;
          bIncr = bDiff / abs(bDiff); // maintain sign
        }
        else {
          delayOut = 1;
          bIncr = bDiff / delayIn;
        }
          
        for (int ms = 0; ms < delayIn; ms += delayOut) {
          if (bIncr > 0 && currentBrightness >= nextVal
              || bIncr < 0 && currentBrightness <= nextVal){
            break;
          }
          currentBrightness += bIncr;
          setBrightness(currentBrightness);
          
          delay(delayOut);
        }
      }
      */
    }


 private:
  CRGB LEDs[300];
  int currentBrightness;
};


LED_Array arr;

void setup() {
 arr.init(10);
 arr.setRGBColor(10,20, 20);
}

void loop() {
  // Blinking between blue and red 
//  arr.setBrightness(150);
//  arr.setRGBColor(10,20, 20);
//  delay(200);
//  arr.setBrightness(20);
//  arr.setRGBColor(200,20, 20);
//  delay(200);

// Gradual color change test
  for (int i = 0; i < 40; ++i) {
    arr.setHSVColor(i*4, 150, 100-i);
    delay(300);
  }
}
