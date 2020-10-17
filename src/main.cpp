#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "Display.h"
#include "WaterLevelDetector.h"
#include "Logger.h"

Display *display;
WaterLevelDetector *detector;

void updateLevels();

void setup()
{
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  Serial.begin(9600);
  Logger::message("Water Mole started");

  display = new Display(0x27, 16, 2);
  display->enable(true);
  display->printMessage("Water Mole Test");

  detector = new WaterLevelDetector(A0);
  detector->addDigitalPin(D5);
  detector->addDigitalPin(D6);
  detector->addDigitalPin(D7);
  detector->addDigitalPin(D8);

  Logger::message("Setup complete");
}

void loop()
{
  updateLevels();
  Logger::message("Waiting");
  display->printMessage("Waiting");
  delay(1000);
}

void updateLevels()
{
  int barWidth = 3;
  int pinsNumber = detector->getDigitalPinsNumber();
  display->printMessage("Checking level");
  detector->refresh();

  char pinsText[barWidth * pinsNumber + 1];

  for (int i = 0; i < pinsNumber; i++)
  {
    for (int j = 0; j < barWidth; j++)
    {
      pinsText[i * barWidth + j] = (detector->getLevel(i) < 10) ? 'X' : '-';
    }
  }

  pinsText[barWidth * pinsNumber] = '\0';
  display->printProgress(pinsText);
}
