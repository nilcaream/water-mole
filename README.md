# Water Mole

Arduino project of piezoelectric mole repellent and waste water level monitor.

# Main components

* ESP8266 NodeMCU V2 - Arduino-compatible board.
* MT3608 DC-DC Converter - to power passive piezoelectric buzzers with 12V.
* 16x2 LCD with HD44780 controller - to display water level.
* HC-SR501 PIR - motion detector to activate display when needed.
* 2N2222 - NPN transistor used as a switch to activate buzzers.

# I/O

* Powered with 5V wall USB charger.
* Analog input used for detecting water level.
* Digital output to trigger buzzers.
* Digital input to react on motion detector.
* Remaining digital outputs to test against set water levels.
* I2S for LCD display.
* Micro USB as power source.
* RJ45 keystone as output for buzzer, analog in and digital water level outputs.
