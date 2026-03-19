#include "traitement.h"
#include <math.h>  // for fabsf

uint8_t traitementJoystick() {
    Joystick val = capterJoy();
    if (val.y > joy_mid + joy_deadzone) {
        return 0b001; //Haut
    } else if (val.y < joy_mid - joy_deadzone) {
        return 0b010; //Bas
    } else if (val.x > joy_mid + joy_deadzone) {
        return 0b011; //Gauche
    } else if (val.x < joy_mid - joy_deadzone) {
        return 0b100; //Droite
    } else {
        return 0b000;
    }

}

//Fonction qui prend les valeurs d'accélération en tension et retourne un struct contenant
//les valeurs d'accélération en g et la direction que la manette tourne
DirectionAccel traitement_acceleration()
{
    //Initialisation variables
    float ratio_V_en_G = 0.3;
    Acceleration acc_en_g = capterAccel();
    float XYZ[3] = {acc_en_g.x,acc_en_g.y,acc_en_g.z}; //Extraction valeurs accel XYZ
    //float XYZ_en_g[3];
    int i;
    DirectionAccel valAccel;

    //Conversion V en g
    /*for(i=0;i<3;i++){
        if (i!=2){
        if(XYZ[i]<1.35 || XYZ[i]>1.75){
            XYZ_en_g[i] = (XYZ[i]-V_0g)/ratio_V_en_G;
            valAccel.valeursAccel[i] = XYZ_en_g[i];
        }
        else{
            XYZ_en_g[i] = 0.0;
            valAccel.valeursAccel[i] = XYZ_en_g[i];
        }
        }
        else {
        if(XYZ[i]<1.35 || XYZ[i]>1.65){
            XYZ_en_g[i] = (XYZ[i]-V_0g)/ratio_V_en_G;
            valAccel.valeursAccel[i] = XYZ_en_g[i];
        }
        else{
            XYZ_en_g[i] = 0.0;
            valAccel.valeursAccel[i] = XYZ_en_g[i];
        }

        }
        
        Serial.print(XYZ_en_g[i]);
    }*/
   valAccel.valeursAccel[0] = XYZ[0];
    if (XYZ[0]>1.60)
        Serial.print("Gauche");
        valAccel.direction = GAUCHE;
    if (XYZ[0]<1.71)
        Serial.print("Droite");
        valAccel.direction = DROITE;
    //Serial.print("Y : ");
    //Serial.print(XYZ[1]);
    //Serial.print("Z : ");
    //Serial.print(XYZ[2]);

   /* //Détection direction accelération
    if(XYZ_en_g[0]<0){
        valAccel.direction = GAUCHE;
    }
    else if(XYZ_en_g[0]>0){
        valAccel.direction = DROITE;
    }
    else {
        valAccel.direction = NEUTRE;
    }

    return valAccel;*/
}
