#include "ctrlFFB.h"
// définition de la variable cible partagée
int target = 0;
void homing() {
  setupAcquisition();
  setupMoteurCtrl();
    pinMode(4, INPUT_PULLUP);
  int zPosition = 0;
  int zCount = 0;
  setSpeed(homingSpeed);
  while(1) {
    if (digitalRead(4) == HIGH) {
      zCount++;
      while(digitalRead(4) == HIGH); // Attendre que Z repasse à LOW
      if(zCount == 2) {
        zPosition = getValues().encoderPos;
        setSpeed(0);
        break;
      }
    }
  }
  target = zPosition + zOffset;
  while(1) {
    int pos = getValues().encoderPos;
    int erreurHoming = target - pos;
    if (abs(erreurHoming) <= 5) {
        setSpeed(0);
        break;
    }
    setSpeed((erreurHoming > 0) ? homingSpeed : -homingSpeed);
  }
}
AcquisitionData FFB() {
  AcquisitionData data = getValues();
  static int prevEncoderPos;
  float erreur = data.encoderPos - target;
  float vitesse = (data.encoderPos - prevEncoderPos) / deltaT; 
  prevEncoderPos = data.encoderPos; // Variable statique pour stocker la position précédente
  float rpm = (erreur * gainLineaire) + (erreur * abs(erreur) * gainExponentiel) - (vitesse * gainD);
  if(rpm > capSpeed) rpm = capSpeed;
  else if(rpm < -capSpeed) rpm = -capSpeed;
  Serial.print(">");
  Serial.print("Erreur:"); Serial.print(erreur);
  Serial.print(",");
  Serial.print("RPM:"); Serial.print(rpm);
  Serial.print(",");
  Serial.print("Position:"); Serial.print(data.encoderPos);
  Serial.println();
  //setSpeed(rpm);
  return data;
}