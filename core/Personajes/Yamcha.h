#ifndef YAMCHA_H
#define YAMCHA_H

#include "Personaje.h"

class Yamcha : public Personaje {
public:
    Yamcha();
    ~Yamcha() override = default;
    void usarEspecial(Personaje* objetivo) override;
};

#endif // YAMCHA_H
