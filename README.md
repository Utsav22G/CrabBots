# CrabBots
### Small robots that use colored light to interact with other robots and the environment to perform complex interactions. 

## Overview
To learn more about our project, visit our [website!](http://poe.olin.edu/2018/crabworks/)

This github serves a storage capsule for our CAD files, PCB designs, and code used in our project. 

## PCB (Robot)
Our PCB is based off the Arduino Uno and includes some additional features:
* An analog mux for an increased number of anlog input pins
* A dual h-bridge motor driver to power our motors
* A 3-axis accelerometer for tap/bump detection
* Support for an RGB strip. We used NeoPixels

Because our PCB follows the same avr architecture as the Arduino Uno (and uses the same Atmega328P-PB), any Arduino code can be
uploaded through the Arduino IDE compiler to program our boards. However, our boards are lacking usb-serial convertera so an external
usb-serial converter is needed ([this is what we used](https://www.sparkfun.com/products/9825)).

You might notice that our assembled PCBs are populated with only a fraction of the parts that are included in our layout. This is 
due to a radical change in our photodiode sensing circuit after shipping the boards to be manufactured. Fortunately, our new circuit
uses less parts so it's still easy to assemble a working board. 

If you are up for an extra challenge, feel free to submit a pull request for a flashy, new board.

## PCB (Beacon)
What is the best accessory for our CrabBot? A fancy flashlight that can be programmed to display any color and controlled with a
tactile toggle button, of course! Our beacons are a useful tool for debugging and controlling our bots.

The schematic for the board stayed mostly the same. An input for **gnd** and **vcc** are needed for the board to function. We also recommend adding a power switch so the Attiny 85 doesn't drain your battery over time.


## Software
Our final bots rely on two code files: chaser, chased. When uploaded to our CrabBots, this code will make them chase each other. The code is written in Arduino and relys on multiple libraries including the Adafruit sensor library. The appropriate packages that need to be downloaded can be found [here](https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/arduino) and [here](https://learn.adafruit.com/adafruit-neopixel-uberguide/basic-connections). 

## Mechanical Design
The final iteration of CAD can be found here. We printed the components on a Prusa with PLA filament. While this design should not
be constrained by the type of plastic or printer used, we can't guarantee success with another setup. 

## Assembly
While we currently don't have a thorough instruction set layed out, we recommend looking at all our pictures. You probably don't need
or want instructions anyways!
