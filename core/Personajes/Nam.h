#ifndef NAM_H
#define NAM_H

#include "Personaje.h"

class Nam : public Personaje {
public:
    Nam();
    ~Nam() override = default;
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new Nam(*this);
    }
};

#endif // NAM_H
