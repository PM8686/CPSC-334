int photoPin = 34;  // Use an ADC-capable pin like GPIO 34
void setup() {
    Serial.begin(9600);
    pinMode(photoPin, INPUT);
}

void loop() {
    int value = analogRead(photoPin);  // Read the analog value from the photoresistor

    Serial.print("Analog Value: ");
    Serial.println(value);
    
    delay(500);
}
