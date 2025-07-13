#ifndef IA_H
#define IA_H

#include "Personaje.h"
enum class IAAccion {Ninguna,MoverIzq,MoverDer,Atacar,Defender,Saltar,Especial
};
void ejecutarIA(Personaje* cpu, Personaje* jugador);

#endif // IA_H
