#define FASTLED_INTERNAL
#include <FastLED.h>

#include "positions.h"
#include "functions.h"
#include "displays/DisplayClass.h"
#include "displays/BouncingBall.h"
#include "displays/Twinkle.h"

#define BLEND

#define PALETTE_FILL CRGB::White

//CRGBPalette16 palette = Rainbow_gp;
//CRGBPalette16 palette = CloudColors_p;
//CRGBPalette16 palette = LavaColors_p;
//CRGBPalette16 palette = OceanColors_p;
CRGBPalette16 palette = CRGBPalette16(
  CRGB::Green, PALETTE_FILL, PALETTE_FILL, PALETTE_FILL,
  CRGB::Red, PALETTE_FILL, PALETTE_FILL, PALETTE_FILL,
  CRGB::Green, PALETTE_FILL, PALETTE_FILL, PALETTE_FILL,
  CRGB::Red, PALETTE_FILL, PALETTE_FILL, PALETTE_FILL);

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB output[NUM_LEDS];

#define NUM_PATTERNS 4

uint8_t pattern;
uint8_t blend_amount = 255;

bool first_run = true;

DisplayClass* dc;
BouncingBallEffect bbe = BouncingBallEffect(31, 4);
Twinkle twinkle = Twinkle();

void setup() {
  Serial.begin(115200);
  Serial.println("HI");

  pinMode(6, OUTPUT);

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(output, NUM_LEDS);
  FastLED.setMaxPowerInMilliWatts(60000);

  dc = &twinkle;

  delay(3000);

}

void loop() {
  
  EVERY_N_MILLISECONDS(10) {
    if (blend_amount < 252) blend_amount += 3;
    else blend_amount = 255;
  }

  EVERY_N_SECONDS(60) {
    pattern = (pattern + 1) % NUM_PATTERNS;
    blend_amount = 0;
    first_run = true;
  }

  // switch (pattern) {
  //   case 0:
  //     show_random(leds_2);
  //     if (blend_amount < 255) {
  //       show_spinning(leds_1);
  //       blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
  //     } else {
  //       memcpy(output, leds_2, NUM_LEDS * 3);
  //     }
  //     break;
  //   case 1:
  //     if (first_run) {
  //       memcpy(leds_1, leds_2, NUM_LEDS * 3);
  //       first_run = false;
  //     }
  //     show_vert_rainbow(leds_2);
  //     if (blend_amount < 255) {
  //         show_random(leds_1);
  //         blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
  //     } else {
  //       memcpy(output, leds_2, NUM_LEDS * 3);
  //     }
  //     break;
  //   case 2:
  //     show_horiz_rainbow(leds_2);
  //     if (blend_amount < 255) {
  //       show_vert_rainbow(leds_1);
  //       blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
  //     } else {
  //       memcpy(output, leds_2, NUM_LEDS * 3);
  //     }
  //     break;
  //   case 3:
  //     show_spinning(leds_2);
  //     if (blend_amount < 255) {
  //       show_horiz_rainbow(leds_1);
  //       blend(leds_1, leds_2, output, NUM_LEDS, blend_amount);
  //     } else {
  //       memcpy(output, leds_2, NUM_LEDS * 3);
  //     }
  //     break;
  // }

  EVERY_N_MILLISECONDS(16) {
    dc->Draw(output);
  }

  EVERY_N_SECONDS(1) {
    Serial.println(FastLED.getFPS());
  }

  FastLED.setBrightness(128);
  FastLED.show();
}
