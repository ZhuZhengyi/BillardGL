/****************************************************************************
 **
 **  Physik.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 **  Berechnet Stoss und schreibt Positionsdaten in die Bewegungstabelle
 **
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Judge.h"
#include "Physics.h"

GLfloat oldPos[16][3]; // alte Pos. der Kugeln
GLfloat newPos[16][3]; // neue Pos. der Kugeln

GLfloat BallSpeed[16][2]; // Geschw. Kugeln
GLfloat FallFaktor = 25.0;
GLfloat VerlustTasche = 1.0;  //loss pocket

// ---------------- Kugel versenken ----------------------------------------

/*
 * 下沉
 * 第nr号球进洞下沉过程
 *
 */
void sink(GLint nr){
    //球落到底部
    if (newPos[nr][2] <= -2.0) {
        newPos[nr][0]=1500;
        newPos[nr][1]=1500;
        newPos[nr][2]=0;
        BallSpeed[nr][0] = 0.0;
        BallSpeed[nr][1] = 0.0;

	}

    //球开始下落
    if ((newPos[nr][2]==0)&&(newPos[nr][0]!=1500)) { // Kugel beginnt zu fallen
        newPos[nr][2] = -0.05;
        BallSpeed[nr][0] = BallSpeed[nr][0]*0.95; // abbremsen
        BallSpeed[nr][1] = BallSpeed[nr][1]*0.95;
	}
    //球下落中
	else           // Kugel faellt bereits
	{
        //right
        if (newPos[nr][0]>10){
            //above
            if (newPos[nr][1]>0){
                BallSpeed[nr][0] = 23.322-newPos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = 12.211-newPos[nr][1]+BallSpeed[nr][1]*0.5;
			}
            //blew
            else{
                BallSpeed[nr][0] = 23.322-newPos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = -12.211-newPos[nr][1]+BallSpeed[nr][1]*0.5;
			}
		}
        //left
        if (newPos[nr][0]<-10){
            //above
            if (newPos[nr][1]>0){                             // oben
                BallSpeed[nr][0] = -23.322-newPos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = 12.211-newPos[nr][1]+BallSpeed[nr][1]*0.5;
			}
            //blew
			else{                                              // unten
                BallSpeed[nr][0] = -23.322-newPos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = -12.211-newPos[nr][1]+BallSpeed[nr][1]*0.5;
			}
		}	
        //middle
        if ((newPos[nr][0]>-2)&&(newPos[nr][0]<2)){               // Mitte
            if (newPos[nr][1]>0){                             // oben
                BallSpeed[nr][0] = 0-newPos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = 12.5547-newPos[nr][1]+BallSpeed[nr][1]*0.5;
			}
			else{                                              // unten
                BallSpeed[nr][0] = 0-newPos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = -12.5547-newPos[nr][1]+BallSpeed[nr][1]*0.5;
			} 
		}
	}

}

/*
 * 碰撞
 *
 *
 *
 */
void Collision(GLfloat newPos1[],
               GLfloat newPos2[],
               GLint first_ball,
               GLint second_ball)
{

	GLfloat verlust = CollisionFactor; 
    newPos[first_ball][0] = newPos1[0]; // neue Position wird festgelegt
    newPos[first_ball][1] = newPos1[1];
    newPos[second_ball][0] = newPos2[0];
    newPos[second_ball][1] = newPos2[1];

    GLfloat dx2 = newPos2[0]-newPos1[0];
    GLfloat dy2 = newPos2[1]-newPos1[1];
	GLfloat Abstand2=sqrt(dx2*dx2+dy2*dy2);
	GLfloat dx = dx2/Abstand2;
	GLfloat dy = dy2/Abstand2;


    GLfloat direction = (BallSpeed[second_ball][0]-BallSpeed[first_ball][0])*dx2
            + (BallSpeed[second_ball][1]-BallSpeed[first_ball][1])*dy2;

    if (direction < 0){
        GLfloat skalarp = .9*(BallSpeed[first_ball][0]*dx+BallSpeed[first_ball][1]*dy)-
            (BallSpeed[second_ball][0]*dx+BallSpeed[second_ball][1]*dy);
		GLfloat Kraftx = dx * skalarp;
		GLfloat Krafty = dy * skalarp;
        BallSpeed[first_ball][0] = (BallSpeed[first_ball][0] - Kraftx) * verlust; // neuer Geschw.-Vektor
        BallSpeed[first_ball][1] = (BallSpeed[first_ball][1] - Krafty) * verlust;
        BallSpeed[second_ball][0] = (BallSpeed[second_ball][0] + Kraftx) * verlust;
        BallSpeed[second_ball][1] = (BallSpeed[second_ball][1] + Krafty) * verlust;
	}
}

/*
 *
 *
 *
 */
void Physics(GLfloat ShotSpeed_x,GLfloat ShotSpeed_y) {

	//printf(" Berechne Stoss ...");
	fflush(stdout);
    // ------------------------ 变量初始化 ------------------------

	GLint Aufloesung = PhysicsFrequenz; // min. 100
    GLfloat TableLen = 22.22; // x-Achse
    GLfloat TableWidth = 11.11; // y-Achse

	GLfloat reibung =  FrictionFactor; // Geschw.-Abzug durch Reibung
    GLfloat band_factor = GangsFactor; // Verlust an Banden

    // ---------------------------Ball positions read and speed set  ----------
    // first Tabelleneintrag enthaellt Start position
    for (GLint i=0;i<16;i++) {
		LightingTable[0][i][0]=Ball[i].Pos_xD(); 
		LightingTable[0][i][1]=Ball[i].Pos_yD();
		LightingTable[0][i][2]=0;

        oldPos[i][0]=Ball[i].Pos_xD();
        oldPos[i][1]=Ball[i].Pos_yD();
        oldPos[i][2]=0;

        newPos[i][2]=0; //Kugel liegt noch auf dem Tisch

        BallSpeed[i][0]=0.0;
        BallSpeed[i][1]=0.0;
	}

    //白球速度
    BallSpeed[0][0] = ShotSpeed_x; //击球速度
    BallSpeed[0][1] = ShotSpeed_y;

    // ------------- Calculation by discrete time steps ---------------------
    int moving = 0;  //moving
	for (int zeit=0;zeit<(20*Aufloesung);zeit++){
        moving = 0; // noch keine Bewegung

		// neue Position berechnen
		for (int nr=0;nr<16;nr++){
            if (oldPos[nr][0] == 1500.0) {
                newPos[nr][0] = 1500.0;
			}
			else {
                newPos[nr][0] = oldPos[nr][0]+BallSpeed[nr][0]/Aufloesung;
                newPos[nr][1] = oldPos[nr][1]+BallSpeed[nr][1]/Aufloesung;
                if (oldPos[nr][2]<0){
                    newPos[nr][2] = oldPos[nr][2]*(1+FallFaktor/Aufloesung);   // Kugel faellt
                    //moving = 1;                                                   // und movingt sich damit
				}
				else
				{
                    newPos[nr][2] = (fabs(BallSpeed[nr][0])+fabs(BallSpeed[nr][1])>0)?0:1;
				}
			}
		}

        // ------------------------ 与另一个球碰撞 ----------------------------------

		{
			for (int i=0;i<15;i++){          //letzte Kugel wird nicht betrachtet
                if (newPos[i][0] != 1500.0){
					for (int i2=i+1;i2<16;i2++){   //nur verbleibende Kugeln beruecksichtigen
                        if (newPos[i2][0] != 1500.0){
                            GLfloat dx = newPos[i][0] - newPos[i2][0];
                            GLfloat dy = newPos[i][1] - newPos[i2][1];
							GLfloat dBetraghoch2 = dx*dx + dy*dy; // Quadratwurzel sparen
							if (dBetraghoch2 <= 1){
                                // Collision
                                Collision(newPos[i],newPos[i2],i,i2);
                                Judge.BallBall(i,newPos[i][0],i2,newPos[i2][0]);
							}
						}
					}
				}
			}
		}

        // ------------------ 进洞--------------------------
		GLfloat Betrax,Betray;
		for (int i=0;i<16;i++){
            if (newPos[i][0]!=1500){
                if (newPos[i][2]<0){
                    sink(i);
				} else {
                    GLfloat x=newPos[i][0];
                    GLfloat y=newPos[i][1];

                  /*   O--------23.32------O--------23.32------O
                   *   |                   |                   |
                   * 12.21               12.55               12.21
                   *   |                   |                   |
                   *   |-------------------|-------------------|
                   *   |                   |                   |
                   * 12.21               12.55               12.21
                   *   |                   |                   |
                   *   O--------23.32------O--------23.32------O
                   */

					if ((x-23.32)*(x-23.32)+(y-12.21)*(y-12.21)<2.808) {
                        Judge.BallHole(i,33);
					}
					if ((x+23.32)*(x+23.32)+(y-12.21)*(y-12.21)<2.808) {
                        Judge.BallHole(i,35);
					}
					if ((x-23.32)*(x-23.32)+(y+12.21)*(y+12.21)<2.808) {
                        Judge.BallHole(i,32);
					}
					if ((x+23.32)*(x+23.32)+(y+12.21)*(y+12.21)<2.808) {
                        Judge.BallHole(i,30);
					}
					if (x*x+(y-12.55)*(y-12.55)<1.617) {
                        Judge.BallHole(i,34);
					}
					if (x*x+(y+12.55)*(y+12.55)<1.617) {
                        Judge.BallHole(i,31);
					}

                    Betrax=fabs(newPos[i][0]);
                    Betray=fabs(newPos[i][1]);
                    if ((Betrax-23.32)*(Betrax-23.32)+(Betray-12.21)*(Betray-12.21)<2.808) {     // edge
                        sink(i);
						//printf("\nKugel %i versenkt",i);
					}
                    if ((Betrax)*(Betrax)+(Betray-12.55)*(Betray-12.55)<1.617){                  // middle
                        sink(i);
						//printf("\nKugel %i versenkt",i);
					}
				}
			}
		}


        // ------------------- 撞边 ---------------------
        // der Kuerzungsfaktor ist 1-band_factor*cosinus Ausfallwinkel
        // somit stellt der band_factor den max. moeglichen Faktor dar (bei senkrechter Reflexion)
		{
			for (int i=0;i<16;i++){
                if (newPos[i][0] != 1500.0) {
                    GLfloat length = 1;
					GLfloat faktor = 1;

                    //below

                    if (newPos[i][1]<(-TableWidth+0.5)) {
                        if (((newPos[i][0]>-20.53)&&(newPos[i][0]<-1.137))
                                ||((newPos[i][0]<20.53)&&(newPos[i][0]>1.137))){
                            Judge.BallBand(i,newPos[i][0],21);
                            newPos[i][1]=(-TableWidth+0.5);
                            length=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-band_factor*(-BallSpeed[i][1]/length);
                            BallSpeed[i][1]=-BallSpeed[i][1]* faktor;
                            BallSpeed[i][0]=BallSpeed[i][0]* faktor;
						} else {
                            // right
                            if (newPos[i][0]>=20.53){
                                if (newPos[i][1] <= -0.75355 * (newPos[i][0]-20.53) + (-TableWidth+0.62)){
                                    Judge.BallBand(i,newPos[i][0],21);
                                    //neuePos[i][1] = -0.75355 * (neuePos[i][0]-20.53) + (-TableWidth+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
                            // left
                            if (newPos[i][0]<=-20.53){
                                if (newPos[i][1] <= 0.75355 * (newPos[i][0]+20.53) + (-TableWidth+0.62)){
                                    Judge.BallBand(i,newPos[i][0],21);
                                    //neuePos[i][1] = 0.75355 * (neuePos[i][0]+20.53) + (-TableWidth+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
                            // middle right
                            if ((newPos[i][0]>0)&&(newPos[i][0]<=1.137)){
                                if (newPos[i][1] <= 5.671 * (newPos[i][0]-1.137) + (-TableWidth+2.879)){
                                    Judge.BallBand(i,newPos[i][0],21);
                                    //neuePos[i][1] = 5.671 * (neuePos[i][0]-1.137) + (-TableWidth+2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = 0.984808;
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
                            // middle left
                            if ((newPos[i][0]<=0)&&(newPos[i][0]>=-1.137)){
                                if (newPos[i][1] <= -5.671 * (newPos[i][0]+1.137) + (-TableWidth+2.879)){
                                    Judge.BallBand(i,newPos[i][0],21);
                                    //neuePos[i][1] = -5.671 * (neuePos[i][0]+1.137) + (-TableWidth+2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = -0.984808;
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}

                    //above
                    if (newPos[i][1]>(TableWidth-0.5)){
                        if (((newPos[i][0]>-20.53)&&(newPos[i][0]<-1.137))||((newPos[i][0]<20.53)&&(newPos[i][0]>1.137))){
                            Judge.BallBand(i,newPos[i][0],23);
                            newPos[i][1]=(TableWidth-0.5);
                            length=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-band_factor*(BallSpeed[i][1]/length);
                            BallSpeed[i][1]=-BallSpeed[i][1]*faktor;
                            BallSpeed[i][0]=BallSpeed[i][0]*faktor;
						} else {
							// rechts
                            if (newPos[i][0]>=20.53){
                                if (newPos[i][1] >= 0.75355 * (newPos[i][0]-20.53) + (TableWidth-0.62)){
                                    Judge.BallBand(i,newPos[i][0],23);
                                    //neuePos[i][1] = 0.75355 * (neuePos[i][0]-20.53) + (TableWidth-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// links
                            if (newPos[i][0]<=-20.53){
                                if (newPos[i][1] >= -0.75355 * (newPos[i][0]+20.53) + (TableWidth-0.62)){
                                    Judge.BallBand(i,newPos[i][0],23);
                                    //neuePos[i][1] = -0.75355 * (neuePos[i][0]+20.53) + (TableWidth-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// Mitte rechts
                            if ((newPos[i][0]>0)&&(newPos[i][0]<=1.137)){
                                if (newPos[i][1] >= -5.671 * (newPos[i][0]-1.137) + (TableWidth-2.879)){
                                    Judge.BallBand(i,newPos[i][0],23);
                                    //neuePos[i][1] = -5.671 * (neuePos[i][0]-1.137) + (TableWidth-2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = -0.984808;		   
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// Mitte links
                            if ((newPos[i][0]<=0)&&(newPos[i][0]>=-1.137)){
                                if (newPos[i][1] >=  5.671 * (newPos[i][0]+1.137) + (TableWidth-2.879)){
                                    Judge.BallBand(i,newPos[i][0],23);
                                    //neuePos[i][1] =  5.671 * (neuePos[i][0]+1.137) + (TableWidth-2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = 0.984808;	
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}

                    //left
                    if (newPos[i][0]<(-TableLen+0.5)) {
                        if ((newPos[i][1]>-9.37)&&(newPos[i][1]<9.37)){
                            Judge.BallBand(i,newPos[i][0],20);
                            newPos[i][0]=(-TableLen+0.5);
                            length=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-band_factor*(-BallSpeed[i][0]/length);
                            BallSpeed[i][0]=-BallSpeed[i][0]*faktor;
                            BallSpeed[i][1]=BallSpeed[i][1]*faktor;
						} else {
							// oben
                            if (newPos[i][1]>=9.37){
                                if (newPos[i][0] <= -0.75355 * (newPos[i][1]-9.37) + (-TableLen+0.62)){
                                    Judge.BallBand(i,newPos[i][0],20);
                                    //neuePos[i][0] = -0.75355 * (neuePos[i][1]-9.37) + (-TableLen+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// unten
                            if (newPos[i][1]<=-9.37){
                                if (newPos[i][0] <= 0.75355 * (newPos[i][1]+9.37) + (-TableLen+0.62)){
                                    Judge.BallBand(i,newPos[i][0],20);
                                    //neuePos[i][0] = 0.75355 * (neuePos[i][1]+9.37) + (-TableLen+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}

                    //right
                    if (newPos[i][0]>(TableLen-0.5)){
                        if ((newPos[i][1]>-9.37)&&(newPos[i][1]<9.37)){
                            Judge.BallBand(i,newPos[i][0],22);
                            newPos[i][0]=(TableLen-0.5);
                            length=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-band_factor*(BallSpeed[i][0]/length);
                            BallSpeed[i][0]=-BallSpeed[i][0]*faktor;
                            BallSpeed[i][1]=BallSpeed[i][1]*faktor;
						} else {
							// oben
                            if (newPos[i][1]>=9.37){
                                if (newPos[i][0] >= 0.75355 * (newPos[i][1]-9.37) + (TableLen-0.62)){
                                    Judge.BallBand(i,newPos[i][0],22);
                                    //neuePos[i][0] = 0.75355 * (neuePos[i][1]-9.37) + (TableLen-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// unten
                            if (newPos[i][1]<=-9.37){
                                if (newPos[i][0] >= -0.75355 * (newPos[i][1]+9.37) + (TableLen-0.62)){
                                    Judge.BallBand(i,newPos[i][0],22);
                                    //neuePos[i][0] = -0.75355 * (neuePos[i][1]+9.37) + (TableLen-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    newPos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    newPos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}
				}
			}
		}


        // ------------------------------- table update -------------------------------
		GLint zeitpunkt = zeit*100/Aufloesung; // aktuelle Zeit berechnen (fuer Tabelle)
		{
			for (int i=0;i<16;i++){
                LightingTable[zeitpunkt][i][0] = newPos[i][0];
                LightingTable[zeitpunkt][i][1] = newPos[i][1];
                LightingTable[zeitpunkt][i][2] = newPos[i][2];
			}
		}



        // -------------------------- 计算新速度 ----------------------------
		{
			for (int i=0;i<16;i++){
                if (newPos[i][0] != 1500.0){
                    GLfloat geschw = sqrt(BallSpeed[i][0]* BallSpeed[i][0] +  BallSpeed[i][1]* BallSpeed[i][1]);
					GLfloat geschwneu = geschw - (reibung/Aufloesung);
                    if (newPos[i][2]<0){ moving=1;  } // Kugel faellt und movingt sich damit
					if (geschwneu <= 0.0) {  // Kugel bleibt stehen
                        BallSpeed[i][0] = 0.0;
                        BallSpeed[i][1] = 0.0;
					}
					else {
                        BallSpeed[i][0] = (BallSpeed[i][0] / geschw) * geschwneu; // neue Geschw. wird gesetzt
                        BallSpeed[i][1] = (BallSpeed[i][1] / geschw) * geschwneu;
                        moving = 1; // Es movingt sich noch was...
					}
				}
			}
		}


        // -------------------- Stossdauer setzen ------------------------------------

        if (moving) {
			Stossdauer = (zeitpunkt<1999)?zeitpunkt+1:1999;
		}

        //  Daten umschreiben
        {
			for (int i=0;i<16;i++){
                oldPos[i][0]=newPos[i][0];
                oldPos[i][1]=newPos[i][1];
                oldPos[i][2]=newPos[i][2];
			}
		}
	} 

	//printf(" fertig!\n\n");


}


