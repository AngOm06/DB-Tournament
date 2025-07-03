#include "IA.h"
#include <cstdlib>  // std::rand
#include <cmath>    // std::abs

void ejecutarIA(Personaje* cpu, Personaje* jugador) {
    if (!cpu || !jugador) return;

    int xCpu = cpu->getPosicionX();
    int xJug = jugador->getPosicionX();
    int distancia = xJug - xCpu;
    int vidaCpu = cpu->getVida();
    int vidaMax = 100;  // si quieres, podrías exponer getVidaMax()

    // 1) Si está lejos: acércate
    if (std::abs(distancia) > ALCANCE_ATAQUE) {
        if (distancia > 0) cpu->moverDerecha();
        else              cpu->moverIzquierda();
        return;
    }

    // 2) Si está en rango, decide según % de vida
    float pctVida = static_cast<float>(vidaCpu) / vidaMax;

    int pAtaque = 0, pDefensa = 0;// pEspecial = 0;
    if (pctVida > 0.6f) {
        pAtaque  = 65;
        pDefensa = 30;

    } else if (pctVida > 0.3f) {
        pAtaque  = 45;
        pDefensa = 45;
    } else {
        pAtaque  = 20;
        pDefensa = 60;
    }

    int roll = std::rand() % 100;
    if (roll < pAtaque) {
        cpu->atacar();
    } else if (roll < pAtaque + pDefensa) {
        cpu->defender();
    } else {
        cpu->usarEspecial(jugador);        // ahora recibe objetivo, ver abajo
    }
}
void ejecutarIAOozaru(MonoGigante* jefe, Personaje* jugador) {
    if (!jefe || !jugador || jefe->estaVulnerable()) return;

    if (std::rand() % 20 == 0) {
        jefe->usarEspecial(jugador);
    }

    jefe->update();
}
