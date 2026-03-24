#include "moteurCtrl.h"
volatile uint16_t lowTicks = 0;
volatile bool speedState = LOW;
volatile bool pendingDirHigh = LOW;
volatile bool stepState = LOW;

void setupMoteurCtrl() {
  // DDRH : Data Direction Register H
  // Bit 3 = pin 6 (STEP), bit 4 = pin 7 (DIR), bit 5 = pin 8 (ENA)
  DDRH |= (1 << 3) | (1 << 4) | (1 << 5);
  // PORTH : Port H Data Register
  // On force STEP et DIR à LOW, ENA à LOW (driver actif)
  PORTH &= ~((1 << 3) | (1 << 4) | (1 << 5));
  // TCCR1A : Timer1 Control Register A
  // On met à 0 pour désactiver tout output compare
  TCCR1A = 0;
  // TCCR1B : Timer1 Control Register B
  // Mode CTC avec ICR1 comme TOP, prescaler 8
  // 16MHz / 8 = 2MHz = 0.5µs par tick
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  // ICR1 : Input Capture Register 1
  // 2000 ticks × 0.5µs = 1ms au repos
  ICR1 = 2000;
  // TCNT1 : Timer1 Counter Register
  TCNT1 = 0;
  // TIMSK1 : Timer1 Interrupt Mask Register
  // ICIE1 : Déclenche l'ISR quand TCNT1 atteint ICR1
  TIMSK1 = (1 << ICIE1);
  setSpeed(0);
}

void setSpeed(float targetRPM) {
  static float currentRPM = 0;
  const float maxStep = 20.0f;
  
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

ISR(TIMER1_CAPT_vect) {
  if (speedState == HIGH) {
    if (stepState == LOW) {
      if (pendingDirHigh) PORTH |=  (1 << 4);
      else                PORTH &= ~(1 << 4);
      PORTH |= (1 << 3);
      stepState = HIGH;
      ICR1 = highTicks;
    } else {
      PORTH &= ~(1 << 3);
      stepState = LOW;
      ICR1 = lowTicks;
    }
  } else {
    PORTH &= ~(1 << 3);
    stepState = LOW;
    ICR1 = 2000;
  }
  TCNT1 = 0;
}