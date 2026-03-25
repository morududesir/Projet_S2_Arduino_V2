#include "communication.h"


void sendData(Encodeur encode, Acceleration accel, Joystick joy, Bouton bouton) {

    StaticJsonDocument<192> doc;
    doc["enc1"] = encode.valeurGauche;
    doc["enc2"] = encode.valeurDroite;
    doc["accelX"] = accel.x;
    doc["accelY"] = accel.y;
    doc["accelZ"] = accel.z;
    doc["switchTL"] = bouton.switch3;
    doc["switchTR"] = bouton.switch1;
    doc["switchBL"] = bouton.switch4;
    doc["switchBR"] = bouton.switch2;
    doc["JoyDirection"] = traitementJoystick();

    serializeJson(doc, Serial);
    Serial.println();
}


void receiveData() {
    
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, input);
        
        if (error) return;
        
        // Extraire les valeurs ici selon ce que le PC envoie
        // par exemple:
        // int valeur = doc["valeur"];
    }
}