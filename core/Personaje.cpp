#include "Personaje.h"
#include <algorithm>    // std::min, std::max
#include <QDebug>

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
void Personaje::recibirDanio(int cantidad) {     // esquiva
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
int               Personaje::getVidaMax()     const { return vidaMax; }
int               Personaje::getVelocidadX()     const { return velocidadX; }
int               Personaje::getKi()       const { return kiActual; }
int               Personaje::getKiMax()     const { return kiMax; }
int               Personaje::getPosicionX()const { return posicionX; }
float             Personaje::getPosicionY()const { return posicionY; }
int               Personaje::getDanoBase() const { return danoBase; }
EstadoPersonaje   Personaje::getEstado()   const { return estado; }

// Acciones de movimiento y postura
void Personaje::moverIzquierda() {
    if (estado == EstadoPersonaje::ATURDIDO) return;
    if (estado != EstadoPersonaje::ATACANDO) {
        posicionX = std::max(MIN_X, posicionX - velocidadX);
        if (estado != EstadoPersonaje::SALTANDO)
            estado = EstadoPersonaje::MOVIENDO;
    }
}

void Personaje::moverDerecha() {
    if (estado == EstadoPersonaje::ATURDIDO) return;
    if (estado != EstadoPersonaje::ATACANDO) {
        posicionX = std::min(MAX_X, posicionX + velocidadX);
        if (estado != EstadoPersonaje::SALTANDO)
            estado = EstadoPersonaje::MOVIENDO;
    }
}
void Personaje::detenerMovimiento() {
    if (estado == EstadoPersonaje::MOVIENDO)
        estado = EstadoPersonaje::IDLE;
}

// Salto con física simple
void Personaje::saltar() {
    // Permitir salto tanto si está IDLE como MOVIENDO
    if ((estado == EstadoPersonaje::IDLE || estado == EstadoPersonaje::MOVIENDO)
        && posicionY == 0.0f) {
        velocidadY = 20.0f;
        estado = EstadoPersonaje::SALTANDO;
    }
}

// Ataques básicos
void Personaje::atacar() {
    if (estado == EstadoPersonaje::IDLE)
        cambiarEstado(EstadoPersonaje::ATACANDO, FRAMES_ATACAR);
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
Personaje::Personaje(const Personaje& otro)
    : vidaMax(otro.vidaMax),
    vida(otro.vida),
    kiActual(otro.kiActual),
    kiMax(otro.kiMax),
    posicionX(otro.posicionX),
    posicionY(otro.posicionY),
    velocidadX(otro.velocidadX),
    velocidadY(otro.velocidadY),
    danoBase(otro.danoBase),
    estado(otro.estado),
    framesAccion(otro.framesAccion)
{
    nombre = copiarTexto(otro.nombre);
}
Personaje& Personaje::operator=(const Personaje& otro) {
    if (this != &otro) {
        delete[] nombre;
        nombre = copiarTexto(otro.nombre);

        vidaMax = otro.vidaMax;
        vida = otro.vida;
        kiActual = otro.kiActual;
        kiMax = otro.kiMax;
        posicionX = otro.posicionX;
        posicionY = otro.posicionY;
        velocidadX = otro.velocidadX;
        velocidadY = otro.velocidadY;
        danoBase = otro.danoBase;
        estado = otro.estado;
        framesAccion = otro.framesAccion;
    }
    return *this;
}
