#include "Combate.h"

void procesarColision(Personaje* atacante, Personaje* defensor, bool& yaGolpeó) {
    if (!atacante || !defensor) return;

    if (yaGolpeó) return;  // ya aplicamos este ataque
    EstadoPersonaje est = atacante->getEstado();
    if (est != EstadoPersonaje::ATACANDO)
    {
        return;
    }
    int dx = std::abs(atacante->getPosicionX() - defensor->getPosicionX());
    if (dx <= ALCANCE_ATAQUE) {
        defensor->recibirDanio(atacante->getDanoBase());
        atacante->recuperarKi(5);
        yaGolpeó = true;  // no más daño hasta que termine este ataque
    }
}
bool puedeMover(Personaje* p, Personaje* rival, bool dir) {
    if (!p || !rival) return false;

    // Si cualquiera está en el aire, permitimos el paso
    if (p->getPosicionY() > 0.0f || rival->getPosicionY() > 0.0f)
        return true;

    // Distancia en X
    int dx = std::abs(p->getPosicionX() - rival->getPosicionX());
    if (dx < ANCHO_PERSONAJE) {
        // Si intento moverme hacia el rival, bloqueo
        if (dir && p->getPosicionX() < rival->getPosicionX()) return false;
        if (!dir && p->getPosicionX() > rival->getPosicionX()) return false;
    }

    return true;
}
