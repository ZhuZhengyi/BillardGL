#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include "ElapsedTime.h"
#include "Namen.h"
#include "Ball.h"
#include "TextItem.h"
#include "Label.h"
#include "Menu.h"
#include "BoardLayout.h"

GLfloat random(GLfloat Epsilon) {
	return (Epsilon*(((rand()*2.0)/RAND_MAX)-1));
}

void BoardLayout() {
    if (StateMachine==VIEWING||
			StateMachine==START||
            StateMachine==NEW_WHITE||
            StateMachine==JUDGEING) {

        LageVerbesserungKopffeld=1;     //Situation improving header

		GLfloat r=5.715;
		GLfloat a=r+3*Epsilon;
		GLfloat asw3=a*sqrt(3)/6;

		srand(ElapsedTime());

		//Anzeige.AlleKugelnAusblenden();

		for (int i=0;i<16;i++) {
			BallsInGame[i]=0;
			BallsSunk[i]=0;
		}


        switch (GameType) {        // Was f"ur ein Spiel?

            case TWO_PLAYERS: {               // Nur zwei Kugeln
						Ball[0].newPositionCM(0.0,0.0);
						Ball[1].newPositionCM(20.0,0.0);
						for (int i=0;i<2;i++) {
							BallsInGame[i]=1;
						}
						for (int j=2;j<16;j++) {
							Ball[j].disappear();
						}
						break;
					}

            case EIGHT_BALL: {               // 8-Ball

						GLint plaziert[16];
						GLint nummer[16];

						do {
							{
								for (GLint i=0;i<16;i++) {
									nummer[i]=0;
									plaziert[i]=0;
								}
							}
							nummer[0]=0;
							plaziert[0]=1;
							nummer[8]=8;
							plaziert[8]=1;

							for (GLint pos=1; pos<16;pos++) {
								while (!nummer[pos]) {
									GLint kugel=(GLint) (rand()*16.0/RAND_MAX);
									if (!plaziert[kugel]) {
										nummer[pos]=kugel;
										plaziert[kugel]=1;
									}
								}
							}
						} while ((nummer[1]<8)&&(nummer[15]<8)||(nummer[1]>8)&&(nummer[15]>8));

						Ball[nummer[0]].newPositionCM(-63.5,0.0);
						Ball[nummer[1]].newPositionCM(63.5+12*asw3+random(Epsilon),-2.0*a+random(Epsilon));
						Ball[nummer[2]].newPositionCM(63.5+9*asw3+random(Epsilon),-1.5*a+random(Epsilon));
						Ball[nummer[3]].newPositionCM(63.5+6*asw3+random(Epsilon),-1.0*a+random(Epsilon));
						Ball[nummer[4]].newPositionCM(63.5+3*asw3+random(Epsilon),-0.5*a+random(Epsilon));
						Ball[nummer[5]].newPositionCM(63.5+0*asw3+random(Epsilon),0.0+random(Epsilon));
						Ball[nummer[6]].newPositionCM(63.5+12*asw3+random(Epsilon),-1.0*a+random(Epsilon));
						Ball[nummer[7]].newPositionCM(63.5+9*asw3+random(Epsilon),-0.5*a+random(Epsilon));
						Ball[nummer[8]].newPositionCM(63.5+6*asw3+random(Epsilon),0.0+random(Epsilon));
						Ball[nummer[9]].newPositionCM(63.5+3*asw3+random(Epsilon),0.5*a+random(Epsilon));
						Ball[nummer[10]].newPositionCM(63.5+12*asw3+random(Epsilon),0.0+random(Epsilon));
						Ball[nummer[11]].newPositionCM(63.5+9*asw3+random(Epsilon),0.5*a+random(Epsilon));
						Ball[nummer[12]].newPositionCM(63.5+6*asw3+random(Epsilon),1.0*a+random(Epsilon));
						Ball[nummer[13]].newPositionCM(63.5+12*asw3+random(Epsilon),1.0*a+random(Epsilon));
						Ball[nummer[14]].newPositionCM(63.5+9*asw3+random(Epsilon),1.5*a+random(Epsilon));
						Ball[nummer[15]].newPositionCM(63.5+12*asw3+random(Epsilon),2.0*a+random(Epsilon));

						{
							for (int i=0;i<=15;i++) {
								BallsInGame[i]=1;
							}
						}

						break;
					}

            case NINE_BALL: {               // 9-Ball

						GLint plaziert[10];
						GLint nummer[10];

						{
							for (int i=0;i<10;i++) {
								BallsInGame[i]=1;
								nummer[i]=0;
								plaziert[i]=0;
							}
						}
						nummer[0]=0;
						plaziert[0]=1;
						nummer[3]=1;
						plaziert[1]=1;
						nummer[9]=9;
						plaziert[9]=1;

						for (GLint pos=1; pos<10;pos++) {
							while (!nummer[pos]) {
								GLint kugel=(GLint) (rand()*10.0/RAND_MAX);
								if (!plaziert[kugel]) {
									nummer[pos]=kugel;
									plaziert[kugel]=1;
								}
							}
						}

						Ball[nummer[0]].newPositionCM(-63.5,0.0);
						Ball[nummer[1]].newPositionCM(63.5+6*asw3+random(Epsilon),-1.0*a+random(Epsilon));
						Ball[nummer[2]].newPositionCM(63.5+3*asw3+random(Epsilon),-0.5*a+random(Epsilon));
						Ball[nummer[3]].newPositionCM(63.5+0*asw3+random(Epsilon),0.0+random(Epsilon));
						Ball[nummer[4]].newPositionCM(63.5+3*asw3+random(Epsilon),0.5*a+random(Epsilon));
						Ball[nummer[5]].newPositionCM(63.5+6*asw3+random(Epsilon),1.0*a+random(Epsilon));
						Ball[nummer[6]].newPositionCM(63.5+9*asw3+random(Epsilon),0.5*a+random(Epsilon));
						Ball[nummer[7]].newPositionCM(63.5+12*asw3+random(Epsilon),0.0+random(Epsilon));
						Ball[nummer[8]].newPositionCM(63.5+9*asw3+random(Epsilon),-0.5*a+random(Epsilon));
						Ball[nummer[9]].newPositionCM(63.5+6*asw3+random(Epsilon),0.0+random(Epsilon));

						{
							for (int i=10;i<16;i++) {
								Ball[i].disappear();
							}
						}
						break;
					}

            case GT_RANDOM: {               // Zufalls-Belegung
						{
							for (int i=0;i<=15;i++) {
								BallsInGame[i]=1;
							}
						}
						{
							for (int i=0;i<16;i++) {
								GLfloat min,x,y;
								do {
									min=3000;
									x=118*((((rand()+0.0)/RAND_MAX)*2)-1);
									y= 59*((((rand()+0.0)/RAND_MAX)*2)-1);
									for (int j=0;j<i;j++) {
										GLfloat dx=x-Ball[j].Pos_xCM();
										GLfloat dy=y-Ball[j].Pos_yCM();
										GLfloat Abstand=sqrt(dx*dx+dy*dy);
										if (Abstand<min) {min=Abstand;}
									}
								} while (min<7);
								Ball[i].newPositionCM(x,y);
							}
							break;
						}
					}

            case GT_EMPTY: {               // Keine Kugeln
						{
							for (int i=0;i<16;i++) {
								Ball[i].disappear();
							}
						}
						break;
					}

		}
	}

    Menu.NewMenuState();

}
