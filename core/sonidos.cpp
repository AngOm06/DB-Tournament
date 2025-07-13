#include "sonidos.h"

#include <QSoundEffect>

QSoundEffect efectoAtaque;
QSoundEffect efectoGolpe;
QSoundEffect efectoSalto;
QSoundEffect efectoBloqueo;
QSoundEffect efectoCorrer;
QSoundEffect efectoCombate;
QSoundEffect efectoTorneo;

QMediaPlayer* musica = nullptr;
QAudioOutput* salidaAudio = nullptr;

static void ensurePlayer() {
    if (!musica) {
        musica = new QMediaPlayer;
        salidaAudio    = new QAudioOutput;
        musica->setAudioOutput(salidaAudio);
        salidaAudio->setVolume(0.2);  // 20%
        musica->setLoops(QMediaPlayer::Infinite);
    }
}

void detenerMusicaAmbiente() {
    if (musica)musica->stop();
}
void reproducirMusicaMenu() {
    ensurePlayer();
    musica->setSource(QUrl("qrc:/sonidos/assets/sonidos/musica_fondo.mp3"));
    musica->play();
}
void reproducirMusicaCombate() {
    ensurePlayer();
    musica->setSource(QUrl("qrc:/sonidos/assets/sonidos/combat.mp3"));
    musica->play();
}
void reproducirMusicaVictoria() {
    ensurePlayer();
    musica->setSource(QUrl("qrc:/sonidos/assets/sonidos/champion.mp3"));
    musica->play();
}
void reproducirMusicaDerrota() {
    ensurePlayer();
    musica->setSource(QUrl("qrc:/sonidos/assets/sonidos/defeat.mp3"));
    musica->play();
}
void inicializarSonidos() {
    efectoAtaque.setSource(QUrl("qrc:/sonidos/assets/sonidos/attack.wav"));
    efectoGolpe.setSource(QUrl("qrc:/sonidos/assets/sonidos/punch.wav"));
    efectoSalto.setSource(QUrl("qrc:/sonidos/assets/sonidos/jump.wav"));
    efectoBloqueo.setSource(QUrl("qrc:/sonidos/assets/sonidos/block.wav"));
    efectoCorrer.setSource(QUrl("qrc:/sonidos/assets/sonidos/running.wav"));
    efectoCombate.setSource(QUrl("qrc:/sonidos/assets/sonidos/combat_start.wav"));
    efectoTorneo.setSource(QUrl("qrc:/sonidos/assets/sonidos/tournamet.wav"));

}
