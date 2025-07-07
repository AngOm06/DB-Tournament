#include "CountDownWidget.h"
#include <QVBoxLayout>

CountDownWidget::CountDownWidget(QWidget *parent) : QWidget(parent), contador(3) {
    label = new QLabel(QString::number(contador), this);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("font-size: 48pt; font-weight: bold; color: white;");
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(label);
    setLayout(lay);

    timer = new QTimer(this);
    timer->setInterval(1000); // 1 segundo
    connect(timer, &QTimer::timeout, this, &CountDownWidget::tick);
    timer->start();
}

void CountDownWidget::tick() {
    contador--;
    if (contador > 0) {
        label->setText(QString::number(contador));
    } else {
        timer->stop();
        emit finished();
    }
}

void CountDownWidget::start() {
    contador = 3;
    label->setText(QString::number(contador));
    timer->start();
}
