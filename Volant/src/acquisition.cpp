//Fichier CPP pour les fonctions d'acquisition de donnée

#include "acquisition.h"
#include "string.h"

Encoder EncodeurDroite(PIN_ENCODEUR1A,PIN_ENCODEUR1B);
Encoder EncodeurGauche(PIN_ENCODEUR2A,PIN_ENCODEUR2B);

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

    //Init Pins Potentiomètre Joystick
    pinMode(PADDLE_UP,INPUT_PULLUP);
    pinMode(PADDLE_DOWN,INPUT_PULLUP);

    //Init Pins Accéléromètre (Peut-être à enlever)
    pinMode(PIN_ACCELEROX,INPUT);
    pinMode(PIN_ACCELEROY,INPUT);
    pinMode(PIN_ACCELEROZ,INPUT);

    //Init Pins Switches
    pinMode(SWITCH_1,INPUT);
    pinMode(SWITCH_2,INPUT);
    pinMode(SWITCH_3,INPUT);
    pinMode(SWITCH_4,INPUT);
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

//Marche à moitié
Encodeur capterEncodeurs() {
    Encodeur encode;
    encode.valeurGauche = EncodeurGauche.read();
    Serial.print(encode.valeurGauche);
    encode.valeurDroite = EncodeurDroite.read();
    Serial.print(encode.valeurDroite);
    return encode;
}

//Devrait marcher correctement
Joystick capterJoy()
{
    Joystick joy;
    joy.x = analogRead(PIN_JOYSTICKX);
    Serial.print("X : ");
    Serial.print(joy.x);
    joy.y = analogRead(PIN_JOYSTICKY);
    Serial.print("Y : ");
    Serial.print(joy.y);
    return joy;
}

//Fonction est good
Bouton capterSwitch()
{
    static unsigned long preMillis = 0; 
    unsigned long MillisActuel = millis();
    bool LECTURE = 1, PRET = 0;
    const int interval = 200;
    bool etat = PRET;

    Bouton bouton;
    bouton.switch1 = digitalRead(SWITCH_1);
    bouton.switch2 = digitalRead(SWITCH_2);
    bouton.switch3 = digitalRead(SWITCH_3);
    bouton.switch4 = digitalRead(SWITCH_4);
    bouton.paddleshiftup = digitalRead(PADDLE_UP);
    bouton.paddleshiftdown = digitalRead(PADDLE_DOWN);

    if (MillisActuel-preMillis >= interval && etat == PRET) {
        preMillis = MillisActuel;
        etat = LECTURE;

    if(bouton.switch1 != HIGH){
        bouton.switch1 = true;
        Serial.print(bouton.switch1);
    }
    if(bouton.switch2 != HIGH){
        bouton.switch2 = true;
        Serial.print(bouton.switch2);
    }
    if(bouton.switch3 != HIGH){
        bouton.switch3 = true;
        Serial.print(bouton.switch3);
    }
    if(bouton.switch4 != HIGH){ 
        bouton.switch4 = true;
        Serial.print(bouton.switch4);
    }
    if(bouton.switch3 != HIGH){
        bouton.switch3 = true;
        Serial.print(bouton.switch3);
    }
    if(bouton.paddleshiftup != HIGH){ 
        bouton.paddleshiftup = true;
        Serial.print(bouton.paddleshiftup);
    }
     if(bouton.paddleshiftdown != HIGH){ 
        bouton.paddleshiftdown = true;
        Serial.print(bouton.paddleshiftdown);
    }
    etat = PRET;
    }
    return bouton;
}

uint8_t traitementJoystick() {
    Joystick val = capterJoy();
    if (val.y > joy_mid + joy_deadzone) {
        return 0b001; //Haut
    } else if (val.y < joy_mid - joy_deadzone) {
        return 0b010; //Bas
    } else if (val.x > joy_mid + joy_deadzone) {
        return 0b011; //Gauche
    } else if (val.x < joy_mid - joy_deadzone) {
        return 0b100; //Droite
    } else {
        return 0b000;
    }
}

    
