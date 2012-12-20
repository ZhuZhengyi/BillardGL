#############################################################################
# Linux Makefile for building BillardGl  Tobias Nopper 2001
#     Project: BillardGL
#############################################################################

####### Compiler, tools and options

CC	=	gcc
CXX	=	g++
CFLAGS	=	-pipe -Wall -W -DNO_DEBUG -g
CXXFLAGS=	-pipe -Wall -W -DNO_DEBUG -g 
INCPATH	=	-I/usr/X11R6/include 
LINK	=	g++
LFLAGS	=	
LIBS	=	-L/usr/X11R6/lib -lGL -lGLU -lglut -lXmu -lXext -lX11 -lm -lXi

## -lqgl -lGLU

TAR	=	tar -cf
GZIP	=	gzip -9f

####### Files

HEADERS =	Anzeige.h\
		Beleuchtung.h\
		Benutzerschnittstelle.h\
		BillardGL.h\
		Einsetzen.h\
		Handling.h\
		Kamera.h\
		KommandoZeilenParameter.h\
		Kugel.h\
		LA.h\
		Menu.h\
		Namen.h\
		Netzwerk.h\
		Physik.h\
		SchattenKreis.h\
		Schiedsrichter.h\
		Schild.h\
		SpielfeldAufbau.h\
		Textfeld.h\
		Tisch.h\
		Tischfunktionen.h\
		Zeit.h\
		bmp.h\
		createTexture.h\
		kugeltabellen.h\
		viertelLoch.h\
		LadeScreen.h

SOURCES =	Anzeige.cpp\
		Beleuchtung.cpp\
		Benutzerschnittstelle.cpp\
		BillardGL.cpp\
		Einsetzen.cpp\
		Handling.cpp\
		Kamera.cpp\
		KommandoZeilenParameter.cpp\
		Kugel.cpp\
		LA.cpp\
		Menu.cpp\
		Netzwerk.cpp\
		Physik.cpp\
		SchattenKreis.cpp\
		Schiedsrichter.cpp\
		Schild.cpp\
		SpielfeldAufbau.cpp\
		Textfeld.cpp\
		Tisch.cpp\
		Tischfunktionen.cpp\
		Zeit.cpp\
		bmp.cpp\
		createTexture.cpp\
		kugeltabellen.cpp\
		viertelLoch.cpp\
		LadeScreen.cpp

OBJECTS =	Anzeige.o\
		Beleuchtung.o\
		Benutzerschnittstelle.o\
		BillardGL.o\
		Einsetzen.o\
		Handling.o\
		Kamera.o\
		KommandoZeilenParameter.o\
		Kugel.o\
		LA.o\
		Netzwerk.o\
		Menu.o\
		Physik.o\
		SchattenKreis.o\
		Schiedsrichter.o\
		Schild.o\
		SpielfeldAufbau.o\
		Textfeld.o\
		Tisch.o\
		Tischfunktionen.o\
		Zeit.o\
		bmp.o\
		createTexture.o\
		kugeltabellen.o\
		viertelLoch.o\
		LadeScreen.o

INTERFACES =	
UICDECLS =	
UICIMPLS =	
SRCMOC	=	
OBJMOC	=	
DIST	=	
TARGET	=	BillardGL
INTERFACE_DECL_PATH = .

####### Implicit rules

.SUFFIXES: .cpp .cxx .cc .C .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules


all: $(TARGET)

$(TARGET): $(UICDECLS) $(OBJECTS) $(OBJMOC) 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(LIBS)

dist:
	$(TAR) BillardGL.tar BillardGL.pro $(SOURCES) $(HEADERS) $(INTERFACES) $(DIST)
	$(GZIP) BillardGL.tar

clean:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core
clear:
	-rm -f $(OBJECTS) $(OBJMOC) $(SRCMOC) $(UICIMPLS) $(UICDECLS) $(TARGET)
	-rm -f *~ core

install: 
	-cp BillardGL /usr/X11R6/bin/BillardGL
	-cp BillardGL /usr/X11R6/bin/billardGL
	-mkdir -p /usr/share/BillardGL
	-cp -R Texturen /usr/share/BillardGL
	-cp -R lang /usr/share/BillardGL
	-mkdir -p /usr/share/doc/packages/BillardGL
	-cp README /usr/share/doc/packages/BillardGL

uninstall:
	-rm /usr/X11R6/bin/BillardGL
	-rm -rf /usr/share/BillardGL
	-rm -rf /usr/share/doc/packages/BillardGL
####### Sub-libraries



