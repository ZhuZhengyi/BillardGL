TEMPLATE = app
CONFIG += console
CONFIG -= qt
TARGET	= BillardGL
INCLUDEPATH += -I/usr/X11R6/include
LIBS += -L. -L/usr/X11R6/lib -lGL -lGLU -lglut -lXmu -lXext -lX11 -lm -lXi

SOURCES += \
    Anzeige.cpp \
    Beleuchtung.cpp \
    Benutzerschnittstelle.cpp \
    BillardGL.cpp \
    bmp.cpp \
    createTexture.cpp \
    Einsetzen.cpp \
    Handling.cpp \
    Kamera.cpp \
    KommandoZeilenParameter.cpp \
    Kugel.cpp \
    kugeltabellen.cpp \
    LA.cpp \
    LadeScreen.cpp \
    Menu.cpp \
    Netzwerk.cpp \
    Physik.cpp \
    SchattenKreis.cpp \
    Schiedsrichter.cpp \
    Schild.cpp \
    SpielfeldAufbau.cpp \
    Textfeld.cpp \
    Tisch.cpp \
    Tischfunktionen.cpp \
    viertelLoch.cpp \
    Zeit.cpp

HEADERS += \
    Anzeige.h \
    Beleuchtung.h \
    Benutzerschnittstelle.h \
    BillardGL.h \
    bmp.h \
    createTexture.h \
    Einsetzen.h \
    Handling.h \
    Kamera.h \
    KommandoZeilenParameter.h \
    Kugel.h \
    kugeltabellen.h \
    LadeScreen.h \
    LA.h \
    Menu.h \
    Namen.h \
    Netzwerk.h \
    Physik.h \
    resource.h \
    SchattenKreis.h \
    Schiedsrichter.h \
    Schild.h \
    SpielfeldAufbau.h \
    sprache.h \
    Textfeld.h \
    Tischfunktionen.h \
    Tisch.h \
    viertelLoch.h \
    Zeit.h

