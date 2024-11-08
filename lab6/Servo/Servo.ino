#include <ESP32Servo.h>

Servo myServo;
int servoPin = 4;
int angle = 0;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(servoPin);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.write(0);
  delay(1000);
  Serial.println("hi");

  myServo.write(180);
  delay(1000);

}