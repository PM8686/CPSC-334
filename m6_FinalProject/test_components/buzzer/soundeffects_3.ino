#include <Arduino.h>
#include "pitches.h"

// change this to make the song slower or faster
int tempo = 85;

// change this to whichever pin you want to use
int buzzer = 15;

// notes of the melody followed by the duration.
// change this to make the song slower or faster
int tempo = 85;

// change this to whichever pin you want to use
int buzzer = 15;

// notes of the melody followed by the duration.
// a 4 means a quarter note, 8 an eighth, 16 sixteenth, and so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighth!!
int melody[] = {
  // Jigglypuff's Song
  // Score available at https://musescore.com/user/28109683/scores/5044153
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1,
};

// calculate the number of notes in the melody
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// calculate the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setup() {
  // Set the buzzer pin as output
  pinMode(buzzer, OUTPUT);

  // iterate over the notes of the melody
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increase duration by 50%
    }

    // play the note
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // wait for the note's duration plus a short pause
    delay(noteDuration);
    noTone(buzzer);
  }
}

void loop() {
  // no need to repeat in loop
}
