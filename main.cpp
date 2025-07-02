/*#include <iostream>
#include <vector>
#include <cstdlib>   // std::srand, std::rand
#include <ctime>     // std::time

#include "Personajes/Goku.h"
#include "Personajes/Krilin.h"
#include "Personajes/Yamcha.h"
#include "Personajes/JackieChun.h"
#include "Personajes/Bacterian.h"
#include "Personajes/Nam.h"
#include "Personajes/Ranfan.h"
#include "Personajes/Giran.h"

#include "Modos/Torneo.h"

int main() {
    // 1) Semilla para IA y decisiones aleatorias
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 2) Crear roster completo de personajes
    std::vector<Personaje*> roster;
    roster.push_back(new Goku());
    roster.push_back(new Krilin());
    roster.push_back(new Yamcha());
    roster.push_back(new JackieChun());
    roster.push_back(new Bacterian());
    roster.push_back(new Nam());
    roster.push_back(new Ranfan());
    roster.push_back(new Giran());

    // 3) Mostrar menú de selección
    std::cout << "=== Dragon Ball: Torneo del Gran Campeon ===\n";
    std::cout << "Elige tu personaje:\n";
    for (size_t i = 0; i < roster.size(); ++i) {
        std::cout << "  " << (i+1) << ") " << roster[i]->getNombre() << "\n";
    }
    std::cout << "Opcion (1-8): ";
    size_t opcion = 0;
    std::cin >> opcion;
    if (opcion < 1 || opcion > roster.size()) opcion = 1;  // fallback

    // 4) Separar jugador y oponentes
    Personaje* jugador = roster[opcion - 1];
    roster.erase(roster.begin() + (opcion - 1));
    std::vector<Personaje*> oponentes = roster;  // ahora roster contiene solo CPUs

    // 5) Ejecutar el torneo de 3 rondas
    Torneo torneo(jugador, oponentes);
    Personaje* campeon = torneo.run();

    // 6) Mostrar resultado final
    std::cout << "\n\n=== Resultado del Torneo ===\n";
    std::cout << "Campeon: " << campeon->getNombre() << "!\n";

    // 7) Limpiar memoria
    // - Jugador
    delete jugador;
    // - Oponentes
    for (Personaje* p : oponentes) {
        delete p;
    }
    oponentes.clear();

    return 0;
}
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Personajes/Goku.h"
#include "Modos/Bossfight.h"
#include "Personajes/MonoGigante.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Crear jugador (Goku) y jefe (Oozaru)
    Personaje* jugador = new Goku();
    MonoGigante* jefe = new MonoGigante();

    // Iniciar bossfight
    Bossfight boss(jugador, jefe);
    bool victoria = boss.run();

    std::cout << "\n\n=== Resultado Bossfight ===\n";
    if (victoria) {
        std::cout << "Victoria contra Oozaru\n";
    } else {
        std::cout << "Derrota ante el jefe\n";
    }

    delete jugador;

    return 0;
}
