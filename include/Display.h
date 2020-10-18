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
    void clear(int rowNumber);

public:
    Display(byte address, int width, int height);
    void enable(bool state);
    void printProgress(int value);
    void printProgress(const char *text);
    void printMessage(const char *text);
    int getWidth();
};

#endif
