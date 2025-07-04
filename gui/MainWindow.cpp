#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "core/Modos/Duelo1v1.h"
#include "core/Modos/Torneo.h"

// Incluye aquí tus subclases
#include "core/Personajes/Goku.h"
#include "core/Personajes/Krilin.h"
#include "core/Personajes/Yamcha.h"
#include "core/Personajes/JackieChun.h"
#include "core/Personajes/Bacterian.h"
#include "core/Personajes/Nam.h"
#include "core/Personajes/Ranfan.h"
#include "core/Personajes/Giran.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QLabel>
#include <QVariant>
#include <QEvent>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Arrancamos en la página de menú
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);

    // Crear prototipos de personaje
    roster = {
        new Goku(), new Krilin(), new Yamcha(),
        new JackieChun(), new Bacterian(),
        new Nam(), new Ranfan(), new Giran()
    };
}

MainWindow::~MainWindow()
{
    qDeleteAll(roster);
    delete ui;
}

// -------------------------------------------------------------
//   EVENT FILTER: detecta clicks en cada celda (QFrame)
// -------------------------------------------------------------
bool MainWindow::eventFilter(QObject* watched, QEvent* ev)
{
    if (ev->type() == QEvent::MouseButtonRelease) {
        QMouseEvent* me = static_cast<QMouseEvent*>(ev);
        if (me->button() == Qt::LeftButton) {
            if (auto cell = qobject_cast<QFrame*>(watched)) {
                // Deselecciona celda anterior
                if (selectedCell) {
                    selectedCell->setStyleSheet("");
                }
                // Selecciona la nueva
                selectedCell = cell;
                cell->setStyleSheet("border: 2px solid blue;");

                // Recupera el personaje asociado
                void* vp = cell->property("personajePtr").value<void*>();
                selectedCharacter = static_cast<Personaje*>(vp);
                showStatsFor(selectedCharacter);
                return true;
            }
        }
    }
    return QMainWindow::eventFilter(watched, ev);
}

// -------------------------------------------------------------
//   Construye la galería de torneo
// -------------------------------------------------------------
void MainWindow::setupTorneoGallery()
{
    // 1) Limpiar cualquier widget previo
    while (auto item = ui->torneoGalleryLayout->takeAt(0)) {
        if (auto w = item->widget()) w->deleteLater();
        delete item;
    }

    // 2) Parámetros de grilla
    const int cols = 4;
    int row = 0, col = 0;

    for (Personaje* p : roster) {
        // Crear celda
        QFrame* cell = new QFrame;
        cell->setFrameShape(QFrame::StyledPanel);
        cell->setProperty("personajePtr", QVariant::fromValue<void*>(p));
        cell->setCursor(Qt::PointingHandCursor);
        cell->installEventFilter(this);

        // Layout vertical dentro de la celda
        QVBoxLayout* vl = new QVBoxLayout(cell);
        vl->setContentsMargins(4,4,4,4);

        // Label para icono (aquí podrías usar QPixmap)
        QLabel* icon = new QLabel(p->getNombre(), cell);
        icon->setAlignment(Qt::AlignCenter);
        vl->addWidget(icon);

        // Label para nombre
        QLabel* name = new QLabel(p->getNombre(), cell);
        name->setAlignment(Qt::AlignCenter);
        vl->addWidget(name);

        // Añadir celda al grid
        ui->torneoGalleryLayout->addWidget(cell, row, col);

        if (++col == cols) { col = 0; ++row; }
    }
}

// -------------------------------------------------------------
//   Muestra barra de stats para el personaje seleccionado
// -------------------------------------------------------------
void MainWindow::showStatsFor(Personaje* p)
{
    if (!p) return;
    ui->labelName->setText(p->getNombre());
    ui->labelVida->setText(QString::number(p->getVida()));
    ui->labelAtaque->setText(QString::number(p->getDanoBase()));
    ui->labelKi->setText(QString::number(p->getVelocidadX()));
}

// -------------------------------------------------------------
//   Slots de navegación
// -------------------------------------------------------------
void MainWindow::on_pushButtonTorneo_clicked()
{
    selectedCell      = nullptr;
    selectedCharacter = nullptr;
    setupTorneoGallery();
    ui->btnTorneo->setEnabled(false);
    ui->stackedWidget->setCurrentWidget(ui->pageSelectTorneo);
}

void MainWindow::on_btnCancel_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_btnTorneo_clicked()
{
    if (!selectedCharacter) return;  // no hay selección

    // Clonar jugador
    Personaje* jugador = selectedCharacter->clone();

    // Clonar oponentes
    std::vector<Personaje*> oponentes;
    for (Personaje* p : roster) {
        if (p != selectedCharacter) {
            oponentes.push_back(p->clone());
        }
    }

    // Ejecutar torneo
    Torneo torneo(jugador, oponentes);
    torneo.run();

    // Limpiar
    delete jugador;
    qDeleteAll(oponentes);

    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_pushButtonDuelo_clicked()
{
    // Aquí montarías la galería de duelo (sólo placeholder de lista)
    ui->stackedWidget->setCurrentWidget(ui->pageSelectDuelo);
}

void MainWindow::on_btnCancel_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_btnDuelo_clicked()
{
    // Por implementar: clonación de p1/p2 y llamada a Duelo1v1
    // Igual patrón a torneo: validar selectedCharacter, clon, run, clean…
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}
