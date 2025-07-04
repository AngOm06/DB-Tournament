#include "Personaje.h"
#include <algorithm>    // std::min, std::max

// Constructor: clona nombre y configura atributos iniciales
Personaje::Personaje(const char* nombre_, int vidaInicial,
                     int velX, int danoBase_, int kiMaximo)
    : nombre(copiarTexto(nombre_)),
    vidaMax(vidaInicial),
    vida(vidaInicial),
    kiActual(0),
    kiMax(kiMaximo),
    posicionX(0),
    posicionY(0.0f),
    velocidadX(velX),
    velocidadY(0.0f),
    danoBase(danoBase_),
    estado(EstadoPersonaje::IDLE),
    framesAccion(0)
{
}

// Destructor: libera el buffer de nombre
Personaje::~Personaje() {
    delete[] nombre;
}

// Recibe daño, teniendo en cuenta estado de agachado o defendiendo
void Personaje::recibirDanio(int cantidad) {
    if (estado == EstadoPersonaje::AGACHADO) return;           // esquiva
    int danio = cantidad;
    if (estado == EstadoPersonaje::DEFENDIENDO) danio /= 2;    // mitiga
    vida = std::max(0, vida - danio);
}

// Recupera Ki, sin exceder el máximo ni bajar de cero
void Personaje::recuperarKi(int cantidad) {
    kiActual = std::clamp(kiActual + cantidad, 0, kiMax);
}

// Getters
const char*       Personaje::getNombre()   const { return nombre; }
int               Personaje::getVida()     const { return vida; }
int               Personaje::getVelocidadX()     const { return velocidadX; }
int               Personaje::getKi()       const { return kiActual; }
int               Personaje::getPosicionX()const { return posicionX; }
float             Personaje::getPosicionY()const { return posicionY; }
int               Personaje::getDanoBase() const { return danoBase; }
EstadoPersonaje   Personaje::getEstado()   const { return estado; }

// Acciones de movimiento y postura
void Personaje::agacharse() {
    if (estado == EstadoPersonaje::IDLE)
        estado = EstadoPersonaje::AGACHADO;
}
void Personaje::levantarse() {
    if (estado == EstadoPersonaje::AGACHADO)
        estado = EstadoPersonaje::IDLE;
}
void Personaje::moverIzquierda() {
    if (estado == EstadoPersonaje::IDLE) {
        // posX nunca baja de MIN_X
        posicionX = max(MIN_X, posicionX - velocidadX);
        estado = EstadoPersonaje::MOVIENDO;
    }
}

void Personaje::moverDerecha() {
    if (estado == EstadoPersonaje::IDLE) {
        // posX nunca sube de MAX_X
        posicionX = min(MAX_X, posicionX + velocidadX);
        estado = EstadoPersonaje::MOVIENDO;
    }
}
void Personaje::detenerMovimiento() {
    if (estado == EstadoPersonaje::MOVIENDO)
        estado = EstadoPersonaje::IDLE;
}

// Salto con física simple
void Personaje::saltar() {
    if (estado == EstadoPersonaje::IDLE && posicionY == 0.0f) {
        velocidadY = /* valor inicial de salto, p.ej. */ 10.0f;
        estado = EstadoPersonaje::SALTANDO;
    }
}

// Ataques básicos
void Personaje::atacar() {
    if (estado == EstadoPersonaje::IDLE)
        cambiarEstado(EstadoPersonaje::ATACANDO, FRAMES_ATACAR);
    else if (estado == EstadoPersonaje::AGACHADO)
        atacarBajo();
}
void Personaje::atacarBajo() {
    if (estado == EstadoPersonaje::IDLE)
        cambiarEstado(EstadoPersonaje::ATACANDO_BAJO, FRAMES_ATAQUE_BAJO);
}
void Personaje::defender() {
    if (estado == EstadoPersonaje::IDLE)
        cambiarEstado(EstadoPersonaje::DEFENDIENDO, FRAMES_DEFENDER);
}

// Cambio de estado y duración
void Personaje::cambiarEstado(EstadoPersonaje nuevoEstado, int duracionFrames) {
    estado = nuevoEstado;
    framesAccion = duracionFrames;
}

// Update por frame: gestiona estado, física de salto y reseteo de movimiento
void Personaje::update() {
    // Decrementa frames de acción bloqueada
    if (framesAccion > 0) {
        --framesAccion;
        if (framesAccion == 0 && estado != EstadoPersonaje::SALTANDO)
            estado = EstadoPersonaje::IDLE;
    }

    // Física de salto
    if (estado == EstadoPersonaje::SALTANDO) {
        posicionY += velocidadY;
        velocidadY -= GRAVEDAD;
        if (posicionY <= 0.0f) {
            posicionY = 0.0f;
            velocidadY = 0.0f;
            estado = EstadoPersonaje::IDLE;
        }
    }

    // Tras moverse, vuelve a IDLE
    if (estado == EstadoPersonaje::MOVIENDO)
        estado = EstadoPersonaje::IDLE;
}

void Personaje::reiniciarStats() {
    vida        = vidaMax;
    kiActual    = 0;
    estado      = EstadoPersonaje::IDLE;
    framesAccion = 0;
}
