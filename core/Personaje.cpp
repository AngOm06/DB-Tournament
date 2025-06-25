#include "Personaje.h"

<<<<<<< Updated upstream
// Constructor principal: clona 'nombre_' usando copiarTexto()
Personaje::Personaje(const char* nombre_, int vida, int ki, int atk, int def, int vel)
    : vidaMax(vida),
    vidaActual(vida),
    kiMax(ki),
    kiActual(ki),
    ataque(atk),
    defensa(def),
    velocidad(vel)
=======
// Constructor: clona nombre, inicializa stats y posición
Personaje::Personaje(const char* nombre_, int vidaInicial, int kiInicial,
                     int velX, int danoBase_, int kiMaximo)
    : vida(vidaInicial), kiActual(kiInicial), kiMax(kiMaximo),
    posicionX(0), posicionY(0.0f),
    velocidadX(velX), velocidadY(0.0f), danoBase(danoBase_),
    estado(EstadoPersonaje::IDLE), framesAccion(0)
>>>>>>> Stashed changes
{
    nombre = copiarTexto(nombre_);
}

<<<<<<< Updated upstream
// Destructor: libera el buffer creado por copiarTexto
=======
// Destructor: libera nombre
>>>>>>> Stashed changes
Personaje::~Personaje() {
    delete[] nombre;
}

<<<<<<< Updated upstream
// Constructor de copia: clona todos los atributos escalares y el C-string
Personaje::Personaje(const Personaje& otro)
    : vidaMax(otro.vidaMax),
    vidaActual(otro.vidaActual),
    kiMax(otro.kiMax),
    kiActual(otro.kiActual),
    ataque(otro.ataque),
    defensa(otro.defensa),
    velocidad(otro.velocidad)
{
    nombre = copiarTexto(otro.nombre);
}

// Operador de asignación: libera el viejo buffer y clona el de 'otro'
Personaje& Personaje::operator=(const Personaje& otro) {
    if (this == &otro) return *this; // auto-asignación

    delete[] nombre; // libera buffer anterior

    vidaMax    = otro.vidaMax;
    vidaActual = otro.vidaActual;
    kiMax      = otro.kiMax;
    kiActual   = otro.kiActual;
    ataque     = otro.ataque;
    defensa    = otro.defensa;
    velocidad  = otro.velocidad;

    nombre = copiarTexto(otro.nombre);
    return *this;
}

// Resta la defensa al daño recibido y actualiza vidaActual
void Personaje::recibirDanio(int cantidad) {
    int danio = cantidad - defensa;
    if (danio < 0) danio = 0;
    vidaActual -= danio;
    if (vidaActual < 0) vidaActual = 0;
}

// Suma Ki hasta el máximo permitido
=======
// Métodos de combate
void Personaje::recibirDanio(int cantidad) {
    // Si está agachado y es un ataque normal (no bajo ni especial), lo esquiva
    if (estado == EstadoPersonaje::AGACHADO) {
        return;
    }
    int danio = cantidad;
    if (estado == EstadoPersonaje::DEFENDIENDO) {
        danio /= 2;
    }
    vida -= danio;
    if (vida < 0) vida = 0;
}

>>>>>>> Stashed changes
void Personaje::recuperarKi(int cantidad) {
    kiActual += cantidad;
    if (kiActual > kiMax) kiActual = kiMax;
}

<<<<<<< Updated upstream
// Reinicia vida y Ki a sus valores máximos
void Personaje::reiniciar() {
    vidaActual = vidaMax;
    kiActual   = kiMax;
}

// Devuelve el C-string del nombre
const char* Personaje::getNombre() const {
    return nombre;
}

// Devuelve la vida actual
int Personaje::getVida() const {
    return vidaActual;
}

// Devuelve el Ki actual
int Personaje::getKi() const {
    return kiActual;
}

// Devuelve la velocidad
int Personaje::getVelocidad() const {
    return velocidad;
}

// Indica si el personaje sigue vivo (vidaActual > 0)
bool Personaje::estaVivo() const {
    return vidaActual > 0;
}

// Imprime todos los atributos en consola (depuración)
void Personaje::imprimirEstado() const {
    std::cout << nombre
              << " | Vida: "  << vidaActual << "/" << vidaMax
              << " | Ki: "    << kiActual   << "/" << kiMax
              << " | Atk: "   << ataque
              << " | Def: "   << defensa
              << " | Vel: "   << velocidad
              << "\n";
=======
// Getters
const char* Personaje::getNombre() const { return nombre; }
int Personaje::getVida()        const { return vida; }
int Personaje::getKi()          const { return kiActual; }
int Personaje::getPosicionX()   const { return posicionX; }
int Personaje::getDanoBase()   const { return danoBase; }
float Personaje::getPosicionY() const { return posicionY; }
EstadoPersonaje Personaje::getEstado() const { return estado; }

// Movimiento horizontal
void Personaje::moverIzquierda() {
    if (estado == EstadoPersonaje::IDLE) {
        posicionX = max(MIN_X, posicionX - velocidadX);
        estado = EstadoPersonaje::MOVIENDO;
    }
}

void Personaje::moverDerecha() {
    if (estado == EstadoPersonaje::IDLE) {
        posicionX = min(MAX_X, posicionX + velocidadX);
        estado = EstadoPersonaje::MOVIENDO;
    }
}

void Personaje::detenerMovimiento() {
    if (estado == EstadoPersonaje::MOVIENDO)
        estado = EstadoPersonaje::IDLE;
}

// Salto vertical con física simple
void Personaje::saltar() {
    if (estado == EstadoPersonaje::IDLE && posicionY == 0.0f) {
        velocidadY = 10.0f;
        estado = EstadoPersonaje::SALTANDO;
    }
}

// Agacharse: evita daño de ataques normales
void Personaje::agacharse() {
    if (estado == EstadoPersonaje::IDLE) {
        cambiarEstado(EstadoPersonaje::AGACHADO, /*duración indefinida*/ 0);
    }
}

// Levantarse: vuelve a idle si estaba agachado
void Personaje::levantarse() {
    if (estado == EstadoPersonaje::AGACHADO) {
        estado = EstadoPersonaje::IDLE;
    }
}


// Ataque
void Personaje::atacar() {
    if (estado == EstadoPersonaje::IDLE) {
        cambiarEstado(EstadoPersonaje::ATACANDO, FRAMES_ATACAR);
    }
    else if (estado == EstadoPersonaje::AGACHADO) {
        // al atacar agachado, dispara el ataque bajo
        atacarBajo();
    }
}

void Personaje::atacarBajo() {
    if (estado == EstadoPersonaje::IDLE) {
        cambiarEstado(EstadoPersonaje::ATACANDO_BAJO, FRAMES_ATAQUE_BAJO);
    }
}

void Personaje::defender() {
    if (estado == EstadoPersonaje::IDLE) {
        cambiarEstado(EstadoPersonaje::DEFENDIENDO, FRAMES_DEFENDER);
    }
}

// Transición de estados internos
void Personaje::cambiarEstado(EstadoPersonaje nuevoEstado, int duracionFrames) {
    estado = nuevoEstado;
    framesAccion = duracionFrames;
}

// Update por frame
void Personaje::update() {
    // Gestión de duración de estados bloqueados
    if (framesAccion > 0) {
        framesAccion--;
        if (framesAccion == 0 && estado != EstadoPersonaje::SALTANDO) {
            estado = EstadoPersonaje::IDLE;
        }
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
    // Terminación automática de movimiento
    if (estado == EstadoPersonaje::MOVIENDO) {
        estado = EstadoPersonaje::IDLE;
    }
>>>>>>> Stashed changes
}
