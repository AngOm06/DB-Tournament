#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "core/Personaje.h"

enum class SelectMode {
    None,
    Tournament,
    DuelPlayer,
    DuelOpponent
};
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QFrame;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    // Para detectar clics en las celdas de la galería
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    // Página principal
    void on_pushButtonDuelo_clicked();
    void on_pushButtonTorneo_clicked();

    // Pagina Selección
    void on_btnInicio_clicked();
    void on_btnCancel_clicked();

    void on_btnSalir_clicked();

private:
    Ui::MainWindow *ui;

    // Prototipos de personajes
    std::vector<Personaje*> roster;

    // Para la galería de torneo
    QFrame*         selectedCell      = nullptr;
    Personaje*      selectedCharacter = nullptr;

    // Métodos auxiliares
    void setupSelectionGallery();
    void showStatsFor(Personaje* p);

    SelectMode currentMode = SelectMode::None;
    Personaje* firstPick   = nullptr;  // para Duelo
};

#endif // MAINWINDOW_H
