#include "Modos/Bossfight.h"
#include "Util/Combate.h"
#include <conio.h>
#include <thread>
#include <chrono>
#include "IA.h"

static constexpr int TIEMPO_MAXIMO = 1000;

Bossfight::Bossfight(Personaje* jugador, MonoGigante* jefe)
    : _jugador(jugador), _jefe(jefe), _tiempoGlobal(TIEMPO_MAXIMO)
{
    _jugador->reiniciarStats();
    _jugador->setPosicionX(20);
    _jefe->setPosicionX(80);
}

Bossfight::~Bossfight() {
    delete _jefe;
}
bool Bossfight::run() {
    std::cout << "\n=== Bossfight: Oozaru aparece! ===\n";

    while (_tiempoGlobal > 0 && _jugador->getVida() > 0 && _jefe->getVida() > 0) {
        char input = '\0';
        if (_kbhit()) input = _getch();
        tick(input);  // ahora sí enviamos la tecla
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // ~20 FPS
    }

    return _jugador->getVida() > 0 && _jefe->getVida() == 0;
}

void Bossfight::tick(char input) {
    procesarInput(input);
    procesarIA();
    actualizarEstado();
    --_tiempoGlobal;
}

void Bossfight::procesarInput(char c) {
    switch (c) {
    case 'a': _jugador->moverIzquierda(); break;
    case 'd': _jugador->moverDerecha();   break;
    case 'w': _jugador->saltar();         break;
    case 'j': _jugador->atacar();         break;
    case 'k': _jugador->defender();       break;
    case 'l': _jugador->usarEspecial(_jefe); break;
        break;
    }
}

void Bossfight::procesarIA() {
    ejecutarIAOozaru(_jefe, _jugador);
}

void Bossfight::actualizarEstado() {
    _jugador->update();
    procesarColision(_jugador, _jefe, _jugadorYaGolpeó);
    procesarColision(_jefe, _jugador, _jefeYaGolpeó);
    if (_jugador->getEstado() != EstadoPersonaje::ATACANDO)
    {
        _jugadorYaGolpeó = false;
    }
    if (_jefe->getEstado() != EstadoPersonaje::ATACANDO)
    {
        _jefeYaGolpeó = false;
    }_jugador->update();
    std::cout << "\r"
              << _jugador->getNombre()
              << ": X=" << _jugador->getPosicionX()
              << " V=" << _jugador->getVida()
              << " | Oozaru: X=" << _jefe->getPosicionX()
              << " V=" << _jefe->getVida()
              << " | Tiempo=" << _tiempoGlobal
              << (_jefe->estaVulnerable() ? " [VULNERABLE]" : "")
              << "     ";
    std::cout.flush();
}

int Bossfight::getVidaJugador() const {
    return _jugador->getVida();
}
int Bossfight::getVidaJefe() const {
    return _jefe->getVida();
}
int Bossfight::getTiempoRestante() const {
    return _tiempoGlobal;
}
