int x_pin = 35;
int y_pin = 34;
int sw_pin = 5;
int button_pin = 4;
int switch_pin = 16;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  pinMode(sw_pin, INPUT_PULLUP); // config pin as input pin and enable the internal pull-up resistor
  pinMode(button_pin, INPUT_PULLUP); // config pin as input pin and enable the internal pull-up resistor
  pinMode(switch_pin, INPUT_PULLUP); // config pin as input pin and enable the internal pull-up resistor

  //set the resolution to 12 bits (0-4095)
  analogReadResolution(12);
}

void loop() {
  // read the pins:
  int analogValue_x = analogRead(x_pin);
  int analogValue_y = analogRead(y_pin);
  int sw = digitalRead(sw_pin);
  int button = digitalRead(button_pin);
  int sw1tch =digitalRead(switch_pin);

  // print out the values read:
  Serial.printf("ADC x = %d", analogValue_x);
  Serial.printf(" y = %d", analogValue_y);
  Serial.printf(" sw = %d", sw);
  Serial.printf(" button = %d", button);
  Serial.printf(" switch = %d\n", sw1tch);

  delay(100);  // delay in between reads for clear read from serial
}
