// CombateWidget.h
#ifndef COMBATEWIDGET_H
#define COMBATEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QSet>
#include <QStackedWidget>
#include "CountDownWidget.h"
#include "ResultadoWidget.h"
#include "core/Modos/Duelo1v1.h"

namespace Ui {
class CombateWidget;
}

class CombateWidget : public QWidget {
    Q_OBJECT
public:
    CombateWidget(Personaje* jugador, Personaje* oponente, QWidget *parent = nullptr);
    ~CombateWidget();

private slots:
    void iniciarCombate();
    void updateFrame();
    void reiniciarCombate();
    void mostrarResultado();
    void on_btnRevancha_clicked();
    void on_btnVolver_clicked();
    void on_countDownWidget_finished();

private:
    Ui::CombateWidget *ui;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

    // Lógica de combate
    Personaje *_jugador;
    Personaje *_oponente;
    Duelo1v1 *duelo;
    QTimer *timer;
    QSet<int> keysPressed;

    // Animación
    QMap<QString, QVector<QPixmap>> animJugador, animOponente;
    QString accionJugador = "idle", accionOponente = "idle";
    bool jugadorMiraDerecha = true, oponenteMiraDerecha = false;
    int frameJugador = 0, frameOponente = 0, cuentaFrames = 0;
    void actualizarHUD();
};

#endif // COMBATEWIDGET_H
