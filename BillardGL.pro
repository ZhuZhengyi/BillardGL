TEMPLATE = app
CONFIG += console
CONFIG -= qt
TARGET	= BillardGL
INCLUDEPATH += -I/usr/X11R6/include
LIBS += -L. -L/usr/X11R6/lib -lGL -lGLU -lglut -lXmu -lXext -lX11 -lm -lXi

SOURCES += \
    BillardGL.cpp \
    bmp.cpp \
    createTexture.cpp \
    Handling.cpp \
    LA.cpp \
    Menu.cpp \
    Schild.cpp \
    Textfeld.cpp \
    Ball.cpp \
    Judge.cpp \
    Camera.cpp \
    Lighting.cpp \
    MouseKey.cpp \
    ParamConfig.cpp \
    Table.cpp \
    TableHelpFunc.cpp \
    ElapsedTime.cpp \
    Chosen.cpp \
    balltable.cpp \
    LoadingScreen.cpp \
    Network.cpp \
    Physics.cpp \
    Shadow.cpp \
    BoardLayout.cpp \
    Display.cpp \
    quarterHole.cpp

HEADERS += \
    BillardGL.h \
    bmp.h \
    createTexture.h \
    Handling.h \
    LA.h \
    Menu.h \
    Namen.h \
    resource.h \
    Schild.h \
    Textfeld.h \
    Ball.h \
    Judge.h \
    Camera.h \
    Lighting.h \
    MouseKey.h \
    ParamConfig.h \
    Table.h \
    TableHelpFunc.h \
    ElapsedTime.h \
    Chosen.h \
    balltable.h \
    LoadingScreen.h \
    Network.h \
    Physics.h \
    Shadow.h \
    BoardLayout.h \
    Display.h \
    language.h \
    quarterHole.h

