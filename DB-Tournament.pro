QT -= gui

CONFIG += c++17 console
<<<<<<< Updated upstream
CONFIG -= app_bundle
=======
CONFIG += console
>>>>>>> Stashed changes

TEMPLATE = app

SOURCES += \
<<<<<<< Updated upstream
    main.cpp \
    Funciones.cpp \
=======
    core/Combate.cpp \
    core/IA.cpp \
    core/Krilin.cpp \
    main.cpp \
    core/Funciones.cpp \
>>>>>>> Stashed changes
    core/Personaje.cpp \
    core/Goku.cpp

HEADERS += \
<<<<<<< Updated upstream
    Funciones.h \
=======
    core/Combate.h \
    core/Funciones.h \
    core/IA.h \
    core/Krilin.h \
>>>>>>> Stashed changes
    core/Personaje.h \
    core/Goku.h

INCLUDEPATH += core
