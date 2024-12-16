/*
 * Simple Braitenberg Vehicle with Buzzer Melodies
 * Focused on buzzer and melody functionality.
 */

#include <Arduino.h>
#include "pitches.h"
#include "melodies.h"

// Define the pin for the piezo buzzer
const int buzzer = 15;

// Define Braitenberg states
enum State {
  FEAR,
  AGGRESSION,
  LOVE,
  EXPLORE
};

// Initialize the current state
State currentState = LOVE;

// current note for melodies
int note = 0;
unsigned long noteStartTime = 0;

// Define the pin for the push button
const int buttonPin = 2;

void setup() {
  Serial.begin(115200);

  // Set button pin as input
  pinMode(buttonPin, INPUT_PULLUP);

  // Set buzzer pin as output
  pinMode(buzzer, OUTPUT);
}

void playMelody(int *melody, int *durations, int size) {
  if (note < size) {
    int duration = 1000 / durations[note];

    // Start playing the note if enough time has passed
    if (millis() - noteStartTime >= duration) {
      tone(buzzer, melody[note], duration);
      noteStartTime = millis();
      note++;
    }
  } else {
    note = 0; // Reset to the first note
  }
}

void Fear() {
  // Melody
  int tempo = 180;
  int notes = sizeof(melodyFear) / sizeof(melodyFear[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  if (note < notes * 2) {
    divider = melodyFear[note + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
    tone(buzzer, melodyFear[note], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
    note = note + 2;
  }
  else {
    note = 0;
  }
}

void Aggression() {
  //Melody
  if (note < sizeAggression) {
    int duration = 1000 / durationsAggression[note];
    tone(buzzer, melodyAggression[note], duration);
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzer);
    note++;
  }
  else {
    note = 0;
  }

  if (note < sizeAggression) {
    int duration = 1000 / durationsAggression[note];
    
    if (millis() - noteStartTime >= duration) {
      tone(buzzer, melodyAggression[note], duration);
      // noTone(buzzer);
      noteStartTime = millis();
      note++;
    }
  }
  else {
    note = 0;
  }
}

void Love() {
    //Melody
  int tempo = 244;
  int notes = sizeof(melodyLove) / sizeof(melodyLove[0]) / 2;
  int wholenote = (60000 * 4) / tempo;
  int divider = 0, noteDuration = 0;
  if (note < notes * 2) {
    divider = melodyLove[note + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
    tone(buzzer, melodyLove[note], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
    note = note + 2;
  }
  else {
    note = 0;
  }
}

void Explore() {
  //Melody
  if (note < sizeExplore) {
    int duration = 1000 / durationsExplore[note];
    tone(buzzer, melodyExplore[note], duration);
    int pauseBetweenNotes = duration * .90;
    delay(pauseBetweenNotes);
    noTone(buzzer);
    note++;
  }
  else {
    note = 0;
  }
}

void loop() {
  static bool lastButtonState = HIGH;
  static unsigned long lastDebounceTime = 0;
  const unsigned long debounceDelay = 50;

  // Read the button state
  int buttonState = digitalRead(buttonPin);

  // Debounce the button
  if ((millis() - lastDebounceTime) > debounceDelay && buttonState == LOW && lastButtonState == HIGH) {
    // Cycle to the next state on button press
    currentState = static_cast<State>((currentState + 1) % 4);
    note = 0; // Reset the note to restart the melody
    lastDebounceTime = millis();
  }

  lastButtonState = buttonState;

  // Continuously play the melody of the current state
  switch (currentState) {
    case FEAR:
      Fear();  // Fear melody repeats continuously
      Serial.println("State: FEAR");
      break;
    case AGGRESSION:
      Aggression();  // Aggression melody repeats continuously
      Serial.println("State: AGGRESSION");
      break;
    case LOVE:
      Love();  // Love melody repeats continuously
      Serial.println("State: LOVE");
      break;
    case EXPLORE:
      Explore();  // Explore melody repeats continuously
      Serial.println("State: EXPLORE");
      break;
  }
}

