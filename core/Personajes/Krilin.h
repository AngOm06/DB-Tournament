#ifndef KRILIN_H
#define KRILIN_H

#include "Personaje.h"

class Krilin : public Personaje {
public:
    // Vida 80, Ki inicial 40, velocidad 5, daño base 10, Ki máximo 40
    Krilin();

    // Ataque especial "Taiyoken" que aturde al rival y causa daño moderado
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new Krilin(*this);
    }
};

#endif // KRILIN_H
