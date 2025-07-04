#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "core/Personaje.h"   // Asegúrate de que Personaje declare virtual Personaje* clone() const;

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

    // Selección Torneo
    void on_btnCancel_2_clicked();
    void on_btnTorneo_clicked();

    // Selección Duelo 1v1
    void on_btnCancel_clicked();
    void on_btnDuelo_clicked();

private:
    Ui::MainWindow *ui;

    // Prototipos de personajes
    std::vector<Personaje*> roster;

    // Para la galería de torneo
    QFrame*         selectedCell      = nullptr;
    Personaje*      selectedCharacter = nullptr;

    // Métodos auxiliares
    void setupTorneoGallery();
    void setupDueloGallery();
    void showStatsFor(Personaje* p);
};

#endif // MAINWINDOW_H
