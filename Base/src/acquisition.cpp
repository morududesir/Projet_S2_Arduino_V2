#include "acquisition.h"

volatile int32_t encoderPos = 0;
volatile bool currentChannel = LOW;
volatile int pot1Value = 0;
volatile int pot2Value = 0;



void setupAcquisition() {
    // DDRE : Data Direction Register E
    // Sur le Mega 2560, pin 2 = PE4 (INT4) est Vert et pin 3 = PE5 (INT5) est Blanc, Z est Jaune
    // On met les bits PE4 et PE5 à 0 pour configurer ces pins en input
    DDRE &= ~((1 << PE4) | (1 << PE5));

    // PORTE : Port E Data Register
    // Quand la pin est en input, écrire 1 active le pullup interne
    // On active le pullup sur PE4 et PE5 pour éviter les états flottants
    PORTE |= (1 << PE4) | (1 << PE5);

    // EICRB : External Interrupt Control Register B
    // Contrôle le type de déclenchement des interruptions INT4 à INT7
    // ISC40 et ISC50 à 1 = déclenche sur tout changement (rising et falling)
    // ISC40 contrôle INT4 (pin 2), ISC50 contrôle INT5 (pin 3)
    EICRB |= (1 << ISC40) | (1 << ISC50);

    // EIMSK : External Interrupt Mask Register
    // INT4 = pin 2, INT5 = pin 3 sur le Mega 2560
    // On met les deux à 1 pour activer les deux interruptions
    EIMSK |= (1 << INT4) | (1 << INT5);

    // ADMUX : ADC Multiplexer Selection Register
    // REFS0 = 1, REFS1 = 0 : référence AVcc (5V)
    // MUX bits à 0 : sélectionne ADC0 (pin A0)
    ADMUX |= (1 << REFS0);

    // ADCSRA : ADC Control and Status Register A
    // ADEN : ADC Enable, ADPS2:0 : prescaler de 128
    // ADSC : Lance une première conversion ADC
    ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // ADCSRA : Active l'interruption de fin de conversion ADC
    ADCSRA |= (1 << ADIE);
}

AcquisitionData getValues() {
    AcquisitionData data;
    // cli/sei : désactive/réactive les interruptions globales
    // Protège la lecture de encoderPos contre une ISR concurrente
    cli();
    data.encoderPos = encoderPos / 2;
    data.pot1Value = pot1Value;
    data.pot2Value = pot2Value;
    sei();
    return data;
}

ISR(INT4_vect) {
    // PINE : Port E Input Pins Register
    // Sur le Mega, pin 2 = PE4 et pin 3 = PE5
    // On lit l'état de A (PE4) et B (PE5) simultanément
    bool A = PINE & (1 << PE4);
    bool B = PINE & (1 << PE5);
    // Si A == B on tourne dans un sens, sinon dans l'autre
    encoderPos += (A == B) ? 1 : -1;
}

ISR(INT5_vect) {
    // Même logique que INT4 mais la condition est inversée
    // car c'est B (PE5) qui a changé cette fois
    bool A = PINE & (1 << PE4);
    bool B = PINE & (1 << PE5);
    encoderPos += (A != B) ? 1 : -1;
}

ISR(ADC_vect) {
    // ADC : ADC Data Register (10 bits)
    // Lecture de la valeur convertie et alternance entre ADC0 et ADC1
    if (currentChannel == LOW) {
        pot1Value = ADC;                // Lire la valeur du pot 1 (ADC0, pin A0)
        currentChannel = HIGH;          // Passer à la lecture du pot 2
        ADMUX |= (1 << MUX0);          // Sélectionner ADC1 (pin A1)
    } else {
        pot2Value = ADC;                // Lire la valeur du pot 2 (ADC1, pin A1)
        currentChannel = LOW;           // Revenir à la lecture du pot 1
        ADMUX &= ~(1 << MUX0);         // Réinitialiser le canal ADC à ADC0 (pin A0)
    }
    ADCSRA |= (1 << ADSC);             // Lancer une nouvelle conversion ADC
}