//Fichier d'entête pour le contrôle du force feedback du volant

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <ArduinoJson.h>
#include "acquisition.h"

void sendData(Encodeur encode, Acceleration accel, Joystick joy, Bouton bouton);

#endif 