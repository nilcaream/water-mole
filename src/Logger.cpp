#include "Logger.h"

void Logger::message(const char *format, ...)
{
    unsigned long time = millis();

    char buffer[128];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 128, format, args);
    va_end(args);

    char message[256];
    sprintf(message, "Log %10lu : %s\n", time, buffer);

    Serial.print(message);
}
