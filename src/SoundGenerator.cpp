#include "SoundGenerator.h"

SoundGenerator::SoundGenerator(byte pin, Display *display)
{
    this->pin = pin;
    this->display = display;
}

void SoundGenerator::loop()
{
    unsigned long now = millis();
    if (now > this->nextActionTime)
    {
        if (this->state == SOUND)
        {
            long time = random(500, 2000);

            noTone(this->pin);

            this->nextActionTime = now + time;
            this->state = PAUSE;
            this->display->printMessage("Pause %dms", time);
        }
        else if (this->state == PAUSE)
        {
            long time = random(500, 2000);
            long frequency = this->nextFrequency();

            tone(this->pin, (double)frequency);

            this->nextActionTime = now + time;
            this->state = SOUND;
            this->display->printMessage("Sound %dHz %dms", frequency, time);
        }
    }
}

long SoundGenerator::nextFrequency()
{
    int option = random(0, 100);
    long result;

    if (option < 50) // low note
    {
        result = random(50, 400);
    }
    else if (option < 75) // mid note
    {
        result = random(400, 3000);
    }
    else // high note
    {
        result = random(3000, 6000);
    }

    return result;
}
