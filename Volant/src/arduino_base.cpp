
#include "arduino_base.h"

//Init Objet Encodeur
Encoder E_BASE(PIN_ENCODEURBASE1,PIN_ENCODEURBASE2);

//Fonction pour lire l'encodeur de la base
long capterEncodeurBase()
{
    return E_BASE.read();
}