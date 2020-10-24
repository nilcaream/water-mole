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
    Logger::message("Added water digital pin %d as #%d", pin, this->digitalPinsNumber);
    this->digitalPinsNumber++;
}

void WaterLevelDetector::refresh()
{
    const int iterations = 64;
    const int sleep = 1;

    int base;

    // set all as input
    for (int i = 0; i < this->digitalPinsNumber; i++)
    {
        pinMode(this->digitalPins[i], INPUT);
    }
    yield();
    base = analogRead(this->analogPin);
    Logger::message("Water level base %d", base);

    for (int pinNumber = 0; pinNumber < this->digitalPinsNumber; pinNumber++)
    {
        int valueMin = 1024;
        int valueMax = 0;
        int valueAverage = 0;

        // set all as input
        for (int i = 0; i < this->digitalPinsNumber; i++)
        {
            pinMode(this->digitalPins[i], INPUT);
            yield();
        }

        // set current one as output with low value
        pinMode(this->digitalPins[pinNumber], OUTPUT);
        yield();
        digitalWrite(this->digitalPins[pinNumber], LOW);
        yield();

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
        yield();

        // update state and log
        this->results[pinNumber] = valueMin < 0.3 * base;
        Logger::message("Water level pin #%d: %d (%d-%d-%d)", pinNumber, this->results[pinNumber], valueMin, valueAverage, valueMax);
    }
}

bool WaterLevelDetector::getLevel(byte index)
{
    return this->results[index];
}
