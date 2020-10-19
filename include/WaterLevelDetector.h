#ifndef WaterLevelDetector_h
#define WaterLevelDetector_h

#include "Arduino.h"

class WaterLevelDetector
{
public:
    WaterLevelDetector(byte analogPin);
    void addDigitalPin(byte pin);
    byte getDigitalPinsNumber();
    bool getLevel(byte index);
    void refresh();
    void loop();

private:
    byte analogPin;
    byte digitalPins[16];
    byte digitalPinsNumber = 0;
    bool results[16];
};

#endif
