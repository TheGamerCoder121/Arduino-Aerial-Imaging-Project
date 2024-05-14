# Descent Circuit Code for Warm and Cuddlies Project

## Overview

This code is designed for the Descent Circuit of the Warm and Cuddlies project, created by Nicklaus Vega. The Descent Circuit is responsible for detecting the distance to the ground and executing various functions during the descent phase. The code is written for the Arduino Uno.

## Features

- Ultrasonic distance measurement using an HCSR04 sensor.
- Altitude measurement and calibration using an EYW_alt altimeter.
- Servo control for camera movement.
- LED and speaker alerts.
- Button-activated setup.

## Components

- **Arduino Uno**
- **HCSR04 Ultrasonic Sensor**
- **EYW_alt Altimeter**
- **Servo Motor**
- **LED**
- **Speaker**
- **Push Button**

## Pin Connections

- **Ultrasonic Sensor:**
  - Trigger Pin: 6
  - Echo Pin: 7
- **Servo Motor:**
  - Signal Pin: 3
- **Speaker:**
  - Pin: 5
- **LED:**
  - Pin: 4
- **Push Button:**
  - Pin: 2

## Code Description

### Libraries

- `HCSR04.h`: Library for the ultrasonic rangefinder sensor.
- `EYW_alt.h`: Library for the altimeter.
- `Servo.h`: Library for servo control.

### Object Declarations

- `Servo cameraServo`: Controls the servo motor for the camera.
- `UltraSonicDistanceSensor distanceSensor(6, 7)`: Measures distance using the ultrasonic sensor.
- `EYW_alt::Altimeter altimeter`: Measures altitude.

### Pin Declarations

- `const int speakerPin = 5`: Speaker pin.
- `int ledPin = 4`: LED pin.
- `int buttonPin = 2`: Push button pin.

### Variable Declarations

- `float currentHeight = 0.0`: Stores the current height in meters.
- `bool heightAchieved = false`: Flag to check if the target altitude is reached.
- `int distance = 0`: Stores the distance to the ground in centimeters.
- `bool setupDone = false`: Flag to check if setup is completed.

### Functions

- `void setup()`: Initializes pins and serial communication.
- `void loop()`: Main program loop. Checks for button press to start setup and continuously measures distance and height.
- `void moveServo(int angle)`: Moves the servo to a specified angle.
- `void playTone(int note, int duration)`: Plays a tone for a specified duration.
- `void flashLED()`: Flashes the LED.
- `void landed()`: Executes landing sequence with tones and LED flashes.

### Setup Process

1. Waits for the button press to start setup.
2. Calibrates the altimeter.
3. Plays a tone and flashes the LED to indicate successful calibration.
4. Attaches the servo motor.
5. Sets the `setupDone` flag to `true`.

### Main Loop

1. Measures the distance to the ground using the ultrasonic sensor.
2. Measures the current height using the altimeter.
3. Outputs the distance and height to the serial monitor.
4. Checks if the distance is less than 3 cm to trigger the landing sequence.
5. Moves the servo to a specified angle.

## Usage

1. Connect the components to the Arduino Uno as described in the pin connections.
2. Upload the code to the Arduino Uno.
3. Press the button to start the setup process.
4. The system will measure distance and height, and control the servo, LED, and speaker accordingly.

## Disclaimer

Created By Nicklaus Vega  
© Warm and Cuddlies 2024  
Please use responsibly.