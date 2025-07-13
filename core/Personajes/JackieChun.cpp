#include "JackieChun.h"

JackieChun::JackieChun()
    :Personaje("JackieChun", /*vida*/85, /*velX*/4, /*danoBase*/6, /*kiMax*/40)
{}

//Daño base x3 y aturde al rival
void JackieChun::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (kiActual < 40) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, FRAMES_ESPECIAL);

    objetivo->recibirDanio(danoBase * 3);
    objetivo->cambiarEstado(EstadoPersonaje::ATURDIDO, 20);

    kiActual -= 40;
}
