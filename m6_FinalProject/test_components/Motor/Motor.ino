// Clockwise and counter-clockwise definitions
#define FORWARD  0
#define REVERSE  1

// Motor definitions
#define MOTOR_A  0
#define MOTOR_B  1

// Pin Assignments
#define DIRA 12  // Direction control for motor A
#define PWMA 18  // PWM control (speed) for motor A
#define DIRB 13  // Direction control for motor B
#define PWMB 19  // PWM control (speed) for motor B

// PWM settings
const int freq = 5000;        // PWM frequency (Hz)
const int resolution = 8;     // PWM resolution (bits)
const int pwmChannelA = 0;    // PWM channel for Motor A
const int pwmChannelB = 1;    // PWM channel for Motor B

void setup() {
  setupArdumoto(); // Set all pins as outputs
}

void loop() {
  // Drive motor A at various speeds, then stop
  driveArdumoto(MOTOR_A, REVERSE, 255);  // Set motor A to REVERSE at max speed
  delay(1000);
  driveArdumoto(MOTOR_A, FORWARD, 127); // Set motor A to FORWARD at half speed
  delay(1000);
  stopArdumoto(MOTOR_A);                // STOP motor A

  // Drive motor B at various speeds, then stop
  driveArdumoto(MOTOR_B, REVERSE, 255); // Set motor B to REVERSE at max speed
  delay(1000);
  driveArdumoto(MOTOR_B, FORWARD, 127); // Set motor B to FORWARD at half speed
  delay(1000);
  stopArdumoto(MOTOR_B);                // STOP motor B

  // Drive both motors forward and backward
  driveArdumoto(MOTOR_A, FORWARD, 255);
  driveArdumoto(MOTOR_B, FORWARD, 255);
  delay(1000);
  driveArdumoto(MOTOR_A, REVERSE, 127);
  driveArdumoto(MOTOR_B, REVERSE, 127);
  delay(1000);

  // Spin in place
  driveArdumoto(MOTOR_A, FORWARD, 255);
  driveArdumoto(MOTOR_B, REVERSE, 255);
  delay(2000);
  stopArdumoto(MOTOR_A);
  stopArdumoto(MOTOR_B);
}

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd) {
  if (motor == MOTOR_A) {
    digitalWrite(DIRA, dir);
    ledcWrite(pwmChannelA, spd);  // Set PWM duty cycle for Motor A
  } else if (motor == MOTOR_B) {
    digitalWrite(DIRB, dir);
    ledcWrite(pwmChannelB, spd);  // Set PWM duty cycle for Motor B
  }
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor) {
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initializes all pins
void setupArdumoto() {
  // Set direction pins as outputs
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Attach PWM channels to pins
  ledcSetup(pwmChannelA, freq, resolution);
  ledcAttachPin(PWMA, pwmChannelA);

  ledcSetup(pwmChannelB, freq, resolution);
  ledcAttachPin(PWMB, pwmChannelB);

  // Initialize all pins as low
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  ledcWrite(pwmChannelA, 0);
  ledcWrite(pwmChannelB, 0);
}
