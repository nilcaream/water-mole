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
  display->printMessage("Water Mole Test");

  detector = new WaterLevelDetector(A0);
  detector->addDigitalPin(D3);
  detector->addDigitalPin(D4);
  detector->addDigitalPin(D5);
  detector->addDigitalPin(D6);
  detector->addDigitalPin(D7);


  pinMode(D8, INPUT); // verify this pin

  sound = new SoundGenerator(D9, display); // verify this pin

  updater = new WaterLevelUpdater(display, detector);
  display->enable(true);

  Logger::message("Setup complete");
}

void loop()
{
  display->loop(digitalRead(D8));
  updater->loop();
  sound->loop();
  delay(100);
}
