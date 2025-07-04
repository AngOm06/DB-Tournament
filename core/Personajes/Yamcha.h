#ifndef YAMCHA_H
#define YAMCHA_H

#include "Personaje.h"

class Yamcha : public Personaje {
public:
    Yamcha();
    ~Yamcha() override = default;
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new Yamcha(*this);
    }
};

#endif // YAMCHA_H
