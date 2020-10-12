#ifndef I2cScanner_h
#define I2cScanner_h

#include "Arduino.h"
#include "Wire.h"

class I2cScanner
{
public:
    byte getFirstAddress();
};

#endif
