#ifndef DISPLAYCLASS
#define DISPLAYCLASS

class DisplayClass {
    public:
        virtual void Draw(CRGB* leds) {Serial.println("Should not be here");}
        bool firstRun = true;
};

#endif