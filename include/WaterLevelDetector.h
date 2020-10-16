#ifndef WaterLevelDetector_h
#define WaterLevelDetector_h

#include "Arduino.h"

class WaterLevelDetector
{
public:
    WaterLevelDetector(byte analogPin);
    void addDigitalPin(byte pin);
    byte getDigitalPinsNumber();
    int getLevel(byte index);
    void refresh();

private:
    byte analogPin;
    byte digitalPins[16];
    byte digitalPinsNumber = 0;
    int results[];
};

#endif
