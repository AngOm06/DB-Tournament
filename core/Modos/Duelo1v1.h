#ifndef DUELO1V1_H
#define DUELO1V1_H

#include "Personaje.h"
#include <Qt>

class Duelo1v1 {
private:
    Personaje* _jugador;
    Personaje* _oponente;

    void procesarInput(char c);
    void procesarIA();
    void actualizarFrame();

    int   _tickIA       = 0;
public:
    Duelo1v1(Personaje* jugador, Personaje* oponente);
    ~Duelo1v1();

    bool run();
    Personaje* getJugador()  const { return _jugador; }
    Personaje* getOponente() const { return _oponente; }
    char  _ultimoInput = '\0';
    bool haTerminado() const {
        return _jugador->getVida() <= 0 || _oponente->getVida() <= 0;
    }
    bool ganoJugador() const {
        return _jugador->getVida() > 0 && _oponente->getVida() <= 0;
    }
};

#endif // DUELO1V1_H
