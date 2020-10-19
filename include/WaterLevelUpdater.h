#ifndef WaterLevelUpdater_h
#define WaterLevelUpdater_h

#include "Arduino.h"
#include "Display.h"
#include "WaterLevelDetector.h"

class WaterLevelUpdater
{
private:
    Display *display;
    WaterLevelDetector *detector;
    unsigned long nextRefresh = 0;
    void update();

public:
    WaterLevelUpdater(Display *display, WaterLevelDetector *detector);
    void loop();
};

#endif
