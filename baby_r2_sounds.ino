#include <IBusBM.h>

IBusBM IBus;

int currentVol = 30; // I belive 30 is max
int ledPIN = 9;

// Set channels. Channels are 0 indexed, so RC channel 1 is set to 0
int volumeChannel = 4; // VRA on FS-i6X
int threePosChannel = 8; // SWC on FS-i6X
int soundsOnChannel = 9; // SWD on FS-i6X

void setup() {
  IBus.begin(Serial1); 
  Serial.begin(9600);
}

void loop() {
  // Get volume and set if needed
  int newVol = GetVolume();

  if (currentVol != newVol) {
    currentVol = newVol;
    // Figure out how to send new vol to DF Mini Player
  }

  // If SDW is on, play random sound
  bool playSounds = ReadChannel(soundsOnChannel);
  if (playSounds) {
    Serial.println("Should play sounds");
  }
}

bool ReadChannel(int c) {
  int ChannelValue = IBus.readChannel(c);

  if (c == threePosChannel) {
    // Figure out 3 position switch. Off is 1000, middle is 1500, on is 2000
    if (ChannelValue == 1000) {
      return false;
    }
    return true;
  }
  return ChannelValue > 1990;
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
