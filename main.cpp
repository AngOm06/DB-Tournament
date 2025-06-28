#include "Goku.h"
#include "Krilin.h"
#include "Duelo1v1.h"
//#include "Torneo.h"

#include <iostream>

int main() {
    std::cout << "Bienvenido a DB Tournament!\n\n";
    std::cout << "1. Combate rapido 1v1\n";
    std::cout << "2. Torneo \n";
    std::cout << "Seleccione una opcion: ";

    int opcion;
    std::cin >> opcion;

    if (opcion == 1) {
        // Combate simple entre Goku y Krilin
        Personaje* goku   = new Goku();
        Personaje* krilin = new Krilin();
        Duelo1v1 duelo(goku, krilin);
        bool gano = duelo.run();
        std::cout << (gano ? "\nGoku gana el duelo!\n" : "\nKrilin gana el duelo!\n");
        delete goku;
        delete krilin;
    }
    else if (opcion == 2) {
        //Torneo torneo;
        //torneo.iniciar();
    }
    else {
        std::cout << "Opción inválida.\n";
    }

    return 0;
}
