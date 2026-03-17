#include "ctrlFFB.h"
const int FreqEchantillonnage = 100; // Fréquence d'échantillonnage en Hz
const float interval = 1.0 / FreqEchantillonnage;
unsigned long previousMillis = 0;

void setup() {
    Serial.begin(9600);
    setupDriverReset();  // avant le homing
    homing();
}

void loop() {
    if (checkAndResetDriver()) {
        // le driver vient de fault — on skip ce cycle
        Serial.println("ALARM RESET");
        return;
    }

    if (millis() - previousMillis >= interval * 1000) {
        previousMillis = millis();
        AcquisitionData data = FFB();
    }
}