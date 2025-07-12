#include <QApplication>
#include <QFontDatabase>
#include <QFile>
#include "gui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(":/fonts/assets/fonts/Saiyan-sans.ttf");
    if (fontId >= 0) {
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont appFont(family);
        a.setFont(appFont);
    }

    QFile qssFile(":/qss/assets/qss/styles.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString style = QString::fromUtf8(qssFile.readAll());
        a.setStyleSheet(style);
        qssFile.close();
    }
    MainWindow* w = new MainWindow;
    w->show();
    int exitCode = a.exec();
    delete w;
    return exitCode;
}
