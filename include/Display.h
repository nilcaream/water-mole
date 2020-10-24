#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

class Display
{
private:
    int width;
    int height;
    unsigned long disableTime;
    bool enabled;
    LiquidCrystal_I2C *lcd;
    void clear(int rowNumber);

public:
    Display(byte address, int width, int height);
    void enable(bool state);
    void printProgress(const char *text);
    void printMessage(const char *format, ...);
    int getWidth();
    void loop(int triggerState);
};

#endif
