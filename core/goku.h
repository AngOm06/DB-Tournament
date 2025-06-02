#ifndef GOKU_H
#define GOKU_H

#include "Personaje.h"

class Goku : public Personaje {
public:
    // Inicializa a Goku con los valores específicos (nombre, vida, ki, ataque, defensa, velocidad)
    Goku();

    virtual ~Goku() = default;

    // Sobrescribe los métodos puros de Personaje
    void atacar(Personaje* objetivo) override;
    void habilidadEspecial(Personaje* objetivo) override;
};

#endif // GOKU_H
