#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "Display.h"
#include "WaterLevelDetector.h"
#include "WaterLevelUpdater.h"
#include "SoundGenerator.h"
#include "Logger.h"

Display *display;
WaterLevelDetector *detector;
WaterLevelUpdater *updater;
SoundGenerator *sound;

void setup()
{
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  delay(1);

  Serial.begin(9600);
  Logger::message("Water Mole started");

  display = new Display(0x27, 16, 2);
  display->enable(true);
  display->printMessage("Water Mole");

  detector = new WaterLevelDetector(A0);
  detector->addDigitalPin(D3);
  detector->addDigitalPin(D4);
  detector->addDigitalPin(D5);
  detector->addDigitalPin(D6);
  detector->addDigitalPin(D7);

  pinMode(D8, OUTPUT); // D8 / GPIO15 / buzzer
  pinMode(D0, INPUT);  // D0 / GPIO16 / PIR

  sound = new SoundGenerator(D8, display);
  updater = new WaterLevelUpdater(display, detector);

  Logger::message("Setup complete");
}

void loop()
{
  display->loop(digitalRead(D0));
  updater->loop();
  sound->loop();
  delay(100);
}
