#include <FastLED.h>

#include "positions.h"
#include "functions.h"

#define FASTLED_INTERNAL

#define RAND_LIGHTS
#define ALL_WHITE
#define COUNTING
#define VERT_RAINBOW
#define HORZ_RAINBOW
#define SPINNING
#define DEBUG_COLS

//CRGBPalette16 palette = Rainbow_gp;
//CRGBPalette16 palette = CloudColors_p;
//CRGBPalette16 palette = LavaColors_p;
//CRGBPalette16 palette = OceanColors_p;
CRGBPalette16 palette = CRGBPalette16(
  CRGB::Green, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::Green, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black);

#define NUM_PATTERNS 4
uint8_t pattern;

void setup() {
  Serial.begin(9600);
  Serial.println("HI");

  PinMode(6, OUTPUT)

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  delay(3000);

}

void loop() {
  
  EVERY_N_SECONDS(60) {
    pattern = (pattern + 1) % NUM_PATTERNS;
  }

  switch (pattern) {
    case 0:
      show_random();
      break;
    case 1:
      show_vert_rainbow();
      break;
    case 2:
      show_horiz_rainbow();
      break;
    case 3:
      show_spinning();
      break;
  }
}
