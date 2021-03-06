# Water Mole

Arduino project of piezoelectric mole repellent and waste water level monitor.

These are actually two separate projects fit into one package. First is a mole repellent that uses parallel array of passive piezoelectric buzzers. Every few minutes (or less) set of random tones is emitted. Buzzers are sealed and digged in the ground (actually in mole tunnels). This should work as most mole repellents work this way.

Second project is a waste water meter. A sewage tank will contain a set of wires at different fill levels e.g. at 5%, 50%, 80%, 90%, 95%. Information about which level is reached is displayed on LCD screed. Motion detector is used to set backlit and enable display.

Electronics are set in home and are connected with external wires by LAN cable. 

# Components

* ESP8266 NodeMCU V2 - Arduino-compatible board.
* MT3608 DC-DC Converter - to power passive piezoelectric buzzers with 12V.
* 16x2 LCD with HD44780 controller - to display water level.
* HC-SR501 PIR - motion detector to activate display when needed.
* 2N2222 - NPN transistor used as a switch to activate buzzers.
* 100 Ohm resistor - for analog input (just in case). Probably not needed.
* 220 Ohm resistor - for buzzer BJT circuit in case of buzzer short.
* 2.7k Ohm resistor - parallel with buzzer circuit.
* 10k Ohm resistor - in transistor base.

# I/O

* Powered with 5V wall USB charger.
* Analog input used for detecting water level.
* Digital output to trigger buzzers.
* Digital input to react on motion detector.
* Remaining digital outputs to test against set water levels.
* I2S for LCD display.
* Micro USB as power source.
* RJ45 keystone as output for buzzer, analog in and digital water level outputs. 
  * 5 wires for water levels
  * 1 wire for analog in
  * 2 wires for buzzer(s)

# Pins

Mandatory read:

* https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
* https://rabbithole.wwwdotorg.org/2017/03/28/esp8266-gpio.html

GPIO

* D0 / GPIO16 - PIR input
* D1 / GPIO5 - SCL (for LCD)
* D2 / GPIO4 - SDA (for LCD)
* D3 / GPIO0 - water level 1 (tank bottom)
* D4 / GPIO2 - water level 2 (0.5 tank volume)
* D5 / GPIO14 - water level 3 (0.8 tank volume)
* D6 / GPIO12 - water level 4 (0.9 tank volume)
* D7 / GPIO13 - water level 5 (tank full)
* D8 / GPIO15 - buzzer trigger (BJT base)

# Operation logic

The non-trivial part of the project is water level detection. This is done by reading the ground voltage on analog in pin (A0) by providing TTL output (LOW) from several digital out pins (D3 to D7).

Other idea is to close the circut with a TTL HIGH state. This method turned out to be not reliable bacause of varying waste water conductivity.

Yet another option would be to create a capacitance water level meter. Expected capacity would be in mid pico to low nano farad range. This is difficult because of few reasons. We could measure time constraint but for 1pF we need 1G Ohm resitor to have time of 1ms. These types of resistors are not so common and measuring millisecond times in Arduino is not that simple (for me). There is a simple way for that (2-wires meter) but 2 analog inputs are needed. ESP8266 has only one. Besides I suppose that waste water would eventually clog the capacitator.

# Breadboard

A bit outdated now but shows general concept of the project.

![Breadboard](docs/water-mole_bb.png)

# Prototypes

![Prototype](docs/prototype-01.jpg)

![Prototype](docs/prototype-02.jpg)

# Board

GIMP-designed universal circuit board (original resolution 98x77 pixel art :). Board size 7cm x 9cm.

![Components setup](docs/board-components.png)

![Complete board](docs/board-wires.png)


# Mole circuit 

Piezo electric buzzer is denoted as 1M Ohm resistor. It is in series connection with 220 Ohm resistor in case buzzer gets shorted.

![Mole circuit](docs/mole-circuit.png)

# Disclaimer

This project is also a C++ learning playground for me. I am a Java developer and I haven't code C++ since 2007. Since then I am doing full time Java and some Javascript. The code is not perfect but I don't want to fallback to C as code written as classes is more natural for me. Yes, it looks like Java and follows some Java coding conventions.

This is my first Arduino and in general first electronic / hardware project.
