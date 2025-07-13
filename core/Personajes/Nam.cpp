#include "Nam.h"

Nam::Nam()
    :Personaje("Nam", /*vida*/75, /*velX*/3, /*danoBase*/5, /*kiMax*/35)
{}

//Daño base x3
void Nam::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (kiActual < 35) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, FRAMES_ESPECIAL);

    objetivo->recibirDanio(danoBase * 3);

    kiActual -= 35;
}
