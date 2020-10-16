#include "WaterLevelDetector.h"
#include "Logger.h"

WaterLevelDetector::WaterLevelDetector(byte analogPin)
{
    this->analogPin = analogPin;
    pinMode(analogPin, INPUT);
    Logger::message("Added water analog pin %d", analogPin);
}

byte WaterLevelDetector::getDigitalPinsNumber()
{
    return this->digitalPinsNumber;
}

void WaterLevelDetector::addDigitalPin(byte pin)
{
    this->digitalPins[this->digitalPinsNumber] = pin;
    this->digitalPinsNumber++;
    Logger::message("Added water digital pin %d", pin);
}

void WaterLevelDetector::refresh()
{
    const int iterations = 16;
    const int sleep = 10;

    for (int pinNumber = 0; pinNumber < this->digitalPinsNumber; pinNumber++)
    {
        int valueMin = 1024;
        int valueMax = 0;
        int valueAverage = 0;

        // set all as input
        for (int i = 0; i < this->digitalPinsNumber; i++)
        {
            pinMode(this->digitalPins[i], INPUT);
        }

        // set current one as output with low value
        pinMode(this->digitalPins[pinNumber], OUTPUT);
        digitalWrite(this->digitalPins[pinNumber], LOW);

        int result = 0;
        for (int i = 0; i < iterations; i++)
        {
            delay(sleep);
            result = analogRead(this->analogPin);
            valueMin = min(valueMin, result);
            valueMax = max(valueMax, result);
            valueAverage += result;
        }
        valueAverage /= iterations;

        // revert
        pinMode(this->digitalPins[pinNumber], INPUT);

        // update state and log
        this->results[pinNumber] = valueMin;
        Logger::message("Water level pin %d min %d (avg %d, max %d)", valueMin, valueAverage, valueMax);
    }
}

int WaterLevelDetector::getLevel(byte index)
{
    return this->results[index];
}
