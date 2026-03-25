#include "communication.h"


void sendData(Encodeur encode, Acceleration accel, int joy, Bouton bouton) {

    JsonDocument doc;
    doc["enc1"] = encode.valeurGauche;
    doc["enc2"] = encode.valeurDroite;
    doc["accelX"] = accel.x;
    doc["accelY"] = accel.y;
    doc["accelZ"] = accel.z;
    doc["switchTL"] = bouton.switch3;
    doc["switchTR"] = bouton.switch1;
    doc["switchBL"] = bouton.switch4;
    doc["switchBR"] = bouton.switch2;
    doc["paddleshiftup"] = bouton.paddleshiftup;
    doc["paddleshiftdown"] = bouton.paddleshiftdown;
    doc["JoyDirection"] = joy;
    String output;
    serializeJson(doc, output);
    Serial.println(output);
}


GameData receiveData() {
    GameData data;
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, input);
        
        if (error) return data;
        
        data.rpm = doc["rpm"];
        data.maxRpm = doc["rpmMax"];
        data.gear = doc["gear"];
        data.fuel = doc["fuel"];
        data.tireWear = doc["tires"];
        data.speed = doc["speed"];
        data.inPit = doc["pit"];
        return data;
    }
    return data;
}