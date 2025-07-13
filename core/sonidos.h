#ifndef SONIDOS_H
#define SONIDOS_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

extern QMediaPlayer* musica;
extern QAudioOutput* salidaAudio;

void reproducirMusicaMenu();
void reproducirMusicaCombate();
void reproducirMusicaVictoria();
void reproducirMusicaDerrota();
void detenerMusica();

extern QSoundEffect efectoGolpe;
extern QSoundEffect efectoAtaque;
extern QSoundEffect efectoSalto;
extern QSoundEffect efectoBloqueo;
extern QSoundEffect efectoCorrer;
extern QSoundEffect efectoCombate;
extern QSoundEffect efectoTorneo;

void inicializarSonidos();

#endif // SONIDOS_H
