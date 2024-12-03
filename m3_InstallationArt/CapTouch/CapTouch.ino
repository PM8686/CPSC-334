// Array of GPIO numbers corresponding to touch-capable pins on the ESP32
int touchPins[] = {4, 0, 2, 15, 13, 12, 14, 27, 33, 32};

void setup() {
  Serial.begin(115200);  // Start serial communication
  delay(1000);  // Give some time for initialization
}

void loop() {
  // Iterate over each touch-capable GPIO pin and read its value
  for (int i = 0; i < 10; i++) {
    int touchValue = touchRead(touchPins[i]);  // Read the touch value from GPIO pin
    Serial.print("Touch on GPIO ");
    Serial.print(touchPins[i]);
    Serial.print(": ");
    Serial.println(touchValue);  // Print the raw touch sensor value
  }
  
  Serial.println("----------");  // Separator between readings
  delay(1000);  // Wait 1 second before reading again
}
