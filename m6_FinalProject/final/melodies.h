
// Fear Melody
// pink panther theme: https://github.com/robsoncouto/arduino-songs/blob/master/pinkpanther/pinkpanther.ino
int melodyFear[] = {
  REST,4, REST,8, NOTE_DS4,8, 
  NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
  NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,   
  
  NOTE_AS4,-1, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, 
  NOTE_E4,-4, REST,4,
  REST,4, NOTE_E5,-8, NOTE_D5,8, NOTE_B4,-8, NOTE_A4,8, NOTE_G4,-8, NOTE_E4,-8,
  NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8, NOTE_AS4,16, NOTE_A4,-8,   
  NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, NOTE_E4,16, NOTE_E4,16, NOTE_E4,2 
};

// Aggression Melody
// star wars from: https://github.com/hibit-dev/buzzer/blob/master/src/movies/star_wars/star_wars.ino
int melodyAggression[] = {
  NOTE_AS4, NOTE_AS4, NOTE_AS4,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_F5, NOTE_C6,
  NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6
};

int durationsAggression[] = {
  8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 4,
  8, 8, 8, 2, 8, 8, 8,
  2, 2,
  8, 8, 8, 2, 4
};

int sizeAggression = sizeof(durationsAggression) / sizeof(int);

//Love Melody
// keyboard cat: https://github.com/robsoncouto/arduino-songs/blob/master/keyboardcat/keyboardcat.ino
int melodyLove[] = {
  NOTE_C4,4, NOTE_E4,4, NOTE_G4,4, NOTE_E4,4, 
  NOTE_C4,4, NOTE_E4,8, NOTE_G4,-4, NOTE_E4,4,
  NOTE_A3,4, NOTE_C4,4, NOTE_E4,4, NOTE_C4,4,
  NOTE_A3,4, NOTE_C4,8, NOTE_E4,-4, NOTE_C4,4,
  NOTE_G3,4, NOTE_B3,4, NOTE_D4,4, NOTE_B3,4,
  NOTE_G3,4, NOTE_B3,8, NOTE_D4,-4, NOTE_B3,4,

  NOTE_G3,4, NOTE_G3,8, NOTE_G3,-4, NOTE_G3,8, NOTE_G3,4, 
  NOTE_G3,4, NOTE_G3,4, NOTE_G3,8, NOTE_G3,2
};


//Explore Melody
// super mario bros: https://github.com/hibit-dev/buzzer/blob/master/src/games/mario_bros/mario_bros.ino
int melodyExplore[] = {

  NOTE_C5, NOTE_G4, REST, NOTE_E4,
  NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5,
  REST, NOTE_E5,NOTE_C5, NOTE_D5, NOTE_B4,
  
  REST, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_DS5, NOTE_E5,
  REST, NOTE_GS4, NOTE_A4, NOTE_C4, REST, NOTE_A4, NOTE_C5, NOTE_D5,
  REST, NOTE_DS5, REST, NOTE_D5,
  NOTE_C5, REST
};

int durationsExplore[] = {
  4, 8, 4, 4,
  4, 4, 8, 4,
  8, 8, 8, 4, 8, 8,
  8, 4, 8, 8, 4,
  
  4, 8, 8, 8, 4, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  4, 4, 8, 4,
  2, 2
};

int sizeExplore = sizeof(durationsExplore) / sizeof(int);
