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

    // Definimos rangos de probabilidad:
    // - Si vida > 60%  → ataca 60%, defiende 20%, especial 20%
    // - Si vida 30–60% → ataca 40%, defiende 40%, especial 20%
    // - Si vida < 30%  → ataca 20%, defiende 60%, especial 20%

    int pAtaque = 0, pDefensa = 0;// pEspecial = 0;
    if (pctVida > 0.6f) {
        pAtaque  = 65;
        pDefensa = 30;
       // pEspecial = 5;
    } else if (pctVida > 0.3f) {
        pAtaque  = 45;
        pDefensa = 45;
      //  pEspecial = 10;
    } else {
        pAtaque  = 20;
        pDefensa = 60;
       // pEspecial = 20;
    }
    // Total debería ser 100: pAtaque + pDefensa + pEspecial == 100

    int roll = std::rand() % 100;
    if (roll < pAtaque) {
        cpu->atacar();
    } else if (roll < pAtaque + pDefensa) {
        cpu->defender();
    } else {
        cpu->usarEspecial(jugador);        // ahora recibe objetivo, ver abajo
    }
}
