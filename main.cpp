#include "core/Goku.h"
#include <iostream>
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

    return 0;
}
