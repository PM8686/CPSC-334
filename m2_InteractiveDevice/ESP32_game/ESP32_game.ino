int x_pin = 35;
int y_pin = 34;
int sw_pin = 5;
int button_pin = 4;
int switch_pin = 16;

void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // Configure the pins as input and enable the internal pull-up resistor for buttons and switches
  pinMode(sw_pin, INPUT_PULLUP);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(switch_pin, INPUT_PULLUP);

  // Set the ADC resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  // Read the analog joystick values:
  int joy_x = analogRead(x_pin);
  int joy_y = analogRead(y_pin);

  // Read the digital button states:
  int joy_sw = digitalRead(sw_pin);
  int button = digitalRead(button_pin);
  int sw1tch = digitalRead(switch_pin);

  // Send the values via serial communication
  Serial.printf("%d %d %d %d %d\n", joy_x, joy_y, joy_sw, button, sw1tch);

  delay(50);  // Small delay for clear reading
}
