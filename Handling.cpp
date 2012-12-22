#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Textfeld.h"
#include "Kamera.h"
#include "Kugel.h"
#include "Anzeige.h"
#include "Namen.h"
#include "Schild.h"
#include "Menu.h"
#include "Schiedsrichter.h"

#include "Einsetzen.h"
#include "Handling.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void StartHandling() {
    Camera.ScenicFlight(Factor);
	//Menu.Update(Faktor);
}

void ConsiderHandling() {
	//Menu.Update(Faktor);
    if (KEY_UP)  {Camera.Move_Front(Factor);}
    if (KEY_DOWN) {Camera.Move_Back(Factor);}
    if (KEY_RIGHT){Camera.Move_Right(Factor);}
    if (KEY_LEFT) {Camera.Move_Left(Factor);}
    if (KEY_SHIFT)       {Camera.Move_Up(Factor);}
    if (KEY_CTRL)        {Camera.Move_Down(Factor);}
    if (KEY_Bild_ON)    {Camera.Move_In(Factor);}
    if (KEY_Bild_Ab)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}
}

void AimHandling() {
    if (KEY_UP)  {Camera.Move_In(Factor);}
    if (KEY_DOWN) {Camera.Move_Out(Factor);}
    if (KEY_RIGHT){Camera.SwingRight(2*Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_LEFT) {Camera.SwingLeft(2*Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_SHIFT)       {Camera.SwingDown(Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_CTRL)        {Camera.SwingUp(Factor,Ball[0].Pos_xCM(),Ball[0].Pos_yCM());}
    if (KEY_Bild_ON)    {Camera.Move_In(Factor);}
    if (KEY_Bild_Ab)     {Camera.Move_Out(Factor);}
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
    if (KEY_Bild_ON)    {Camera.Move_In(Factor);}
    if (KEY_Bild_Ab)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}

	AusholStaerke=MaxAusholStaerke*(1-exp((-FrameTimePoint+AusholStartTime)/400.0));
    Display.setShockStaerke(AusholStaerke/3.333);

}

//击球处理
void ShockHandling() {

	AllerersterStoss=0;
	//WeisseVersetzbar=0;

    if (KEY_UP)  {Camera.Move_Front(Factor);}
    if (KEY_DOWN) {Camera.Move_Back(Factor);}
    if (KEY_RIGHT){Camera.Move_Right(Factor);}
    if (KEY_LEFT) {Camera.Move_Left(Factor);}
    if (KEY_SHIFT)       {Camera.Move_Up(Factor);}
    if (KEY_CTRL)        {Camera.Move_Down(Factor);}
    if (KEY_Bild_ON)    {Camera.Move_In(Factor);}
    if (KEY_Bild_Ab)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}

	//Frames++;                       // F"ur die Frames/sec-Anzeige

	// Zeit seit Stossbeginn
    GLint Zeit=FrameTimePoint-StartTime;  //time

	// Letzten Zustand noch zeichnen, wenn Stoss
	if (Zeit>Stossdauer) {Zeit=Stossdauer;} // eigentlich schon vorbei

	//printf("%i-%i=%i: ",FrameZeitpunkt,Startzeit,Zeit);

	for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln neu positionieren
		if (LightingTable[Zeit][Kugelnr][2]<=0) {
			//if (Kugelnr<8)
			//printf("%i,%i ",(GLint)Bewegungstabelle[Zeit][Kugelnr][0],(GLint)Bewegungstabelle[Zeit][Kugelnr][1]);
            Ball[Kugelnr].newPositionD(LightingTable[Zeit][Kugelnr]);
		}
	}
	//printf("\n");

	//DelayAusgleich=1;

    Display.setShockStaerke(AusholStaerke/3.333-Zeit/3.0);

	if (!(Zeit & 31)) {
		GLint neu=0;
		for (int i=0;i<16;i++) {
			if (BallsInGame[i] && !BallsSunk[i] && (Ball[i].Pos_x()==3000)) {
				BallsSunk[i]=1;
				neu=1;
			}
		}
        if (neu) {Menu.NewMenuState();}
	}


	if (Zeit==Stossdauer &&
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

		if (GameMode == TRAININGSSPIEL||GameMode == TUTORIAL) {
			if (Ball[0].Pos_x()==3000) {
				StateMachine=WEISSNEU;
                Display.setShockStaerke(0.0);
				LageVerbesserung=1;
				LageVerbesserungKopffeld=1;
				WeisseEinsetzen();
                Menu.NewMenuState();
			} else {
				StateMachine=BETRACHTEN;
                Display.setShockStaerke(0.0);
                Menu.NewMenuState();
			}
		} else if (Referee.Entscheidung()) {
			StateMachine=SCHIEDSRICHTER;
            Display.setShockStaerke(0.0);
		} else {
			StateMachine=BETRACHTEN;
            Display.setShockStaerke(0.0);
            Menu.NewMenuState();
		}
	}
}

void WeissneuHandling() {

	if (GameMode==TRAININGSSPIEL) {
		LageVerbesserungKopffeld=0;
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

	GLint ungueltig=0;

	if (x<-124 || x>124 || (x>-63.5 && LageVerbesserungKopffeld)) {
		x=Ball[0].Pos_xCM();
	}
	if (y<-60.5||y>60.5) {
		y=Ball[0].Pos_yCM();
	}

	for (int nr=1;nr<16;nr++) {
		if ((Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
				(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y)<32.7) {
			ungueltig=1;
		}
	}

	if (!ungueltig) {
		Ball[0].newPositionCM(x,y);
	}

    if (KEY_SHIFT)       {Camera.Move_Up(Factor);}
    if (KEY_CTRL)        {Camera.Move_Down(Factor);}
    if (KEY_Bild_ON)    {Camera.Move_In(Factor);}
    if (KEY_Bild_Ab)     {Camera.Move_Out(Factor);}
    if (KEY_Pos1)        {Camera.Zoom_In(Factor);}
    if (KEY_END)        {Camera.Zoom_Out(Factor);}
}

void RefereeHandling() {
	if (RefereeDecision == -1) {
		RefereeDecision = Referee.Entscheidung();

		RecodingChanges = RefereeDecision & 1;
		Foul = RefereeDecision & 2;
		LageVerbesserungKopffeld = RefereeDecision & 4;
		LageVerbesserung = RefereeDecision & 8;
		NeuAufbauenOderWeiterspielen = RefereeDecision & 16;
		NeuAufbauenOderAchtEinsetzen = RefereeDecision & 32;
		Player1Win = RefereeDecision & 64;
		Player2Win = RefereeDecision & 128;

        Menu.NewMenuState();

	}
}




