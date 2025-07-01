#ifndef TORNEO_H
#define TORNEO_H

#include <vector>
#include <cstdlib>      // std::rand()
#include "Personaje.h"
#include "Duelo1v1.h"

class Torneo {
public:
    Torneo(Personaje* jugador, const std::vector<Personaje*>& listaParticipantes);
    ~Torneo() = default;

    // Inicia el bracket y al final devuelve el campeón
    Personaje* run();

private:
    Personaje* _jugador;
    std::vector<Personaje*> participantes;
    std::vector<Duelo1v1> duelos;
    int rondaActual;

    void prepararDuelos();
    void avanzarRonda();
};

#endif // TORNEO_H
