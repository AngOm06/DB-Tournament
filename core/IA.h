#ifndef IA_H
#define IA_H

#include "Personaje.h"

// Decide y ejecuta una acción para el personaje 'cpu' en función de
// la distancia al 'jugador' y de su propio estado.
// Debe llamarse cada N ticks en el bucle principal.
void ejecutarIA(Personaje* cpu, Personaje* jugador);

#endif // IA_H
