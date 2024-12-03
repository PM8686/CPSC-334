int button_pin = 4;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  pinMode(button_pin, INPUT_PULLUP); // config pin as input pin and enable the internal pull-up resistor
}

void loop() {
  // read the pin:
  int button_val = digitalRead(button_pin);

  // print out the values read:
  Serial.printf(" button = %d\n", button_val);

  delay(100);  // delay in between reads for clear read from serial
}
