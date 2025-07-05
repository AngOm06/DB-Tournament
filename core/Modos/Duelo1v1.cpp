#include "Duelo1v1.h"
#include "Util/Combate.h"
#include "IA.h"

Duelo1v1::Duelo1v1(Personaje* jugador, Personaje* oponente)
    : _jugador(jugador), _oponente(oponente)
{
    _jugador->reiniciarStats();
    _oponente->reiniciarStats();
    _jugador->setPosicionX(40);
    _oponente->setPosicionX(60);
}

Duelo1v1::~Duelo1v1() {}

bool Duelo1v1::run()
{
    procesarInput(_ultimoInput);
    _ultimoInput = '\0';

    if (++_tickIA >= 5) {
        _tickIA = 0;
        procesarIA();
    }

    actualizarFrame();

    return _jugador->getVida() > 0;
}

void Duelo1v1::procesarInput(char c) {
    switch (c) {
    case 'a':
        if (puedeMover(_jugador, _oponente, false))
            _jugador->moverIzquierda();
        break;
    case 'd':
        if (puedeMover(_jugador, _oponente, true))
            _jugador->moverDerecha();
        break;
    case 'w': _jugador->saltar();          break;
    case 's': _jugador->agacharse();       break;
    case 'j': _jugador->atacar();          break;
    case 'k': _jugador->defender();        break;
    case 'l': _jugador->usarEspecial(_oponente); break;
    case 'q':
        _jugador->cambiarEstado(EstadoPersonaje::IDLE, 0);
        _oponente ->cambiarEstado(EstadoPersonaje::IDLE, 0);
        _jugador->recibirDanio(_jugador->getVida());
        break;
    default:
        if (_jugador->getEstado() == EstadoPersonaje::AGACHADO)
            _jugador->levantarse();
        break;
    }
}

void Duelo1v1::procesarIA() {
    ejecutarIA(_oponente, _jugador);
}

void Duelo1v1::actualizarFrame() {
    _jugador->update();
    _oponente->update();
    procesarColision(_jugador, _oponente);
    procesarColision(_oponente, _jugador);
}
