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

The Master connects to the slaves via a serial connection (running at 9600 baud).
The master will send commands to run the slaves. This would be:
"SA1RUN" - This would be Slave 1 motor set A run
"S3BRUN" - This would be slave 3 motor set B run
"SALLRUN" - This would tell all the slave motors to run.
A 'run' is to rotate a set number of degrees in a set time, all the way to the position sensor to align the unit each time (in case of any inaccuracies).

The motor controller boards have the following connections:

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
The real time clock is the DS3231 I2C unit avialble from here:

https://www.ebay.co.uk/itm/DS3231-RTC-Precision-Board-Real-Time-Clock-Module-for-Arduino-Raspberry-Pi/262828567746?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

Information about using the DS3231 with Arduino is available here:

http://tronixstuff.com/2014/12/01/tutorial-using-ds1307-and-ds3231-real-time-clock-modules-with-arduino/

This project is using the DS3231 arduino library from here:

DS3231_Serial_Easy
Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
web: http://www.RinkyDinkElectronics.com/

The position sensors are NJK - 5002C type available from many suppliers, including:

https://www.ebay.co.uk/itm/Detective-Effect-Hall-Sensor-Proximity-Switch-NPN-3-wires-Normally-Open-Magnet/152534784195?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649

They need a 10k pull up resistor and the output goes low when it detects a magnetic field.

