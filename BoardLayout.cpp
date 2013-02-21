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

                        GLint placed[16];
                        GLint numbers[16];

						do {
							{
								for (GLint i=0;i<16;i++) {
                                    numbers[i]=0;
                                    placed[i]=0;
								}
							}
                            numbers[0]=0;
                            placed[0]=1;
                            numbers[8]=8;
                            placed[8]=1;

							for (GLint pos=1; pos<16;pos++) {
                                while (!numbers[pos]) {
                                    GLint ball_id=(GLint) (rand()*16.0/RAND_MAX);
                                    if (!placed[ball_id]) {
                                        numbers[pos]=ball_id;
                                        placed[ball_id]=1;
									}
								}
							}
                        } while ((numbers[1]<8)&&(numbers[15]<8)||(numbers[1]>8)&&(numbers[15]>8));

                        Ball[numbers[0]].newPositionCM(-63.5,0.0);
                        Ball[numbers[1]].newPositionCM(63.5+12*asw3+random(Epsilon),-2.0*a+random(Epsilon));
                        Ball[numbers[2]].newPositionCM(63.5+9*asw3+random(Epsilon),-1.5*a+random(Epsilon));
                        Ball[numbers[3]].newPositionCM(63.5+6*asw3+random(Epsilon),-1.0*a+random(Epsilon));
                        Ball[numbers[4]].newPositionCM(63.5+3*asw3+random(Epsilon),-0.5*a+random(Epsilon));
                        Ball[numbers[5]].newPositionCM(63.5+0*asw3+random(Epsilon),0.0+random(Epsilon));
                        Ball[numbers[6]].newPositionCM(63.5+12*asw3+random(Epsilon),-1.0*a+random(Epsilon));
                        Ball[numbers[7]].newPositionCM(63.5+9*asw3+random(Epsilon),-0.5*a+random(Epsilon));
                        Ball[numbers[8]].newPositionCM(63.5+6*asw3+random(Epsilon),0.0+random(Epsilon));
                        Ball[numbers[9]].newPositionCM(63.5+3*asw3+random(Epsilon),0.5*a+random(Epsilon));
                        Ball[numbers[10]].newPositionCM(63.5+12*asw3+random(Epsilon),0.0+random(Epsilon));
                        Ball[numbers[11]].newPositionCM(63.5+9*asw3+random(Epsilon),0.5*a+random(Epsilon));
                        Ball[numbers[12]].newPositionCM(63.5+6*asw3+random(Epsilon),1.0*a+random(Epsilon));
                        Ball[numbers[13]].newPositionCM(63.5+12*asw3+random(Epsilon),1.0*a+random(Epsilon));
                        Ball[numbers[14]].newPositionCM(63.5+9*asw3+random(Epsilon),1.5*a+random(Epsilon));
                        Ball[numbers[15]].newPositionCM(63.5+12*asw3+random(Epsilon),2.0*a+random(Epsilon));


                        for (int i=0;i<=15;i++) {
                            BallsInGame[i]=1;
                        }


						break;
					}

            case NINE_BALL: {               // 9-Ball

                        GLint placed[10];
                        GLint numbers[10];


                        for (int i=0;i<10;i++) {
                            BallsInGame[i]=1;
                            numbers[i]=0;
                            placed[i]=0;
                        }

                        numbers[0]=0;
                        placed[0]=1;
                        numbers[3]=1;
                        placed[1]=1;
                        numbers[9]=9;
                        placed[9]=1;

						for (GLint pos=1; pos<10;pos++) {
                            while (!numbers[pos]) {
                                GLint ball_id=(GLint) (rand()*10.0/RAND_MAX);
                                if (!placed[ball_id]) {
                                    numbers[pos]=ball_id;
                                    placed[ball_id]=1;
								}
							}
						}

                        Ball[numbers[0]].newPositionCM(-63.5,0.0);
                        Ball[numbers[1]].newPositionCM(63.5+6*asw3+random(Epsilon),-1.0*a+random(Epsilon));
                        Ball[numbers[2]].newPositionCM(63.5+3*asw3+random(Epsilon),-0.5*a+random(Epsilon));
                        Ball[numbers[3]].newPositionCM(63.5+0*asw3+random(Epsilon),0.0+random(Epsilon));
                        Ball[numbers[4]].newPositionCM(63.5+3*asw3+random(Epsilon),0.5*a+random(Epsilon));
                        Ball[numbers[5]].newPositionCM(63.5+6*asw3+random(Epsilon),1.0*a+random(Epsilon));
                        Ball[numbers[6]].newPositionCM(63.5+9*asw3+random(Epsilon),0.5*a+random(Epsilon));
                        Ball[numbers[7]].newPositionCM(63.5+12*asw3+random(Epsilon),0.0+random(Epsilon));
                        Ball[numbers[8]].newPositionCM(63.5+9*asw3+random(Epsilon),-0.5*a+random(Epsilon));
                        Ball[numbers[9]].newPositionCM(63.5+6*asw3+random(Epsilon),0.0+random(Epsilon));

                        for (int i=10;i<16;i++) {
                            Ball[i].disappear();
                        }

						break;
					}

            case GT_RANDOM: {               // Zufalls-Belegung
                        for (int i=0;i<=15;i++) {
                            BallsInGame[i]=1;
                        }

                        for (int i=0;i<16;i++) {
                            GLfloat min,x,y;
                            do {
                                min=3000;
                                x=118*((((rand()+0.0)/RAND_MAX)*2)-1);
                                y= 59*((((rand()+0.0)/RAND_MAX)*2)-1);
                                for (int j=0;j<i;j++) {
                                    GLfloat dx=x-Ball[j].Pos_xCM();
                                    GLfloat dy=y-Ball[j].Pos_yCM();
                                    GLfloat distance=sqrt(dx*dx+dy*dy);
                                    if (distance<min) {min=distance;}
                                }
                            } while (min<7);
                            Ball[i].newPositionCM(x,y);
                        }
                        break;
					}

            case GT_EMPTY: {               // Keine Kugeln

                        for (int i=0;i<16;i++) {
                            Ball[i].disappear();
                        }
						break;
					}

		}
	}

    Menu.NewMenuState();

}
