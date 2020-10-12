#include "Arduino.h"
#include "Display.h"

Display *display;

void setup()
{
  display = new Display(0x27, 16, 2);
  display->printMessage("Water Mole Test");
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
    display->printProgress(i);
    delay(1000);
  }
}
