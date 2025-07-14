QT       += core gui widgets multimedia
CONFIG   += c++17
TARGET    = DB-Tournament
TEMPLATE  = app
CONFIG += console

INCLUDEPATH += core gui
SOURCES += \
    core/sonidos.cpp \
    gui/CombateWidget.cpp \
    gui/CountDownWidget.cpp \
    gui/MainWindow.cpp \
    core/Modos/Duelo1v1.cpp \
    core/Personajes/Bacterian.cpp \
    core/Personajes/Giran.cpp \
    core/Personajes/JackieChun.cpp \
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
    gui/ResultadoWidget.cpp \
    gui/TorneoWidget.cpp \
    main.cpp
HEADERS += \
    core/sonidos.h \
    gui/CombateWidget.h \
    gui/CountDownWidget.h \
    gui/MainWindow.h \
    core/Util/Funciones.h \
    core/Util/Combate.h \
    core/Modos/Duelo1v1.h \
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
    core/Modos/Torneo.h \
    gui/ResultadoWidget.h \
    gui/TorneoWidget.h

FORMS += \
    gui/CombateWidget.ui \
    gui/MainWindow.ui \
    gui/TorneoWidget.ui

RESOURCES += \
    resources.qrc
