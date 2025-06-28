QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG += console
TEMPLATE = app
SOURCES += \
    core/Duelo1v1.cpp \
    core/Personajes/Bacterian.cpp \
    core/Personajes/Giran.cpp \
    core/Personajes/JackieChun.cpp \
    core/Personajes/Nam.cpp \
    core/Personajes/Ranfan.cpp \
    core/Personajes/Yamcha.cpp \
    core/Torneo.cpp \
    main.cpp \
    Funciones.cpp \
    core/Combate.cpp \
    core/IA.cpp \
    core/Personajes/Krilin.cpp \
    core/Personaje.cpp \
    core/Personajes/Goku.cpp
HEADERS += \
    Funciones.h \
    core/Combate.h \
    core/Duelo1v1.h \
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
    core/Torneo.h

INCLUDEPATH += core
