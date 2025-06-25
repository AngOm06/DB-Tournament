#include "core/Goku.h"
#include <iostream>
<<<<<<< Updated upstream
#include <memory>

int main() {
    // Creamos dos instancias de Goku
    std::shared_ptr<Goku> goku  = std::make_shared<Goku>();
    std::shared_ptr<Goku> rival = std::make_shared<Goku>();

    // Imprimimos el estado inicial
    std::cout << goku->getNombre() << " creado con " << goku->getVida() << " puntos de vida.\n";

    // Goku ataca al rival con puño normal
    goku->atacar(rival.get());
    std::cout << "Vida del rival tras el golpe: " << rival->getVida() << "\n";

    // Goku lanza Kamehameha
    goku->habilidadEspecial(rival.get());
    std::cout << "Vida del rival tras Kamehameha: " << rival->getVida() << "\n";

=======
#include <cstdlib>     // std::rand(), std::srand()
#include <ctime>       // std::time()
#include <conio.h>     // _kbhit(), _getch()
#include <thread>
#include <chrono>
#include "IA.h"
#include "Goku.h"
#include "Krilin.h"
#include "Combate.h"

int main() {
    // Inicializar semilla para IA
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear jugador (Goku) y CPU (Krilin)
    Personaje* jugador = new Goku();
    Personaje* cpu     = new Krilin();

    std::cout << "Duelo 1v1: Goku vs Krilin\n";
    std::cout << "Controles jugador:\n"
              << "  a: izquierda   d: derecha   w: salto\n"
              << "  s: agacharse   j: ataque   k: defender\n"
              << "  l: especial q: salir\n\n";

    bool running = true;
    int tickCpu = 0;

    while (running && jugador->getVida() > 0 && cpu->getVida() > 0) {
        // --- Entrada jugador ---
        bool didCrouch = false;
        if (_kbhit()) {
            char c = _getch();
            switch (c) {
            case 'a': jugador->moverIzquierda();  break;
            case 'd': jugador->moverDerecha();    break;
            case 'w': jugador->saltar();          break;
            case 's':
                jugador->agacharse();
                didCrouch = true;
                break;
            case 'j': jugador->atacar();          break;
            case 'k': jugador->defender();        break;
            case 'l': jugador->usarEspecial(cpu);    break;
            case 'q': running = false;            break;
            default: break;
            }
        }
        if (!didCrouch && jugador->getEstado() == EstadoPersonaje::AGACHADO) {
            jugador->levantarse();
        }

        // --- Lógica CPU simple cada N ticks ---
        if (++tickCpu >= 10) {
            tickCpu = 0;
            ejecutarIA(cpu, jugador);
        }

        // --- Actualizar ambos personajes ---
        jugador->update();
        cpu->update();

        // --- Procesar colisiones y daño ---
        procesarColision(jugador, cpu);
        procesarColision(cpu, jugador);

        // --- Mostrar estados ---
        std::cout << "\r"
                  << "Goku: X=" << jugador->getPosicionX()
                  << " V=" << jugador->getVida()
                  << " K=" << jugador->getKi()
                  << " | Krilin: X=" << cpu->getPosicionX()
                  << " V=" << cpu->getVida()
                  << " K=" << cpu->getKi()
                  << "      ";
        std::cout.flush();

        // Ritmo de ejecución (~20 FPS)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "\n\nResultado:\n";
    if (jugador->getVida() > 0)
        std::cout << "Goku gana\n";
    else if (cpu->getVida() > 0)
        std::cout << "Krilin gana\n";
    else
        std::cout << "Empate.\n";

    delete jugador;
    delete cpu;
>>>>>>> Stashed changes
    return 0;
}
