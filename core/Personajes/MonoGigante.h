#ifndef MONOGIGANTE_H
#define MONOGIGANTE_H

#include "Personaje.h"

class MonoGigante : public Personaje {
private:
    int cooldownEspecial;
    int tiempoVulnerable;

public:
    MonoGigante();

    void usarEspecial(Personaje* objetivo) override;
    bool estaVulnerable() const;
    void update() override;
};

#endif // MONOGIGANTE_H
