#include <IBusBM.h>
#include "AltSoftSerial.h"
#include "DFRobotDFPlayerMini.h"

int currentVol = 15; // Set initial volume value. From 0 to 30

// Set channels. Channels are 0 indexed, so RC channel 1 is set to 0
int volumeChannel = 4; // VRA on FS-i6X
int randomSoundsChannel = 6; // SWA on FS-i6X
int randomScreamsChannel = 7; // SWB on FS-i6X
int leiaChannel = 8; // SWC on FS-i6X
int randomMusicChannel = 9; // SWD on FS-i6X
long randDelay;
long randomSound;
long randomScream;
long randomSong;
unsigned long previousMillis = 0; // will store last time a file stopped playing
long soundInterval = 0;

bool debugDfMiniPlayer = false;
bool debugTransmitter = false; // Set serial monitor to 115200
int lastVolume = 0;
int lastRandomSoundValue = 0;
int lastRandomScreamsValue = 0;
int lastLeiaValue = 0;
int lastRandomMusicValue = 0;

IBusBM IBus;
AltSoftSerial softwareSerial; // Will use pins 8 & 9
DFRobotDFPlayerMini mp3Player;

void setup() {
  softwareSerial.begin(9600);

  if (debugDfMiniPlayer) {
    IBus.begin(Serial);

    Serial.println(F("DFRobot DFPlayer Mini Demo"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!mp3Player.begin(softwareSerial)) {
      Serial.println(F("Unable to begin:"));
      Serial.println(F("1.Please recheck the connection!"));
      Serial.println(F("2.Please insert the SD card!"));
      while(true);
    }
    Serial.println(F("DFPlayer Mini online."));
  } else if (debugTransmitter) {
    IBus.begin(Serial);
    Serial.println("Started iBus");
  } else {
    if (!mp3Player.begin(softwareSerial)) {
      while(true);
    }
    IBus.begin(Serial);
    mp3Player.volume(currentVol);
    mp3Player.play(1);
    randomSeed(analogRead(0));
    delay(3000); // Let's boot sound play and iBus initialize
  }
}

void loop() {
  if (!debugTransmitter) {
    unsigned long currentMillis = millis();

    // Get volume and set if needed
    int newVol = currentVol;
    if (!debugDfMiniPlayer) {
      newVol = GetVolume();
    }

    if (currentVol != newVol) {
      currentVol = newVol;
      mp3Player.volume(currentVol);
    }

    // If all switches are off set soundInterval back to 0
    // This makes the next switch immediatly play a sound when flipped to the on position
    if (AllSwitchesOff()) {
      soundInterval = 0;    
    }

    // Check to see if the MP3 is still playing
    // If so, skip all of this
    bool mp3Playing = mp3Player.readState();
    if (!mp3Playing) {
      // If SWA is on, play random sound
      bool playRandomSounds;
      if (debugDfMiniPlayer) {
        playRandomSounds = true;
      } else {
        playRandomSounds = ReadChannel(randomSoundsChannel);
      }

      if (playRandomSounds && RandomTimePassed(currentMillis, previousMillis)) {
        // Play random sound
        randomSound = random(1, 52);
        mp3Player.play(randomSound);
        previousMillis = currentMillis;
      }

      // If SWB is on, play random scream
      bool playRandomScream = ReadChannel(randomScreamsChannel);
      if (playRandomScream && RandomTimePassed(currentMillis, previousMillis)) {
        randomScream = random(52, 55);
        mp3Player.play(randomScream);
        previousMillis = currentMillis;
      }

      // If SWC is on, play random Leia's message
      bool playLeiaMessage = ReadChannel(leiaChannel);
      if (playLeiaMessage) {
        mp3Player.play(55);
      }

      // If SWD is on, play random song
      bool playRandomSong = ReadChannel(randomMusicChannel);
      if (playRandomSong && RandomTimePassed(currentMillis, previousMillis)) {
        randomSong = random(58, 77);
        mp3Player.play(randomSong);
        previousMillis = currentMillis;
      } 
    }   

    // Get mp3 player status
    // if (mp3Player.available()) {
    //   printDetail(mp3Player.readType(), mp3Player.read()); //Print the detail message from DFPlayer to handle different errors and states.
    // }
  }

  if (debugTransmitter) {
    runRcDebugger();
  }
}

bool AllSwitchesOff() {
  bool swa = ReadChannel(randomSoundsChannel);
  bool swb = ReadChannel(randomScreamsChannel);
  bool swc = ReadChannel(leiaChannel);
  bool swd = ReadChannel(randomMusicChannel);

  return !swa || !swb || !swc || !swd;
}

bool ReadChannel(int c) {
  int ChannelValue = IBus.readChannel(c);

  if (c == leiaChannel) {
    // Figure out 3 position switch. Off is 1000, middle is 1500, on is 2000
    if (ChannelValue < 1500) {
      return false;
    }
    return true;
  }
  return ChannelValue > 1990;
}

bool RandomTimePassed(long currentMillis, long previousMillis) {

  bool well = currentMillis - previousMillis >= (soundInterval * 1000);
  if (well) {
    // Serial.println(soundInterval);
    soundInterval = random(5, 12);
  }
  return currentMillis - previousMillis >= (soundInterval * 1000);
}

// This will convert the controller range to the volume range. In this instance the volume is 0-30. 
int GetVolume() {
  int value = IBus.readChannel(volumeChannel);
  int max = 30, min = 0; // the volume max and  min.
  int oldRange = 2000 - 1000;
  int newRange = max - min;
  int newValue = ((value - 1000) * newRange / oldRange) + min;
 
  return newValue;
}

void runRcDebugger() {
  // Volume
  int volumeValue = IBus.readChannel(volumeChannel);

  if (lastVolume != volumeValue) {
      Serial.print("Volume Channel Value: ");
      Serial.println(volumeValue);
      lastVolume = volumeValue;
  }

  // Random Sounds
  int randomSoundsValue = IBus.readChannel(randomSoundsChannel);
  if (lastRandomSoundValue != randomSoundsValue) {
      Serial.print("Random Sound Channel Value: ");
      Serial.println(randomSoundsValue);
      lastRandomSoundValue = randomSoundsValue;
  }

  // Random Screams
  int randomScreamsValue = IBus.readChannel(randomScreamsChannel);
  if (lastRandomScreamsValue != randomScreamsValue) {
      Serial.print("Random Scream Channel Value: ");
      Serial.println(randomScreamsValue);
      lastRandomScreamsValue = randomScreamsValue;
  }

  // Leia
  int leiaValue = IBus.readChannel(leiaChannel);
  if (lastLeiaValue != leiaValue) {
      Serial.print("Leia Channel Value: ");
      Serial.println(leiaValue);
      lastLeiaValue = leiaValue;
  }

  // Random Music
  int randomMusicChannelValue = IBus.readChannel(randomMusicChannel);
  if (lastRandomMusicValue != randomMusicChannelValue) {
      Serial.print("Random Music Channel Value: ");
      Serial.println(randomMusicChannelValue);
      lastRandomMusicValue = randomMusicChannelValue;
  }
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
