#include "Yamcha.h"

Yamcha::Yamcha()
    :Personaje("Yamcha", /*vida*/90, /*velX*/4, /*danoBase*/5, /*kiMax*/30)
{}

//Daño base x3 y aturde al rival
void Yamcha::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (kiActual < 15) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, FRAMES_ESPECIAL);

    objetivo->recibirDanio(danoBase * 3);
    objetivo->cambiarEstado(EstadoPersonaje::ATURDIDO, 25);

    kiActual -= 15;
}
