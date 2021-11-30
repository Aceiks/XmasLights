#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "positions.h"
#include "DisplayClass.h"

#define GRAVITY -9.81
#define START_HEIGHT 1
#define SPEED_KNOB 4.0

#define NUM_BALLS 4

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static const CRGB ballColors [] = 
{
    CRGB::Green,
    CRGB::Red,
    CRGB::Blue,
    CRGB::Orange,
    CRGB::Indigo
};

class Ball
{
  public:
    float height, lastBounce, dampening, speed;
    CRGB color;
    Ball() { }
    Ball(float height, float lastBounce, float dampening, CRGB color)
      : height(height),
        lastBounce(lastBounce),
        dampening(dampening),
        color(color) {
          speed = InitialBallSpeed(height);
         }

    static float InitialBallSpeed(float h) {
      return sqrt(-2 * GRAVITY * h);
    }

    float GetTimeSinceLastBounce() {
      return (millis() - lastBounce) / 1000 / float(SPEED_KNOB);
    }

    static float Time() {
      return (millis() / float(1000));
    }

    void Update() {
      float t = GetTimeSinceLastBounce();
      height = 0.5 * GRAVITY * pow(t, 2.0) + speed * t;

      if (height < 0) {
        height = 0;
        speed = dampening * speed;
        lastBounce = millis();

        if (speed < 1.75) {
          speed = InitialBallSpeed(START_HEIGHT * 1.05) - (random8(64)/256.0);
        }
      }
    }
};

class BouncingBallEffect: public DisplayClass
{
  private:
    
    CRGB* leds;
    uint16_t length;
    uint8_t fadeRate;
    bool mirrored; 

    Ball balls[NUM_BALLS];

  public:
    BouncingBallEffect(uint16_t length, uint8_t fade = 0, bool mirrored = false)
      : length(length - 1),
        fadeRate(fade),
        mirrored(mirrored)
      {
        for (uint8_t i = 0; i < NUM_BALLS; i++) {
          balls[i] = Ball(
            START_HEIGHT,
            millis(),
            0.90 - i / pow(NUM_BALLS, 2),
            ballColors[i % 5]);
        }

      }
    
    void Draw(CRGB* leds) {
      if (fadeRate != 0) {
        for (uint16_t i = 0; i < NUM_LEDS; i++)
          leds[i].fadeToBlackBy(fadeRate);
      } else {
        for (uint16_t i = 0; i < NUM_LEDS; i++)
          leds[i] = CRGB(0, 0, 0);
      }

      for (uint8_t i = 0; i < NUM_BALLS; i++) {
        balls[i].Update();
        float position = (balls[i].height * (length - 1) / START_HEIGHT) + 1;

        float fraction = position - (uint8_t)position;
        uint8_t iPosLow = (uint8_t)position;
        uint8_t iPosHigh = iPosLow + 1;
        CRGB lowColor = CRGB(balls[i].color).fadeToBlackBy((uint8_t)(256 * fraction));
        CRGB highColor = CRGB(balls[i].color).fadeToBlackBy((uint8_t)(256 * (1-fraction)));
        for (uint16_t j = 0; j < NUM_LEDS; j++) {
          uint8_t val = pgm_read_byte_near(positions + j*2 + 1);
          if (val == iPosLow) {
            leds[j] += lowColor;
          } else if (val == iPosHigh) {
            leds[j] += highColor;
          }
        }
        Serial.println();

      }

    }
};