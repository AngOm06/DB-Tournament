    #include "Torneo.h"
    #include <random>
    #include <algorithm>

    Torneo::Torneo(Personaje* jugador, const std::vector<Personaje*>& listaParticipantes)
        : _jugador(jugador),
        participantes(listaParticipantes),
        rondaActual(0)
    {
        participantes = listaParticipantes;
        std::mt19937 rng(std::random_device{}());
        std::shuffle(participantes.begin(), participantes.end(), rng);
        participantes.insert(participantes.begin(), _jugador);
    }

    void Torneo::prepararDuelos() {
        duelos.clear();
        for (size_t i = 0; i + 1 < participantes.size(); i += 2) {
            duelos.emplace_back(participantes[i], participantes[i + 1]);
        }
    }

    void Torneo::iniciar() {
        rondaActual = 0;
        ganadores.clear();
    }

    bool Torneo::hayMasDuelos() const {
        return participantes.size() > 1;
    }

    void Torneo::registraGanador(Personaje* ganador) {
        ganadores.push_back(ganador);
        if (ganadores.size() == duelos.size()) {
            std::reverse(ganadores.begin(),ganadores.end());
            participantes = ganadores;
            ganadores.clear();
            rondaActual++;
        }
    }

    Personaje* Torneo::getCampeon() const {
        return !participantes.empty() ? participantes.front() : nullptr;
    }

    const std::vector<Personaje*>& Torneo::getGanadores() const {
        return ganadores;
    }

    std::pair<Personaje*, Personaje*> Torneo::obtenerDueloJugador() {
        for (auto& duelo : duelos) {
            if (duelo.first == _jugador || duelo.second == _jugador)
                return duelo;
        }
        return {nullptr, nullptr};
    }

    std::vector<std::pair<Personaje*,Personaje*>> Torneo::generarYObtenerDuelos() {
        prepararDuelos();
        return duelos;
    }
