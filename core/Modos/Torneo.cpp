    #include "Torneo.h"
    #include <random>
    #include <algorithm>

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

        // Copiar todos los participantes excepto el jugador
        std::vector<Personaje*> pool;
        for (Personaje* p : participantes) {
            if (p != _jugador) {
                pool.push_back(p);
            }
        }

        // Mezclar los oponentes
        static std::mt19937 rng(std::random_device{}());
        std::shuffle(pool.begin(), pool.end(), rng);

        // Insertar al jugador en una posición aleatoria
        std::uniform_int_distribution<int> dist(0, static_cast<int>(pool.size()));
        int pos = dist(rng);
        pool.insert(pool.begin() + pos, _jugador);

        // Formar duelos de 2 en 2
        for (size_t i = 0; i + 1 < pool.size(); i += 2) {
            duelos.emplace_back(pool[i], pool[i + 1]);
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
        return {nullptr, nullptr}; // No hay duelo del jugador (puede ser error)
    }
