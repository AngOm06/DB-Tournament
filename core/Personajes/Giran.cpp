#include "Giran.h"

Giran::Giran()
    :Personaje("Giran", /*vida*/95, /*velX*/2, /*danoBase*/6, /*kiMax*/30)
{}

// Daño 4× base
void Giran::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (kiActual < 30) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, FRAMES_ESPECIAL);

    objetivo->recibirDanio(danoBase * 4);

    kiActual -= 30;
}
