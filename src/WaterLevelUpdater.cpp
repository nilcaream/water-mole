#include "WaterLevelUpdater.h"
#include "Logger.h"

WaterLevelUpdater::WaterLevelUpdater(Display *display, WaterLevelDetector *detector)
{
    this->display = display;
    this->detector = detector;
}

void WaterLevelUpdater::loop()
{
    unsigned long now = millis();
    if (now > this->nextRefresh)
    {
        this->update();
        this->nextRefresh = now + 3 * 1000;
    }
}

void WaterLevelUpdater::update()
{
    int pinsNumber = detector->getDigitalPinsNumber();
    int barWidth = (int)floor(1.0 * display->getWidth() / pinsNumber);

    display->printMessage("Checking level");
    Logger::message("Checking level");
    detector->refresh();

    char pinsText[this->display->getWidth() + 1];

    for (int i = 0; i < pinsNumber; i++)
    {
        for (int j = 0; j < barWidth; j++)
        {
            pinsText[i * barWidth + j + 1] = (detector->getLevel(i)) ? '>' : '-';
        }
    }

    pinsText[0] = '[';
    pinsText[display->getWidth() - 1] = ']';
    pinsText[display->getWidth()] = '\0';

    display->printProgress(pinsText);
}
