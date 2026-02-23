//Fichier d'entête pour les fonctions d'acquisition de données pour les capteurs du volant

#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include "acquisition.h"

enum Direction {NEUTRE = 0, GAUCHE = 1, DROITE = 2};

const int joy_deadzone = 50;
const int joy_mid = 512;

const float V_0g = 1.5; // 0g +/- 0.15V

struct DirectionAccel {
    float valeursAccel[3];
    Direction direction;
    
};

uint8_t traitementJoystick();
DirectionAccel traitement_acceleration();




#endif