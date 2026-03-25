

#include <Arduino.h>
#include "acquisition.h"

#include <U8g2lib.h>



void setup() {
  Serial.begin(9600);
  setupCapteurs();
}

void loop() {
  //capterEncodeurs();
  //traitement_acceleration();
  //capterJoy();
  //capterSwitch();
  
Encodeur enc = capterEncodeurs();
Acceleration accel = capterAccel();
uint8_t joy = traitementJoystick();
Bouton bouton = capterSwitch();

// Suppose accel et bouton sont déjà définis

Serial.print("accelX: ");
Serial.print(accel.x);
Serial.print("  accelY: ");
Serial.print(accel.y);
Serial.print("  accelZ: ");
Serial.println(accel.z); // println pour passer à la ligne



Serial.print("switchTL: ");
Serial.print(bouton.switch3);
Serial.print("  switchTR: ");
Serial.print(bouton.switch1);
Serial.print("  switchBL: ");
Serial.print(bouton.switch4);
Serial.print("  switchBR: ");
Serial.println(bouton.switch2);



Serial.print("JoyDirection: ");
Serial.println(traitementJoystick());



Serial.print(enc.valeurGauche);
Serial.print("  ");
Serial.println(enc.valeurDroite);
}

