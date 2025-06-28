QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
CONFIG += console
TEMPLATE = app
SOURCES += \
    core/Duelo1v1.cpp \
    main.cpp \
    Funciones.cpp \
    core/Combate.cpp \
    core/IA.cpp \
    core/Krilin.cpp \
    core/Personaje.cpp \
    core/Goku.cpp
HEADERS += \
    Funciones.h \
    core/Combate.h \
    core/Duelo1v1.h \
    core/Funciones.h \
    core/IA.h \
    core/Krilin.h \
    core/Personaje.h \
    core/Goku.h

INCLUDEPATH += core
