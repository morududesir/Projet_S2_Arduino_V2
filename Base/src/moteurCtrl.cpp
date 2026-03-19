#include "moteurCtrl.h"
volatile uint16_t lowTicks = 0;
volatile bool speedState = LOW;
volatile bool pendingDirHigh = LOW;
volatile bool stepState = LOW;
void setupMoteurCtrl() {
  // DDRB : Data Direction Register B
  // Configure les pins du port B en entrée (0) ou sortie (1)
  // Bit 6 = pin 12 (STEP), bit 7 = pin 13 (DIR) sur le Mega 2560
  DDRB |= (1 << 6) | (1 << 7);
  // PORTB : Port B Data Register
  // Quand la pin est en output, contrôle l'état HIGH/LOW
  // On force STEP et DIR à LOW au démarrage
  PORTB &= ~((1 << 6) | (1 << 7));
  // TCCR1A : Timer1 Control Register A
  // Contrôle les modes de sortie compare (OC1A, OC1B)
  // On met à 0 pour désactiver tout output compare, on veut juste le timer
  TCCR1A = 0;
  // TCCR1B : Timer1 Control Register B
  // WGM13 et WGM12 : Waveform Generation Mode
  // Ensemble ils sélectionnent le mode CTC avec ICR1 comme TOP
  // Le timer compte de 0 jusqu'à ICR1 puis repart à 0
  // CS11 : Clock Select, prescaler 8
  // 16MHz / 8 = 2MHz = 0.5µs par tick
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  // ICR1 : Input Capture Register 1
  // Définit la valeur TOP du timer en mode CTC
  // Le timer déclenche l'interruption quand TCNT1 atteint ICR1
  // 2000 ticks × 0.5µs = 1ms au repos
  ICR1 = 2000;
  // TCNT1 : Timer1 Counter Register
  // Valeur actuelle du compteur
  // On remet à 0 pour partir proprement
  TCNT1 = 0;
  // TIMSK1 : Timer1 Interrupt Mask Register
  // Chaque bit active une source d'interruption du Timer1
  // ICIE1 : Input Capture Interrupt Enable
  // Déclenche l'ISR quand TCNT1 atteint ICR1
  TIMSK1 = (1 << ICIE1);
  setSpeed(0);
}
void setSpeed(float targetRPM) {
  static float currentRPM = 0;
  const float maxStep = 20.0f; // RPM maximum par appel, ajustez selon vos besoins
  
  if (fabs(targetRPM - currentRPM) > maxStep) {
    currentRPM += (targetRPM > currentRPM) ? maxStep : -maxStep;
  } else {
    currentRPM = targetRPM;
  }

  if (fabs(currentRPM) < 0.5f) {
    cli(); speedState = LOW; sei();
    return;
  }

  bool dirHigh = (currentRPM > 0);
  float absRPM = fabs(currentRPM);
  unsigned long stepSec = (unsigned long)((float)stepRes * absRPM / 60.0f);
  if (stepSec > maxRate) stepSec = maxRate;
  if (stepSec < 1) stepSec = 1;
  unsigned long period = 1000000UL / stepSec;
  unsigned long low = period - 5UL;
  if (low < 5) low = 5;
  cli();
  lowTicks = (uint16_t)min(low * 2, 65535UL);
  pendingDirHigh = dirHigh;
  speedState = HIGH;
  sei();
}

void setupDriverReset() {
    pinMode(pinENA, OUTPUT);
    pinMode(pinALM, INPUT_PULLUP);
    digitalWrite(pinENA, LOW);  // LOW = driver actif (ENA non activé)
}

bool checkAndResetDriver() {
    if (digitalRead(pinALM) == LOW) {   // alarme = OC tire vers GND
        digitalWrite(pinENA, HIGH);      // désactiver le driver
        delay(150);                      // laisser le driver se reset
        digitalWrite(pinENA, LOW);       // réactiver
        delay(50);
        return true;
    }
    return false;
}

ISR(TIMER1_CAPT_vect) {
  if (speedState == HIGH) {
    if (stepState == LOW) {
      if (pendingDirHigh) PORTB |=  (1 << 7);
      else                PORTB &= ~(1 << 7);
      PORTB |= (1 << 6);
      stepState = HIGH;
      ICR1 = highTicks;
    } else {
      PORTB &= ~(1 << 6);
      stepState = LOW;
      ICR1 = lowTicks;
    }
  } else {
    PORTB &= ~(1 << 6);
    stepState = LOW;
    ICR1 = 2000;
  }
  TCNT1 = 0;
}