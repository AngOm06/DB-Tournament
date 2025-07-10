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
        void registraGanador(Personaje* ganador);
        Personaje* getCampeon() const;
        const std::vector<Personaje*>& getGanadores() const;
        int getNumeroRonda() const { return rondaActual; }
        Personaje* getJugador() const { return _jugador; }
        std::pair<Personaje*, Personaje*> obtenerDueloJugador();
        std::vector<std::pair<Personaje*,Personaje*>> generarYObtenerDuelos();
    };

    #endif // TORNEO_H
