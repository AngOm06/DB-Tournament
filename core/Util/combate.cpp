#include "Combate.h"

void procesarColision(Personaje* atacante, Personaje* defensor) {
    if (!atacante || !defensor) return;

    // Sólo atacamos si estamos en un estado de golpe válido
    EstadoPersonaje est = atacante->getEstado();
    int alcance = 0;
    if (est == EstadoPersonaje::ATACANDO || est == EstadoPersonaje::ATACANDO_BAJO) {
        alcance = ALCANCE_ATAQUE;
    } else if (est == EstadoPersonaje::USANDO_ESPECIAL) {
        alcance = ALCANCE_ESPECIAL;
    } else {
        return;
    }

    // Chequeo de distancia
    int dx = std::abs(atacante->getPosicionX() - defensor->getPosicionX());
    if (dx <= alcance) {
        defensor->recibirDanio(atacante->getDanoBase());
        atacante->recuperarKi(5);
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
