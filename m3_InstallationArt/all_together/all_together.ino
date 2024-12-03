// Photoresistor
int photoPin = 34;  // ADC-capable pin for the photoresistor

// Touch sensor
int touchPin = 2;   // Use GPIO 2 for capacitive touch

// Piezo buzzer
const int buzzerPin = 17; 
int bpm = 70;       // Set your desired BPM (beats per minute)

// Ultrasonic sensor (HC-SR04)
const int trigPin = 5;
const int echoPin = 16;
float duration, distance;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize sensors
  pinMode(photoPin, INPUT);         // Photoresistor
  pinMode(buzzerPin, OUTPUT);       // Piezo buzzer
  pinMode(trigPin, OUTPUT);         // Ultrasonic sensor trigger
  pinMode(echoPin, INPUT);          // Ultrasonic sensor echo

  // Add a slight delay for initialization
  delay(1000);
}

void loop() {
  // 1. Read Photoresistor Value
  int photoValue = analogRead(photoPin);  // Read analog value from photoresistor
  Serial.print("Photoresistor (GPIO 34) Value: ");
  Serial.println(photoValue);

  // 2. Read Capacitive Touch Value
  int touchValue = touchRead(touchPin);  // Read touch sensor value
  Serial.print("Touch Sensor (GPIO 2) Value: ");
  Serial.println(touchValue);

  // 3. Play Heartbeat on Piezo Buzzer
  int beatDuration = 60000 / bpm;  // Calculate duration for one beat in milliseconds
  playHeartbeat(beatDuration);

  // 4. Read Ultrasonic Distance Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);  // Measure the time it takes for the pulse to return
  distance = (duration * 0.0343) / 2;  // Convert the time into distance
  Serial.print("Ultrasonic Sensor Distance (cm): ");
  Serial.println(distance);

  // Separator for easier reading of sensor values
  Serial.println("-----------------------------");

  // Delay before the next loop iteration
  delay(1000);
}

// Function to play the heartbeat sound on the piezo buzzer
void playHeartbeat(int beatDuration) {
  // First pulse (lub)
  // tone(buzzerPin, 500, beatDuration * 0.08);  // Lower, shorter tone
  delay(beatDuration * 0.1);  // Pause between lub and dub

  // Second pulse (dub)
  // tone(buzzerPin, 400, beatDuration * 0.12);  // Lower, slightly longer tone
  delay(beatDuration * 0.2);  // Short pause after dub
}
