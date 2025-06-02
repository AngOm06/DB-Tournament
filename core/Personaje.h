#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Funciones.h"
#include <iostream>

class Personaje {
protected:
    char *nombre;      // C-string dinámico
    int vidaMax;
    int vidaActual;
    int kiMax;
    int kiActual;
    int ataque;
    int defensa;
    int velocidad;

public:
    // Constructor principal: clona el nombre con copiarTexto()
    Personaje(const char* nombre_,
              int vida, int ki,
              int atk, int def, int vel);

    // Destructor: libera la memoria de 'nombre'
    virtual ~Personaje();

    // Rule of Three:
    Personaje(const Personaje& otro);            // Constructor de copia
    Personaje& operator=(const Personaje& otro); // Operador de asignación

    // Métodos puros: obligan a que cada derivado implemente su propia lógica
    virtual void atacar(Personaje* objetivo) = 0;
    virtual void habilidadEspecial(Personaje* objetivo) = 0;

    // Métodos comunes
    void recibirDanio(int cantidad);
    void recuperarKi(int cantidad);
    void reiniciar();

    // Getters
    const char* getNombre() const;
    int getVida() const;
    int getKi() const;
    int getVelocidad() const;
    bool estaVivo() const;

    // Para depurar: imprime estado completo en consola
    void imprimirEstado() const;
};

#endif // PERSONAJE_H
