#define FASTLED_INTERNAL
#include <FastLED.h>

#include "positions.h"
#include "functions.h"


#define BLEND

//CRGBPalette16 palette = Rainbow_gp;
//CRGBPalette16 palette = CloudColors_p;
//CRGBPalette16 palette = LavaColors_p;
//CRGBPalette16 palette = OceanColors_p;
CRGBPalette16 palette = CRGBPalette16(
  CRGB::Green, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::Green, CRGB::Black, CRGB::Black, CRGB::Black,
  CRGB::Red, CRGB::Black, CRGB::Black, CRGB::Black);

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB output[NUM_LEDS];

#define NUM_PATTERNS 2

uint8_t pattern;
uint8_t blend_amount = 255;

void setup() {
  Serial.begin(9600);
  Serial.println("HI");

  pinMode(6, OUTPUT);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(output, NUM_LEDS);

  delay(3000);

}

void loop() {
  
  EVERY_N_MILLISECONDS(10) {
    if (blend_amount < 252) blend_amount += 3;
    else blend_amount = 255;
  }

  EVERY_N_SECONDS(15) {
    pattern = (pattern + 1) % NUM_PATTERNS;
    blend_amount = 0;
  }

  switch (pattern) {
    case 0:
      show_random(leds_2);
      if (blend_amount < 255) {
        show_spinning(leds_1);
        blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
      } else {
        memcpy(output, leds_2, NUM_LEDS * 3);
      }
      break;
    case 1:
      show_vert_rainbow(leds_2);
      if (blend_amount < 255) {
          show_random(leds_1);
          blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
      } else {
        memcpy(output, leds_2, NUM_LEDS * 3);
      }
      break;
    case 2:
      show_horiz_rainbow(leds_2);
      if (blend_amount < 255) {
        show_vert_rainbow(leds_1);
        blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
      } else {
        memcpy(output, leds_2, NUM_LEDS * 3);
      }
      break;
    case 3:
      show_spinning(leds_2);
      if (blend_amount < 255) {
        show_horiz_rainbow(leds_1);
        blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
      } else {
        memcpy(output, leds_2, NUM_LEDS * 3);
      }
      break;
  }

  FastLED.show();
}
