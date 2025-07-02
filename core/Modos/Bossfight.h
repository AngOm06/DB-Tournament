#ifndef BOSSFIGHT_H
#define BOSSFIGHT_H

#include "Personajes/MonoGigante.h"
#include "Personaje.h"

class Bossfight {
public:
    Bossfight(Personaje* jugador, MonoGigante* jefe);
    ~Bossfight();

    // Ejecuta la pelea; retorna true si el jugador gana
    bool run();

    // Devuelve la vida del jugador y jefe, útil para GUI
    int getVidaJugador() const;
    int getVidaJefe() const;
    int getTiempoRestante() const;

    // Permite ejecutar un paso de lógica (para GUI frame a frame)
    void tick(char input); // input = tecla, '\0' si nada

private:
    Personaje* _jugador;
    MonoGigante* _jefe;
    int _tiempoGlobal;

    void procesarInput(char c);
    void procesarIA();
    void actualizarEstado();
};

#endif // BOSSFIGHT_H
