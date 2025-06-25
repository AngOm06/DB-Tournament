#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Funciones.h"
<<<<<<< Updated upstream
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
=======

// Constantes de escenario y mecánicas
static constexpr int MAX_X = 99;
static constexpr int MIN_X = 0;
static constexpr int ALCANCE_ATAQUE = 5;
static constexpr int FRAMES_ATACAR = 2;
static constexpr int FRAMES_ATAQUE_BAJO = 2;
static constexpr int FRAMES_DEFENDER = 2;
static constexpr float GRAVEDAD = 1.0f;    // unidades de velocidad vertical por frame

// Estados posibles del personaje en el combate
enum class EstadoPersonaje {
    IDLE,
    MOVIENDO,
    SALTANDO,
    ATACANDO,
    AGACHADO,
    ATACANDO_BAJO,
    DEFENDIENDO,
    USANDO_ESPECIAL,
    ATURDIDO
};

class Personaje {
protected:
    char* nombre;           // Nombre en C-string dinámico
    int vida;               // Puntos de vida actuales
    int kiActual;           // Energía para ataques especiales
    int kiMax;              // Energía máxima para especiales
    int posicionX;          // Posición horizontal (0..99)
    float posicionY;        // Altura sobre el suelo
    int velocidadX;         // Velocidad de desplazamiento horizontal
    float velocidadY;       // Velocidad vertical (para salto)
    int danoBase;           // Daño base de ataques normales

    EstadoPersonaje estado; // Estado actual
    int framesAccion;       // Ciclos restantes en estado bloqueado

public:
    // Constructor principal: clona nombre y configura stats
    Personaje(const char* nombre_, int vidaInicial, int kiInicial,
              int velX, int danoBase, int kiMaximo);

    virtual ~Personaje();

    // Métodos de combate
    void recibirDanio(int cantidad);
    void recuperarKi(int cantidad);

    // Getters esenciales
    const char* getNombre() const;
    int getVida() const;
    int getKi() const;
    int getPosicionX() const;
    int getDanoBase() const;
    float getPosicionY() const;
    EstadoPersonaje getEstado() const;

    // Acciones básicas
    void agacharse();
    void levantarse();
    void moverIzquierda();
    void moverDerecha();
    void detenerMovimiento();
    void saltar();
    void atacar();
    void atacarBajo();
    void defender();

    // Cada subclase define su propio ataque especial
    virtual void usarEspecial(Personaje* objetivo) = 0;

    // Update por frame: física y transición de estados
    virtual void update();
    // Cambia el estado y fija duración en frames
    void cambiarEstado(EstadoPersonaje nuevoEstado, int duracionFrames);
>>>>>>> Stashed changes
};

#endif // PERSONAJE_H
