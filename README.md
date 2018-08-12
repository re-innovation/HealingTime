# HealingTime
Code and some design files for motor controller boards

# Overview
The main project is an array of stepper motors (20 in total in a bank 4 wide and 5 high, measuring around 1.5m (w) x 2m (h)).
These motors spin 360 degrees after a set time delay (typically every 15 mins). The spin takes a set amount of time (typically 30 seconds). They must reset to the same point afetr each spin.

# Detail

Each stpper motors has a power driver. They are 4 wire steppers which need to be controlled in the correct order to rotate in either direction or at a certain speed.

Each stpper motor 

The position sensor

The time is montiored using a real time clock. This needs to be accurately set at the start of the project.




# Motor controllers
There are 4 otor controller boards. Each motor controller board controls a set of 2 steppers and a set of 3 steppers (so a total of 5 motors per board).

These have the following connections:

Arduino Pin  | Function
-------------|--------------------
D0           | test 
D1           | test 
D2           | test 
D3           | test 
D4           | test 
D5           | test 
D6           | test 
D7           | test 
D8           | test 
D9           | test 
D10          | test 
D11          | test 
D12          | test 
D13          | test 
A0           | test 
A1           | test 
A2           | test 
A3           | test 
A4           | test 
A5           | test 





