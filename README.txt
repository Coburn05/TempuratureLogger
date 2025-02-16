this project uses a DS18B20-like tempurature sensor to log monitor the tempurature.
The goal is to make something that can work with minimal maninace, and user input to keep it running.

To start you will need to enable the 1-Wire interface, this can be done with
	sudo raspi-config
	then navigate to "interface options" (3)
	enable "1-Wire" (I7)
after this you will need to wire the tempurature sensor
	sensor VCC -> raspberry 3.3V (pin 1)
	sensor GND -> raspberry GND (pin 9)
	sensor OUT -> raspberry GPIO4 (pin 7)
	it is important to note that a 4.7kΩ resistor between VCC and OUT is needed
 after this you will need to find the device location
	ls /sys/bus/w1/devices
	you are looking for something like "28-xxxxxxxxxxxx"
	copy this
in the code on line 16, replace the placeholder with the address you coppied, do not change anything else.

To compile you can use
	g++ logger.cpp -Wall -o logger
or use
	make

This will write a file on your device with a tempurature reading every 10 minutes,
but this can be changed in the loop in main
	
