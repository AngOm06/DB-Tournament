#ifndef RESULTADOWIDGET_H
#define RESULTADOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class ResultadoWidget : public QWidget {
    Q_OBJECT
public:
    ResultadoWidget(QWidget *parent = nullptr);
    void setResultado(const QString &nombreGanador);

signals:
    void revanchaClicked();
    void volverClicked();

private:
    QLabel *labelResultado;
    QPushButton *btnRevancha;
    QPushButton *btnVolver;
};

#endif // RESULTADOWIDGET_H
