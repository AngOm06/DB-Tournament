#include "CombateWidget.h"
#include "ui_CombateWidget.h"
#include "core/Personaje.h"
#include "sonidos.h"
#include <QPainter>
#include <QKeyEvent>
#include <QPixmap>
#include <QTransform>
#include <QFile>
#include <QVBoxLayout>


CombateWidget::CombateWidget(Personaje* jugador, Personaje* oponente, QWidget *parent, ModoCombate modo_, bool ownsCharacters)
    : QWidget(parent)
    , ui(new Ui::CombateWidget)
    , _jugador(jugador)
    , _oponente(oponente)
    , modo(modo_)
    ,ownsCharacters(ownsCharacters)
{
    ui->setupUi(this);
    ui->btnContinuar->hide();

    QFile f(":/qss/assets/qss/combate.qss");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        setStyleSheet(QString::fromUtf8(f.readAll()));
    }

    keysPressed.clear();

    ui->labelNombreJugador->setText(_jugador->getNombre());
    ui->labelNombreOponente->setText(_oponente->getNombre());
    QPixmap portadaJugador(QString(":/portadas/assets/portadas/%1.png").arg(_jugador->getNombre()));
    QPixmap portadaOponente(QString(":/portadas/assets/portadas/%1.png").arg(_oponente->getNombre()));
    ui->labelPortadaJugador->setPixmap(portadaJugador.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelPortadaOponente->setPixmap(portadaOponente.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->barraVidaJug->setRange(0, _jugador->getVidaMax());
    ui->barraKiJug->setRange(0, _jugador->getKiMax());
    ui->barraVidaOponent->setRange(0, _oponente->getVidaMax());
    ui->barraKiOponent->setRange(0, _oponente->getKiMax());
    ui->barraVidaJug->setTextVisible(false);
    ui->barraKiJug  ->setTextVisible(false);
    ui->barraVidaOponent->setTextVisible(false);
    ui->barraKiOponent  ->setTextVisible(false);

    _jugador->reiniciarStats();
    _oponente->reiniciarStats();
    actualizarHUD();

    // Inicializar el duelista y temporizador de frames
    duelo = new Duelo1v1(_jugador, _oponente);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CombateWidget::updateFrame);
    timer->setInterval(33);

    //Animaciones :
    auto cargar = [&](Personaje* p, QMap<QString, QVector<QPixmap>>& mapa){
        QString nombre = p->getNombre();
        for (auto accion : {"idle", "walk", "jump", "attack", "super","block"}) {
            QVector<QPixmap>& vec = mapa[accion];
            int idx = 0;
            while (true) {
                QString path = QString(":/sprites/assets/sprites/%1/%2_%3.png")
                .arg(nombre, accion).arg(idx);
                QPixmap img(path);
                if (img.isNull()) break;
                vec << img.scaled(140,140,Qt::KeepAspectRatio,Qt::SmoothTransformation);
                ++idx;
            }
        }
    };
    auto makeMirrors = [](QMap<QString, QVector<QPixmap>>& mapa) {
        QTransform flipH;
        flipH.scale(-1, 1);
        for (const QString& key : mapa.keys()) {
            QVector<QPixmap> espejados;
            for (const QPixmap& frame : mapa[key]) {
                espejados.push_back(frame.transformed(flipH));
            }
            mapa.insert(key + "_mir", espejados);
        }
    };
    cargar(_jugador,  animJugador);
    cargar(_oponente, animOponente);
    makeMirrors(animJugador);
    makeMirrors(animOponente);


    ui->stackedWidget->setCurrentIndex(0);
    ui->countDownWidget->start();
}

CombateWidget::~CombateWidget() {
    delete duelo;
    if (ownsCharacters) {
        delete _jugador;
        delete _oponente;
    }
    delete ui;
}

void CombateWidget::keyPressEvent(QKeyEvent* event) {
    // Registrar tecla presionada
    keysPressed.insert(event->key());
}

void CombateWidget::keyReleaseEvent(QKeyEvent* event) {
    // Quitar tecla al soltarla
    keysPressed.remove(event->key());
}

void CombateWidget::updateFrame() {
    if (ui->stackedWidget->currentIndex() != 1)
        return;
    int oldXJ = _jugador->getPosicionX();
    int oldXO = _oponente->getPosicionX();

    // Procesar entradas múltiples (movimiento/salto/ataque)
    duelo->procesarMultiEntrada(keysPressed);
    // IA del oponente y física/collisiones
    static int iaCounter = 0;
    const int IA_INTERVAL = 2;
    if (++iaCounter >= IA_INTERVAL) {
            iaCounter = 0;
            duelo->procesarIA();
        }
    duelo->actualizarFrame();
    actualizarHUD();

    QString vieja = accionJugador;

    auto estJ = _jugador->getEstado();
    if      (estJ == EstadoPersonaje::SALTANDO)     accionJugador = "jump";
    else if (estJ == EstadoPersonaje::ATACANDO)     accionJugador = "attack";
    else if (estJ == EstadoPersonaje::USANDO_ESPECIAL)    accionJugador = "super";
    else if (estJ == EstadoPersonaje::DEFENDIENDO)  accionJugador = "block";

    else if (_jugador->getPosicionX() != oldXJ) {
        accionJugador = "walk";
        jugadorMiraDerecha = (_jugador->getPosicionX() > oldXJ);
    }
    else accionJugador = "idle";
    if (accionJugador != vieja) {
        if (vieja == "walk") {
            efectoCorrer.stop();
        }
        // al entrar en “walk”, lanzar loop
        if (accionJugador == "walk") {
            efectoCorrer.play();
        }
        if (accionJugador == "attack")
            efectoAtaque.play();
        else if (accionJugador == "block")
            efectoBloqueo.play();
        else if (accionJugador == "jump")
            efectoSalto.play();
        else if (accionJugador == "super")
            efectoGolpe.play();
    }

    QString viejaO = accionOponente;
    auto estO = _oponente->getEstado();
    if      (estO == EstadoPersonaje::SALTANDO)           accionOponente = "jump";
    else if (estO == EstadoPersonaje::ATACANDO)           accionOponente = "attack";
    else if (estO == EstadoPersonaje::USANDO_ESPECIAL)    accionOponente = "super";
    else if (estO == EstadoPersonaje::DEFENDIENDO)     accionOponente = "block";
    else if (_oponente->getPosicionX() != oldXO) {
        accionOponente = "walk";
        oponenteMiraDerecha = (_oponente->getPosicionX() > oldXO);
    }
    else accionOponente = "idle";
    if (accionOponente != vieja) {
        if (vieja == "walk") {
            efectoCorrer.stop();
        }
        // al entrar en “walk”, lanzar loop
        if (accionOponente == "walk") {
            efectoCorrer.play();
        }
        if (accionOponente == "attack")
            efectoAtaque.play();
        else if (accionOponente == "block")
            efectoBloqueo.play();
        else if (accionOponente == "jump")
            efectoSalto.play();
        else if (accionOponente == "super")
            efectoGolpe.play();
    }


    // Avanzar frame de animación cada pocos ticks
    cuentaFrames = (cuentaFrames + 1) % 4;
    if (cuentaFrames == 0) {
        const auto& aniJ = animJugador.value(accionJugador);
        if (!aniJ.isEmpty()) {
            frameJugador = (frameJugador + 1) % aniJ.size();
        }
        const auto& aniO = animOponente.value(accionOponente);
        if (!aniO.isEmpty()) {
            frameOponente = (frameOponente + 1) % aniO.size();
        }
    }
    if (duelo->haTerminado()) {
            mostrarResultado();
            return;
        }
    update(); // repaint del widget
    }
void CombateWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    QPixmap fondo(":/fondos/assets/fondos/fondo_combate.png");
    if (!fondo.isNull()) {
        painter.drawPixmap(rect(), fondo);
    } else {
        painter.fillRect(rect(), Qt::black);
    }

    int yBase = height() - 30;
    const int escalaX = 5;

    int xJugador = _jugador->getPosicionX() * escalaX;
    int xOponente = _oponente->getPosicionX() * escalaX;
    int yJugador = _jugador->getPosicionY();
    int yOponente = _oponente->getPosicionY();

    QString accionJ = accionJugador + (jugadorMiraDerecha ? "" : "_mir");
    const auto& vecJ = animJugador.value(accionJ);
    if (!vecJ.isEmpty() && frameJugador < vecJ.size()) {
        const QPixmap& pm = vecJ[frameJugador];
        painter.drawPixmap(
            xJugador,
            yBase - yJugador - pm.height(),
            pm
            );
    }
    QString accionO = accionOponente + (oponenteMiraDerecha ? "" : "_mir");
    const auto& vecO = animOponente.value(accionO);
    if (!vecO.isEmpty() && frameOponente < vecO.size()) {
        const QPixmap& pm = vecO[frameOponente];
        painter.drawPixmap(
            xOponente,
            yBase - yOponente - pm.height(),
            pm
            );
    }
}


void CombateWidget::actualizarHUD() {
    if (!_jugador || !_oponente) return;
    ui->barraVidaJug->setValue(_jugador->getVida());
    ui->barraKiJug->setValue(_jugador->getKi());
    ui->barraVidaOponent->setValue(_oponente->getVida());
    ui->barraKiOponent->setValue(_oponente->getKi());
}

void CombateWidget::iniciarCombate() {
    ui->stackedWidget->setCurrentIndex(1);
    efectoCombate.play();
    QCoreApplication::processEvents();
    keysPressed.clear();
    _jugador->reiniciarStats();
    _oponente->reiniciarStats();
    actualizarHUD();
    QTimer::singleShot(0, this, [this]() {
        timer->start();
    });
}
void CombateWidget::mostrarResultado() {
    timer->stop();
    QString texto;

    if (_jugador->getVida() <= 0 && _oponente->getVida() <= 0) {
        texto = "Empate";
    } else if (duelo->ganoJugador()) {
        texto = _jugador->getNombre();
    } else {
        texto = _oponente->getNombre();
    }

    ui->labelResultado->setText(QStringLiteral("GANADOR: %1").arg(texto));

    if (modo == ModoCombate::Duelo) {
        ui->btnRevancha->show();
        ui->btnVolver->show();
        ui->btnContinuar->hide();
    } else { // Torneo
        ui->btnRevancha->hide();
        ui->btnVolver->hide();
        if (duelo->ganoJugador()) {
            ui->btnContinuar->show();
        } else {
            ui->btnContinuar->setText("Salir");
            ui->btnContinuar->show();
        }
    }
    ui->stackedWidget->setCurrentIndex(2);

}

void CombateWidget::reiniciarCombate() {
        delete duelo;
        duelo = new Duelo1v1(_jugador, _oponente);
        ui->stackedWidget->setCurrentIndex(0);
        keysPressed.clear();
        _jugador->reiniciarStats();
        _oponente->reiniciarStats();
        actualizarHUD();
        ui->countDownWidget->start();
}


void CombateWidget::on_btnRevancha_clicked()
{
    reiniciarCombate();
}


void CombateWidget::on_btnVolver_clicked()
{
    close();
}


void CombateWidget::on_countDownWidget_finished()
{
    iniciarCombate();
}


void CombateWidget::on_btnContinuar_clicked()
{
    if (duelo->ganoJugador()) {
        emit combateTerminado(true);
    } else {
        emit combateTerminado(false);
    }
    close();
}

