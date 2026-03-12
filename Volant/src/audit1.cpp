
/*
#include <Arduino.h>
#include "acquisition.h"
#include "traitement.h"

#include <U8g2lib.h>

 //SW SPI: (rotation, clock, data, cs, dc, reset)
U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(
  U8G2_R0,
  13,   //clock
  11,   //data 
  10,   //cs
  9,   //dc
  8   //reset
); 


//Pin bargraph
const int bar1 = 22;
const int bar2 = 23;
const int bar3 = 24;
const int bar4 = 25;
const int bar5 = 26;
const int bar6 = 27;
const int bar7 = 28;
const int bar8 = 29;
const int bar9 = 30;
const int bar10 = 31;

int interval = 100; // interval to update display (ms)
unsigned long previousMillis = 0;  // will store last time display was updated

void setup() {
  Serial.begin(9600);
  setupCapteurs();

  for(int i = bar1; i <= bar10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  u8g2.begin();
  u8g2.clearBuffer();
}

void loop() {

  //uint8_t val = traitementJoystick();
  //Serial.println(val, BIN);

  Encodeur enc = capterEncodeurs();
  String encStr = "Gauche: " + String(enc.valeurGauche) + " Droit: " + String(enc.valeurDroite);

  DirectionAccel valAccel = traitement_acceleration();
  String dirStr = "Direction: ";
  if (valAccel.direction == NEUTRE) {
    dirStr += "NEUTRE";
  } else if (valAccel.direction == GAUCHE) {
    dirStr += "GAUCHE";
  } else if (valAccel.direction == DROITE) {
    dirStr += "DROITE";
  }
  String accelStr = "Accel(g): X=" + String(valAccel.valeursAccel[0], 2) + " Y=" + String(valAccel.valeursAccel[1], 2) + " Z=" + String(valAccel.valeursAccel[2], 2);
  Serial.println(accelStr);
  Serial.println(dirStr);
  /*Bouton bouton = capterSwitch();
  String switchStr = "Switch 1: " + String(bouton.switch3) + " - Switch 2: " + String(bouton.switch4);

  Joystick joy = capterJoy();
  String joyStr = "Joystick: X=" + String(joy.x, BIN) + " Y=" + String(joy.y, BIN);

  // update bargraph according to left encoder (4 counts per step)
  // compute how many bars should be lit (0–10)
  long count = enc.valeurGauche / 4;          // each 4 increments = one bar
  if (count < 0) count = 0;
  if (count > 10) count = 10;
  for (int pin = bar1; pin <= bar10; pin++) {
    int idx = pin - bar1;                     // 0-based index of bar
    digitalWrite(pin, (idx < count) ? HIGH : LOW);
  }
  
  if (millis() - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = millis();

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_4x6_tr);
    u8g2.drawStr(0, 7, accelStr.c_str());
    u8g2.drawStr(0, 14, dirStr.c_str());
    u8g2.drawStr(0, 21, encStr.c_str());
    u8g2.drawStr(0, 28, switchStr.c_str());
    u8g2.drawStr(0, 35, joyStr.c_str());
    u8g2.sendBuffer();

}

  delay(100); // pause before repeating
}*/

