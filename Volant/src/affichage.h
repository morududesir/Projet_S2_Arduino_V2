#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <U8g2lib.h>
#include "communication.h"



void setupOLED();

void afficherData(float rpm, float maxRpm, int gear, float fuel, float tireWear, float speed, bool inPit);

#endif