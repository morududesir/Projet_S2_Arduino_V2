// main.cpp
#include <Arduino.h>
#include "acquisition.h"
#include "communication.h"
#include "affichage.h"

const int freqHz = 100;
const unsigned long interval = 1000 / freqHz;
unsigned long previousMillis = 0;

GameData lastGameData;   // ← garde la dernière valeur valide

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(10);
    setupCapteurs();
    setupOLED();
}

void loop() {
    unsigned long now = millis();
    if (now - previousMillis >= interval) {
        previousMillis = now;
        Encodeur enc = capterEncodeurs();
        Acceleration accel = capterAccel();
        Bouton bouton = capterSwitch();
        int joy = traitementJoystick();
        sendData(enc, accel, joy, bouton);

        GameData newData = receiveData();

        // ← met à jour seulement si de nouvelles données arrivent
        if (newData.maxRpm > 0) {
            lastGameData = newData;
        }

        afficherData(lastGameData.rpm, lastGameData.maxRpm, lastGameData.gear,
                     lastGameData.fuel, lastGameData.tireWear, lastGameData.speed,
                     lastGameData.inPit);
    }
}