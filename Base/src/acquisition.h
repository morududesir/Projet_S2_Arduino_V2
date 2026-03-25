#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <Arduino.h>

typedef struct {
    int32_t encoderPos;
    int pot1Value;
    int pot2Value;
} AcquisitionData;

void setupAcquisition();
AcquisitionData getValues();

#endif