#include "moteurCtrl.h"

volatile uint16_t lowTicks = 0;
volatile bool speedState = LOW;
volatile bool pendingDirHigh = LOW;
volatile bool stepState = LOW;


void setupMoteurCtrl() {
  DDRB |= (1 << 4) | (1 << 5);
  PORTB &= ~((1 << 4) | (1 << 5));

  // Timer1 mode CTC avec ICR1 comme TOP, prescaler 8
  TCCR1A = 0;
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
  ICR1 = 2000; // idle ~1ms
  TCNT1 = 0;
  TIMSK1 = (1 << ICIE1); // Interruption sur ICR1

  setSpeed(0);
}


void setSpeed(int RPM) {
  if (RPM == 0) {
    cli(); speedState = LOW; sei();
    return;
  }
  bool dirHigh = (RPM > 0);
  unsigned long stepSec = (unsigned long)stepRes * (unsigned long)abs(RPM) / 60UL;
  if (stepSec > maxRate) stepSec = maxRate;
  unsigned long period = 1000000UL / stepSec;
  unsigned long low = period - 5UL;
  if (low < 5) low = 5;

  cli();
  lowTicks = (uint16_t)(low * 2);  // µs → ticks (×2 car 0.5µs/tick)
  pendingDirHigh = dirHigh;
  speedState = HIGH;
  sei();
}

ISR(TIMER1_CAPT_vect) {
  if (speedState == HIGH) {
    if (stepState == LOW) {
      if (pendingDirHigh) PORTB |=  (1 << 5);
      else                PORTB &= ~(1 << 5);
      PORTB |= (1 << 4);
      stepState = HIGH;
      ICR1 = highTicks;
    } else {
      PORTB &= ~(1 << 4);
      stepState = LOW;
      ICR1 = lowTicks;
    }
  } else {
    PORTB &= ~(1 << 4);
    stepState = LOW;
    ICR1 = 2000;
  }
  TCNT1 = 0;
}