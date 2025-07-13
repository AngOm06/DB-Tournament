#include "IA.h"
#include <cstdlib>  // std::rand
#include <cmath>    // std::abs

static IAAccion iaActual     = IAAccion::Ninguna;
static int       iaFramesLeft = 0;

static void decidirAccion(Personaje* cpu, Personaje* jugador) {
    int distancia = jugador->getPosicionX() - cpu->getPosicionX();

    if (std::abs(distancia) > ALCANCE_ATAQUE) {
        iaActual     = (distancia > 0) ? IAAccion::MoverDer : IAAccion::MoverIzq;
        iaFramesLeft = 6;
        return;
    }

    float pctVida = float(cpu->getVida())/cpu->getVidaMax();

    int pAtaque   = 0;
    int pDefensa  = 0;
    int pEspecial = 0;
    int pSalto    = 0;

    if (pctVida > 0.6f) {
        pAtaque   = 50;
        pDefensa  = 20;
        pSalto    = 10;
    } else if (pctVida > 0.3f) {
        pAtaque   = 35;
        pDefensa  = 35;
        pSalto    = 10;
    } else {
        pAtaque   = 20;
        pDefensa  = 40;
        pSalto    = 10;
    }
    if (cpu->getKi() == cpu->getKiMax()) {
        pEspecial = 20;
    }

    int total = pAtaque + pDefensa + pEspecial + pSalto;
    int roll  = std::rand() % total;
    if (roll < pAtaque)        iaActual = IAAccion::Atacar;
    else if (roll < pAtaque + pDefensa)
        iaActual = IAAccion::Defender;
    else if (roll < pAtaque + pDefensa + pEspecial)
        iaActual = IAAccion::Especial;
    else                        iaActual = IAAccion::Saltar;

    iaFramesLeft = 6;
}

void ejecutarIA(Personaje* cpu, Personaje* jugador) {
    if (!cpu || !jugador || jugador->getVida() <= 0 || cpu->getVida() <= 0) return;

    if (iaFramesLeft <= 0) {
        decidirAccion(cpu, jugador);
    }

    switch (iaActual) {
    case IAAccion::MoverIzq:  cpu->moverIzquierda();   break;
    case IAAccion::MoverDer:  cpu->moverDerecha();     break;
    case IAAccion::Atacar:    cpu->atacar();           break;
    case IAAccion::Defender:  cpu->defender();         break;
    case IAAccion::Saltar:    cpu->saltar();           break;
    case IAAccion::Especial:  cpu->usarEspecial(jugador); break;
    default: /* Ninguna */;                            break;
    }
    --iaFramesLeft;
}
