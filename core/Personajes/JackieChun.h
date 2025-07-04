#ifndef JACKIECHUN_H
#define JACKIECHUN_H

#include "Personaje.h"

class JackieChun : public Personaje {
public:
    JackieChun();
    ~JackieChun() override = default;
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new JackieChun(*this);
    }
};

#endif // JACKIECHUN_H
