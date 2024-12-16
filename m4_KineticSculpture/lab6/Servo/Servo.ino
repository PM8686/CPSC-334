#include <ESP32Servo.h>

Servo servo1; // First servo
Servo servo2; // Second servo

int servoPin1 = 4; // Pin for the first servo
int servoPin2 = 17; // Pin for the second servo

// Servo 1 position variables
int currentAngle1 = 30;        // Starting angle for servo 1
int targetAngle1 = 90;         // Target angle for servo 1
int step1 = 1;                 // Step size for smooth motion
int previousMillis1 = 0; // Timer for servo 1
int interval1 = 20; // Interval for servo 1

// Servo 2 (mirrored) position variables
int currentAngle2 = 60;        // Initial angle for servo 2
int previousMillis2 = 0; // Timer for servo 2
int interval2 = 20; // Interval for servo 2

// Mode toggle: true = same motion, false = mirrored motion
bool sameMotion = true;

void setup() {
  // Attach servos to their respective pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Set initial positions
  servo1.write(currentAngle1);
  servo2.write(currentAngle2);

  Serial.begin(115200);
  Serial.println("Servo control started");
}

void loop() {
  unsigned long currentMillis = millis();

  // Update servo 1 motion
  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    updateServoMotion(servo1, currentAngle1, targetAngle1, step1);

    // Reverse direction at target angle for servo 1
    if (currentAngle1 == targetAngle1) {
      targetAngle1 = (targetAngle1 == 90) ? 0 : 90;
    }
  }

  // Update servo 2 motion
  if (currentMillis - previousMillis2 >= interval2) {
    previousMillis2 = currentMillis;

    if (sameMotion) {
      // Servo 2 plays the same motion as Servo 1
      currentAngle2 = currentAngle1;
      interval1 = 20;
      interval2 = 20;
    } else {
      // Servo 2 mirrors Servo 1
      currentAngle2 = 90 - currentAngle1; // Reflection logic
      interval1 = 5;
      interval2 = 5;
    }

    servo2.write(currentAngle2);
    Serial.print("Servo 2 Angle: ");
    Serial.println(currentAngle2);
  }

  // Toggle mode example (replace with your condition to toggle modes)
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == 'm') {
      sameMotion = !sameMotion;
      Serial.print("Mode switched to: ");
      Serial.println(sameMotion ? "Same Motion" : "Mirror Motion");
    }
  }
}

// Function to update a servo's motion
void updateServoMotion(Servo &servo, int &currentAngle, int &targetAngle, int step) {
  if (currentAngle < targetAngle) {
    currentAngle += step;
  } else if (currentAngle > targetAngle) {
    currentAngle -= step;
  }

  servo.write(currentAngle);
  Serial.print("Servo 1 Angle: ");
  Serial.println(currentAngle);
}
