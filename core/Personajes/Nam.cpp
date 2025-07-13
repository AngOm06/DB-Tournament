#include "Nam.h"
#include <iostream>

Nam::Nam()
    : Personaje("Nam", 75, 3, 5, 35)
{}

void Nam::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (getKi() < 18) {
        std::cout << getNombre() << " no puede usar Onda Mortal.\n";
        return;
    }
    std::cout << getNombre() << " lanza Onda Mortal!\n";
    objetivo->recibirDanio(getDanoBase() * 3);
    recuperarKi(-18);
}
