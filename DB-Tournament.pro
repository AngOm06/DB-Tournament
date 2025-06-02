QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    Funciones.cpp \
    core/Personaje.cpp \
    core/Goku.cpp

HEADERS += \
    Funciones.h \
    core/Personaje.h \
    core/Goku.h

INCLUDEPATH += core
