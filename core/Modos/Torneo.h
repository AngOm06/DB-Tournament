    #ifndef TORNEO_H
    #define TORNEO_H

    #include <vector>
    #include "Personaje.h"

    class Torneo {
    private:
        Personaje* _jugador;
        std::vector<Personaje*> participantes;
        std::vector<Personaje*> ganadores;
        std::vector<std::pair<Personaje*,Personaje*>> duelos;
        int rondaActual;

        void prepararDuelos();
    public:
        Torneo(Personaje* jugador, const std::vector<Personaje*>& listaParticipantes);
        ~Torneo() = default;

        void iniciar();
        bool hayMasDuelos() const;
        std::vector<std::pair<Personaje*,Personaje*>> obtenerDuelosRonda();
        void registraGanador(Personaje* ganador);
        Personaje* getCampeon() const;
        const std::vector<Personaje*>& getGanadores() const;
        int getNumeroRonda() const { return rondaActual; }
        Personaje* getJugador() const { return _jugador; }
        std::pair<Personaje*, Personaje*> obtenerDueloJugador();
    };

    #endif // TORNEO_H
