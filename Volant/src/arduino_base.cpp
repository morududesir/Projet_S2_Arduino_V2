
#include "arduino_base.h"

//Init Objet Encodeur
Encoder E_BASE(PIN_ENCODEURBASE1,PIN_ENCODEURBASE2);

long capterEncodeurBase()
{
    return E_BASE.read();
}