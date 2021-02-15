#include "pitches.h" //speaker relevant

const int sensorPin = 0; //pin A0 == analog pin 0
const int ledPin = 9; 
const int buttonOne = 10;
const int buttonTwo = 11;
const int buttonThree = 12;

int lightLevel, low = 0, high = 1023;
int buttonState = 0;
int state;
int timeLeft;
int lightLevelLED = 0;

long timeStarted;

// notes in the melody:
int good_melody[] = {

  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int bad_melody[] = {

  NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};

void setup()
{
  //Setting pin 9 as the output
  pinMode(ledPin, OUTPUT);
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(buttonThree, INPUT);
  Serial.begin(9600);
}



void loop()
{
  buttonState = digitalRead(buttonOne);
  Serial.println("Time Left: ");
  Serial.println(timeLeft);
  lightLevel = analogRead(sensorPin);
//  Serial.println("Light Level: ");
//  Serial.println(lightLevel);
  Serial.print("State: ");
  Serial.println(state);
  if(state == 0) {
    if(digitalRead(buttonOne) && timeLeft < 5) {
      timeLeft += 1;
      lightLevelLED += (255/5);
      analogWrite(ledPin, lightLevelLED);
      delay(1000);
    }
    
    if(digitalRead(buttonTwo) && timeLeft >= 1) {
      timeLeft -= 1;
      lightLevelLED -= (255/5);
      analogWrite(ledPin, lightLevelLED);
      delay(1000);
    }
    
    if(digitalRead(buttonThree)) {
      lightLevelLED = 0;
      analogWrite(ledPin, lightLevelLED);
      while(lightLevel > 1){}
      state = 1;
      timeStarted = millis();
    }   
  }
  else if(state == 1) {
    /* Code for led light that indicates how much time is left */
    lightLevel = analogRead(sensorPin);
    
    if(millis() > timeLeft*60000 + timeStarted) {
      state = 3;
    }

    else if(lightLevel > 10) {
    state = 2;
    }

  }
  else if(state == 2) {
    /* code for making speakers bad noises*/
    lightLevel = analogRead(sensorPin);
    Serial.println("bad music");
    playMelody(bad_melody);
    if(lightLevel < 10) {
    state = 1;
    }

  }
  else if(state == 3) {
    /* code for making speakers play nice sounds*/
    Serial.println("nice music");
    playMelody(good_melody);
    state = 0;
    timeLeft = 0;

  }
  


}

void playMelody(int melody[]){
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(8);
    }
  
}

//void autoTune()
//{
//  for (int thisNote = 0; thisNote < 8; thisNote++) {
//
//    // to calculate the note duration, take one second divided by the note type.
//
//    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//
//    int noteDuration = 1000 / noteDurations[thisNote];
//
//    if (lightLevel > low)
//  //so far, I added this conditon so that diode turns on and speaker turns on, I added this if conditon within the while loop of the speaker
//  //to hopefully excecute the sound part only when the if condition is satisfied
//    {
//      high = lightLevel;
//  
//    lightLevel = map(lightLevel, low+30, high-30, 0, 255);
//    lightLevel = constrain(lightLevel, 0, 255);
//      tone(8, melody[thisNote], noteDuration);
//  
//      // to distinguish the notes, set a minimum time between them.
//  
//      // the note's duration + 30% seems to work well:
//  
//      int pauseBetweenNotes = noteDuration * 1.30;
//  
//      delay(pauseBetweenNotes);
//  
//      // stop the tone playing:
//  
//      noTone(8);
//    }
//  }
//}  

  //manualTune();  // manually change the range from light to dark

  //autoTune();  // have the Arduino do the work for us!


  //analogWrite(ledPin, lightLevel);
  //Serial.println(lightLevel);
  

// void tuneLightThingy()
//{
//
////  if (lightLevel < low)
////  {
////    low = lightLevel;
////  }
//
//
// // if (lightLevel > high)
//  //{
//   // high = lightLevel;
//
//  //lightLevel = map(lightLevel, low+30, high-30, 0, 255);
//  //lightLevel = constrain(lightLevel, 0, 255);
//  //}
//}
