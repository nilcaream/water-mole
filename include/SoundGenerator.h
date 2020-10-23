#ifndef SoundGenerator_h
#define SoundGenerator_h

#include "Arduino.h"
#include "Display.h"

enum SoundGeneratorState
{
    SOUND,
    PAUSE
};

class SoundGenerator
{
private:
    byte pin;
    Display *display;
    SoundGeneratorState state = SOUND;
    unsigned long nextActionTime = 0;
    long nextFrequency();

public:
    SoundGenerator(byte pin, Display *display);
    void loop();
};

#endif
