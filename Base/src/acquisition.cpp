#include "acquisition.h"
volatile int32_t encoderPos = 0;
volatile bool currentChannel = LOW; //Permet d'alterner entre les lectures des 2 pots
volatile int pot1Value = 0;
volatile int pot2Value = 0;

void setupAcquisition() {
	// DDRD : Data Direction Register D
	// Chaque bit correspond à une pin du port D
	// 0 = input, 1 = output
	// On met les bits 2 et 3 à 0 pour configurer pin 2 et 3 en input
	DDRD &= ~((1 << 2) | (1 << 3));
    
	// PORTD : Port D Data Register
	// Quand la pin est en input, écrire 1 active le pullup interne
	// On active le pullup sur pin 2 et 3 pour éviter les états flottants
	PORTD |= (1 << 2) | (1 << 3);

	// EICRA : External Interrupt Control Register A
	// Contrôle le type de déclenchement des interruptions INT0 à INT3
	// ISC00 et ISC10 à 1 = déclenche sur tout changement (rising et falling)
	// ISC00 contrôle INT0 (pin 2), ISC10 contrôle INT1 (pin 3)
	EICRA |= (1 << ISC00) | (1 << ISC10);

	// EIMSK : External Interrupt Mask Register
	// Chaque bit active ou désactive une interruption externe
	// INT0 = pin 2, INT1 = pin 3
	// On met les deux à 1 pour activer les deux interruptions
	EIMSK |= (1 << INT0) | (1 << INT1);

	// ADMUX : ADC Multiplexer Selection Register
	// Contrôle la référence de tension et le canal ADC sélectionné
	// REFS0 = 1, REFS1 = 0 : référence AVcc (5V)
	// MUX bits à 0 : sélectionne ADC0 (pin A0)
	ADMUX |= (1 << REFS0);
	// ADCSRA : ADC Control and Status Register A
	// ADEN : ADC Enable, ADPS2:0 : ADC Prescaler Select bits
	// ADSC : Lance une conversion ADC
	// On active l'ADC et on choisit un prescaler de 128
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

AcquisitionData getValues() {
	AcquisitionData data;
	// cli/sei : désactive/réactive les interruptions globales
	// Protège la lecture de encoderPos contre une ISR concurrente
	cli();
	data.encoderPos = encoderPos;
	data.pot1Value = pot1Value;
	data.pot2Value = pot2Value;
	sei();
	return data; 
}

ISR(INT0_vect) {
	// PIND : Port D Input Pins Register
	// Lecture directe de l'état physique des pins du port D
	// Plus rapide que digitalRead() — 1 cycle CPU au lieu de ~50
	// On lit l'état de A (bit 2) et B (bit 3) simultanément
	bool A = PIND & (1 << 2);
	bool B = PIND & (1 << 3);
	// Si A == B on tourne dans un sens, sinon dans l'autre
	encoderPos += (A == B) ? 1 : -1;
}

ISR(INT1_vect) {
	// Même logique que INT0 mais la condition est inversée
	// car c'est B qui a changé cette fois
	bool A = PIND & (1 << 2);
	bool B = PIND & (1 << 3);
	encoderPos += (A != B) ? 1 : -1;
}

ISR(ADC_vect) {
    // ADC : ADC Data Register
    // Contient la valeur convertie par l'ADC (10 bits)
    // On peut lire les 8 bits de poids faible avec ADCL et les 2 bits de poids fort avec ADCH
    // Ici on lit directement ADC qui combine les deux
    if(currentChannel == LOW) {
        pot1Value = ADC; // Lire la valeur du pot 1 (ADC0)
        currentChannel = HIGH; // Passer à la lecture du pot 2 au prochain déclenchement
        ADMUX |= (1 << MUX0); // Sélectionner ADC1 (pin A1) pour la prochaine conversion

    } else {
        pot2Value = ADC; // Lire la valeur du pot 2 (ADC0, même canal)
        currentChannel = LOW; // Revenir à la lecture du pot 1 au prochain déclenchement
        ADMUX &= ~(1 << MUX0); // Réinitialiser le canal ADC à ADC0 (pin A0)
    }
	ADCSRA |= (1 << ADSC); // Lancer une nouvelle conversion ADC
}  