#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

class Display
{
private:
    int width;
    int height;
    LiquidCrystal_I2C *lcd;

public:
    Display(byte address, int width, int height);
    void enable(bool state);
    void printProgress(int value);
    void printMessage(const char *text);
};

#endif
