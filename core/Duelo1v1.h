#ifndef DUELO1V1_H
#define DUELO1V1_H

#include "Personaje.h"

// Clase que ejecuta un combate 1 vs 1 entre dos Personaje*
// hasta que uno de los dos agota su vida.
class Duelo1v1 {
public:
    // Recibe dos punteros a Personaje (jugador y oponente IA)
    Duelo1v1(Personaje* jugador, Personaje* oponente);
    ~Duelo1v1();

    // Lanza el loop de combate; devuelve true si gana el jugador
    bool run();

private:
    Personaje* _jugador;
    Personaje* _oponente;

    // Procesa la entrada del jugador (mover, salto, ataque, etc.)
    void procesarEntrada();

    // Ejecuta la IA del oponente
    void procesarIA();

    // Actualiza física, estados y colisiones
    void actualizarFrame();
};

#endif // DUELO1V1_H
