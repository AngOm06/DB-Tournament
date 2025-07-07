#ifndef COUNTDOWNWIDGET_H
#define COUNTDOWNWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

class CountDownWidget : public QWidget {
    Q_OBJECT
public:
    CountDownWidget(QWidget *parent = nullptr);
    void start();

signals:
    void finished();

private slots:
    void tick();

private:
    QLabel *label;
    QTimer *timer;
    int contador;
};

#endif // COUNTDOWNWIDGET_H
