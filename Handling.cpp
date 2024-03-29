#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "TextItem.h"
#include "Camera.h"
#include "Ball.h"
#include "ShotStrength.h"
#include "Namen.h"
#include "Label.h"
#include "Menu.h"
#include "Judge.h"

#include "Chosen.h"
#include "Handling.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void StartHandling() {
    Camera.ScenicFlight(Factor);
	//Menu.Update(Faktor);
}

void ViewingHandling() {
	//Menu.Update(Faktor);
    if (KEY_UP)  {Camera.Move_Front(Factor);}
    if (KEY_DOWN) {Camera.Move_Back(Factor);}
    if (KEY_RIGHT){Camera.Move_Right(Factor);}
    if (KEY_LEFT) {Camera.Move_Left(Factor);}
    if (KEY_SHIFT)       {Camera.Move_Up(Factor);}
    if (KEY_CTRL)        {Camera.Move_Down(Factor);}
    if (KEY_PAGE_UP)    {Camera.Move_In(Factor);}
    if (KEY_PAGE_DOWN)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}
}

/*
 * Aim Handling
 */
void AimHandling() {
    if (KEY_UP)  {Camera.Move_In(Factor);}
    if (KEY_DOWN) {Camera.Move_Out(Factor);}
    if (KEY_RIGHT){Camera.SwingRight(2*Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_LEFT) {Camera.SwingLeft(2*Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_SHIFT)       {Camera.SwingDown(Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_CTRL)        {Camera.SwingUp(Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_PAGE_UP)    {Camera.Move_In(Factor);}
    if (KEY_PAGE_DOWN)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Vertigo_In(Factor);}
    if (KEY_END)        {Camera.Vertigo_Out(Factor);}
}

//后摆处理
void BackswingHandling() {
    if (KEY_UP)  {Camera.Move_In(Factor);}
    if (KEY_DOWN) {Camera.Move_Out(Factor);}
    if (KEY_RIGHT){Camera.SwingRight(2*Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_LEFT) {Camera.SwingLeft(2*Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_SHIFT)       {Camera.SwingDown(Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_CTRL)        {Camera.SwingUp(Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_PAGE_UP)    {Camera.Move_In(Factor);}
    if (KEY_PAGE_DOWN)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}

	AusholStaerke=MaxAusholStaerke*(1-exp((-FrameTimePoint+AusholStartTime)/400.0));
    ShotStrength.setShotStrength(AusholStaerke/3.333);

}

//击球处理
void ShotHandling() {

	AllerersterStoss=0;
	//WeisseVersetzbar=0;

    if (KEY_UP)  {Camera.Move_Front(Factor);}
    if (KEY_DOWN) {Camera.Move_Back(Factor);}
    if (KEY_RIGHT){Camera.Move_Right(Factor);}
    if (KEY_LEFT) {Camera.Move_Left(Factor);}
    if (KEY_SHIFT)       {Camera.Move_Up(Factor);}
    if (KEY_CTRL)        {Camera.Move_Down(Factor);}
    if (KEY_PAGE_UP)    {Camera.Move_In(Factor);}
    if (KEY_PAGE_DOWN)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}

	//Frames++;                       // F"ur die Frames/sec-Anzeige

    // time seit Stossbeginn
    GLint time=FrameTimePoint-StartTime;  //time

	// Letzten Zustand noch zeichnen, wenn Stoss
    if (time>shot_time) {time=shot_time;} // eigentlich schon vorbei

    //printf("%i-%i=%i: ",FrameZeitpunkt,Startzeit,time);

	for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln neu positionieren
        if (LightingTable[time][Kugelnr][2]<=0) {
			//if (Kugelnr<8)
            //printf("%i,%i ",(GLint)Bewegungstabelle[time][Kugelnr][0],(GLint)Bewegungstabelle[time][Kugelnr][1]);
            Ball[Kugelnr].newPositionD(LightingTable[time][Kugelnr]);
		}
	}
	//printf("\n");

	//DelayAusgleich=1;

    ShotStrength.setShotStrength(AusholStaerke/3.333-time/3.0);

    if (!(time & 31)) {
		GLint neu=0;
		for (int i=0;i<16;i++) {
			if (BallsInGame[i] && !BallsSunk[i] && (Ball[i].Pos_x()==3000)) {
				BallsSunk[i]=1;
				neu=1;
			}
		}
        if (neu) {Menu.NewMenuState();}
	}


    if (time==shot_time &&
			!(GameMode == TUTORIAL && FrameTimePoint-StartTime < 1900)) {
		// Animation schon fertig?

		//#ifndef _WIN32 
		//printf(" %f Frames/sec\n",(Frames*100.0)/(Stossdauer+1.0));
		//#endif    

		for (int i=0;i<16;i++) {
			if (BallsInGame[i] && !BallsSunk[i] && (Ball[i].Pos_x()==3000)) {
				BallsSunk[i]=1;
			}
		}

        if (GameMode == TRAINING_MODE||GameMode == TUTORIAL) {
			if (Ball[0].Pos_x()==3000) {
                StateMachine=NEW_WHITE;
                ShotStrength.setShotStrength(0.0);
				LageVerbesserung=1;
				LageVerbesserungKopffeld=1;
                WhiteChosen();
                Menu.NewMenuState();
			} else {
                StateMachine=VIEWING;
                ShotStrength.setShotStrength(0.0);
                Menu.NewMenuState();
			}
        } else if (Judge.Decision()) {
            StateMachine=JUDGEING;
            ShotStrength.setShotStrength(0.0);
		} else {
            StateMachine=VIEWING;
            ShotStrength.setShotStrength(0.0);
            Menu.NewMenuState();
		}
	}
}

void NewWhiteHandling() {

    if (GameMode==TRAINING_MODE) {
        LageVerbesserungKopffeld=0; //Location improving header
		LageVerbesserung=1;
	}

	GLfloat x=Ball[0].Pos_xCM();
	GLfloat y=Ball[0].Pos_yCM();

	GLfloat Faktor2=sqrt((Ball[0].Pos_xCM()-Camera.Pos_xCM())*
			(Ball[0].Pos_xCM()-Camera.Pos_xCM())+
			(Ball[0].Pos_yCM()-Camera.Pos_yCM())*
			(Ball[0].Pos_yCM()-Camera.Pos_yCM())+
			Camera.Pos_zCM()*Camera.Pos_zCM());

	Faktor2*=.005;

	if (KEY_UP) {
		x+=.3*Factor*Faktor2*sin(Camera.Beta*M_PI/180.0);
		y+=.3*Factor*Faktor2*cos(Camera.Beta*M_PI/180.0);
	}
	if (KEY_DOWN) {
		x-=.3*Factor*Faktor2*sin(Camera.Beta*M_PI/180.0);
		y-=.3*Factor*Faktor2*cos(Camera.Beta*M_PI/180.0);
	}
	if (KEY_LEFT) {
		x-=.3*Factor*Faktor2*cos(Camera.Beta*M_PI/180.0);
		y+=.3*Factor*Faktor2*sin(Camera.Beta*M_PI/180.0);
	}
	if (KEY_RIGHT) {
		x+=.3*Factor*Faktor2*cos(Camera.Beta*M_PI/180.0);
		y-=.3*Factor*Faktor2*sin(Camera.Beta*M_PI/180.0);
	}

    GLint invalid=0;

	if (x<-124 || x>124 || (x>-63.5 && LageVerbesserungKopffeld)) {
		x=Ball[0].Pos_xCM();
	}
	if (y<-60.5||y>60.5) {
		y=Ball[0].Pos_yCM();
	}

	for (int nr=1;nr<16;nr++) {
		if ((Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
				(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y)<32.7) {
            invalid=1;
		}
	}

    //invalid
    if (!invalid) {
		Ball[0].newPositionCM(x,y);
	}

    if (KEY_SHIFT)       {Camera.Move_Up(Factor);}
    if (KEY_CTRL)        {Camera.Move_Down(Factor);}
    if (KEY_PAGE_UP)    {Camera.Move_In(Factor);}
    if (KEY_PAGE_DOWN)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}
}

void JudgeHandling() {
	if (JudgeDecision == -1) {
        JudgeDecision = Judge.Decision();

		RecodingChanges = JudgeDecision & 1;
		Foul = JudgeDecision & 2;
		LageVerbesserungKopffeld = JudgeDecision & 4;
		LageVerbesserung = JudgeDecision & 8;
		NeuAufbauenOderWeiterspielen = JudgeDecision & 16;
		NeuAufbauenOderAchtEinsetzen = JudgeDecision & 32;
		Player1Win = JudgeDecision & 64;
		Player2Win = JudgeDecision & 128;

        Menu.NewMenuState();

	}
}




