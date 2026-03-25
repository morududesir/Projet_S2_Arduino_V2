#include "communication.h"
const int FreqEchantillonnage = 100; // Fréquence d'échantillonnage en Hz
const float interval = 1.0 / FreqEchantillonnage;
unsigned long previousMillis = 0;
AcquisitionData data;
void setup() {
    Serial.begin(115200);
    //homing();
    setupAcquisition();
    setupMoteurCtrl();

    
}

void loop() {
    if (millis() - previousMillis >= interval * 1000) {
        previousMillis = millis();
        data = getValues();
        sendData(data);
    }


    //Serial.print(" Pot1: "); Serial.print(currentData.pot1Value);
    //Serial.print(" Pot2: "); Serial.println(currentData.pot2Value);
}