#include "Duelo1v1.h"
#include "Combate.h"
#include "IA.h"
#include <conio.h>     // _kbhit(), _getch()
#include <thread>
#include <chrono>

Duelo1v1::Duelo1v1(Personaje* jugador, Personaje* oponente)
    : _jugador(jugador), _oponente(oponente)
{}

Duelo1v1::~Duelo1v1() { /* no liberamos _jugador/_oponente */ }

bool Duelo1v1::run() {
    bool running = true;
    int tickIA = 0;

    while (running && _jugador->getVida() > 0 && _oponente->getVida() > 0) {
        procesarEntrada();

        if (++tickIA >= 10) {
            tickIA = 0;
            procesarIA();
        }

        actualizarFrame();

        // ~20 FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    return _jugador->getVida() > 0;
}

void Duelo1v1::procesarEntrada() {
    if (!_kbhit()) return;
    char c = _getch();

    switch (c) {
    case 'a': _jugador->moverIzquierda();  break;
    case 'd': _jugador->moverDerecha();    break;
    case 'w': _jugador->saltar();          break;
    case 's': _jugador->agacharse();       break;
    case 'j': _jugador->atacar();          break;
    case 'k': _jugador->defender();        break;
    case 'l': _jugador->usarEspecial(_oponente); break;
    case 'q':
        // salir inmediatamente
        _jugador->cambiarEstado(EstadoPersonaje::IDLE, 0);
        _oponente ->cambiarEstado(EstadoPersonaje::IDLE, 0);
        // forzamos fin de bucle
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
    // actualiza física y estados
    _jugador->update();
    _oponente->update();

    // procesar colisiones en ambos sentidos
    procesarColision(_jugador, _oponente);
    procesarColision(_oponente, _jugador);

    // ---- Imprime el estado en consola (como en main) ----
    std::cout << "\r"
              << _jugador->getNombre()
              << ": X=" << _jugador->getPosicionX()
              << " V=" << _jugador->getVida()
              << " K=" << _jugador->getKi()
              << " | "
              << _oponente->getNombre()
              << ": X=" << _oponente->getPosicionX()
              << " V=" << _oponente->getVida()
              << " K=" << _oponente->getKi()
              << "      ";
    std::cout.flush();
}
