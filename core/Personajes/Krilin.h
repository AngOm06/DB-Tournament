#ifndef KRILIN_H
#define KRILIN_H

#include "Personaje.h"
#include <iostream>

class Krilin : public Personaje {
public:
    // Vida 80, Ki inicial 40, velocidad 5, daño base 10, Ki máximo 40
    Krilin();

    // Ataque especial "Taiyoken" que aturde al rival y causa daño moderado
    void usarEspecial(Personaje* objetivo) override;
};

#endif // KRILIN_H
