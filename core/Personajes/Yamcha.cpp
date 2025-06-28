#include "Yamcha.h"
#include <iostream>

Yamcha::Yamcha()
    : Personaje("Yamcha", 90, 30, 4, 5, 30)
{}

void Yamcha::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (getKi() < 15) {
        std::cout << getNombre() << " no tiene suficiente Ki para Rohan.\n";
        return;
    }
    std::cout << getNombre() << " usa Rohan!\n";
    objetivo->recibirDanio(getDanoBase() * 3);
    recuperarKi(-15);
}
