#ifndef RANFAN_H
#define RANFAN_H

#include "Personaje.h"

class Ranfan : public Personaje {
public:
    Ranfan();
    ~Ranfan() override = default;
    void usarEspecial(Personaje* objetivo) override;
};

#endif // RANFAN_H
