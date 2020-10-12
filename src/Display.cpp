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

void Display::printMessage(const char *text)
{
    char blank[width];
    for (int i = 0; i < width; i++)
    {
        blank[i] = ' ';
    }
    lcd->setCursor(0, 0);
    lcd->print(blank);
    lcd->print(text);
}

void Display::printProgress(int value)
{
    char text[width];
    // TODO remove hardcoded bar size of 4
    int barWidth = value * 4;

    for (int i = 0; i < width; i++)
    {
        text[i] = i < barWidth ? 'X' : ' ';
    }

    lcd->setCursor(0, 1);
    lcd->print(text);
}
