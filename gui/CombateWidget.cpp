#include "CombateWidget.h"
#include "ui_CombateWidget.h"
#include "core/Personaje.h"

#include <QPainter>
#include <QKeyEvent>

#include <QPixmap>
#include <QString>

CombateWidget::CombateWidget(Personaje* jugador, Personaje* oponente, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CombateWidget)
    , _jugador(jugador)
    , _oponente(oponente)
{
    ui->setupUi(this);
    this->setStyleSheet(R"(
/* ─── Contenedor general ──────────────────────────────────────────── */
QWidget#CombateWidget {
  background-color: transparent; /* el fondo general queda el del widget padre */
}

/* ─── Portrait y HUD container ────────────────────────────────────── */
/* Si envuelves portrait + barras + nombre en un QFrame con objectName frameHUDJugador / frameHUDOponente */
QFrame#frameHUDJugador,
QFrame#frameHUDOponente {
  background-color: black;
  border: 1px solid #333;
  border-radius: 5px;
  padding: 10px;
}

/* ─── Portrait ───────────────────────────────────────────────────── */
QLabel#labelPortadaJugador,
QLabel#labelPortadaOponente {
  background: white;
  border-radius: 10px;
}

/* ─── Nombre ───────────────────────────── */
QLabel#labelNombreJugador,
QLabel#labelNombreOponente {
  background: transparent;
  color: white;
  font: "Saiyan-sans";
  font-size: 20pt;
  margin-top: 3px;
  qproperty-alignment: 'AlignLeft';
}

/* ─── Barra de vida (verde) ───────────────────────────────────────── */
QProgressBar#barraVidaJugador,
QProgressBar#barraVidaOponente {
  background-color: #222222;    /* ligeramente más claro que negro */
  border: white;
  height: 30px;
  border-radius: 2px;
  margin: 0px 0;
}
QProgressBar#barraVidaJugador::chunk,
QProgressBar#barraVidaOponente::chunk {
  background-color: #2ECC71;    /* verde */
  border-radius: 2px;
}

/* ─── Barra de ki (amarillo) ─────────────────────────────────────── */
QProgressBar#barraKiJugador,
QProgressBar#barraKiOponente {
  background-color: #222222;
  border: none;
  height: 30px;
  border-radius: 2px;
  margin: 0px 0;
}
QProgressBar#barraKiJugador::chunk,
QProgressBar#barraKiOponente::chunk {
  background-color: #F1C40F;    /* amarillo */
  border-radius: 2px;
}
)");


    // Mostrar nombres
    ui->labelNombreJugador->setText(_jugador->getNombre());
    ui->labelNombreOponente->setText(_oponente->getNombre());

    // Mostrar portadas
    QPixmap portadaJugador(QString(":/portadas/assets/portadas/%1.png").arg(_jugador->getNombre()));
    QPixmap portadaOponente(QString(":/portadas/assets/portadas/%1.png").arg(_oponente->getNombre()));

    ui->labelPortadaJugador->setPixmap(portadaJugador.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->labelPortadaOponente->setPixmap(portadaOponente.scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Configurar barras
    ui->barraVidaJugador->setRange(0, _jugador->getVidaMax());
    ui->barraKiJugador->setRange(0, _jugador->getKiMax());
    ui->barraVidaOponente->setRange(0, _oponente->getVidaMax());
    ui->barraKiOponente->setRange(0, _oponente->getKiMax());
    ui->barraVidaJugador->setTextVisible(false);
    ui->barraKiJugador  ->setTextVisible(false);
    ui->barraVidaOponente->setTextVisible(false);
    ui->barraKiOponente  ->setTextVisible(false);

    duelo = new Duelo1v1(_jugador, _oponente);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CombateWidget::updateFrame);
    spriteJugador = QPixmap(QString(":/sprites/assets/sprites/%1/idle_0.png")
                                .arg(_jugador->getNombre()));
    spriteOponente = QPixmap(QString(":/sprites/assets/sprites/%1/idle_0.png")
                                 .arg(_oponente->getNombre()));
    spriteJugador = spriteJugador.scaled(spriteJugador.width()*3,
                                         spriteJugador.height()*3,
                                         Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);

    spriteOponente = spriteOponente.scaled(spriteOponente.width()*3,
                                           spriteOponente.height()*3,
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);
    timer->start(33); // 30 FPS aprox


    // Primer actualización visual
    actualizarHUD();
}


CombateWidget::~CombateWidget() {
    delete ui;
    delete duelo;
    delete _jugador;
    delete _oponente;
}

void CombateWidget::keyPressEvent(QKeyEvent* event) {
    char c = '\0';
    switch (event->key()) {
    case Qt::Key_A: c = 'a'; break;
    case Qt::Key_D: c = 'd'; break;
    case Qt::Key_W: c = 'w'; break;
    case Qt::Key_S: c = 's'; break;
    case Qt::Key_J: c = 'j'; break;
    case Qt::Key_K: c = 'k'; break;
    case Qt::Key_L: c = 'l'; break;
    case Qt::Key_Q: c = 'q'; break;
    default: break;
    }
    if (duelo && c) duelo->_ultimoInput = c;
}

void CombateWidget::keyReleaseEvent(QKeyEvent* event) {
    _keysPressed.remove(event->key());
}

void CombateWidget::updateFrame() {
    duelo->run();
    actualizarHUD();
    if (duelo->haTerminado()) {
        timer->stop();
        qDebug() << (duelo->ganoJugador() ? "¡Ganó el jugador!"
                                          : "¡Ganó el oponente!");
        close();  // o emitir señal para volver al menú
        return;
    }
    update();
}

void CombateWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    // Fondo
    QPixmap fondo(":/fondos/assets/fondos/fondo_combate.png");
    if (!fondo.isNull()) {
        painter.drawPixmap(rect(), fondo);
    } else {
        painter.fillRect(rect(), Qt::black);
    }

    // Base del suelo en pantalla (ajustala según necesites)
    int yBase = height() - 30;

    // Posición lógica de los personajes
    const int escalaX = 8; // ajusta este valor hasta que se vea bien
    int xJugador = _jugador->getPosicionX() * escalaX;
    int xOponente = _oponente->getPosicionX() * escalaX;
    int yJugador = _jugador->getPosicionY(); // si no existe, usa 0
    int yOponente = _oponente->getPosicionY();

    // Cargar sprites estáticos (más adelante vendrán animaciones)
    QString nombreJugador = _jugador->getNombre();
    QString nombreOponente = _oponente->getNombre();

    QPixmap spriteJugador(QString(":/sprites/assets/sprites/%1/idle_0.png").arg(nombreJugador));
    QPixmap spriteOponente(QString(":/sprites/assets/sprites/%1/idle_0.png").arg(nombreOponente));

    QPixmap spriteEscaladoJugador = spriteJugador.scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap spriteEscaladoOponente = spriteOponente.scaled(140, 140, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    painter.drawPixmap(xJugador, yBase - yJugador - spriteEscaladoJugador.height(), spriteEscaladoJugador);
    painter.drawPixmap(xOponente, yBase - yOponente - spriteEscaladoOponente.height(), spriteEscaladoOponente);
}


void CombateWidget::actualizarHUD() {
    if (!_jugador || !_oponente) return;

    ui->barraVidaJugador->setValue(_jugador->getVida());
    ui->barraKiJugador->setValue(_jugador->getKi());

    ui->barraVidaOponente->setValue(_oponente->getVida());
    ui->barraKiOponente->setValue(_oponente->getKi());
}
