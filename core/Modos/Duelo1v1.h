#ifndef DUELO1V1_H
#define DUELO1V1_H

#include "Personaje.h"
#include <QSet>

class Duelo1v1 {
private:
    Personaje* _jugador;
    Personaje* _oponente;
    bool _jugadorYaGolpeó = false;
    bool _oponenteYaGolpeó = false;
    int _tickIA = 0;

public:
    Duelo1v1(Personaje* jugador, Personaje* oponente);
    ~Duelo1v1();

    void procesarIA();
    void actualizarFrame();
    void procesarMultiEntrada(const QSet<int>& teclas);

    Personaje* getJugador()  const { return _jugador; }
    Personaje* getOponente() const { return _oponente; }
    bool haTerminado() const {
        return _jugador->getVida() <= 0 || _oponente->getVida() <= 0;
    }
    bool ganoJugador() const {
        return _jugador->getVida() > 0 && _oponente->getVida() <= 0;
    }
};

#endif // DUELO1V1_H
