#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "pitches.h"
#include "melodies.h"
#include <ESP32Servo.h>

// Define pins and objects
int SDA_pin = 22;
int SCL_pin = 21;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
unsigned long turnStartTime = 0; // Time when the turning started
const unsigned long turnDuration = 500; // Duration for the turn in milliseconds
bool turning = false; // Whether the turn is in progress


// Distance Sensor
const int trigPin = 5;
const int echoPin = 16;
float duration, distance;

// Define buzzer
const int buzzer = 15;

// States enumeration
enum State {
  NORMAL,
  NORMAL_DELAY,
  TURN_LEFT,
  DELAY,
  PANIC,
  PANIC_DELAY
};

// State variables
State currentState = NORMAL;
unsigned long stateStartTime = 0;
const int delayDuration = 1000; // 1 second delay
const int delayDuration_panic = 500;

// Panic counter
int num_turns = 0;

Servo servo1; // First servo
Servo servo2; // Second servo

int servoPin1 = 4; // Pin for the first servo
int servoPin2 = 17; // Pin for the second servo

// Servo 1 position variables
int currentAngle1 = 30;        // Starting angle for servo 1
int targetAngle1 = 90;         // Target angle for servo 1
int step1 = 2;                 // Step size for smooth motion
int previousMillis1 = 0; // Timer for servo 1
int interval1 = 20; // Interval for servo 1

// Servo 2 (mirrored) position variables
int currentAngle2 = 60;        // Initial angle for servo 2
int previousMillis2 = 0; // Timer for servo 2
int interval2 = 20; // Interval for servo 2

// Mode toggle: true = same motion, false = mirrored motion
bool calmServo;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  // Initialize I2C
  Wire.begin(SDA_pin, SCL_pin);

  if (!AFMS.begin()) {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Initialize distance sensor and buzzer
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  // Attach servos to their respective pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Set initial positions
  servo1.write(currentAngle1);
  servo2.write(currentAngle2);

  Serial.begin(115200);
  Serial.println("Servo control started");

  // Set initial motor speed
  motor1->setSpeed(100);
  motor1->run(FORWARD);
  motor1->run(RELEASE);

  motor2->setSpeed(100);
  motor2->run(FORWARD);
  motor2->run(RELEASE);
}

void loop() {
  switch (currentState) {
    case NORMAL:
      normalState();
      break;

    case NORMAL_DELAY:
      normalDelay();
      break;

    case TURN_LEFT:
      turnLeftState();
      break;

    case DELAY:
      delayState();
      break;

    case PANIC:
      panicState();
      break;

    case PANIC_DELAY:
      panicDelay();
      break;
  }

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

    if (calmServo == true) {
      // Servo 2 plays the same motion as Servo 1
      currentAngle2 = currentAngle1;
      interval1 = 20;
      interval2 = 20;
    } else {
      // Servo 2 mirrors Servo 1
      currentAngle2 = 90 - currentAngle1; // Reflection logic
      Serial.println(currentAngle2);
      interval1 = 5;
      interval2 = 5;
    }

    servo2.write(currentAngle2);
    // Serial.print("Servo 2 Angle: ");
    // Serial.println(currentAngle2);
  }
}

// State: NORMAL (Moving Forward)
void normalState() {
  // servos are normal
  calmServo = true;

  // Move motors forward
  motor1->run(FORWARD);
  motor1->setSpeed(110);

  motor2->run(FORWARD);
  motor2->setSpeed(75);

  // Check distance
  distance = get_distance();

  if (distance < 15) {
    Serial.println("Object too close! Switching to TURN_LEFT state.");
    currentState = DELAY;
  }
}

void normalDelay() {
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  if (millis() - stateStartTime >= delayDuration) {
    Serial.println("Delay over. Switching to Normal state.");
    currentState = NORMAL;
  }
}

void turnLeftState() {
  if (!turning) {
    // Start the turning process
    Serial.println("Turning left.");
    num_turns++;
    motor1->setSpeed(100);
    motor2->setSpeed(100);
    motor1->run(FORWARD);
    motor2->run(BACKWARD);

    turnStartTime = millis(); // Record the start time
    turning = true;
  } else {
    // Check if the turn duration has elapsed
    if (millis() - turnStartTime >= turnDuration) {
      // Stop motors after turning
      motor1->run(RELEASE);
      motor2->run(RELEASE);
      turning = false;

      // Update distance
      distance = get_distance();

      if (distance >= 15) {
        Serial.println("Object cleared. Switching to NORMAL state.");
        num_turns = 0;
        currentState = NORMAL_DELAY;
      } else {
        if (num_turns > 3) {
          Serial.println("Too many turns! Switching to PANIC state.");
          currentState = PANIC_DELAY;
          calmServo = false;
        } else {
          Serial.println("Still too close. Switching to DELAY state.");
          currentState = DELAY;
          stateStartTime = millis();
        }
      }
    }
  }
}


// State: DELAY
void delayState() {
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  if (millis() - stateStartTime >= delayDuration) {
    Serial.println("Delay over. Switching to TURN_LEFT state.");
    currentState = TURN_LEFT;
  }
}

void panicState() {
  if (!turning) {
    // Start the turning process
    Serial.println("PANIC!!! Turning left.");
    num_turns++;
    motor1->setSpeed(100);
    motor2->setSpeed(100);
    motor1->run(FORWARD);
    motor2->run(BACKWARD);

    turnStartTime = millis(); // Record the start time
    turning = true;

    // Play a warning sound (non-blocking tone could be implemented here)
    // tone(buzzer, 1000, 500); 
  } else {
    // Check if the turn duration has elapsed
    if (millis() - turnStartTime >= turnDuration) {
      // Stop motors after turning
      motor1->run(RELEASE);
      motor2->run(RELEASE);
      turning = false;

      // Update distance
      distance = get_distance();

      if (distance >= 15) {
        Serial.println("Object cleared. Switching to NORMAL state.");
        num_turns = 0;
        currentState = NORMAL_DELAY;
      } else {
        Serial.println("Still too close. Switching to PANIC_DELAY state.");
        currentState = PANIC_DELAY;
        stateStartTime = millis();
      }
    }
  }
}


void panicDelay(){
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  if (millis() - stateStartTime >= delayDuration_panic) {
    Serial.println("Delay over. Switching to PANIC state.");
    currentState = PANIC;
  }
}

// use ultrasonic distance sensor
int get_distance() {
    // Read the distance sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return distance = (duration * 0.0343) / 2;
}

// // Function to turn left by running motors in opposite directions
// void turnLeft() {
//   // Set both motors to run at speed 100 but in opposite directions
//   motor1->setSpeed(100);  // Motor 1 runs forward
//   motor2->setSpeed(100);  // Motor 2 runs backward
  
//   motor1->run(FORWARD);   // Motor 1 moves forward
//   motor2->run(BACKWARD);  // Motor 2 moves backward
//   delay(500);             // Turn left for 0.5 seconds (adjust as needed)

//   // Stop motors after turning
//   motor1->run(RELEASE);
//   motor2->run(RELEASE);
// }

// Function to update a servo's motion
void updateServoMotion(Servo &servo, int &currentAngle, int &targetAngle, int step) {
  if (currentAngle < targetAngle) {
    currentAngle += step;
  } else if (currentAngle > targetAngle) {
    currentAngle -= step;
  }

  servo.write(currentAngle);
  // Serial.print("Servo 1 Angle: ");
  // Serial.println(currentAngle);
}

// void Explore() {
//   //Melody
//   Serial.println(note);
//   if (note < sizeExplore) {
//     int duration = 1000 / durationsExplore[note];
//     tone(buzzer, melodyExplore[note], duration);
//     int pauseBetweenNotes = duration * .90;
//     delay(pauseBetweenNotes);
//     noTone(buzzer);
//     note++;
//   }
//   else {
//     note = 0;
//   }
// }