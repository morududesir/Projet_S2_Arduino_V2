//Fichier d'entête pour les fonctions d'acquisition de données pour les capteurs du volant

#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <Arduino.h>
#include <Encoder.h>

//Structure pour les valeurs de retour d'accélération
struct Acceleration {
    float x;
    float y;
    float z;
};

struct Encodeur {
    long valeurGauche;
    long valeurDroite;
};

//Structure pour les valeurs de joysticks
struct Joystick {
    float x;
    float y;
};

struct Bouton {
    bool switch1;
    bool switch2;
    bool switch3;
    bool switch4;
    bool paddleshiftup;
    bool paddleshiftdown;
};


//Pins Encodeur
// acquisition.h
const int PIN_ENCODEUR_DROIT_A = 2; 
const int PIN_ENCODEUR_DROIT_B = 3; 
const int PIN_ENCODEUR_GAUCHE_A = 18;   
const int PIN_ENCODEUR_GAUCHE_B = 19;    

//Pins Joystick
const int PIN_JOYSTICKX = A3;
const int PIN_JOYSTICKY = A4;

//Pins Accéléromètre
const int PIN_ACCELEROX = A0;
const int PIN_ACCELEROY = A1;
const int PIN_ACCELEROZ = A2;

//Pins DELs
const int PIN_DEL1 = 4;
const int PIN_DEL2 = 5;

//Pins Switch
const int SWITCH_1 = 9;
const int SWITCH_2 = 8;
const int SWITCH_3 = 7;
const int SWITCH_4 = 6;

//Pins Paddles
const int PADDLE_UP = 43; 
const int PADDLE_DOWN = 45;

const int joy_deadzone = 50;
const int joy_mid = 512;

//Fonction Init Pins
void setupCapteurs();

//Fonction pour capter les valeurs d'accélération XYZ
Acceleration capterAccel();

//Fonction pour lire les encodeurs
Encodeur capterEncodeurs();

//Fonction pour acquisitionner les valeurs de joysticks
Joystick capterJoy();

Bouton capterSwitch();

uint8_t traitementJoystick();

#endif 