#include "acquisition.h"
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int32_t encoderPos = 0;

void setupAcquisition() {
    cli();

    // Encodeur INT4 INT5
    DDRE &= ~((1 << PE4) | (1 << PE5));
    PORTE |= (1 << PE4) | (1 << PE5);

    EICRB |= (1 << ISC40) | (1 << ISC50);
    EIMSK |= (1 << INT4) | (1 << INT5);

    sei();
}

AcquisitionData getValues() {
    AcquisitionData data;

    cli();
    data.encoderPos = encoderPos / 2;
    sei();

    // Lire potentiomètres simplement
    data.pot1Value = analogRead(A11);
    data.pot2Value = analogRead(A12);

    return data;
}

ISR(INT4_vect) {
    bool A = PINE & (1 << PE4);
    bool B = PINE & (1 << PE5);
    encoderPos += (A == B) ? 1 : -1;
}

ISR(INT5_vect) {
    bool A = PINE & (1 << PE4);
    bool B = PINE & (1 << PE5);
    encoderPos += (A != B) ? 1 : -1;
}