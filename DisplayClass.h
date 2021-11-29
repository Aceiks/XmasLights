#ifndef DISPLAYCLASS
#define DISPLAYCLASS

class DisplayClass {
    public:
        virtual void Draw(CRGB* leds) {};
        bool firstRun = true;
};

#endif