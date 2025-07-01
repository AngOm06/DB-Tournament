#include "Torneo.h"
#include <iostream>

Torneo::Torneo(Personaje* jugador, const std::vector<Personaje*>& listaParticipantes)
    : _jugador(jugador),
    participantes(listaParticipantes),
    rondaActual(0)
{}

void Torneo::prepararDuelos() {
    duelos.clear();
    for (size_t i = 0; i + 1 < participantes.size(); i += 2) {
        duelos.emplace_back(participantes[i], participantes[i+1]);
    }
}

Personaje* Torneo::run() {
    std::cout << "=== Torneo iniciado ===\n";
    while (participantes.size() > 1) {
        avanzarRonda();
    }
    return participantes.front();  // el campeón
}

void Torneo::avanzarRonda() {
    std::cout << "\n--- Ronda " << (rondaActual + 1) << " ---\n";

    prepararDuelos();
    std::vector<Personaje*> ganadores;
    ganadores.reserve(duelos.size());

    for (auto& duelo : duelos) {
        Personaje* p1 = duelo.getJugador();
        Personaje* p2 = duelo.getOponente();
        Personaje* ganador = nullptr;

        // ¿Está el jugador en este duelo?
        if (p1 == _jugador || p2 == _jugador) {
            bool ganaPrimero = duelo.run();
            ganador = ganaPrimero ? p1 : p2;
        } else {
            // CPU vs CPU → resolución aleatoria
            ganador = (std::rand() % 2 == 0) ? p1 : p2;
            std::cout << "\n[CPU duelo] " << p1->getNombre()
                      << " vs " << p2->getNombre()
                      << ": Ganador aleatorio: " << ganador->getNombre() << "\n";
        }

        ganadores.push_back(ganador);
    }

    participantes = std::move(ganadores);
    rondaActual++;
}
