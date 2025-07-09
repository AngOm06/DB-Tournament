#include "ResultadoWidget.h"
#include <QVBoxLayout>

ResultadoWidget::ResultadoWidget(QWidget *parent) : QWidget(parent) {
    labelResultado = new QLabel("GANADOR:", this);
    labelResultado->setAlignment(Qt::AlignCenter);
    labelResultado->setStyleSheet("font-size: 24pt; color: white;");
    btnRevancha = new QPushButton("Revancha", this);
    btnVolver = new QPushButton("Volver al menú", this);

    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(labelResultado);
    lay->addWidget(btnRevancha);
    lay->addWidget(btnVolver);
    setLayout(lay);

    connect(btnRevancha, &QPushButton::clicked, this, &ResultadoWidget::revanchaClicked);
    connect(btnVolver, &QPushButton::clicked, this, &ResultadoWidget::volverClicked);
}

void ResultadoWidget::setResultado(const QString &nombreGanador) {
    labelResultado->setText("GANADOR: " + nombreGanador);
}
