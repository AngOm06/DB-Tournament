#include "TorneoWidget.h"
#include "ui_TorneoWidget.h"
#include "sonidos.h"
#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QGraphicsOpacityEffect>
#include <random>

TorneoWidget::TorneoWidget(Personaje* jugador, const std::vector<Personaje*>& oponentes, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TorneoWidget)
    , torneo(jugador, oponentes)
{
    ui->setupUi(this);
    torneo.iniciar();
    indiceDuelo = 0;
    onDuelosObtenidos();
}

TorneoWidget::~TorneoWidget()
{
    for (Personaje* p : torneo.getParticipantes()) {
        if (p) delete p;
    }
    delete ui;
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
            /*Personaje* perdedor = (ganador == p1 ? p2 : p1);
            delete perdedor;*/
        }
    }

    indiceDuelo = 0;
    actualizarFase();
}


void TorneoWidget::iniciarSiguienteDuelo()
{
    if (indiceDuelo >= duelosActuales.size()) return;

    Personaje* p1 = duelosActuales[indiceDuelo].first;
    Personaje* p2 = duelosActuales[indiceDuelo].second;

    this->hide();
    CombateWidget* combate = new CombateWidget(p1, p2,nullptr, ModoCombate::Torneo, false);
    combate->setAttribute(Qt::WA_DeleteOnClose);
    connect(combate, &CombateWidget::combateTerminado,
            this, &TorneoWidget::onCombateTerminado);
    connect(combate, &QObject::destroyed, this, [this]() {
        this->show();
    });
    combate->show();
}
void TorneoWidget::onCombateTerminado(bool ganoJugador)
{
    musica->stop();
    if(!ganoJugador){
        ui->stackedWidget->setCurrentWidget(ui->pagePerdedor);
        reproducirMusicaDerrota();
        return;
    }

    Personaje* p1 = duelosActuales[indiceDuelo].first;
    Personaje* p2 = duelosActuales[indiceDuelo].second;
    Personaje* ganador = nullptr;
    if (p1 == torneo.getJugador()) ganador = (ganoJugador ? p1 : p2);
    else if (p2 == torneo.getJugador()) ganador = (ganoJugador ? p2 : p1);
    torneo.registraGanador(ganador);
    ++indiceDuelo;
    /*Personaje* perdedor = (ganador == p1 ? p2 : p1);
    delete perdedor;*/

    if (indiceDuelo >= duelosActuales.size()) {
        if (torneo.hayMasDuelos()) {
            duelosActuales = torneo.generarYObtenerDuelos();
            indiceDuelo = 0;
            onDuelosObtenidos();
        } else {
            Personaje* campeon = torneo.getCampeon();
            if(campeon==torneo.getJugador()){
                ui->stackedWidget->setCurrentWidget(ui->pageGanador);
                reproducirMusicaVictoria();
                QPixmap portada(QString(":/portadas/assets/portadas/%1.png").arg(campeon->getNombre()));
                ui->labelPortadaGanador->setPixmap(portada.scaled(302, 242, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            }
        }
    }
}

void TorneoWidget::on_btnSalir_clicked(){close();}
void TorneoWidget::on_btnSalirTorneo_clicked(){close();}
void TorneoWidget::on_btnIniciar_clicked(){iniciarSiguienteDuelo();}

void TorneoWidget::actualizarFase()
{
    QString textoFase = QString("Fase %1").arg(torneo.getNumeroRonda() + 1);
    efectoTorneo.play();
    ui->labelFase->setText(textoFase);
    const std::vector<Personaje*>& participantes = torneo.getParticipantes();
    int ronda = torneo.getNumeroRonda();
    for (int i = 0; i < participantes.size(); ++i) {
        QString labelName = QString("label_%1_%2").arg(ronda).arg(i + 1);
        QLabel* label = findChild<QLabel*>(labelName);
        if (label) {
            QPixmap imagen(QString(":/portadas/assets/portadas/%1.png").arg(participantes[i]->getNombre()));
            label->setPixmap(imagen.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            label->setAlignment(Qt::AlignCenter);
        }
    }
}
