#ifndef GOKU_H
#define GOKU_H

#include "Personaje.h"
#include <iostream>

class Goku : public Personaje {
public:
    Goku();
    ~Goku() override = default;

    void usarEspecial(Personaje* objetivo) override;
};

#endif // GOKU_H
