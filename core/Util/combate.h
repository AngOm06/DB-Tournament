#ifndef COMBATE_H
#define COMBATE_H

#include "Personaje.h"

// Procesa la colisión de un atacante sobre un defensor.
// Si están lo bastante cerca (≤ ALCANCE_ATAQUE) y el atacante está
// en estado ATACANDO o ATACANDO_BAJO, aplica daño al defensor.
void procesarColision(Personaje* atacante, Personaje* defensor);

#endif // COMBATE_H
