#include "Ranfan.h"

Ranfan::Ranfan()
    :Personaje("Ranfan", /*vida*/60, /*velX*/3, /*danoBase*/5, /*kiMax*/50)
{}

//Daño base x4 pero Ranfan queda aturdida
void Ranfan::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (kiActual < 20) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, FRAMES_ESPECIAL);

    objetivo->recibirDanio(danoBase * 4);
    cambiarEstado(EstadoPersonaje::ATURDIDO, 15);

    kiActual -= 20;
}
