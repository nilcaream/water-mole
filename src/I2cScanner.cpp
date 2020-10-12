#include "I2cScanner.h"

byte I2cScanner::getFirstAddress()
{
    byte result = 0;

    for (byte address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        delay(10);
        int exitCode = Wire.endTransmission();

        Serial.print("I2C address ");
        Serial.print(address, HEX);
        Serial.print(" exit code ");
        Serial.print(exitCode);

        if (exitCode == 0)
        {
            Serial.println(" found");
            result = (result == 0) ? address : result;
        }
        else
        {
            Serial.println("");
        }
    }

    return result;
}
