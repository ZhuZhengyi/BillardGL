/****************************************************************************
 **
 ** BillardGL.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  


#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#include "Textfeld.h"
#include "Schild.h"
#include "Table.h"
#include "Camera.h"
#include "Ball.h"
#include "Display.h"
#include "Menu.h"
#include "Lighting.h"

#include "Namen.h" 
#include "LA.h"
#include "bmp.h"
#include "ElapsedTime.h"
#include "Physics.h"
#include "BoardLayout.h"
#include "MouseKey.h"
#include "ParamConfig.h"
#include "Handling.h"
#include "Judge.h"
#include "balltable.h"
#include "LoadingScreen.h"

#include "BillardGL.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//Tabellen
GLfloat LightingTable[2000][16][3];
GLint   SoundTable[1000];

//Objekte
class Ball   Ball[16];      //球
class Table   Table;        //球台
class Display Display;      //显示
class Camera  Camera;       //相机
class Menu Menu;            //菜单
class Judge Judge;      //裁判
class Lighting Lighting;    //光照

//Sonstige Variablen
GLint   MouseLookLast_x;
GLint   MouseLookLast_y;

GLint   Stossdauer=1999;  //shock duartion
GLint   StartTime;
GLint   Frames=0;
GLint   FrameTimePoint;
GLint   LastFrameTimePoint=-1;  //Last Frame

GLint   AusholStartTime;        //aushol start time
GLfloat AusholStaerke=0;        //aushol Thickness
GLfloat MaxAusholStaerke=100;   //max aushol Thickness

GLint   DelayCompensation;     //Delay compensation
GLint   Factor;

GLint   AllerersterStoss=1;  //kick

GLint   FullScreen;
GLint   BackgroundColor=0;

GLint   BallsSunk[16];     //ballsunk
GLint   BallsInGame[16];

GLint   xnor=0;
GLint   MouseButtonIntercepted=0; //click intercept

//State-Maschin'
GLint   StateMachine=START;
GLint   GameType=EIGHT_BALL;         //Game
GLint   GameMode=TRAINING_MODE;  //Game

// Schiedsrichter
GLint JudgeDecision=0; //Judge decision
GLint RecodingChanges=0;   //recording changes
//GLint SpielerAmStoss=0;
GLint Foul=0;           //犯规
GLint LageVerbesserungKopffeld=1;       //Situation improving header
GLint LageVerbesserung=0;
GLint NeuAufbauenOderWeiterspielen=0;       //Rebuild Or Next play
GLint NeuAufbauenOderAchtEinsetzen=0;       //
GLint Player1Win=0;
GLint Player2Win=0;

//Tasten
GLint KEY_UP=0;  //up_arrow_key
GLint KEY_DOWN=0;  //down_arrow_key
GLint KEY_RIGHT=0; //right
GLint KEY_LEFT=0;  //left
GLint KEY_SHIFT=0;        //shift
GLint KEY_CTRL=0;         //ctrl
GLint KEY_PAGE_UP=0;     //
GLint KEY_PAGE_DOWN=0;      //
GLint KEY_Pos1=0;         //pos1
GLint KEY_END=0;         //end


//GLint   KameraFahrt=0;


//Betrachtungsweise
GLint PolygonMode_mode=GL_FILL;
GLint PolygonMode_view=GL_FRONT;

int value;

GLint TextureSize,DisplayTextureSize,TableTextureSize;
GLint BallResolution;  //Ball 分辨率
GLint InvertX,InvertY,Shadow,ZBufferDelete;
GLint TexMMM;
GLfloat MouseSpeed,Epsilon;   //鼠标速率,
GLint PhysicsFrequenz=400;      //物理频率
GLfloat FrictionFactor,GangsFactor,CollisionFactor; //摩擦系数,混乱系数,碰撞系数
GLint ColorDepth, Reflections; //色深,
GLint ScreenResolution;         //屏幕分辨率
GLint Language;                 //语言

GLint LoadingProgress=0;    //载入进度
GLuint ThirteenTexture;      //13号球纹理
GLuint LogoTexture;          //logo纹理

char Player1[10];          //Player1
char Player2[10];          //Player2
char NetworkPlayer[10];   //NetworkPlayer1
char NetworkTeam[10];    //NetworkPlayer2

int OriginalWindow=0,CurrentWindow=0;

GLint ShowFPS;              //显示FPS
GLint AmbientLighting;      //环境光
GLint TableLamps;           //球台灯
GLint GreenLamp;            //

GLfloat EffectVolumeDown=.5;     //效果音量减小量
GLfloat MusicVolumeDown=.5;      //音乐音量减小量

//KugelTabellen

GLfloat *ball_vertices[30];     //球顶点
GLfloat *ball_texcoord[30];
GLint *ball_indices[30];

void updateGL()
{
    if (ZBufferDelete) {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}

    Camera.draw();                        // Kamera-Postion und -Parameter setzen

    Lighting.draw();

    Table.drawSurface();                  // Tischflaeche zeichen

	glDisable(GL_DEPTH_TEST);

    Table.drawLine();

    for (int BallIndex=0;BallIndex<16;BallIndex++) {
        Ball[BallIndex].drawShadow();      // Schatten zeichen
	}

	glEnable(GL_DEPTH_TEST);

    Table.drawBorder();

    GLfloat Abstand=0;  //distance
    GLint Aufloesung=1; //Display resolution

	for (int Kugelnr2=0;Kugelnr2<16;Kugelnr2++) {
        GLfloat x=Ball[Kugelnr2].Pos_xCM()-Camera.Pos_x;
        GLfloat y=Ball[Kugelnr2].Pos_yCM()-Camera.Pos_y;
		GLfloat z=Camera.Pos_z;
		Abstand=sqrt(x*x+y*y+z*z);
		Aufloesung=(GLint(400/Abstand));//300
		if (Aufloesung<3) Aufloesung=3;
        Aufloesung=(Aufloesung/2)*2+1;
        if (Aufloesung>BallResolution) Aufloesung=BallResolution;
        Ball[Kugelnr2].draw(Aufloesung);              // Kugeln zeichen
	}

	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LIGHTING);

    Menu.draw();

    if (StateMachine!=START) {
        Display.draw();                       // Anzeige zeichnen
	}
	glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

/* -------------------- timerEvent -------------------- */
void timerEvent()
{

	//egal+=egal;

	//glutTimerFunc(20,timerEvent,0);

    FrameTimePoint=ElapsedTime();              // Framezeit bestimmen

	// Faktor= Zeit seit letztem Frame
    Factor=FrameTimePoint-LastFrameTimePoint;


    if (DelayCompensation) {
        Factor=1;
        DelayCompensation=0;
	}

    if (Factor) {

        if (ShowFPS) {
            if ((FrameTimePoint%200)<(LastFrameTimePoint%200)) {
                Menu.SetFPS(Frames/2);
				Frames=0;
			} else Frames++;
		} 

        Menu.Update(Factor);

        switch (StateMachine) {

			case START: StartHandling();break;

            case VIEWING: ViewingHandling();break;

            case AIMING: AimHandling();break;

            case AUSHOLEN: BackswingHandling();break;

            case SHOCK: ShockHandling();break;      //击球

            case NEW_WHITE: NewWhiteHandling();break;

            case JUDGEING: JudgeHandling();break;

		}

        Camera.Ride(Factor);

        LastFrameTimePoint=FrameTimePoint;

        glutPostWindowRedisplay(CurrentWindow);
	}  
} 


int main(int argc, char **argv)
{ 
	//char string[10];  

    GetCommandParam(argc,argv);

	for (int i=0;i<16;i++) {
        BallsInGame[i]=1;
        BallsSunk[i]=0;
	}
    BallsInGame[0]=0;

	//GLUT initialisieren, Fenster setzen
	glutInit(&argc, argv);	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	if (FullScreen) {
		char temp[20];
        sprintf(temp,"%ix%i:%i",ScreenResolution,(ScreenResolution*3)/4,ColorDepth);
		glutGameModeString(temp);
		if (!glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
			printf ("  No Game Mode possible!\n\n");
		glutEnterGameMode();
		glutFullScreen();
	} else {
        glutInitWindowSize (ScreenResolution,(ScreenResolution*3)/4);
		glutInitWindowPosition (0, 0);
		glutCreateWindow ("BillardGL 1.7");
	}

	glClearColor(0,0,0,0);


	glutIdleFunc(LSidle);

	//Callback zum Zeichnen der GL-Funktion
	glutDisplayFunc(LSupdateGL);

    CurrentWindow=glutGetWindow();

	//  CreateMenu();

	//  timerEvent(0);

	glutMainLoop();

	return EXIT_SUCCESS;
}

/* -------------------- Stoss -------------------- */
void Stoke(GLfloat Stoss_x, GLfloat Stoss_y) {

    Judge.NewStoke();
    JudgeDecision=-1;

    Physics(Stoss_x, Stoss_y);               // Physik-Simulation

    StartTime=ElapsedTime();               // Startzeit bestimmen

}

void Visible (int vis) {
	if (vis == GLUT_VISIBLE) {
		glutIdleFunc(timerEvent);
	}
}

