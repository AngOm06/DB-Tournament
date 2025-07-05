QT       += core gui widgets
CONFIG   += c++17
TARGET    = DB-Tournament
TEMPLATE  = app

INCLUDEPATH = core
SOURCES += \
    gui/CombateWidget.cpp \
    gui/MainWindow.cpp \
    core/Modos/Bossfight.cpp \
    core/Modos/Duelo1v1.cpp \
    core/Personajes/Bacterian.cpp \
    core/Personajes/Giran.cpp \
    core/Personajes/JackieChun.cpp \
    core/Personajes/MonoGigante.cpp \
    core/Personajes/Nam.cpp \
    core/Personajes/Ranfan.cpp \
    core/Personajes/Yamcha.cpp \
    core/Modos/Torneo.cpp \
    core/Util/Funciones.cpp \
    core/Util/Combate.cpp \
    core/IA.cpp \
    core/Personajes/Krilin.cpp \
    core/Personaje.cpp \
    core/Personajes/Goku.cpp\
    main.cpp
HEADERS += \
    gui/CombateWidget.h \
    gui/MainWindow.h \
    core/Personajes/MonoGigante.h \
    core/Util/Funciones.h \
    core/Modos/Bossfight.h \
    core/Combate.h \
    core/Modos/Duelo1v1.h \
    core/Funciones.h \
    core/IA.h \
    core/Personajes/Bacterian.h \
    core/Personajes/Giran.h \
    core/Personajes/JackieChun.h \
    core/Personajes/Krilin.h \
    core/Personaje.h \
    core/Personajes/Goku.h \
    core/Personajes/Nam.h \
    core/Personajes/Ranfan.h \
    core/Personajes/Yamcha.h \
    core/Modos/Torneo.h

FORMS += \
    gui/CombateWidget.ui \
    gui/MainWindow.ui

RESOURCES += \
    resources.qrc
