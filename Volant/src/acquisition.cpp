//Fichier CPP pour les fonctions d'acquisition de donnée

#include "acquisition.h"

Encoder EncodeurGauche(PIN_ENCODEUR1A,PIN_ENCODEUR1B);
Encoder EncodeurDroite(PIN_ENCODEUR2A,PIN_ENCODEUR2B);

//Fonction pour init les pins pour les capteurs
void setupCapteurs()
{
    //Init Pins Encodeurs volants
    pinMode(PIN_ENCODEUR1A,INPUT);
    pinMode(PIN_ENCODEUR1B,INPUT);
    pinMode(PIN_ENCODEUR2A,INPUT);
    pinMode(PIN_ENCODEUR2B,INPUT);

    //Init Pins Potentiomètre Joystick
    pinMode(PIN_JOYSTICKX,INPUT);
    pinMode(PIN_JOYSTICKY,INPUT);

    //Init Pins Accéléromètre (Peut-être à enlever)
    pinMode(PIN_ACCELEROX,INPUT);
    pinMode(PIN_ACCELEROY,INPUT);
    pinMode(PIN_ACCELEROZ,INPUT);

    //Init Pins Switches
    pinMode(SWITCH_1,INPUT_PULLUP);
    pinMode(SWITCH_2,INPUT_PULLUP);
    pinMode(SWITCH_3,INPUT_PULLUP);
    pinMode(SWITCH_4,INPUT_PULLUP);
}

//Fonction pour lire les accélérations des axes XYZ
Acceleration capterAccel()
{
    Acceleration accel;
    accel.x = analogRead(PIN_ACCELEROX) * 5 / 1023.0;
    accel.y = analogRead(PIN_ACCELEROY) * 5 / 1023.0;
    accel.z = analogRead(PIN_ACCELEROZ) * 5 / 1023.0;
    return accel;
}

Encodeur capterEncodeurs() {

    Encodeur encode;
    encode.valeurGauche = EncodeurGauche.read();
    encode.valeurDroite = EncodeurDroite.read();
    return encode;
}

Joystick capterJoy()
{
    Joystick joy;
    joy.x = analogRead(PIN_JOYSTICKX);
    joy.y = analogRead(PIN_JOYSTICKY);
    return joy;
}

Bouton capterSwitch()
{
    Bouton bouton;
    bouton.switch1 = !(digitalRead(SWITCH_1));
    bouton.switch2 = !(digitalRead(SWITCH_2));
    bouton.switch3 = !(digitalRead(SWITCH_3));
    bouton.switch4 = !(digitalRead(SWITCH_4));
    return bouton;
}

    