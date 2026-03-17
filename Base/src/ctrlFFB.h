//Fichier d'entête pour le contrôle du force feedback du volant

#ifndef CTRLFFB_H
#define CTRLFFB_H
#include "acquisition.h"
#include "moteurCtrl.h"

const int pinZ = 4; // Pin de la phase Z
const int zOffset = 0; // Offset pour la position Z
const float gainLineaire = 0.0002; // Ajustez ce gain pour la partie linéaire
const float gainExponentiel = 0.000; // Ajustez ce gain pour la partie Exponentielle
const int homingSpeed = 10; // Vitesse de homing, ajustez selon vos besoins
const int capSpeed = 50; // Vitesse maximale du moteur
extern int target; // Position cible pour le homing (définition dans ctrlFFB.cpp)
const float deltaT = 0.01; //Intervalle de temps en s pour le calcul de la vitesse
const float gainD = 0.007; // Gain pour la composante dérivative

void homing();
AcquisitionData FFB();


#endif 