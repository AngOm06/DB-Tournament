#ifndef FUNCIONES_H
#define FUNCIONES_H

// Funciones para operar con C-strings (char*), sin dependencias externas

// Copia un C-string dinámicamente.
// Devuelve un nuevo buffer en heap con la misma cadena.
char* copiarTexto(const char* fuente);

// Compara dos C-strings; devuelve true si son idénticos (misma longitud y caracteres).
bool sonIguales(const char* a, const char* b);

// Devuelve true si 'texto' comienza con 'prefijo'.
bool iniciaCon(const char* texto, const char* prefijo);

int min(int a, int b);
int max(int a, int b);

#endif // FUNCIONES_H
