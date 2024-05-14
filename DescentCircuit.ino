/*
  Created By Nicklaus Vega
  © Warm and Cuddlies 2024
  This code is for the Descent Circuit of the Warm and Cuddlies project.
  The Descent Circuit is responsible for detecting the distance to the ground and misc functions.
  Code is written for the Arduino Uno.
  Please use responsibly.
*/

// Includes necessary libraries
#include <HCSR04.h>   // Ultrasonic rangefinder sensor library
#include <EYW_alt.h>  // Altimeter library
#include <Servo.h>    // Servo library

// Object Declarations
Servo cameraServo;                              // Servo for camera control
UltraSonicDistanceSensor distanceSensor(6, 7);  // Ultrasonic sensor on pins 6 (Trigger) and 7 (Echo)
EYW_alt::Altimeter altimeter;                   // Altimeter object

// Pin Declarations
const int speakerPin = 5;
int ledPin = 4;     // Pin 13 has an LED connected on most Arduino boards. Give it a name:
int buttonPin = 2;  // Use a variable to store the pushbutton pin #

// Variable Declarations
float currentHeight = 0.0;    // Current height in meters
bool heightAchieved = false;  // Flag for reaching target altitude
int distance = 0;             // Distance to object in centimeters
bool setupDone = false;       // Checks if button is press to start setup
int picsTaken = 0;            // Number of pictures taken

/*
    digitalWrite(ledPin, LOW); // LED on
    digitalWrite(ledPin, HIGH); // LED off
*/

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);        // Start serial communication at 9600 baud
  cameraServo.attach(3);     // Attach servo signal to pin 3
  Serial.println("System ready. Press the button to start setup.");
}

void loop() {
  if (!setupDone) {
    if (digitalRead(buttonPin) == LOW) { // Check for LOW instead of HIGH
      altimeter.begin();         // Initialize altimeter
      altimeter.calibrate(100);  // Calibrate altimeter to establish ground level
      Serial.println("Altimeter calibrated");

      tone(speakerPin, 500);       // Play a 500 Hz tone
      digitalWrite(ledPin, HIGH);  // Turn on LED
      delay(1000);                 // Delay for 1 second
      noTone(speakerPin);          // Stop tone
      digitalWrite(ledPin, LOW);   // Turn off LED

      setupDone = true;
    }
  } else {
    distance = distanceSensor.measureDistanceCm();  // Measure distance
    currentHeight = altimeter.getHeightAvg(30);     // Average altitude from 50 measurements

    // Serial output for distance and height
    Serial.print("Current Distance: ");
    Serial.println(distance);
    Serial.print("Current Height in meters: ");
    Serial.println(currentHeight);

    if (picsTaken < 3) {
      takePic();
      picsTaken++;
    }

    if (distance < 0) {
      landed();
    }


  }
}

// Function to move the servo to a specific angle
void moveServoToAngle(int angle) {
  if (angle >= 0 && angle <= 180) {
    cameraServo.write(angle);
    Serial.print("Servo moved to angle: ");
    Serial.println(angle);
  } else {
    Serial.println("Invalid angle. Angle must be between 0 and 180.");
  }
}

// Function to play a tone, pause, then wait
void playTone(int note, int duration) {
  tone(speakerPin, note);
  delay(duration);
  noTone(speakerPin);
  delay(50);  // Short pause after playing a note
}

void flashLED() {
  digitalWrite(ledPin, HIGH);  // Turn on LED
  delay(1000);                 // Delay for 1 second
  digitalWrite(ledPin, LOW);   // Turn off LED
}

void landed() {
  playTone(220, 300);
  flashLED();
  playTone(494, 300);
  flashLED();
  playTone(1047, 300);
  flashLED();
}

void takePic() {
    moveServoToAngle(150); // Move servo to 30 degrees
    delay(2000);          // Wait for 2 seconds
    moveServoToAngle(0); // Move servo to 150 degrees
    delay(2000);          // Wait for 2 seconds
}
