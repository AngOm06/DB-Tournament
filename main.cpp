/*#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Personajes/Goku.h"
#include "Personajes/Krilin.h"
#include "Personajes/Yamcha.h"
#include "Personajes/JackieChun.h"
#include "Personajes/Bacterian.h"
#include "Personajes/Nam.h"
#include "Personajes/Ranfan.h"
#include "Personajes/Giran.h"
#include "Personajes/MonoGigante.h"

#include "Modos/Duelo1v1.h"
#include "Modos/Torneo.h"
#include "Modos/Bossfight.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // 1. Menú de modo de juego
    int modo = 0;
    std::cout << "=== Dragon Ball: Torneo del Gran Campeon ===\n";
    std::cout << "Seleccione modo de juego:\n";
    std::cout << "  1) Duelo 1v1\n";
    std::cout << "  2) Torneo\n";
    std::cout << "  3) Bossfight (DEBUG)\n";
    std::cout << "Opcion: ";
    std::cin >> modo;

    // 2. Roster de personajes jugables
    std::vector<Personaje*> roster;
    roster.push_back(new Goku());
    roster.push_back(new Krilin());
    roster.push_back(new Yamcha());
    roster.push_back(new JackieChun());
    roster.push_back(new Bacterian());
    roster.push_back(new Nam());
    roster.push_back(new Ranfan());
    roster.push_back(new Giran());

    // 3. Selección de personaje
    std::cout << "\nElige tu personaje:\n";
    for (size_t i = 0; i < roster.size(); ++i) {
        std::cout << "  " << (i + 1) << ") " << roster[i]->getNombre() << "\n";
    }
    std::cout << "Opcion (1-" << roster.size() << "): ";
    size_t opcion = 0;
    std::cin >> opcion;
    if (opcion < 1 || opcion > roster.size()) opcion = 1;

    Personaje* jugador = roster[opcion - 1];
    roster.erase(roster.begin() + (opcion - 1));

    // 4. Ejecutar el modo elegido
    if (modo == 1) {
        // --- DUELO 1v1 ---
        Personaje* cpu = roster.front();
        roster.erase(roster.begin());

        std::cout << "\n=== Duelo 1v1 ===\n";
        Duelo1v1 duelo(jugador, cpu);
        bool victoria = duelo.run();

        std::cout << "\n\n=== Resultado del Duelo ===\n";
        if (victoria)
            std::cout << jugador->getNombre() << " gana el combate!\n";
        else
            std::cout << cpu->getNombre() << " gana el combate!\n";

        delete jugador;
        delete cpu;
        for (Personaje* p : roster) delete p;

    } else if (modo == 2) {
        // --- TORNEO ---
        Torneo torneo(jugador, roster);
        Personaje* campeon = torneo.run();

        std::cout << "\n\n=== Resultado del Torneo ===\n";
        std::cout << "Campeon: " << campeon->getNombre() << "!\n";

        delete jugador;
        for (Personaje* p : roster) delete p;

    } else {
        // --- BOSSFIGHT (DEBUG) ---
        MonoGigante* jefe = new MonoGigante();
        Bossfight boss(jugador, jefe);
        bool victoria = boss.run();

        std::cout << "\n\n=== Resultado Bossfight ===\n";
        if (victoria)
            std::cout << "Victoria contra Oozaru!\n";
        else
            std::cout << "Derrota ante el jefe!\n";

        delete jugador;
        for (Personaje* p : roster) delete p;
    }

    return 0;
}*/
#include <QApplication>
#include "gui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}

