

#include <Arduino.h>
#include "acquisition.h"
#include "traitement.h"

#include <U8g2lib.h>



void setup() {
  Serial.begin(9600);
  setupCapteurs();
}

void loop() {
  //capterEncodeurs();
  //traitement_acceleration();
  //capterJoy();
  //capterSwitch();
  
}

