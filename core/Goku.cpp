#include "Goku.h"
<<<<<<< Updated upstream
#include <iostream>

// Constructor: pasa el literal "Goku" a la clase base y fija atributos
Goku::Goku()
    : Personaje("Goku",  // nombre clonado con copiarTexto
                100,     // vidaMax
                50,      // kiMax
                15,      // ataque
                5,       // defensa
                10)      // velocidad
{
    // Nada adicional; Personaje ya reservó y copió "Goku"
}

// Ataca con puño normal: imprime mensaje y recupera Ki
void Goku::atacar(Personaje* objetivo) {
    if (!objetivo || !objetivo->estaVivo()) return;
    std::cout << getNombre() << " ataca con punio normal!\n";
    objetivo->recibirDanio(ataque);
    recuperarKi(5);
}

// Habilidad especial Kamehameha: requiere Ki >= 20, causa daño doble y consume Ki
void Goku::habilidadEspecial(Personaje* objetivo) {
    if (getKi() < 20 || !objetivo || !objetivo->estaVivo()) {
        std::cout << getNombre() << " no tiene suficiente Ki para Kamehameha.\n";
        return;
    }
    std::cout << getNombre() << " lanza Kamehameha!\n";
    objetivo->recibirDanio(ataque * 2);
    kiActual -= 20; // consume Ki
=======

Goku::Goku()
    : Personaje("Goku", /*vida*/100, /*kiIni*/50, /*velX*/3, /*danoBase*/4, /*kiMax*/50)
{}

// Kamehameha: daño 2× base y aturde 1 frame al rival
void Goku::usarEspecial(Personaje* objetivo) {
    if (!objetivo || !objetivo->getVida()>0) return;
    if (estado != EstadoPersonaje::IDLE) {
        std::cout << getNombre() << " está ocupado.\n";
        return;
    }
    if (kiActual < 50) {
        std::cout << getNombre() << " no tiene suficiente Ki.\n";
        return;
    }
    std::cout << getNombre() << " lanza Kamehameha!\n";
    cambiarEstado(EstadoPersonaje::USANDO_ESPECIAL, 5);
    objetivo->recibirDanio(danoBase * 4);
    objetivo->cambiarEstado(EstadoPersonaje::ATURDIDO, 10);
    kiActual -= 50;
>>>>>>> Stashed changes
}
