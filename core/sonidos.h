#ifndef SONIDOS_H
#define SONIDOS_H

#include <QSoundEffect>

extern QSoundEffect efectoGolpe; //Conecta el golpe
extern QSoundEffect efectoAtaque; //Lanza el ataque
extern QSoundEffect efectoSalto;
extern QSoundEffect efectoBloqueo;
extern QSoundEffect efectoCorrer;
extern QSoundEffect efectoCombate;

void inicializarSonidos();

#endif // SONIDOS_H
