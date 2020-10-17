#include "Display.h"

Display::Display(byte address, int width, int height)
{
    this->width = width;
    this->height = height;

    lcd = new LiquidCrystal_I2C(address, width, height);
    lcd->begin(width, height);
    lcd->init();
    lcd->noBlink();
    lcd->noCursor();
}

void Display::enable(bool state)
{
    if (state)
    {
        lcd->backlight();
        lcd->display();
    }
    else
    {
        lcd->noDisplay();
        lcd->noBacklight();
    }
}

void Display::clear(int rowNumber)
{
    char blank[width + 1];
    for (int i = 0; i < width; i++)
    {
        blank[i] = ' ';
    }
    blank[width] = '\0';

    lcd->setCursor(0, rowNumber);
    lcd->print(blank);
}

void Display::printMessage(const char *text)
{
    this->clear(0);
    lcd->setCursor(0, 0);
    lcd->print(text);
}

void Display::printProgress(int value)
{
    char text[width + 1];
    // TODO remove hardcoded bar size of 4
    int barWidth = value * 4;

    for (int i = 0; i < width; i++)
    {
        text[i] = i < barWidth ? 'X' : ' ';
    }
    text[width] = '\0';

    lcd->setCursor(0, 1);
    lcd->print(text);
}

void Display::printProgress(const char *text)
{
    this->clear(1);
    lcd->setCursor(0, 1);
    lcd->print(text);
}
