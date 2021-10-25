#include <FastLED.h>

#define DATA_PIN 6

class LED_Array {
public:

  // REQUIRES: numLEDsIn <= 300 
  void init(int numLEDsIn) {
    numLEDs = numLEDsIn;
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(LEDs, numLEDs);

    setRGBColor(10, 10, 10);
  }

  // delayIn (ms) affects how quickly the display fades to black
  void fadeToBlack(int delayIn){
    int itrs = 20;
    while (itrs > 0) {
      // half the brightness of all LEDs until dark
      fadeToBlackBy(LEDs, numLEDs, 64);
      FastLED.show();
      delay(delayIn);
      --itrs;
    }
  }
  
  // REQUIRES: 0 <= h, s, v <= 255
  void setHSVColor(int h, int s, int v) {
    for (int i = 0; i < numLEDs; ++i) {
      LEDs[i] = CHSV(h,s,v);
    }
    FastLED.show();
  }

  // REQUIRES: 0 <= r, g, b <= 255
  // note: the strip uses GRB by default but CRGB() handles the conversion
  void setRGBColor(int r, int g, int b) {
    for (int i = 0; i < numLEDs; ++i) {
      LEDs[i] = CRGB(r,g,b);
    }
    FastLED.show();
  }
    
  // REQUIRES: 0 <= r1, g1, b1, r2, g2, b2 <= 255
  // delayIn (ms) affects the smoothness of color transition
  void colorTransition(int r1, int g1, int b1, int r2, int g2, int b2, int delayIn) {
    colorTransition(CRGB(r1, g1, b1), CRGB(r2, g2, b2), delayIn);
  }

  // REQUIRES: 0 <= r1, g1, b1, r2, g2, b2 <= 255
  // delayIn (ms) affects the smoothness of color transition
  void colorTransition(CRGB color1, CRGB color2, int delayIn) {
    for (int percent = 0; percent <= 255; percent += 5) {
      for (int i = 0; i < numLEDs; ++i) {
        LEDs[i] = blend(color1, color2, percent);
      }
    FastLED.show();
    delay(delayIn);
    }
  }

  // REQUIRES: 0 <= r, g, b <= 255
  // delayIn (ms) affects how long the end color val remains visible
  void createColorCycle(int startColorVal[], int endColorVal[], int delayIn) {
    colorTransition(startColorVal[0], startColorVal[1], startColorVal[2], 
                endColorVal[0], endColorVal[0], endColorVal[0], 60);
    delay(delayIn);
    colorTransition(endColorVal[0], endColorVal[0], endColorVal[0], 
                startColorVal[0], startColorVal[1], startColorVal[2], 60);
  }


 private:
  CRGB LEDs[300];
  int currentBrightness;
  int numLEDs;
};