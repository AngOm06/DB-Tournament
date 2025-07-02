#include "MonoGigante.h"
#include <iostream>

static constexpr int COOLDOWN_ESPECIAL = 20;
static constexpr int DURACION_VULNERABLE = 15;

MonoGigante::MonoGigante()
    : Personaje("Oozaru", /*vida*/120,/*velX*/0, /*danoBase*/6, /*kiMax*/0),
    cooldownEspecial(0), tiempoVulnerable(0)
{
    posicionX = 70; // siempre aparece a la derecha
}

void MonoGigante::usarEspecial(Personaje* objetivo) {
    if (cooldownEspecial > 0 || !objetivo || objetivo->getVida() <= 0) {
        return;
    }

    int ataque = std::rand() % 3; // 0: pisotón, 1: embestida, 2: cola

    switch (ataque) {
    case 0:
        std::cout << "\nOozaru usa Pisoton de area!\n";
        if (objetivo->getEstado() != EstadoPersonaje::SALTANDO)
            objetivo->recibirDanio(8);
        break;
    case 1:
        std::cout << "\nOozaru embiste con furia!\n";
        objetivo->recibirDanio(6);
        break;
    case 2:
        std::cout << "\nOozaru golpea con su cola!\n";
        if (objetivo->getEstado() != EstadoPersonaje::AGACHADO)
            objetivo->recibirDanio(7);
        break;
    }

    cooldownEspecial = COOLDOWN_ESPECIAL;
    tiempoVulnerable = DURACION_VULNERABLE;
    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, 5);
}

bool MonoGigante::estaVulnerable() const {
    return tiempoVulnerable > 0;
}

void MonoGigante::update() {
    if (cooldownEspecial > 0) --cooldownEspecial;
    if (tiempoVulnerable > 0) --tiempoVulnerable;

    // Solo actualiza cosas visuales o físicas si no está vulnerable
    if (!estaVulnerable()) {
        Personaje::update();  // Solo cuando no está vulnerable (opcional)
    }

    // IMPORTANTE: si se vuelve no-vulnerable, cambiar estado a IDLE
    if (tiempoVulnerable == 0 && estado == EstadoPersonaje::USANDO_ESPECIAL) {
        estado = EstadoPersonaje::IDLE;
    }
}
