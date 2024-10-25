// Photoresistor
int photoPin = 34;  // ADC-capable pin for the photoresistor
float avg_light = 0;

// Touch sensors
int touchPin1 = 2;   // Use GPIO 2 for the first capacitive touch (calming)
int touchPin2 = 15;  // Use GPIO 15 for the second capacitive touch (increasing)

// Piezo buzzer
const int buzzerPin = 17; 
int bpm = 70;       // Set initial BPM (beats per minute)

// Heartbeat variables
const int minBPM = 60;
const int maxBPM = 180;
int targetBPM = 70;
int calmEffect1 = 300;
int calmEffect2 = -300;
int change_calm = 5;

// Ultrasonic sensor (HC-SR04)
const int trigPin = 5;
const int echoPin = 16;
float duration, distance;

// Timing variables
unsigned long lastUpdate = 0;
unsigned long lightChangeTime = 0;
unsigned long distanceChangeTime = 0;
int previousPhotoValue = 0;
float previousDistance = 0.0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize sensors
  pinMode(photoPin, INPUT);         // Photoresistor
  pinMode(buzzerPin, OUTPUT);       // Piezo buzzer
  pinMode(trigPin, OUTPUT);         // Ultrasonic sensor trigger
  pinMode(echoPin, INPUT);          // Ultrasonic sensor echo

  // calibrate light sensor
  // 1. Read Photoresistor Value
  for (int i = 0; i < 5; i++) {
    avg_light += analogRead(photoPin);
    delay(100);
  }
  avg_light /= 5.0;

  // Add a slight delay for initialization
  delay(1000);
}

void loop() {
  // 1. Read Photoresistor Value
  int photoValue = analogRead(photoPin);  // Read analog value from photoresistor
  Serial.print("Photoresistor (GPIO 34) Value: ");
  Serial.println(photoValue);
  handlePhotoresistor(photoValue);

  // 2. Read Capacitive Touch Values
  int touchValue1 = touchRead(touchPin1);  // Read first touch sensor value
  int touchValue2 = touchRead(touchPin2);  // Read second touch sensor value
  Serial.print("Touch Sensor 1 (GPIO 2) Value: ");
  Serial.println(touchValue1);
  Serial.print("Touch Sensor 2 (GPIO 15) Value: ");
  Serial.println(touchValue2);
  handleTouchSensors(touchValue1, touchValue2);

  // 3. Read Ultrasonic Distance Sensor
  readUltrasonicSensor();

  Serial.print("BPM: ");
  Serial.println(bpm);

  // Separator for easier reading of sensor values
  Serial.println("-----------------------------");

  // Delay before the next loop iteration
  delay(500);
}

// Function to handle the photoresistor changes
void handlePhotoresistor(int photoValue) {
  // If there is a sudden change in light (e.g., from bright to dark or vice versa)
  if (abs(photoValue - previousPhotoValue) > 200) {
    bpm = constrain(bpm + 20, minBPM, maxBPM);  // Increase heart rate due to sudden change
    lightChangeTime = millis();  // Record the time of the change
    playScaredSound();  // Play "scared" sound when a large change in light occurs
  } else {
    // If light is consistent, gradually calm the heart rate over time, then stops impacting after 100s
    if (millis() - lightChangeTime > 5000 && millis() - lightChangeTime < 10000) {
      bpm = constrain(bpm - 1, minBPM, maxBPM);  // Slow decrease in heart rate
    }
    // If kept in the dark for too long, increase the heart rate
    if (photoValue < avg_light - 500 && millis() - lightChangeTime > 10000) {
      bpm = constrain(bpm + 1, minBPM, maxBPM);  // Slow increase if in the dark too long
    }
  }
  previousPhotoValue = photoValue;
}

// Function to handle the touch sensors
void handleTouchSensors(int touchValue1, int touchValue2) {
  // First touch sensor (calming effect initially, but harmful after prolonged use)
  if (touchValue1 < 40) {  // If touched
    calmEffect1 += change_calm;

    // First sensor initially decreases BPM, then increases after saturation
    bpm = constrain(bpm - calmEffect1 / 50, minBPM, maxBPM);

    // If calmEffect1 exceeds a certain threshold, reverse the effect
    if (calmEffect1 > 300) {
      change_calm = -50;  // Start making the sensor harmful, reducing the calming effect
    } else if (calmEffect1 < -300) {
      change_calm = 50;  // Start making the sensor calming again
    }
  } 

  // Second touch sensor (inverse behavior of the first sensor)
  if (touchValue2 < 40) {  // If touched
    calmEffect2 += change_calm * -1;  // Inverse of the first sensor's effect

    // Second sensor initially increases BPM, then decreases after saturation
    bpm = constrain(bpm - calmEffect2 / 50, minBPM, maxBPM);

    // If calmEffect2 exceeds a certain threshold, reverse the effect
    if (calmEffect2 > 300) {
      change_calm = 50;  // Start making the sensor calming
    } else if (calmEffect2 < -300) {
      change_calm = -50;  // Start making the sensor harmful again
    }
  } 
}

// Function to read the ultrasonic sensor
void readUltrasonicSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // Measure the time it takes for the pulse to return
  distance = (duration * 0.0343) / 2;  // Convert the time into distance
  Serial.print("Ultrasonic Sensor Distance (cm): ");
  Serial.println(distance);

  // Handle sudden changes in distance
  if (abs(distance - previousDistance) > 10) {
    bpm = constrain(bpm + 20, minBPM, maxBPM);  // Increase heart rate due to sudden change
    distanceChangeTime = millis();  // Record the time of the change
    playScaredSound();  // Play "scared" sound when a large change in distance occurs
  } else {
    // If distance is consistent, gradually calm the heart rate
    if (millis() - distanceChangeTime > 5000 && millis() - distanceChangeTime < 100000) { // after 5 seconds, before 100 seconds
      bpm = constrain(bpm - 1, minBPM, maxBPM);  // Slow decrease in heart rate
    }
    // If no object is detected for too long, increase the heart rate
    if (distance > 400 && millis() - distanceChangeTime > 100000) { // after 100 seconds of no one there
      bpm = constrain(bpm + 1, minBPM, maxBPM);  // Slow increase if nothing detected for too long
    }
  }
  previousDistance = distance;
}

// Function to play "scared" sound on the buzzer
void playScaredSound() {
  // Play a quick sequence of tones to simulate a "scared" sound
  tone(buzzerPin, 500, 200);  // High-pitched tone for 200 ms
  delay(300);
  tone(buzzerPin, 400, 200);  // Even higher-pitched tone
  delay(200);
  noTone(buzzerPin);  // Stop the buzzer after playing the sequence
}


// Function to play the heartbeat sound on the piezo buzzer
void playHeartbeat(int beatDuration) {
  // First pulse (lub)
  tone(buzzerPin, 500, beatDuration * 0.08);  // Lower, shorter tone
  delay(beatDuration * 0.1);  // Pause between lub and dub

  // Second pulse (dub)
  tone(buzzerPin, 400, beatDuration * 0.12);  // Lower, slightly longer tone
  delay(beatDuration * 0.2);  // Short pause after dub
}
