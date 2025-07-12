#include "Giran.h"
#include <iostream>

Giran::Giran()
    : Personaje("Giran", 95, 3, 6, 30)
{}

void Giran::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (getKi() < 25) {
        std::cout << getNombre() << " no tiene suficiente Ki para Golpe Giratorio.\n";
        return;
    }
    std::cout << getNombre() << " ejecuta Golpe Giratorio!\n";
    objetivo->recibirDanio(getDanoBase() * 4);
    recuperarKi(-25);
}
