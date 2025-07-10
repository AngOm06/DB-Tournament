#include "TorneoWidget.h"
#include "ui_TorneoWidget.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsOpacityEffect>
#include <random>


// Constructor
TorneoWidget::TorneoWidget(Personaje* jugador,
                           const std::vector<Personaje*>& oponentes,
                           QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TorneoWidget)
    , torneo(jugador, oponentes)
{
    ui->setupUi(this);

    participantesOriginal.reserve(1 + oponentes.size());
    participantesOriginal.push_back(jugador);
    for (auto* p : oponentes)
        participantesOriginal.push_back(p);
    torneo.iniciar();
    duelosActuales = torneo.generarYObtenerDuelos();
    indiceDuelo = 0;
    onDuelosObtenidos();
}

// Destructor
TorneoWidget::~TorneoWidget()
{
    delete ui;
}
void TorneoWidget::actualizarListaParticipantes()
{
    QGridLayout* layout = ui->layoutGaleriaTorneo;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* w = item->widget()) {
            w->deleteLater();
        }
        delete item;
    }

    const int columnas = 4;
    int fila = 0, col = 0;

    for (Personaje* p : participantesOriginal) {
        QFrame* celda = new QFrame;
        celda->setFrameShape(QFrame::StyledPanel);
        celda->setMinimumSize(120, 140);
        celda->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        QVBoxLayout* layoutInterno = new QVBoxLayout(celda);
        layoutInterno->setContentsMargins(4, 4, 4, 4);
        layoutInterno->setSpacing(6);

        QLabel* icono = new QLabel(celda);
        QPixmap imagen(QString(":/portadas/assets/portadas/%1.png").arg(p->getNombre()));
        icono->setFixedSize(100, 100);
        icono->setScaledContents(true);
        icono->setPixmap(imagen);
        icono->setAlignment(Qt::AlignCenter);
        layoutInterno->addWidget(icono, 0, Qt::AlignHCenter);

        QLabel* nombre = new QLabel(p->getNombre(), celda);
        nombre->setAlignment(Qt::AlignCenter);
        layoutInterno->addWidget(nombre);

        // Verifica si fue eliminado
        bool fueEliminado = std::find(torneo.getGanadores().begin(),
                                      torneo.getGanadores().end(),
                                      p) == torneo.getGanadores().end();

        if (fueEliminado) {
            // Aplica opacidad
            QGraphicsOpacityEffect* efecto = new QGraphicsOpacityEffect(celda);
            efecto->setOpacity(0.2);
            celda->setGraphicsEffect(efecto);
            nombre->setStyleSheet("color: gray;");
        }

        layout->addWidget(celda, fila, col);
        if (++col == columnas) {
            col = 0;
            ++fila;
        }
    }
}

void TorneoWidget::onDuelosObtenidos()
{
    duelosActuales.clear();

    std::vector<std::pair<Personaje*,Personaje*>> duelos = torneo.generarYObtenerDuelos();

    for (std::pair<Personaje*,Personaje*>& duelo : duelos) {
        Personaje* p1 = duelo.first;
        Personaje* p2 = duelo.second;
        if (p1 == torneo.getJugador() || p2 == torneo.getJugador()) {
            // Duelo del jugador
            duelosActuales.push_back(duelo);
        } else {
            // CPU vs CPU → resolver aleatoriamente
            std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<int> dist(0, 1);
            bool ganaP1 = (dist(rng) == 0);
            Personaje* ganador = ganaP1 ? p1 : p2;
            torneo.registraGanador(ganador);
        }
    }

    indiceDuelo = 0;
    actualizarListaParticipantes();
    actualizarFaseLabel();
    mostrarProximoOponente();
}


void TorneoWidget::iniciarSiguienteDuelo()
{
    if (indiceDuelo >= duelosActuales.size()) {
        return;
    }

    Personaje* p1 = duelosActuales[indiceDuelo].first;
    Personaje* p2 = duelosActuales[indiceDuelo].second;

    CombateWidget* combate = new CombateWidget(p1, p2, nullptr, ModoCombate::Torneo);
    connect(combate, &CombateWidget::combateTerminado,
            this, &TorneoWidget::onCombateTerminado);
    combate->show();
}
void TorneoWidget::onCombateTerminado(bool ganoJugador)
{
    if(!ganoJugador){
         ui->stackedWidget->setCurrentWidget(ui->pagePerdedor);;
    }
    Personaje* p1 = duelosActuales[indiceDuelo].first;
    Personaje* p2 = duelosActuales[indiceDuelo].second;
    Personaje* ganador = nullptr;
    if (p1 == torneo.getJugador()) {
        ganador = (ganoJugador ? p1 : p2);
    } else if (p2 == torneo.getJugador()) {
        ganador = (ganoJugador ? p2 : p1);
    }
    torneo.registraGanador(ganador);
    ++indiceDuelo;

    if (indiceDuelo >= duelosActuales.size()) {
        if (torneo.hayMasDuelos()) {
            duelosActuales = torneo.generarYObtenerDuelos();
            indiceDuelo = 0;
            onDuelosObtenidos();
        } else {
            Personaje* campeon = torneo.getCampeon();
            if(campeon==torneo.getJugador()){
                ui->stackedWidget->setCurrentWidget(ui->pageGanador);
                //ui->labelGanadorTitulo->setText();
            }
        }
    } else {
        mostrarProximoOponente();
    }

    actualizarListaParticipantes();
}

void TorneoWidget::on_btnSalir_clicked()
{
    close();
}
void TorneoWidget::on_btnIniciar_clicked()
{
    iniciarSiguienteDuelo();
}

void TorneoWidget::mostrarProximoOponente()
{
    if (indiceDuelo < duelosActuales.size()) {
        Personaje* oponente = duelosActuales[indiceDuelo].second;
        QString texto = QString("Próximo oponente: %1").arg(oponente->getNombre());
        ui->labelProximoOponente->setText(texto);
    } else {
        ui->labelProximoOponente->setText("No hay más oponentes");
    }
}

void TorneoWidget::actualizarFaseLabel()
{
    QString textoFase = QString("Fase %1").arg(torneo.getNumeroRonda() + 1);
    ui->labelFase->setText(textoFase);
}
