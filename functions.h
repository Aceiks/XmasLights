CRGB leds[NUM_LEDS];

#define COUNT_INC 2

#define MAX_X 18
#define MAX_Y 31

extern CRGBPalette16 palette;

uint8_t count = 0;

void flash(uint8_t led, CRGB color) {
  leds[count] = color;
  FastLED.show();
  FastLED.delay(400);
  leds[led] = CRGB::Black;
  FastLED.show();
  FastLED.delay(200);
}

void horizWipe(boolean left_to_right, CRGB c_wipe, CRGB c_orig, uint32_t duration)
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
   
} //horizWipe

CHSV set_color(uint8_t index, uint16_t led_index) {
  leds[led_index] = ColorFromPalette(palette, index);
}

void show_random() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = individual_random();
  }
  FastLED.show();
  FastLED.delay(200);
}

CRGB individual_random() {
  return CHSV(random8(), 255, 255);
}

void show_all_white() {
  FastLED.setBrightness(128);
  for(int i = 0;i < NUM_LEDS; i++){
    leds[i] = CRGB::White;
  }
  FastLED.show();
  FastLED.delay(20000);
}

void show_counting() {
  uint16_t tmp = count + 1;
  while(tmp > 100) {
    flash(count, CRGB::Blue);
    tmp -= 100;
  }
  
  while(tmp > 10) {
    flash(count, CRGB::Green);
    tmp -= 10;
  }

  while(tmp > 0) {
    flash(count, CRGB::Red);
    tmp--;
  }

  leds[count] = CRGB::White;
  FastLED.show();
  FastLED.delay(3000);
  FastLED.clear();

  count++;
}

void show_vert_rainbow() {
  for(int i = 0; i < NUM_LEDS; i++) {
    uint8_t val = pgm_read_byte_near(norm_positions + i*2 + 1);
    set_color(val+count, i);
  }
  FastLED.show();
  count += COUNT_INC;
}

CRGB invidual_vert_rainbow(tuint16_t index) {
  uint8_t val = pgm_read_byte_near(norm_positions + index*2 + 1);
  return ColorFromPalette(palette, val + count);
}

void show_horiz_rainbow() {
  for(int i = 0; i < NUM_LEDS; i++) {
    uint8_t val = pgm_read_byte_near(norm_positions + i*2);
    set_color(val+count, i);
  }
  FastLED.show();
  count += COUNT_INC;
}

CRGB invidual_horiz_rainbow(tuint16_t index) {
  uint8_t val = pgm_read_byte_near(norm_positions + index*2);
  return ColorFromPalette(palette, val + count);
}

void show_spinning() {
  for(int i = 0; i < NUM_LEDS; i++) {
    uint8_t val = pgm_read_byte_near(angles + i);
    set_color(val + count, i);
  }
  FastLED.show();
  count += COUNT_INC;
}

void show_debug() {
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
