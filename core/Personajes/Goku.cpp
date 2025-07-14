#include "Goku.h"

Goku::Goku()
    : Personaje("Goku", /*vida*/100, /*velX*/4, /*danoBase*/4, /*kiMax*/50)
{}

//Daño base x5, pero Goku queda aturdido por unos frames
void Goku::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (estado != EstadoPersonaje::IDLE) return;
    if (kiActual < 50) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, FRAMES_ESPECIAL);

    objetivo->recibirDanio(danoBase * 5);

    cambiarEstado(EstadoPersonaje::ATURDIDO, 20);

    kiActual -= 50;
}
