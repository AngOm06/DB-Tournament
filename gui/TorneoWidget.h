#ifndef TORNEOWIDGET_H
#define TORNEOWIDGET_H

#include <QWidget>
#include "core/Modos/Torneo.h"
#include "CombateWidget.h"

namespace Ui {
class TorneoWidget;
}

class TorneoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TorneoWidget(Personaje* jugador, const std::vector<Personaje*>& oponentes, QWidget* parent = nullptr);
    ~TorneoWidget();

private slots:
    void onDuelosObtenidos();
    void iniciarSiguienteDuelo();
    void onCombateTerminado(bool ganoJugador);
    void on_btnSalir_clicked();

    void on_btnIniciar_clicked();

private:
    Ui::TorneoWidget *ui;
    Torneo torneo;
    std::vector<Personaje*> participantesOriginal;
    std::vector<std::pair<Personaje*,Personaje*>> duelosActuales;
    size_t indiceDuelo;
    // Helpers de UI
    void actualizarListaParticipantes();
    void actualizarFaseLabel();
    void mostrarProximoOponente();
    std::map<Personaje*, QFrame*> celdas;
};

#endif // TORNEOWIDGET_H
