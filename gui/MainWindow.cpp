#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "gui/CombateWidget.h"
#include "gui/TorneoWidget.h"

#include "core/Modos/Duelo1v1.h"
#include "core/Modos/Torneo.h"

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
    if (ui->stackedWidget->currentWidget() == ui->pageSelectCharacter
        && ev->type() == QEvent::MouseButtonRelease)
    {
        auto me = static_cast<QMouseEvent*>(ev);
        if (me->button() == Qt::LeftButton) {
            QFrame* cell = qobject_cast<QFrame*>(watched);
            if (cell) {
                if (selectedCell) selectedCell->setStyleSheet("");
                selectedCell = cell;
                cell->setStyleSheet("border: 2px solid blue;");

                // Guardar personaje actual
                void* vp = cell->property("personajePtr").value<void*>();
                selectedCharacter = static_cast<Personaje*>(vp);
                showStatsFor(selectedCharacter);
                ui->btnInicio->setEnabled(selectedCharacter != nullptr);
                ui->btnInicio->setEnabled(selectedCharacter != nullptr);

                return true;
            }
        }
    }

    return QMainWindow::eventFilter(watched, ev);
}


// -------------------------------------------------------------
//   Construye las galerias
// -------------------------------------------------------------
void MainWindow::setupSelectionGallery()
{
    // Limpia la rejilla igual que antes…
    auto& layout = ui->characterGalleryLayout;   // tu único GridLayout
    while (auto item = layout->takeAt(0)) {
        if (auto w = item->widget()) w->deleteLater();
        delete item;
    }

    // Cambia el título según modo
    switch (currentMode) {
    case SelectMode::Tournament:
        ui->labelTitle->setText("Elige tu personaje para Torneo");
        break;
    case SelectMode::DuelPlayer:
        ui->labelTitle->setText("Elige tu guerrero");
        break;
    case SelectMode::DuelOpponent:
        ui->labelTitle->setText("Elige al oponente");
        break;
    default:
        ui->labelTitle->setText("");
    }

    // Monta la rejilla
    const int cols = 4;
    int row = 0, col = 0;
    for (Personaje* p : roster) {
        QFrame* cell = new QFrame;

        cell->setFrameShape(QFrame::StyledPanel);
        cell->setProperty("personajePtr", QVariant::fromValue<void*>(p));
        cell->setCursor(Qt::PointingHandCursor);
        cell->installEventFilter(this);

        // Que la celda pida un mínimo pero pueda crecer
        cell->setMinimumSize(120, 140);
        cell->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        // Layout vertical dentro de la celda
        QVBoxLayout* vl = new QVBoxLayout(cell);
        vl->setContentsMargins(4,4,4,4);
        vl->setSpacing(6);

        // Label para icono QPixmap
        QPixmap img(QString(":/portadas/assets/portadas/%1.png").arg(p->getNombre()));
        QLabel* icon = new QLabel(cell);
        icon->setFixedSize(100, 100);            // tamaño fijo para la imagen
        icon->setScaledContents(true);            // que el label haga la escala
        icon->setPixmap(img);
        icon->setAlignment(Qt::AlignCenter);
        icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        vl->addWidget(icon, 0, Qt::AlignHCenter);

        // (Opcional) Label con nombre pequeñito
        QLabel* name = new QLabel(p->getNombre(), cell);
        name->setAlignment(Qt::AlignCenter);
        vl->addWidget(name);


        if (currentMode == SelectMode::DuelOpponent && p == firstPick) {
            cell->setEnabled(false);
            cell->setStyleSheet("opacity: 0.4;");
        }
        layout->addWidget(cell, row, col);
        if (++col == cols) {
            col = 0; ++row;
        }
    }
}


// -------------------------------------------------------------
//   Muestra stats
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
    currentMode = SelectMode::Tournament;
    firstPick = nullptr;
    setupSelectionGallery();
    ui->stackedWidget->setCurrentWidget(ui->pageSelectCharacter);
}

void MainWindow::on_pushButtonDuelo_clicked()
{
    currentMode = SelectMode::DuelPlayer;
    firstPick   = nullptr;
    setupSelectionGallery();
    ui->stackedWidget->setCurrentWidget(ui->pageSelectCharacter);
}

void MainWindow::on_btnCancel_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}

void MainWindow::on_btnInicio_clicked()
{
    if (!selectedCharacter) return;

    switch (currentMode) {
    case SelectMode::Tournament: {
        Personaje* jugador = selectedCharacter->clone();
        std::vector<Personaje*> oponentes;
        for (Personaje* p : roster)
            if (p != selectedCharacter)
                oponentes.push_back(p->clone());

        TorneoWidget* torneoW = new TorneoWidget(jugador, oponentes);
        torneoW->setAttribute(Qt::WA_DeleteOnClose);
        torneoW->show();
        break;
    }

    case SelectMode::DuelPlayer: {
        // Guardar selección de jugador 1 y pasar a elegir oponente
        firstPick = selectedCharacter;
        selectedCharacter = nullptr;
        selectedCell = nullptr;
        currentMode = SelectMode::DuelOpponent;
        setupSelectionGallery();
        return; // no volvemos al menú todavía
    }

    case SelectMode::DuelOpponent: {
        if (!firstPick || !selectedCharacter) return;

        Personaje* c1 = firstPick->clone();
        Personaje* c2 = selectedCharacter->clone();

        CombateWidget* cw = new CombateWidget(c1, c2);
        cw->show();

        break;
    }

    default: break;
    }

    // Volver al menú y limpiar selección
    firstPick = nullptr;
    selectedCharacter = nullptr;
    selectedCell = nullptr;
    currentMode = SelectMode::Tournament;
    ui->stackedWidget->setCurrentWidget(ui->pageMenu);
}
