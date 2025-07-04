#ifndef GOKU_H
#define GOKU_H

#include "Personaje.h"

class Goku : public Personaje {
public:
    // Inicializa a Goku con los valores específicos (nombre, vida, ki, ataque, defensa, velocidad)
    Goku();

    virtual ~Goku() = default;

    // Sobrescribe los métodos puros de Personaje
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new Goku(*this);
    }
};

#endif // GOKU_H
