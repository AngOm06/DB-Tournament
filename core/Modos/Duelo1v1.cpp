#include "Duelo1v1.h"
#include "Util/Combate.h"
#include "IA.h"

Duelo1v1::Duelo1v1(Personaje* jugador, Personaje* oponente)
    : _jugador(jugador), _oponente(oponente)
{
    _jugador->reiniciarStats();
    _oponente->reiniciarStats();
    _jugador->setPosicionX(40);
    _oponente->setPosicionX(110);
    _jugador->setPosicionY(0.0f);
    _oponente->setPosicionY(0.0f);
}

Duelo1v1::~Duelo1v1() {}

void Duelo1v1::procesarIA() {
    if (_oponente->getEstado() == EstadoPersonaje::ATURDIDO) return;
    ejecutarIA(_oponente, _jugador);
}

void Duelo1v1::actualizarFrame() {
    _jugador->update();
    _oponente->update();
    procesarColision(_jugador, _oponente, _jugadorYaGolpeó);
    procesarColision(_oponente, _jugador, _oponenteYaGolpeó);
    if (_jugador->getEstado() != EstadoPersonaje::ATACANDO)
    {
        _jugadorYaGolpeó = false;
    }
    if (_oponente->getEstado() != EstadoPersonaje::ATACANDO)
    {
        _oponenteYaGolpeó = false;
    }
}


void Duelo1v1::procesarMultiEntrada(const QSet<int>& teclas) {
    if (_jugador->getEstado() == EstadoPersonaje::ATURDIDO)
        return;
    if (teclas.contains(Qt::Key_W) && _jugador->getPosicionY() == 0.0f) {
        _jugador->saltar();
    }
    if (teclas.contains(Qt::Key_A) && puedeMover(_jugador, _oponente, false)) {
        _jugador->moverIzquierda();
    }
    if (teclas.contains(Qt::Key_D) && puedeMover(_jugador, _oponente, true)) {
        _jugador->moverDerecha();
    }
    if (teclas.contains(Qt::Key_J)) _jugador->atacar();
    if (teclas.contains(Qt::Key_K)) _jugador->defender();
    if (teclas.contains(Qt::Key_L)) _jugador->usarEspecial(_oponente);

    if (teclas.contains(Qt::Key_Q)) {
        _jugador->cambiarEstado(EstadoPersonaje::IDLE, 0);
        _jugador->recibirDanio(_jugador->getVida());
    }
}
