#include "Bacterian.h"

Bacterian::Bacterian()
    : Personaje("Bacterian", 70, 2, 7, 30)
{}

//Daño base x3 y aturde al rival
void Bacterian::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (kiActual < 30) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, FRAMES_ESPECIAL);

    objetivo->recibirDanio(danoBase * 3);
    objetivo->cambiarEstado(EstadoPersonaje::ATURDIDO, 30);

    kiActual -= 30;
}
