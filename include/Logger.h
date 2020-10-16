#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include "string.h"
#include "stdarg.h"

class Logger
{
public:
    static void message(const char *format, ...);
};

#endif
