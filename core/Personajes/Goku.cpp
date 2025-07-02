#include "Goku.h"
#include <iostream>

Goku::Goku()
    : Personaje("Goku", /*vida*/100, /*velX*/3, /*danoBase*/4, /*kiMax*/50)
{}

// Kamehameha: daño 2× base y aturde 1 frame al rival
void Goku::usarEspecial(Personaje* objetivo) {
    if (!objetivo || !objetivo->getVida()>0) return;
    if (estado != EstadoPersonaje::IDLE) {
        std::cout << getNombre() << " esta ocupado.\n";
        return;
    }
    if (kiActual < 50) {
        std::cout << getNombre() << " no tiene suficiente Ki.\n";
        return;
    }
    std::cout << getNombre() << " lanza Kamehameha!\n";
    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, 5);
    objetivo->recibirDanio(danoBase * 4);
    objetivo->cambiarEstado(EstadoPersonaje::ATURDIDO, 10);
    kiActual -= 50;
}
