#include "Krilin.h"

Krilin::Krilin()
    : Personaje("Krilin",/*vidaInicial=*/80,/*velX=*/4,/*danoBase=*/4,/*kiMaximo=*/40)
{}

// Daño base x3, aturde al rival bastante
void Krilin::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) return;
    if (kiActual < 40) return;

    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, 10);

    objetivo->recibirDanio(danoBase * 3);
    objetivo->cambiarEstado(EstadoPersonaje::ATURDIDO, 50);

    kiActual -= 40;
}
