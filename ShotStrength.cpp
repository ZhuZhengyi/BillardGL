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

#include "ShotStrength.h"

#include "Namen.h"

#include "createTexture.h"   // Funktion zum Generieren einer Textur aus einem 
// Matrix-Bild (aus "Ubungen)

int BallDisplay[16];

//display

/* --------- Konstruktor ---------- */
ShotStrength::ShotStrength() {
    shotStrength=0;
}


void ShotStrength::draw() {

    if (shotStrength>0.0) {

        glPushMatrix();
		glBegin(GL_QUADS);

        glColor4f(1.0,1.0,1.0,0.2-0.2/shotStrength);
		glVertex2f(14.0,2.0);
		glVertex2f(15.0,2.0);

        glColor4f(1.0,1.0,1.0,.7*shotStrength/45.0);
        glVertex2f(15.0,2.0+shotStrength*.2666);
        glVertex2f(14.0,2.0+shotStrength*.2666);

        glColor4f(1.0,1.0,1.0,0.1-0.1/shotStrength);
		glVertex2f(15.0,10.0);
		glVertex2f(14.0,10.0);

        glColor4f(1.0,1.0,1.0,.1*shotStrength/45.0);
        glVertex2f(14.0,2.0+shotStrength*.2666);
        glVertex2f(15.0,2.0+shotStrength*.2666);

		glEnd();
		glPopMatrix();
	}
}

void ShotStrength::Init() {
}

void ShotStrength::setShotStrength(GLfloat newShotStrength) {
    shotStrength=newShotStrength;
}
