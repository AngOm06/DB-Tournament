#include "Goku.h"
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
}
