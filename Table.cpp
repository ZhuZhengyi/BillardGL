/***************************************************************************
 **
 **  Tisch.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "LA.h"
#include "bmp.h"

#include "createTexture.h"  

#include "Table.h"

#include "Lighting.h"
#include "TableHelpFunc.h"
#include "quarterHole.h"

FMatrix woodtex_r,woodtex_g,woodtex_b;     // Matrix-Bilder, in die die Textur kommt


Table::Table() {
    TableSurfaceTexture=0;
    WoodBorderTexture=0;

	/* */
}

GLfloat color1[38][4]={
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,0.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2}
};
GLfloat vertex1[][3] = 	{
    {-64.2,68.5,-2.8575},{-64.2,0.7,-2.8575},
    {-63.5,0.0,-2.8575},{-63.5,68.5,-2.8575},
    {-64.2,0.7,-2.8575},{-65.2,0.7,-2.8575},
    {-64.5,0.0,-2.8575},{-63.5,0.0,-2.8575},
    {-65.2,0.7,-2.8575},{-65.2,-0.7,-2.8575},
    {-64.5,0.0,-2.8575},{-64.5,0.0,-2.8575},
    {-65.2,-0.7,-2.8575},{-64.2,-0.7,-2.8575},
    {-63.5,0.0,-2.8575},{-64.5,0.0,-2.8575},
    {-64.2,-0.7,-2.8575},{-64.2,-68.5,-2.8575},
    {-63.5,-68.5,-2.8575},{-63.5,0.0,-2.8575},
    {-63.5,68.5,-2.8575},{-63.5,0,-2.8575},
    {-62.8,0,-2.8575},{-62.8,68.5,-2.8575},
    {-63.5,0,-2.8575},{-63.5,-68.5,-2.8575},
    {-62.8,-68.5,-2.8575},{-62.8,0,-2.8575},
    {-.5,0.5,-2.8575},{-1.5,0.5,-2.8575},
    {-1,0.0,-2.8575},{0,0.0,-2.8575},
    {-1.5,0.5,-2.8575},{-1.5,-0.5,-2.8575},
    {-1,0.0,-2.8575},{-1,0.0,-2.8575},
    {-1.5,-0.5,-2.8575},{-.5,-0.5,-2.8575},
    {0,0.0,-2.8575},{-1,0.0,-2.8575},
    {-.5,-0.5,-2.8575},{-.5,-1.5,-2.8575},
    {0,-1,-2.8575},{0,0.0,-2.8575},
    {-.5,-1.5,-2.8575},{.5,-1.5,-2.8575},
    {0,-1,-2.8575},{0,-1,-2.8575},
    {.5,-1.5,-2.8575},{.5,-0.5,-2.8575},
    {0,0.0,-2.8575},{0,-1,-2.8575},
    {.5,-0.5,-2.8575},{1.5,-0.5,-2.8575},
    {1,0.0,-2.8575},{0,0.0,-2.8575},
    {1.5,-0.5,-2.8575},{1.5,0.5,-2.8575},
    {1,0.0,-2.8575},{1,0.0,-2.8575},
    {1.5,0.5,-2.8575},{.5,0.5,-2.8575},
    {0,0.0,-2.8575},{1,0.0,-2.8575},
    {.5,0.5,-2.8575},{.5,1.5,-2.8575},
    {0,1,-2.8575},{0,0.0,-2.8575},
    {.5,1.5,-2.8575},{-.5,1.5,-2.8575},
    {0,1,-2.8575},{0,1,-2.8575},
    {-.5,1.5,-2.8575},{-.5,0.5,-2.8575},
    {0,0.0,-2.8575},{0,1,-2.8575}
};
GLfloat color2[82][4]={
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
    {1.0,1.0,1.0,0},
    {1.0,1.0,1.0,.2},
};


GLfloat vertex2[][3] = 	{
    {-2.91,1.68,-2.8575},   {-3.36,0,-2.8575},
    {-2.86,0,-2.8575},      {-2.47,1.43,-2.8575},
    {-1.68,2.91,-2.8575},   {-2.91,1.68,-2.8575},
    {-2.47,1.43,-2.8575},   {-1.43,2.47,-2.8575},
    {13.17,11.48,-2.8575},  {-1.68,2.91,-2.8575},
    {-1.43,2.47,-2.8575},   {13.42,11.05,-2.8575},
    {14.85,11.93,-2.8575},  {13.17,11.48,-2.8575},
    {13.42,11.05,-2.8575},  {14.85,11.43,-2.8575},
    {16.53,11.48,-2.8575},  {14.85,11.93,-2.8575},
    {14.85,11.43,-2.8575},  {16.28,11.05,-2.8575},
    {17.76,10.25,-2.8575},  {16.53,11.48,-2.8575},
    {16.28,11.05,-2.8575},  {17.32,10.00,-2.8575},
    {18.21,8.57,-2.8575},   {17.76,10.25,-2.8575},
    {17.32,10.00,-2.8575},  {17.71,8.57,-2.8575},
    {18.21,0.5,-2.8575},    {18.21,8.57,-2.8575},
    {17.71,8.57,-2.8575},   {17.71,0.0,-2.8575},
    {53,0.5,-2.8575},       {18.21,0.5,-2.8575},
    {17.71,0.0,-2.8575},    {53,0.0,-2.8575},
    {18.21,-0.5,-2.8575},   {53,-0.5,-2.8575},
    {53,0.0,-2.8575},       {17.71,0.0,-2.8575},
    {18.21,-8.57,-2.8575},  {18.21,-0.5,-2.8575},
    {17.71,0.0,-2.8575},    {17.71,-8.57,-2.8575},
    {17.76,-10.25,-2.8575}, {18.21,-8.57,-2.8575},
    {17.71,-8.57,-2.8575},  {17.32,-10.0,-2.8575},
    {16.53,-11.48,-2.8575}, {17.76,-10.25,-2.8575},
    {17.32,-10.0,-2.8575},  {16.28,-11.05,-2.8575},
    {14.85,-11.93,-2.8575}, {16.53,-11.48,-2.8575},
    {16.28,-11.05,-2.8575}, {14.85,-11.43,-2.8575},
    {13.17,-11.48,-2.8575}, {14.85,-11.93,-2.8575},
    {14.85,-11.43,-2.8575}, {13.42,-11.05,-2.8575},
    {-1.68,-2.91,-2.8575},  {13.17,-11.48,-2.8575},
    {13.42,-11.05,-2.8575}, {-1.43,-2.47,-2.8575},
    {-2.91,-1.68,-2.8575},  {-1.68,-2.91,-2.8575},
    {-1.43,-2.47,-2.8575},  {-2.47,-1.43,-2.8575},
    {-3.36,0.0,-2.8575},    {-2.91,-1.68,-2.8575},
    {-2.47,-1.43,-2.8575},  {-2.86,0.0,-2.8575},
    {-2.36,0.0,-2.8575},    {-2.04,1.18,-2.8575},
    {-2.47,1.43,-2.8575},   {-2.86,0.0,-2.8575},
    {-2.04,1.18,-2.8575},   {-1.18,2.04,-2.8575},
    {-1.43,2.47,-2.8575},   {-2.47,1.43,-2.8575},
    {-1.18,2.04,-2.8575},   {13.67,10.61,-2.8575},
    {13.42,11.05,-2.8575},  {-1.43,2.47,-2.8575},
    {13.67,10.61,-2.8575},  {14.85,10.93,-2.8575},
    {14.85,11.43,-2.8575},  {13.42,11.05,-2.8575},
    {14.85,10.93,-2.8575},  {16.03,10.61,-2.8575},
    {16.28,11.05,-2.8575},  {14.85,11.43,-2.8575},
    {16.03,10.61,-2.8575},  {16.89,9.75,-2.8575},
    {17.32,10.0,-2.8575},   {16.28,11.05,-2.8575},
    {16.89,9.75,-2.8575},   {17.21,8.57,-2.8575},
    {17.71,8.57,-2.8575},   {17.32,10.0,-2.8575},
    {17.21,8.57,-2.8575},   {17.21,0.5,-2.8575},
    {17.71,0.0,-2.8575},    {17.71,8.57,-2.8575},
    {17.21,0.5,-2.8575},    {0.5,0.5,-2.8575},
    {0.0,0.0,-2.8575},      {17.71,0.0,-2.8575},
    {0.5,0.5,-2.8575},      {0.5,1.5,-2.8575},
    {0.0,1.0,-2.8575},      {0.0,0.0,-2.8575},
    {0.5,1.5,-2.8575},      {-0.5,1.5,-2.8575},
    {0.0,1.0,-2.8575},      {0.0,1.0,-2.8575},
    {-0.5,1.5,-2.8575},     {-0.5,-1.5,-2.8575},
    {0.0,-1.0,-2.8575},     {0.0,1.0,-2.8575},
    {-0.5,-1.5,-2.8575},    {0.5,-1.5,-2.8575},
    {0.0,-1.0,-2.8575},     {0.0,-1.0,-2.8575},
    {0.5,-1.5,-2.8575},     {0.5,-0.5,-2.8575},
    {0.0,0.0,-2.8575},      {0.0,-1.0,-2.8575},
    {0.5,-0.5,-2.8575},     {17.21,-0.5,-2.8575},
    {17.71,0.0,-2.8575},    {0.0,0.0,-2.8575},
    {-2.04,-1.18,-2.8575},  {-2.36,0.0,-2.8575},
    {-2.86,0.0,-2.8575},    {-2.47,-1.43,-2.8575},
    {-1.18,-2.04,-2.8575},  {-2.04,-1.18,-2.8575},
    {-2.47,-1.43,-2.8575},  {-1.43,-2.47,-2.8575},
    {13.67,-10.61,-2.8575}, {-1.18,-2.04,-2.8575},
    {-1.43,-2.47,-2.8575},  {13.42,-11.05,-2.8575},
    {14.85,-10.93,-2.8575}, {13.67,-10.61,-2.8575},
    {13.42,-11.05,-2.8575}, {14.85,-11.43,-2.8575},
    {16.03,-10.61,-2.8575}, {14.85,-10.93,-2.8575},
    {14.85,-11.43,-2.8575}, {16.28,-11.05,-2.8575},
    {16.89,-9.75,-2.8575},  {16.03,-10.61,-2.8575},
    {16.28,-11.05,-2.8575}, {17.32,-10.0,-2.8575},
    {17.21,-8.57,-2.8575},  {16.89,-9.75,-2.8575},
    {17.32,-10.0,-2.8575},  {17.71,-8.57,-2.8575},
    {17.21,-0.5,-2.8575},   {17.21,-8.57,-2.8575},
    {17.71,-8.57,-2.8575},  {17.71,-0.0,-2.8575}
};

GLfloat color3[8][4]={
    {0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,.6},
    {0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,.6},
    {0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,.6},
    {0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,.6}
};

GLfloat vertex3[][3] = 	{
    {-139,65,-2.8575},      {139,65,-2.8575},
    {139,68.5,-2.8575},     {-139,68.5,-2.8575},
    {139,-65,-2.8575},      {-139,-65,-2.8575},
    {-139,-68.5,-2.8575},   {139,-68.5,-2.8575},
    {128.5,65,-2.8575},     {128.5,-65,-2.8575},
    {132,-65,-2.8575},      {132,65,-2.8575},
    {-128.5,-65,-2.8575},   {-128.5,65,-2.8575},
    {-132,65,-2.8575},      {-132,-65,-2.8575}

};
/* ----------------------
   Tisch initialisieren
   ---------------------- */

void Table::Init(GLint TextureSize) {
    if (!LinesIndex) {
        LinesIndex=glGenLists(1);      // Display List erzeugen
	}
    glNewList(LinesIndex,GL_COMPILE_AND_EXECUTE);
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
    for(int i=0; i<38; i++)
    {
        glColor4f(color1[i][0],color1[i][3],color1[i][2], color1[i][3]);
        glVertex3f(vertex1[i*2][0],vertex1[i*2][1],vertex1[i*2][2]);
        glVertex3f(vertex1[i*2+1][0],vertex1[i*2+1][1],vertex1[i*2+1][2]);
    }
	//Dreieck
	glEnd();

	glPushMatrix();
	glTranslatef(63.5,0.0,0.0);
	glScalef(1.35,1.35,1);

	glBegin(GL_QUADS);
    for(int i=0; i<82; i++)
    {
        glColor4f(color2[i][0],color2[i][3],color2[i][2], color2[i][3]);
        glVertex3f(vertex2[i*2][0],vertex2[i*2][1],vertex2[i*2][2]);
        glVertex3f(vertex2[i*2+1][0],vertex2[i*2+1][1],vertex2[i*2+1][2]);
    }
	glEnd();
	glPopMatrix();

	glBegin(GL_QUADS);

    for(int i=0; i<8; i++)
    {
        glColor4f(color3[i][0],color3[i][3],color3[i][2], color3[i][3]);
        glVertex3f(vertex3[i*2][0],vertex3[i*2][1],vertex3[i*2][2]);
        glVertex3f(vertex3[i*2+1][0],vertex3[i*2+1][1],vertex3[i*2+1][2]);
    }

	glEnd();

	glEnable(GL_LIGHTING);
	glEndList();

    if (!TableSurfaceTexture)
        glGenTextures(1,&TableSurfaceTexture);

    if (TextureSize && TextureSize<8) {
        GLint T=TextureSize;
		if (T==4) T=2;
		char Name[40];
		sprintf(Name,"Texturen/%i/filzkachel.bmp",T); 
		loadBMP(woodtex_r,woodtex_g,woodtex_b,Name);
        glBindTexture(GL_TEXTURE_2D,TableSurfaceTexture);
		createTextureMipmap(woodtex_r,woodtex_g,woodtex_b);
	}

    if (!TableSurfaceIndex) {
        TableSurfaceIndex=glGenLists(1);      // Display List erzeugen
	}
    glNewList(TableSurfaceIndex,GL_COMPILE_AND_EXECUTE);
	glPushMatrix();

	glTranslatef(0,0,-2.8575);     // Tisch um Kugelradius nach unten schieben

	//Licht an:
	//Beleuchtung(0,0,1,0,0,Reflektionen);

	//GLfloat mat_ambient[]={0.1,0.45,0.2,1.0};
	//GLfloat mat_diffuse[]={0.1,0.45,0.2,1.0};
	//GLfloat mat_specular[]={0,0,0,1.0};
	//GLfloat mat_shininess = 0.0;
	//glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
	//glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);


	// Ma遝 der Spielfl鋍he (in cm):
	// 254 x 127
	GLint xteile=16;     // Anzahl muss gerade sein
	GLint yteile=8;     // Anzahl muss gerade sein; 
	GLfloat widthx=264.0/xteile;
	GLfloat widthy=137.0/yteile;

	/* -------------------------
	   Flaeche berechnen  
	   ------------------------- */  

    if (TextureSize && TextureSize<8) {
		GLfloat mat_ambient[]={1.0,1.0,1.0,1.0};
		GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
		GLfloat mat_specular[]={0,0,0,1.0};
		GLfloat mat_shininess = 0.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
        glBindTexture(GL_TEXTURE_2D,TableSurfaceTexture);
		glEnable(GL_TEXTURE_2D);
        TableSurfaceBindTexture();
		/* -------------
		   L鯿her machen
		   ------------- */

        // bottom left
		glPushMatrix();
		glTranslatef(-133.29,-69.79,0);
        quarterHole(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21,-133.29,-69.79,1,0,0,1);
		glPopMatrix();

        // bottom center
		glPushMatrix();
		glTranslatef(0,-71.75,0);
        quarterHole(widthx+0.01,widthy+3.26,4,4,.63,10,7.62,6.99,0,-71.75,1,0,0,1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,-71.75,0);
		glRotatef(90,0,0,1);
        quarterHole(widthy+3.26,widthx+0.01,4,4,.63,10.2,7.62,6.99,0,-71.75,0,-1,1,0);
		glPopMatrix();

        //bottom right
		glPushMatrix();
		glTranslatef(133.29,-69.79,0); 
		glRotatef(90,0,0,1);
        quarterHole(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21,133.29,-69.79,0,-1,-1,0);
		glPopMatrix();

        //top right
		glPushMatrix();
		glTranslatef(133.29,69.79,0);
		glRotatef(180,0,0,1);
        quarterHole(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21,133.29,69.79,-1,0,0,-1);
		glPopMatrix();

        //top center
		glPushMatrix();
		glTranslatef(0,71.75,0);
		glRotatef(180,0,0,1);
        quarterHole(widthx+0.1,widthy+3.26,4,4,.63,10,7.62,6.99,0,71.75,-1,0,0,-1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,71.75,0);
		glRotatef(-90,0,0,1);
        quarterHole(widthy+3.26,widthx+0.1,4,4,.63,10,7.62,6.99,0,71.75,0,1,-1,0);
		glPopMatrix();

        //top left
		glPushMatrix();
		glTranslatef(-133.29,69.79,0); 
		glRotatef(-90,0,0,1);
        quarterHole(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21,-133.29,69.79,0,1,-1,0);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

	} else {

		GLfloat mat_ambient[]={0.1,0.45,0.2,1.0};
		GLfloat mat_diffuse[]={0.1,0.45,0.2,1.0};
		GLfloat mat_specular[]={0,0,0,1.0};
		GLfloat mat_shininess = 0.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);


        TableSurface();

		/* -------------
		   L鯿her machen
		   ------------- */

		// unten links
		glPushMatrix();
		glTranslatef(-133.29,-69.79,0);
        quarterHole(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21);
		glPopMatrix();

		// unten Mitte 
		glPushMatrix();
		glTranslatef(0,-71.75,0);
        quarterHole(widthx+0.01,widthy+3.26,4,4,.63,10,7.62,6.99);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,-71.75,0);
		glRotatef(90,0,0,1);
        quarterHole(widthy+3.26,widthx+0.01,4,4,.63,10.2,7.62,6.99);
		glPopMatrix();

		//unten rechts   
		glPushMatrix();
		glTranslatef(133.29,-69.79,0); 
		glRotatef(90,0,0,1);
        quarterHole(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21);
		glPopMatrix();

		//oben rechts
		glPushMatrix();
		glTranslatef(133.29,69.79,0);
		glRotatef(180,0,0,1);
        quarterHole(widthx+1.3,widthy+1.3,4,4,.63,10,9.84,9.21);
		glPopMatrix();

		//oben Mitte
		glPushMatrix();
		glTranslatef(0,71.75,0);
		glRotatef(180,0,0,1);
        quarterHole(widthx+0.1,widthy+3.26,4,4,.63,10,7.62,6.99);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0,71.75,0);
		glRotatef(-90,0,0,1);
        quarterHole(widthy+3.26,widthx+0.1,4,4,.63,10,7.62,6.99);
		glPopMatrix();

		//oben links
		glPushMatrix();
		glTranslatef(-133.29,69.79,0); 
		glRotatef(-90,0,0,1);
        quarterHole(widthy+1.3,widthx+1.3,4,4,.63,10,9.84,9.21);
		glPopMatrix();

	}

	glPopMatrix();
	glEndList();

	/* --------------------
	   Banden berechnen 
	   -------------------- */

    if (!WoodBorderTexture)
        glGenTextures(1,&WoodBorderTexture);

    if (TextureSize) {
		char Name[40];
        sprintf(Name,"Texturen/%i/holz.bmp",TextureSize);

		loadBMP(woodtex_r,woodtex_g,woodtex_b,Name);
        glBindTexture(GL_TEXTURE_2D,WoodBorderTexture);
		//createTextureMipmap(woodtex_r,woodtex_g,woodtex_b);
		createTexture(woodtex_r,woodtex_g,woodtex_b);
	}

    if (!BorderIndex) {
        BorderIndex=glGenLists(1);      // Display List erzeugen
	}
    glNewList(BorderIndex,GL_COMPILE_AND_EXECUTE);
	{
		GLfloat mat_ambient[]={0.1,0.45,0.2,1.0};
		GLfloat mat_diffuse[]={0.1,0.45,0.2,1.0};
		GLfloat mat_specular[]={0,0,0,1.0};
		GLfloat mat_shininess = 127.0;
		glMaterialfv(GL_FRONT, GL_AMBIENT,mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);

		glPushMatrix();

		glTranslatef(0,0,-2.8575);     // Tisch um Kugelradius nach unten schieben

		// Bande links 
		glPushMatrix();
		Banden(0,1);
		glPopMatrix();

		// Bande rechts 
		glPushMatrix();
		glRotatef(180,0,0,1);
		Banden(0,1);
		glPopMatrix();

		// Bande oben links
		glPushMatrix();
		Banden(1,1);
		glPopMatrix();    

		// Bande oben rechts
		glPushMatrix();
		Banden(1,-1);
		glPopMatrix();

		// Bande unten links
		glPushMatrix();
		glRotatef(180,0,0,1);
		Banden(1,-1);
		glPopMatrix();

		// Bande unten rechts
		glPushMatrix();
		glRotatef(180,0,0,1);
		Banden(1,1);
		glPopMatrix();

		//Verkleidungen (;)
		glPushMatrix();
		MittelLochVerkleidung();
		MittelLochInnenverkleidung();
		MittelLochRand();
		glRotatef(180,0,0,1);
		MittelLochVerkleidung();
		MittelLochInnenverkleidung();
		MittelLochRand();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(132,68.5,0);
		EckLochVerkleidung();
		EckLochInnenverkleidung();
		EckLochRand();
		glPopMatrix();

		glPushMatrix();
		glRotatef(180,0,0,1);
		glTranslatef(132,68.5,0);
		EckLochVerkleidung();
		EckLochInnenverkleidung();
		EckLochRand();
		glPopMatrix();

		glPushMatrix();
		glRotatef(90,0,0,1);
		glTranslatef(68.5,132,0);
		EckLochVerkleidung();
		EckLochInnenverkleidung();
		EckLochRand();
		glPopMatrix();

		glPushMatrix();
		glRotatef(-90,0,0,1);
		glTranslatef(68.5,132,0);
		EckLochVerkleidung();
		EckLochInnenverkleidung();
		EckLochRand();
		glPopMatrix();

		{
			GLfloat mat_diffuse[]={0.8,0.8,1.0,1.0};
			GLfloat mat_specular[]={1.0,0.8,0.8,1.0};
			GLfloat mat_shininess = 127.0;

			glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
			glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
			glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
		}

        Diamod(31.75,72.5,4.9);
        Diamod(63.5,72.5,4.9);
        Diamod(95.25,72.5,4.9);
        Diamod(-31.75,72.5,4.9);
        Diamod(-63.5,72.5,4.9);
        Diamod(-95.25,72.5,4.9);
        Diamod(31.75,-72.5,4.9);
        Diamod(63.5,-72.5,4.9);
        Diamod(95.25,-72.5,4.9);
        Diamod(-31.75,-72.5,4.9);
        Diamod(-63.5,-72.5,4.9);
        Diamod(-95.25,-72.5,4.9);
        Diamod(136.5,31.75,4.9);
        Diamod(136.5,0,4.9);
        Diamod(136.5,-31.75,4.9);
        Diamod(-136.5,31.75,4.9);
        Diamod(-136.5,0,4.9);
        Diamod(-136.5,-31.75,4.9);


		//Holzbanden
        if (TextureSize) {
			//char Name[40];
            //sprintf(Name,"Texturen/%i/holz.bmp",TextureSize);

			//loadBMP(woodtex_r,woodtex_g,woodtex_b,Name);
			//createWoodTexture(woodtex_r,woodtex_g,woodtex_b,Nearest);
            glBindTexture(GL_TEXTURE_2D,WoodBorderTexture);
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

			glPushMatrix();
			glTranslatef(7.5,68.5,0);
            WoodBand(115.5,8,1,1);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180,0,0,1);
			glTranslatef(7.5,68.5,0);
            WoodBand(115.5,8,1,1);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-123,68.5,0);
            WoodBand(115.5,8,1,1);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180,0,0,1);
			glTranslatef(-123,68.5,0);
            WoodBand(115.5,8,1,1);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-132,-59.5,0);
			glRotatef(90,0,0,1);
            WoodBand(119,8,1,1);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(132,59.5,0);
			glRotatef(-90,0,0,1);
            WoodBand(119,8,1,1);
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);

		} else {
			glPushMatrix();
			glTranslatef(7.5,68.5,0);
            WoodBandOT(115.5,8);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180,0,0,1);
			glTranslatef(7.5,68.5,0);
            WoodBandOT(115.5,8);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-123,68.5,0);
            WoodBandOT(115.5,8);
			glPopMatrix();

			glPushMatrix();
			glRotatef(180,0,0,1);
			glTranslatef(-123,68.5,0);
            WoodBandOT(115.5,8);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-132,-59.5,0);
			glRotatef(90,0,0,1);
            WoodBandOT(119,8);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(132,59.5,0);
			glRotatef(-90,0,0,1);
            WoodBandOT(119,8);
			glPopMatrix();

			GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
			GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
			GLfloat mat_shininess = 0.0;

			glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
			glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
			glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);

		}

		glPopMatrix();

	}

	glEndList();

    if (TextureSize) {
		woodtex_r.free_FMatrix();
		woodtex_g.free_FMatrix();
		woodtex_b.free_FMatrix();
	}

}


/* -----------------
   Tisch malen
   ----------------- */

void Table::drawSurface() {
    glCallList(TableSurfaceIndex);       // Tischflaeche zeichnen-draw
}

void Table::drawBorder() {
    glCallList(BorderIndex);       // Banden zeichnen
}

void Table::drawLine() {
    glCallList(LinesIndex);
}
