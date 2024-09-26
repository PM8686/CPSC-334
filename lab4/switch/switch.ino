int switch_pin = 4;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  pinMode(switch_pin, INPUT_PULLUP); // config pin as input pin and enable the internal pull-up resistor
}

void loop() {
  // read the pin:
  int switch_val = digitalRead(switch_pin);

  // print out the values read:
  Serial.printf(" switch = %d\n", switch_val);

  delay(100);  // delay in between reads for clear read from serial
}

