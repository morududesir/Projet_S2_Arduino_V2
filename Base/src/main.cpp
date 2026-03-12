#include "ctrlFFB.h"
const int FreqEchantillonnage = 100; // Fréquence d'échantillonnage en Hz
const float interval = 1.0 / FreqEchantillonnage;
unsigned long previousMillis = 0;

void setup() {


    Serial.begin(9600);


  homing();
  //setupMoteurCtrl();
  //setupAcquisition();
}

void loop() {

  if(millis() - previousMillis >= interval * 1000) {
    previousMillis = millis();
    FFB();
  }

}