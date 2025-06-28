#include "JackieChun.h"
#include <iostream>

JackieChun::JackieChun()
    : Personaje("JackieChun", 85, 40, 4, 6, 40)
{}

void JackieChun::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (getKi() < 20) {
        std::cout << getNombre() << " no puede usar Reversa de Sabio.\n";
        return;
    }
    std::cout << getNombre() << " lanza Reversa de Sabio!\n";
    objetivo->recibirDanio(getDanoBase() * 2);
    recuperarKi(-20);
}
