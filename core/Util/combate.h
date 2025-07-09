#ifndef COMBATE_H
#define COMBATE_H

#include "Personaje.h"
#include <cmath>

static constexpr int ANCHO_PERSONAJE  = 10;

void procesarColision(Personaje* atacante, Personaje* defensor, bool& yaGolpeó);
bool puedeMover(Personaje* p, Personaje* rival, bool dir);

#endif // COMBATE_H
