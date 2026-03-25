//Fichier d'entête pour le contrôle du force feedback du volant

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include <ArduinoJson.h>
#include "acquisition.h"

// communication.h
struct GameData {
    float rpm = 0;
    float maxRpm = 0;
    int gear = 0;
    float fuel = 0;
    float tireWear = 0;
    float speed = 0;
    bool inPit = false;
};

void sendData(Encodeur encode, Acceleration accel, int joy, Bouton bouton);

GameData receiveData();

#endif 