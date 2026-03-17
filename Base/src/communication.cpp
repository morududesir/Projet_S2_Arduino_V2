#include "communication.h"

/*
void sendData(AcquisitionData data) {
    float posNormalisee = (float)(data.encoderPos - target) / (600.0 * 2);
    if(posNormalisee > 1.0) posNormalisee = 1.0;
    if(posNormalisee < -1.0) posNormalisee = -1.0;

    float gasNormalise = (float)(data.pot1Value - minGas) / (maxGas - minGas);
    if(gasNormalise > 1.0) gasNormalise = 1.0;
    if(gasNormalise < 0.0) gasNormalise = 0.0;

    float brakeNormalise = (float)(data.pot2Value - minBrake) / (maxBrake - minBrake);
    if(brakeNormalise > 1.0) brakeNormalise = 1.0;
    if(brakeNormalise < 0.0) brakeNormalise = 0.0;

    StaticJsonDocument<64> doc;
    doc["pos"] = posNormalisee;
    doc["pot1"] = gasNormalise;
    doc["pot2"] = brakeNormalise;
    String output;
    serializeJson(doc, output);
    Serial.println(output);
}
    */