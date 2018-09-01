/*
  Healing Time Stepper Motor Controller Test Program

  This runs a stepper motor (or motors) from an Arduino Nano
  5V ATMEGA328 16MHz (12MHz?)
  I'm using the 28BYJ-48 stepper motor with driver
  This Motor has a Gear ratio of 64 , and Stride Angle 5.625°
  so this motor has a 4096 Steps .
  Lots more info here:
  http://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/
  Gear ratio is: 64 approx :1
  Actual gear ratio: 63.68395 : 1

  The PCB has the following wiring:
  Stepper Motor Set 1 (6 x motors) is on:
  D5,D6,D7,D8

  Stepper Motor Set 2 (6 x motors) is on:
  D9,D10,D11,D12

  Connectors K1/K2/K3/K4 decide if all 12 Motors do the same thing or
  if there are two sets of 6 motors which can do different things.

  INPUTS:
  D2  Magnetic Sensor 1 (with 10k pull up)
  D3  Magnetic Sensor 2 (with 10k pull up)
  D4

  DETECT_IN1
  A0
  A1
  A2
  A3  This is the input voltage with a 100k/10k divider.
  A4  SDA for I2C for the DS3231 RTC
  A5  SCL for I2C for the DS3231 RTC

  This code has the following functions:

  Show the time from the RTC every second
  When there is a magnet near the sensor then it runs the stepper motor.
  This code is only for testing.

  This example code is in the public domain.
*/
#include <EEPROM.h>        // For writing values to the EEPROM
#include <avr/eeprom.h>

#include <DS3231.h>
// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  5     // IN1 on the ULN2003 driver 1
#define motorPin2  6     // IN2 on the ULN2003 driver 1
#define motorPin3  7     // IN3 on the ULN2003 driver 1
#define motorPin4  8     // IN4 on the ULN2003 driver 1

#define voltageMonitor A3  // This is the pin to measure the voltage on the input

int detect1 = 2;
int detect2 = 3;

int led = 13;  // LED on pin 13 - flash to make it obvious

int maxSpeed = 500;     // For the stepper motor
int acceleration = 100; // For the stepper motor

unsigned long int oldMillis = millis();

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {

  // Initialise the PIR as a input with a pull up resistor
  pinMode(detect1, INPUT);
  pinMode(detect2, INPUT);

  pinMode(voltageMonitor, INPUT);

  pinMode(led, OUTPUT); // Have the LED display an output

  Serial.begin(115200);

  stepper1.setMaxSpeed(maxSpeed);  // usual value = 500
  stepper1.setSpeed(maxSpeed);  // usual value = 200
  stepper1.setAcceleration(acceleration); // usual value = 100

  // Initialize the rtc object
  rtc.begin();

  // The following lines can be uncommented to set the date and time
  //  rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(15, 51, 30);     // Set the time to 12:00:00 (24hr format)
  //  rtc.setDate(1, 9, 2018);   // Set the date to January 1st, 2014


  // Switch off the motors
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

}
//--(end setup )---

void loop() {

  if (millis() >= oldMillis + 1000)
  {
    // Send Day-of-Week
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");
    // Send date
    Serial.print(rtc.getDateStr());
    Serial.print(" -- ");
    // Send time
    Serial.println(rtc.getTimeStr());
    oldMillis = millis();
    if (digitalRead(detect1) == LOW)
    {
      Serial.println("Triggered");
      stepper1.moveTo(0);
      while (stepper1.run())
      {
      }
      stepper1.moveTo(180);
      while (stepper1.run())
      {
      }
      // Switch off the motors
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      digitalWrite(motorPin3, LOW);
      digitalWrite(motorPin4, LOW);

    }
  }

}
