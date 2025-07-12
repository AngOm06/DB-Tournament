#include "sonidos.h"

#include <QSoundEffect>

QSoundEffect efectoAtaque;
QSoundEffect efectoGolpe;
QSoundEffect efectoSalto;
QSoundEffect efectoBloqueo;
QSoundEffect efectoCorrer;
QSoundEffect efectoCombate;

void inicializarSonidos() {
    efectoAtaque.setSource(QUrl("qrc:/sonidos/assets/sonidos/attack.wav"));
    efectoGolpe.setSource(QUrl("qrc:/sonidos/assets/sonidos/punch.wav"));
    efectoSalto.setSource(QUrl("qrc:/sonidos/assets/sonidos/jump.wav"));
    efectoBloqueo.setSource(QUrl("qrc:/sonidos/assets/sonidos/block.wav"));
    efectoCorrer.setSource(QUrl("qrc:/sonidos/assets/sonidos/running.wav"));
    efectoCombate.setSource(QUrl("qrc:/sonidos/assets/sonidos/combat_start.wav"));
}
