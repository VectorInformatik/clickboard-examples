#include <Arduino.h>

#include "lib/CANCommunication.h"

long currentMillis = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);
  setupCANCommunication();
}

void loop() {
  currentMillis = millis();
  loopCANCommunication(currentMillis);

  // replace ths contents of the following if statement
  // with your incoming coordinates update functionality
  if (packetWaiting) {
    w_c1.x = r_c1.x + 1;
    w_c1.y = r_c1.y + 1;
    w_c1.z = r_c1.z + 1;
    w_c2.x = r_c2.x + 1;
    w_c2.y = r_c2.y + 1;
    w_c2.z = r_c2.z + 1;
    packetWaiting = false;
    Serial.println("Processed received message!");
  }

  // put your code to update the outgoing coordinates
  // here
}
