#include "Bacterian.h"
#include <iostream>

Bacterian::Bacterian()
    : Personaje("Bacterian", 70, 6, 7, 25)
{}

void Bacterian::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (getKi() < 12) {
        std::cout << getNombre() << " no tiene suficiente Ki para Eructo Toxico.\n";
        return;
    }
    std::cout << getNombre() << " usa Eructo Toxico!\n";
    objetivo->recibirDanio(getDanoBase() * 4);
    recuperarKi(-12);
}
