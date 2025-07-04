#ifndef GIRAN_H
#define GIRAN_H

#include "Personaje.h"

class Giran : public Personaje {
public:
    Giran();
    ~Giran() override = default;
    void usarEspecial(Personaje* objetivo) override;
    Personaje* clone() const override {
        return new Giran(*this);
    }
};

#endif // GIRAN_H
