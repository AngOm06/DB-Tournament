#include "Personaje.h"

// Constructor principal: clona 'nombre_' usando copiarTexto()
Personaje::Personaje(const char* nombre_, int vida, int ki, int atk, int def, int vel)
    : vidaMax(vida),
    vidaActual(vida),
    kiMax(ki),
    kiActual(ki),
    ataque(atk),
    defensa(def),
    velocidad(vel)
{
    nombre = copiarTexto(nombre_);
}

// Destructor: libera el buffer creado por copiarTexto
Personaje::~Personaje() {
    delete[] nombre;
}

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
void Personaje::recuperarKi(int cantidad) {
    kiActual += cantidad;
    if (kiActual > kiMax) kiActual = kiMax;
}

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
}
