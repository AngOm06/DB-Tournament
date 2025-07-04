#ifndef RANFAN_H
#define RANFAN_H

#include "Personaje.h"

class Ranfan : public Personaje {
public:
    Ranfan();
    ~Ranfan() override = default;
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new Ranfan(*this);
    }
};

#endif // RANFAN_H
