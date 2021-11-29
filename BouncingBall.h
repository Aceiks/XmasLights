#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#include "DisplayClass.h"

#define GRAVITY -9.81
#define START_HEIGHT 1
#define SPEED_KNOB 4.0

#define NUM_BALLS 3

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
        lastBounce = Time();

        if (speed < 0.01)
          speed = InitialBallSpeed(START_HEIGHT) * dampening;
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
        for (uint8_t i = 0; i < length + 1; i++)
          leds[i].fadeToBlackBy(fadeRate);
      } else {
        for (uint8_t i = 0; i < length + 1; i++)
          leds[i] = CRGB::Black;
      }

      for (uint8_t i = 0; i < NUM_BALLS; i++) {
        balls[i].Update();
        uint16_t position = (uint16_t)(balls[i].height * (length - 1) / START_HEIGHT);

        leds[position] += balls[i].color;
        leds[position+1] += balls[i].color;

        if (mirrored) {
          leds[length - 1 - position] += balls[i].color;
          leds[length - position] += balls[i].color;
        }
      }
      delay(20);

    }
};