#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Util/Funciones.h"
#include <iostream>

// Constantes de escenario y mecánicas
static constexpr int MAX_X = 150;
static constexpr int MIN_X = 0;
static constexpr int ALCANCE_ATAQUE = 16;
static constexpr int ALCANCE_ESPECIAL = 80;
static constexpr int FRAMES_ATACAR = 8;
static constexpr int FRAMES_DEFENDER = 5;
static constexpr int FRAMES_ESPECIAL = 20;
static constexpr float GRAVEDAD = 2.0f;    // unidades de velocidad vertical por frame

// Estados posibles del personaje en el combate
enum class EstadoPersonaje {
    IDLE,
    MOVIENDO,
    SALTANDO,
    ATACANDO,
    DEFENDIENDO,
    USANDO_ESPECIAL,
    ATURDIDO
};

class Personaje {
protected:
    char* nombre;           // Nombre en C-string dinámico
    int vidaMax;            // Vida inicial del personaje
    int vida;               // Puntos de vida actuales
    int kiActual;           // Energía para ataques especiales
    int kiMax;              // Energía máxima para especiales
    int posicionX;          // nueva: posición X donde reaparece
    float posicionY;        // nueva: altura de aparición (normalmente 0)
    int velocidadX;         // Velocidad de desplazamiento horizontal
    float velocidadY;       // Velocidad vertical (para salto)
    int danoBase;           // Daño base de ataques normales

    EstadoPersonaje estado; // Estado actual
    int framesAccion;       // Ciclos restantes en estado bloqueado

public:
    // Constructor principal: clona nombre y configura stats
    Personaje(const char* nombre_, int vidaInicial,
              int velX, int danoBase, int kiMaximo);
    Personaje(const Personaje& otro);
    Personaje& operator=(const Personaje& otro);

    virtual ~Personaje();

    // Métodos de combate
    void recibirDanio(int cantidad);
    void recuperarKi(int cantidad);

    // Getters esenciales
    const char* getNombre() const;
    int getVida() const;
    int getKi() const;
    int getVidaMax() const;
    int getKiMax() const;
    int getPosicionX() const;
    int getVelocidadX() const;
    int getDanoBase() const;
    float getPosicionY() const;
    EstadoPersonaje getEstado() const;
    void reiniciarStats();
    void setPosicionX(int x) { posicionX = x; }
    void setPosicionY(int y) { posicionY = y; }

    // Acciones básicas
    void moverIzquierda();
    void moverDerecha();
    void detenerMovimiento();
    void saltar();
    void atacar();
    void defender();

    // Cada subclase define su propio ataque especial
    virtual void usarEspecial(Personaje* objetivo) = 0;

    // Update por frame: física y transición de estados
    virtual void update();
    // Cambia el estado y fija duración en frames
    void cambiarEstado(EstadoPersonaje nuevoEstado, int duracionFrames);
    virtual Personaje* clone() const = 0;

};
#endif // PERSONAJE_H
