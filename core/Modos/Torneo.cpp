#include "Torneo.h"

Torneo::Torneo(Personaje* jugador, const std::vector<Personaje*>& listaParticipantes)
    : _jugador(jugador),
    participantes(listaParticipantes),
    rondaActual(0)
{
    // Inserta al jugador al inicio del vector:
    participantes.insert(participantes.begin(), _jugador);
}

void Torneo::prepararDuelos() {
    duelos.clear();
    for (size_t i = 0; i + 1 < participantes.size(); i += 2) {
        duelos.emplace_back(participantes[i], participantes[i+1]);
    }
}

void Torneo::iniciar() {
    rondaActual = 0;
    ganadores.clear();
}

bool Torneo::hayMasDuelos() const {
    return participantes.size() > 1;
}

std::vector<std::pair<Personaje*,Personaje*>> Torneo::obtenerDuelosRonda() {
    // Prepara los duelos para la ronda actual
    prepararDuelos();
    // Devolver el vector de pares de combate
    return duelos;
}

void Torneo::registraGanador(Personaje* ganador) {
    ganadores.push_back(ganador);

    if (ganadores.size() == duelos.size()) {
        participantes = ganadores;
        ganadores.clear();
        duelos.clear();
        rondaActual++;
    }
}

Personaje* Torneo::getCampeon() const {
    return !participantes.empty() ? participantes.front() : nullptr;
}
