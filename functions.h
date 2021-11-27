#include <avr/pgmspace.h>
#include <FastLED.h>

#define COUNT_INC 1

#define MAX_X 18
#define MAX_Y 31

extern CRGBPalette16 palette;

void flash(CRGB* leds, uint8_t led, CRGB color) {
  leds[led] = color;
  FastLED.show();
  FastLED.delay(400);
  leds[led] = CRGB::Black;
  FastLED.show();
  FastLED.delay(200);
}

/* void horizWipe(boolean left_to_right, CRGB c_wipe, CRGB c_orig, uint32_t duration)
{
   uint32_t elapsed_time = 0;
   uint32_t X_temp;
   
 
   while (elapsed_time < duration) 
   {
     //Locate the wipe X
     X_temp = (uint32_t)(float(elapsed_time)/float(duration)*float(MAX_X));
      
    
     for(uint16_t i=0; i<NUM_LEDS; i++)
     { if (left_to_right) 
          {if (pgm_read_byte_near(positions + i*2) < X_temp ) {leds[i] = c_wipe; } else {leds[i] = c_orig;   }}
       else
          {if (pgm_read_byte_near(positions + i*2) > MAX_X - X_temp ) {leds[i] = c_wipe; } else {leds[i] = c_orig;   }}       
     }
     FastLED.show();     
     FastLED.delay(50); 
     elapsed_time += 55;     
   }
   for(uint16_t i=0; i<NUM_LEDS; i++)
     { leds[i] = c_wipe; }
   FastLED.show();
   
} //horizWipe */

CHSV set_color(CRGB* leds, uint8_t index, uint16_t led_index) {
  leds[led_index] = ColorFromPalette(palette, index);
}

void show_random(CRGB* leds) {
  EVERY_N_MILLISECONDS(200) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(random8(), 255, 128);
    }
  }
}

void show_all_white(CRGB* leds) {
  FastLED.setBrightness(128);
  for(int i = 0;i < NUM_LEDS; i++){
    leds[i] = CRGB::White;
  }
  FastLED.show();
  FastLED.delay(20000);
}

void show_counting(CRGB* leds) {
  static uint8_t count = 0;
  uint16_t tmp = count + 1;
  while(tmp > 100) {
    flash(leds, count, CRGB::Blue);
    tmp -= 100;
  }
  
  while(tmp > 10) {
    flash(leds, count, CRGB::Green);
    tmp -= 10;
  }

  while(tmp > 0) {
    flash(leds, count, CRGB::Red);
    tmp--;
  }

  leds[count] = CRGB::White;
  FastLED.show();
  FastLED.delay(3000);
  FastLED.clear();

  count++;
}

void show_vert_rainbow(CRGB* leds) {
  static uint8_t count = 0;
  for(int i = 0; i < NUM_LEDS; i++) {
    uint8_t val = pgm_read_byte_near(norm_positions + i*2 + 1);
    set_color(leds, val+count, i);
  }
  count += COUNT_INC;
}

void show_horiz_rainbow(CRGB* leds) {
  static uint8_t count = 0;
  for(int i = 0; i < NUM_LEDS; i++) {
    uint8_t val = pgm_read_byte_near(norm_positions + i*2);
    set_color(leds, val+count, i);
  }
  count += COUNT_INC;
}

void show_spinning(CRGB* leds) {
  static uint8_t count = 0;
  for(int i = 0; i < NUM_LEDS; i++) {
    uint8_t val = pgm_read_byte_near(angles + i);
    set_color(leds, val + count, i);
  }
  count += COUNT_INC;
}

void show_debug(CRGB* leds) {
  for(int i = 0; i < MAX_X; i++) {
    FastLED.clear();
    for(int j = 0; j < NUM_LEDS; j++) {
      uint8_t val = pgm_read_byte_near(positions + j*2);
      if(val == i) {
        leds[j] = CRGB::White;  
      }
    }
    FastLED.show();
    FastLED.delay(500);
  }
  for(int i = 0; i < MAX_Y; i++) {
    FastLED.clear();
    for(int j = 0; j < NUM_LEDS; j++) {
      uint8_t val = pgm_read_byte_near(positions + j*2 + 1);
      if(val == i) {
        leds[j] = CRGB::White;  
      }
    }
    FastLED.show();
    FastLED.delay(500);
  }
}
