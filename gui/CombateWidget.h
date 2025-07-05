#ifndef COMBATEWIDGET_H
#define COMBATEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSet>
#include "core/Modos/Duelo1v1.h"

class Personaje;

namespace Ui {
class CombateWidget;
}

class CombateWidget : public QWidget {
    Q_OBJECT

public:
    explicit CombateWidget(Personaje* jugador, Personaje* oponente, QWidget* parent = nullptr);
    ~CombateWidget();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void actualizarHUD();

private slots:
    void updateFrame();  // llamada por el QTimer

private:
    Ui::CombateWidget *ui;

    QPixmap spriteJugador;
    QPixmap spriteOponente;
    int xJugador = 100;
    int xOponente = 600;
    int yBase    = 530;

    QTimer* _timer;
    QSet<int> _keysPressed;

    Personaje* _jugador;
    Personaje* _oponente;
    Duelo1v1* duelo = nullptr;
    QTimer* timer = nullptr;
};

#endif // COMBATEWIDGET_H
