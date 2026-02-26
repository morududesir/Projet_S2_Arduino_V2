#include <Arduino.h>
#include "moteurCtrl.h"
#include "acquisition.h"

const float gainLinéaire = 0.04; // Ajustez ce gain pour la partie linéaire
const float gainExponentiel = 0.00; // Ajustez ce gain pour la partie Exponentielle

int rpm = 0;
int erreur = 0;
int target = 0;
int centre = 0; // Position centrale de l'encodeur

void setup() {
  // put your setup code here, to run once:
  setSpeed(0);
}

void loop() {
  AcquisitionData data = getValues();

  erreur = data.encoderPos - centre;
  rpm = (erreur * gainLinéaire) + (erreur * erreur * gainExponentiel);
}

