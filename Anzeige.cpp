/****************************************************************************
 **
 **  Anzeige.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 *****************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h> //2CHANGE wieder raus wenn kein printf mehr drin
#include <GL/glut.h>

#include "LA.h"                // Zum Handling von .bmp-Files bzw. Matrix-Bildern
#include "bmp.h"

#include "Anzeige.h"

#include "Namen.h"

#include "createTexture.h"   // Funktion zum Generieren einer Textur aus einem 
// Matrix-Bild (aus "Ubungen)

int BallDisplay[16];

//display

/* --------- Konstruktor ---------- */
Display::Display() {
    ShockStaerke=0;

	//for (int i=1;i<16;i++) {
	//  KugelAnzeige[i]=0;
	//}
}


void Display::draw() {

    if (ShockStaerke>0.0) {

		glPushMatrix();
		glBegin(GL_QUADS);
        glColor4f(1.0,1.0,1.0,0.2-0.2/ShockStaerke);
		glVertex2f(14.0,2.0);
		glVertex2f(15.0,2.0);
        glColor4f(1.0,1.0,1.0,.7*ShockStaerke/45.0);
        glVertex2f(15.0,2.0+ShockStaerke*.2666);
        glVertex2f(14.0,2.0+ShockStaerke*.2666);
        glColor4f(1.0,1.0,1.0,0.1-0.1/ShockStaerke);
		glVertex2f(15.0,10.0);
		glVertex2f(14.0,10.0);
        glColor4f(1.0,1.0,1.0,.1*ShockStaerke/45.0);
        glVertex2f(14.0,2.0+ShockStaerke*.2666);
        glVertex2f(15.0,2.0+ShockStaerke*.2666);
		glEnd();
		glPopMatrix();
	}
}

void Display::Initialisiere() {
}

void Display::setShockStaerke(GLfloat neuStossStaerke) {
    ShockStaerke=neuStossStaerke;
}
