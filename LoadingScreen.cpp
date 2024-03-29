#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "TextItem.h"
#include "Label.h"
#include "Table.h"
#include "Camera.h"
#include "Ball.h"
#include "ShotStrength.h"
#include "Menu.h"
#include "Lighting.h"
#include "Judge.h"

#include "LA.h"
#include "bmp.h"

#include "createTexture.h"  

#include "BoardLayout.h"
#include "balltable.h"
#include "BillardGL.h"
#include "MouseKey.h"

#include "LoadingScreen.h"


/*
 * Loading Screen Update
 *
 */
void LSupdateGL() {

	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-4,4,-3,3);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D,ThirteenTexture);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor4f(1.0,1.0,1.0,1);
	glTexCoord2f(0,0);
	glVertex2f(-1,-1-.5);
	glTexCoord2f(1,0);
	glVertex2f( 1,-1-.5);
	glTexCoord2f(1,1);
	glVertex2f( 1, 1-.5);
	glTexCoord2f(0,1);
	glVertex2f(-1, 1-.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	GLfloat Winkel=(1-(LoadingProgress/29.0))*6.2832;

	glColor4f(0.0,0.0,0.0,0.2);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f( 0.0, 0.0-.5);
	glVertex2f(-2*sin(1.00*Winkel),2*cos(1.00*Winkel)-.5);
	glVertex2f(-2*sin(0.75*Winkel),2*cos(0.75*Winkel)-.5);
	glVertex2f(-2*sin(0.50*Winkel),2*cos(0.50*Winkel)-.5);
	glVertex2f(-2*sin(0.25*Winkel),2*cos(0.25*Winkel)-.5);
	glVertex2f( 0.0, 2.0-.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,LogoTexture);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glColor4f(1.0,1.0,1.0,.7);
	glTexCoord2f(0,0);
	glVertex2f(-2,0);
	glTexCoord2f(1,0);
	glVertex2f( 2,0);
	glTexCoord2f(1,1);
	glVertex2f( 2,1);
	glTexCoord2f(0,1);
	glVertex2f(-2,1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();

}

/*
 * Loading Screen idle
 */
void initLogo()
{
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glClear(GL_COLOR_BUFFER_BIT);
    FMatrix r,g,b;
    loadBMP(r,g,b,"Texturen/1/dreizehn.bmp");
    glGenTextures(1,&ThirteenTexture);
    glBindTexture(GL_TEXTURE_2D,ThirteenTexture);
    createTexture(r,g,b);
    r.free_FMatrix();
    g.free_FMatrix();
    b.free_FMatrix();
    loadBMP(r,g,b,"Texturen/1/logo.bmp");
    glGenTextures(1,&LogoTexture);
    glBindTexture(GL_TEXTURE_2D,LogoTexture);
    createTextureAlpha(r,g,b);
    r.free_FMatrix();
    g.free_FMatrix();
    b.free_FMatrix();
}

/*
 *
 */
void runGame()
{
    glDeleteTextures(1,&ThirteenTexture);

    DelayCompensation=1;

    glutIgnoreKeyRepeat(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //Callbacks setzen: Reaktion auf Mausklicks und -bewegungen, Tastaturaktivit鋞en
    glutMouseFunc(MouseClick);
    glutMotionFunc(MouseMove);
    glutKeyboardFunc(KeyPress);
    glutKeyboardUpFunc(KeyRelease);
    glutSpecialFunc(SpecialKeyPress);
    glutSpecialUpFunc(SpecialKeyRelease);

    glutVisibilityFunc(Visible);
    glutIdleFunc(timerEvent);
    glutDisplayFunc(updateGL);
}

void LSidle() {

	switch (LoadingProgress++) {
        case 0: initLogo();break;
        case 1: initializeBallTables(BallResolution); break;  //table init
        case 2: Ball[0].Init(0,TextureSize,BallResolution,Shadow); break; //ball0 init
        case 3: Ball[1].Init(1,TextureSize,BallResolution,Shadow); break;
        case 4: Ball[2].Init(2,TextureSize,BallResolution,Shadow); break;
        case 5: Ball[3].Init(3,TextureSize,BallResolution,Shadow); break;
        case 6: Ball[4].Init(4,TextureSize,BallResolution,Shadow); break;
        case 7: Ball[5].Init(5,TextureSize,BallResolution,Shadow); break;
        case 8: Ball[6].Init(6,TextureSize,BallResolution,Shadow); break;
        case 9: Ball[7].Init(7,TextureSize,BallResolution,Shadow); break;
        case 10: Ball[8].Init(8,TextureSize,BallResolution,Shadow); break;
        case 11: Ball[9].Init(9,TextureSize,BallResolution,Shadow); break;
        case 12: Ball[10].Init(10,TextureSize,BallResolution,Shadow); break;
        case 13: Ball[11].Init(11,TextureSize,BallResolution,Shadow); break;
        case 14: Ball[12].Init(12,TextureSize,BallResolution,Shadow); break;
        case 15: Ball[13].Init(13,TextureSize,BallResolution,Shadow); break;
        case 16: Ball[14].Init(14,TextureSize,BallResolution,Shadow); break;
        case 17: Ball[15].Init(15,TextureSize,BallResolution,Shadow); break;
        case 18: Table.Init(TableTextureSize); break;
        case 19: Lighting.Init(AmbientLighting,TableLamps,GreenLamp,Reflections); break;
        case 20: ShotStrength.Init(); break;
        case 21: Menu.Init(DisplayTextureSize); break;
        case 22: Menu.LoadLanguage(900); break;
        case 23: Menu.LoadLanguage(901); break;
        case 24: Menu.LoadLanguage(999); break;
        case 25: Menu.Init(DisplayTextureSize); break;
        case 26: BoardLayout(); break;
        case 27: Judge.NewGame(GameType); break;
        case 28: runGame(); break;
	}
	glutPostWindowRedisplay(CurrentWindow);
}
