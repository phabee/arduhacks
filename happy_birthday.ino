int speakerPin = 9;
int length = 29; // the number of notes
char notes[] = "GGAGcBGGAGdcGGxeccBAyyecdc ";

// calculate durations for each tone: subtract one beat for each pause between every two tones
// 10-1 = 1/16, 20-1 = 1/8, 30-1 = 3/16 = 1/8 *, 40-1=1/4, 80-1=1/2
int beats[] = { 29, 9, 39, 39, 39, 79, 29, 9, 39, 39,
                39, 79, 29, 9, 39, 39, 29, 9, 39, 39, 
                29, 9, 39, 39, 39, 79, 159};

int tempo = 60;
bool played = false;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }

}

void playNote(char note, int duration) {
  char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',
                  'c', 'd', 'e', 'f', 'g', 'a', 'b',
                  'x', 'y'
                 };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,
                  956,  834,  765,  593,  468,  346,  224,
                  635 , 715
                };
  int SPEE = 5;

  // play the tone corresponding to the note name
  for (int i = 0; i < 17; i++) {
    if (names[i] == note) {
      int newduration = duration / SPEE;
      playTone(tones[i], newduration);
    }
  }
}

void playMelody() {
    for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }
    // pause between notes
    delay(tempo);
  }
}

void setup() {
  played = false;
  pinMode(speakerPin, OUTPUT);
}


void loop() {
    // play melody only once, require reset-button to replay
    if (!played) {
      playMelody();
      played = true;      
    }
}
