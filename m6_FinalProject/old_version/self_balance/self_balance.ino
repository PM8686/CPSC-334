#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MotorShield.h>

// MPU6050 Pins
int SDA_pin = 22;
int SCL_pin = 21;

// Motor Shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

// MPU6050
Adafruit_MPU6050 mpu;

// PID variables
float kp = 20.0;  // Proportional gain
float ki = 0.0;   // Integral gain
float kd = 2.0;   // Derivative gain
float setPoint = 0; // Target angle (upright position)
float previousError = 0;
float integral = 0;

void setup() {
  Serial.begin(115200);

  // Initialize I2C and MPU6050
  Wire.begin(SDA_pin, SCL_pin); // only one wire.begin is allowed for I2C
  if (!mpu.begin()) {
    Serial.println("Failed to initialize MPU6050");
    while (1);
  }

  // Motor shield
  if (!AFMS.begin()) {
    Serial.println("Motor Shield not found");
    while (1);
  }

  leftMotor->setSpeed(0);
  leftMotor->run(RELEASE);
  rightMotor->setSpeed(0);
  rightMotor->run(RELEASE);

  Serial.println("Setup complete.");
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  // Calculate tilt angle from accelerometer and gyroscope
  float angle = atan2(accel.acceleration.x, accel.acceleration.z) * 180 / PI;

  // PID calculation
  float error = setPoint - angle;
  integral += error;
  float derivative = error - previousError;
  float output = kp * error + ki * integral + kd * derivative;

  previousError = error;

  // Adjust motor speeds based on PID output
  int motorSpeed = constrain(abs(output), 0, 255);
  if (output > 0) {
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
  } else {
    leftMotor->run(BACKWARD);
    rightMotor->run(BACKWARD);
  }

  leftMotor->setSpeed(motorSpeed);
  rightMotor->setSpeed(motorSpeed);

  // Debug output
  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print(" | Error: ");
  Serial.print(error);
  Serial.print(" | Output: ");
  Serial.println(output);

  delay(10);
}
