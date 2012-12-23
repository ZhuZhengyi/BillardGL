#include <GL/glut.h>
#include <stdlib.h>
#include "Ball.h"
#include "Camera.h"
#include "Chosen.h"

//white insert
void WhiteChosen() {
    if (LageVerbesserungKopffeld) {  //Situation improving header
		GLfloat x=-63.2,y=0.0;
		GLfloat mabs=100,abs;
		for (int nr=1;nr<16;nr++) {
			abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
				(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
			if (abs<mabs) {mabs=abs;}
		}
		if (mabs<=32.7) {
			while (mabs<32.7) {
				mabs=100;
				x=(rand()*60.5/RAND_MAX)-124;
				y=(rand()*121.0/RAND_MAX)-60.5;
				for (int nr=1;nr<16;nr++) {
					abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
						(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
					if (abs<mabs) {mabs=abs;}
				}
			}
		}
        Ball[0].newPositionCM(x,y);
		BallsSunk[0]=0;
		Camera.EyesOn2(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
	} else {
		GLfloat x=0.0,y=0.0;
		GLfloat mabs=100,abs;
		for (int nr=1;nr<16;nr++) {
			abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
				(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
			if (abs<mabs) {mabs=abs;}
		}
		if (mabs<=32.7) {
			while (mabs<32.7) {
				mabs=100;
				x=(rand()*248/RAND_MAX)-124;
				y=(rand()*121.0/RAND_MAX)-60.5;
				for (int nr=1;nr<16;nr++) {
					abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
						(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
					if (abs<mabs) {mabs=abs;}
				}
			}
		}
        Ball[0].newPositionCM(x,y);
		BallsSunk[0]=0;
		Camera.EyesOn2(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
	}
}

/*
 * eight insertion
 */
void EightChosen() {
    Ball[8].newPositionCM(3000,3000);
	GLfloat x=63.5,y=0.0;
	GLfloat mabs=100,abs;  

	for (int nr=1;nr<16;nr++) {
		abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
			(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
		if (abs<mabs) {mabs=abs;}
	}
	if (mabs<=32.7) {
		while (mabs<32.7) {
			mabs=100;
			x+=.1;
			for (int nr=0;nr<16;nr++) {
				abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
					(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
				if (abs<mabs) {mabs=abs;}
			}
		}
	}
    Ball[8].newPositionCM(x,y);
	BallsSunk[8]=0;
}

//
//nine insertion
void NineChosen() {
    Ball[9].newPositionCM(3000,3000);
	GLfloat x=63.5,y=0.0;
	GLfloat mabs=100,abs;  

	for (int nr=1;nr<16;nr++) {
		abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
			(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
		if (abs<mabs) {mabs=abs;}
	}
	if (mabs<=32.7) {
		while (mabs<32.7) {
			mabs=100;
			x+=.1;
			for (int nr=0;nr<16;nr++) {
				abs=(Ball[nr].Pos_xCM()-x)*(Ball[nr].Pos_xCM()-x)+
					(Ball[nr].Pos_yCM()-y)*(Ball[nr].Pos_yCM()-y);
				if (abs<mabs) {mabs=abs;}
			}
		}
	}
    Ball[9].newPositionCM(x,y);
	BallsSunk[9]=0;
}
