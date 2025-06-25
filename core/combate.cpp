#include "Combate.h"
#include <cmath>  // std::abs

void procesarColision(Personaje* atacante, Personaje* defensor) {
    if (!atacante || !defensor) return;

    // Sólo aplicamos daño si el atacante está realizando un ataque
    EstadoPersonaje est = atacante->getEstado();
    if (est != EstadoPersonaje::ATACANDO &&
        est != EstadoPersonaje::ATACANDO_BAJO)
    {
        return;
    }

    // Comprobamos distancia en X
    int dx = std::abs(atacante->getPosicionX() - defensor->getPosicionX());
    if (dx <= ALCANCE_ATAQUE) {
        // Atacante golpea: aplicamos daño base
        defensor->recibirDanio(atacante->getDanoBase());
        atacante->recuperarKi(5);
    }
}
