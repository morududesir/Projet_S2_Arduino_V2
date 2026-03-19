#include "communication.h"


void sendData(Encodeur encode, Acceleration accel, Joystick joy, Bouton bouton) {

    JsonDocument doc;
    doc["enc1"] = encode.valeurGauche;
    doc["enc2"] = encode.valeurDroite;
    doc["accelX"] = accel.x;
    doc["accelY"] = accel.y;
    doc["accelZ"] = accel.z;
    doc["joyX"] = joy.x;
    doc["joyY"] = joy.y;
    doc["switchTL"] = bouton.switch1;
    doc["switchTR"] = bouton.switch2;
    doc["switchBL"] = bouton.switch3;
    doc["switchBR"] = bouton.switch4;
    doc["JoyDirection"] = traitementJoystick();
    String output;
    serializeJson(doc, output);
    Serial.println(output);
}
