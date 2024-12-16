/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

int SDA_pin = 22;
int SCL_pin = 21;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  // Initialize I2C with custom pins for ESP32 (default SDA_pin=21, SCL_pin=22)
  Wire.begin(SDA_pin, SCL_pin); // Replace with your SDA_pin/SCL_pin pins if different

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the initial speed to start, from 0 (off) to 255 (max speed) for both motors
  motor1->setSpeed(100);
  motor1->run(FORWARD);
  motor1->run(RELEASE);

  motor2->setSpeed(100);
  motor2->run(FORWARD);
  motor2->run(RELEASE);
}

void loop() {
  uint8_t i;

  Serial.print("tick");

  // Control motor1 (M1)
  motor1->run(FORWARD);
  motor1->setSpeed(100);

  // Control motor2 (M2)
  motor2->run(FORWARD);
  motor2->setSpeed(75);

  Serial.println("forward");
  delay(1000);

  // turn left
  turnLeft(); // Call the turnLeft function
  delay(1000);
}

void turnLeft() {
  // Set both motors to run at speed 100 but in opposite directions
  motor1->setSpeed(100);  // Motor 1 runs forward
  motor2->setSpeed(100);  // Motor 2 runs backward
  
  motor1->run(FORWARD);   // Motor 1 moves forward
  motor2->run(BACKWARD);  // Motor 2 moves backward
  delay(500);             // Turn left for 1 second (adjust as needed)

  // Stop motors after turning
  motor1->run(RELEASE);
  motor2->run(RELEASE);
}
