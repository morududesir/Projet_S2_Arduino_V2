//Fichier d'entête pour le communication entre l'Arduino et le PC

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <ArduinoJson.h>
#include "ctrlFFB.h"

void sendData(AcquisitionData data);

extern int minBrake;
extern int maxBrake;

extern int minGas;
extern int maxGas;

#endif 