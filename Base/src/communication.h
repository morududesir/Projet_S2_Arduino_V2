//Fichier d'entête pour le contrôle du force feedback du volant

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <ArduinoJson.h>
#include "ctrlFFB.h"

//void sendData(AcquisitionData data);

int minBrake = 0;
int maxBrake = 1023;

int minGas = 0;
int maxGas = 1023;

#endif 