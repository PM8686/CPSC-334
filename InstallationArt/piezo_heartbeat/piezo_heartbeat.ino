// Pin connected to the piezo buzzer
const int buzzerPin = 16; 

// Set your desired BPM (beats per minute)
int bpm = 70; 

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Calculate the duration for one beat in milliseconds
  int beatDuration = 60000 / bpm;

  // Heartbeat sound (lub-dub)
  playHeartbeat(beatDuration);

  // Wait for the remaining time until the next heartbeat
  delay(beatDuration * 0.7); // Adjust the pause between beats
}

void playHeartbeat(int beatDuration) {
  // First pulse (lub)
  tone(buzzerPin, 500, beatDuration * 0.08); // Lower, shorter tone
  delay(beatDuration * 0.1); // Pause between lub and dub

  // Second pulse (dub)
  tone(buzzerPin, 400, beatDuration * 0.12); // Lower, slightly longer tone
  delay(beatDuration * 0.2); // Short pause after dub
}
