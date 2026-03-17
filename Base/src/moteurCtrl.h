//Fichier d'entête pour le contrôle du moteur du volant

#ifndef MOTEURCTRL_H
#define MOTEURCTRL_H
#include <avr/interrupt.h>
#include <Arduino.h>

const int stepRes = 3200;
const int maxRate = 20000;
const uint32_t highTicks = 10; // 5µs × 2 ticks/µs (prescaler 8 = 0.5µs/tick)

const int pinENA = 5;
const int pinALM = 6;

void setupMoteurCtrl();
void setSpeed(float RPM);

void setupDriverReset();
bool checkAndResetDriver();


#endif 