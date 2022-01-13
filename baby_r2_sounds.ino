#include <IBusBM.h>

IBusBM IBus;
int LEDPIN = 9;

void setup() {
 IBus.begin(Serial); 
// Serial.begin(115200);
 pinMode(LEDPIN, OUTPUT);
}

void loop() {
  int val;
  val = IBus.readChannel(9);

  if (val > 1990) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }

//  Serial.print(val);
}
