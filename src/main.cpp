#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "Display.h"
#include "WaterLevelDetector.h"
#include "Logger.h"

Display *display;
WaterLevelDetector *detector;

void updateLevels();
void enableDisplay();
void disableDisplay();

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
  detector->addDigitalPin(D3);
  detector->addDigitalPin(D4);
  detector->addDigitalPin(D5);
  detector->addDigitalPin(D6);
  detector->addDigitalPin(D7);

  pinMode(D9, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(D9), enableDisplay, RISING);
  attachInterrupt(digitalPinToInterrupt(D9), disableDisplay, FALLING);

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
  int pinsNumber = detector->getDigitalPinsNumber();
  int barWidth = (int)floor(1.0 * display->getWidth() / pinsNumber);

  display->printMessage("Checking level");
  detector->refresh();

  char pinsText[display->getWidth() + 1];

  for (int i = 0; i < pinsNumber; i++)
  {
    for (int j = 0; j < barWidth; j++)
    {
      pinsText[i * barWidth + j + 1] = (detector->getLevel(i) < 10) ? '>' : '-';
    }
  }

  pinsText[0] = '[';
  pinsText[display->getWidth() - 1] = ']';
  pinsText[display->getWidth()] = '\0';

  display->printProgress(pinsText);
}

void enableDisplay()
{
  Logger::message("Movement detected - enable");
  display->enable(true);
}

void disableDisplay()
{
  Logger::message("Movement gone - disable");
  display->enable(false);
}
