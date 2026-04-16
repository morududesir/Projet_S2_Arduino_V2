#include <Arduino.h>
#include "acquisition.h"
#include "communication.h"
#include "affichage.h"

const int freqHz = 10;
const unsigned long interval = 1000 / freqHz;
unsigned long previousMillis = 0;

volatile bool muonFlag = false;
unsigned long muonTime = 0;
const unsigned long muonDebounce = 10;
int muonCount = 0;

unsigned long ledTime = 0;
const unsigned long ledDuration = 100;

GameData lastGameData;

ISR(PCINT2_vect) {
    if (digitalRead(A15) == HIGH) {
        muonFlag = true;
    }
}

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(10);
    setupCapteurs();
    setupOLED();
    digitalWrite(PIN_DEL1, LOW);
    digitalWrite(PIN_DEL2, HIGH);
    pinMode(A15, INPUT);
    PCICR  |= (1 << PCIE2);
    PCMSK2 |= (1 << PCINT23);
}

void loop() {
    // Muon debounce + LED
    if (muonFlag) {
        muonFlag = false;
        unsigned long now = millis();
        if (now - muonTime >= muonDebounce) {
            muonTime = now;
            muonCount++;
            digitalWrite(PIN_DEL1, HIGH);
            ledTime = now;
        }
    }

    if (digitalRead(PIN_DEL1) == HIGH && millis() - ledTime >= ledDuration) {
        digitalWrite(PIN_DEL1, LOW);
    }

    // Main timed loop
    unsigned long now = millis();
    if (now - previousMillis >= interval) {
        previousMillis = now;
        sendData(capterEncodeurs(), capterAccel(), traitementJoystick(), capterSwitch(), muonCount);
        GameData newData = receiveData();
        if (newData.maxRpm > 0) {
            lastGameData = newData;
        }
        afficherData(lastGameData.rpm, lastGameData.maxRpm, lastGameData.gear,
                     lastGameData.fuel, lastGameData.tireWear, lastGameData.speed,
                     lastGameData.inPit);
    }
}