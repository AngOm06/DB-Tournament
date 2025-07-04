#ifndef BACTERIAN_H
#define BACTERIAN_H

#include "Personaje.h"

class Bacterian : public Personaje {
public:
    Bacterian();
    ~Bacterian() override = default;
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new Bacterian(*this);
    }
};

#endif // BACTERIAN_H
