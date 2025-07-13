#include "Ranfan.h"
#include <iostream>

Ranfan::Ranfan()
    : Personaje("Ranfan", 60, 3, 5, 50)
{}

void Ranfan::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (getKi() < 20) {
        std::cout << getNombre() << " no puede usar Zambombazo.\n";
        return;
    }
    std::cout << getNombre() << " lanza Zambombazo!\n";
    objetivo->recibirDanio(getDanoBase() * 3);
    cambiarEstado(EstadoPersonaje::ATURDIDO, 1);
    recuperarKi(-20);
}
