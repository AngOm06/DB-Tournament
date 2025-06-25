#include "Krilin.h"

Krilin::Krilin()
    : Personaje("Krilin",/*vidaInicial=*/80,/*kiInicial=*/40,/*velX=*/5,/*danoBase=*/4,/*kiMaximo=*/40)
{
    std::cout << "[LOG] Krilin creado: vida=" << getVida()
    << ", ki=" << getKi() << std::endl;
}

void Krilin::usarEspecial(Personaje* objetivo) {
    if (!objetivo || objetivo->getVida() <= 0) {
        std::cout << getNombre() << " no tiene objetivo válido.\n";
        return;
    }
    if (kiActual < 15) {
        std::cout << getNombre() << " no tiene suficiente Ki para Taiyoken.\n";
        return;
    }

    std::cout << getNombre() << " lanza Taiyoken!\n";
    // Bloquea su propia acción durante 2 frames
    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, 5);

    // Causa daño base * 3
    objetivo->recibirDanio(danoBase * 3);

    // Aturde al objetivo 1 frame
    objetivo->cambiarEstado(EstadoPersonaje::ATURDIDO, 20);

    // Consume Ki
    kiActual -= 40;
}
