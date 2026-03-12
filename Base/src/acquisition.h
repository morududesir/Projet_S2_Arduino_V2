//Fichier d'entête pour les fonctions d'acquisition de données pour les capteurs du volant

#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <Arduino.h>

struct AcquisitionData {
    int32_t encoderPos;
    int pot1Value;
    int pot2Value;
};

const int resEncoder = 1440; // Résolution de l'encodeur (ticks par tour)

int getPosition();
void setupAcquisition();
AcquisitionData getValues();

#endif 