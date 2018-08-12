# HealingTime

Code and some design files for motor controller boards for an wall art piece.

# Overview

The main project is an array of stepper motors (20 in total in a bank 4 wide and 5 high, measuring around 1.5m (w) x 2m (h)).
These motors spin 360 degrees after a set time delay (typically every 15 mins). The spin takes a set amount of time (typically 30 seconds). They must reset to the same point after each spin.

In addition to this operation, at another time delay (typically 5 mins) then a random set of some of the motors will spin.

# Detail

Each stpper motors has a power driver. They are 4 wire steppers which need to be controlled in the correct order to rotate in either direction or at a certain speed.
Each stpper motor controls two arms, with each arm on a different cog so they rotate in sync but at different speeds.
These are powered through a stepper controller board (an Arduino Nano) which has the wiring connections as described below.

A position sensor uses a magnetic position sensor to ensure that the motor always returns back to the same point each time. As each unit will be slightly different (slight variation in starting point, positions of everything and alignment) then there needs to be a 'fudge factor' used for each of the motor sets to align each one. These fudge factors will be different for each motor/gear unit.

The time is montiored using a real time clock. This needs to be accurately set at the start of the project. It uses an I2C interface and can be asked the time every second or so. Depending upon the returned real time then the motors can be activated.

# Motor controllers

There are 4 motor controller boards. Each motor controller board controls a set of 2 steppers and a set of 3 steppers (so a total of 5 motors per board).
There will be one Master controller and 3 slaves.
The Master controller unit will have the real time clock. It will look at the time and decide what to do. It will also decide upon the ranom set of motors to run at 5 min intervals.
The Master connectors to the slaves 

These have the following connections:

Arduino Pin  | Function
-------------|--------------------
D0           | Rx - Serial
D1           | Tx - Serial
D2           | Position Sensor A
D3           | Position Sensor B
D4           | 
D5           | STEPA - 1
D6           | STEPA - 2
D7           | STEPA - 3 
D8           | STEPA - 4 
D9           | STEPB - 1
D10          | STEPB - 2 
D11          | STEPB - 3 
D12          | STEPB - 4
D13          | LED 
A0           |  
A1           | 
A2           |  
A3           |  
A4           | SDA
A5           | SCL
A6           | 
A7           | 

SDA and SCL are used for the real time clock.



