#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "LA.h"
#include "bmp.h"
#include "createTexture.h"
#include "Label.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


Label::Label() {
    LabelIndex=0;
    labelType=0;
    Aspect=0;
	ax=ay=bx=by=0.0;
	Alpha=0.0;
	soll_ax=soll_ay=soll_bx=soll_by=0.0;
	soll_Alpha=0.0;
	alt_ax=alt_ay=alt_bx=alt_by=0.0;
	alt_Alpha=0.0;
	InAnimation=0;
	Signal=0;
    ElapseTime=0;
    Texture=0;
	//
}

void Label::Init(GLint TexGr,
		char Name[],
		char AlphaName[]){
	FMatrix texr,texg,texb,texa;     // Matrix-Bilder, in die die Textur kommt
    if (!LabelIndex) {
        LabelIndex=glGenLists(1);
	}
    if (!Texture)
        glGenTextures(1,&Texture);
	char DateiName[60];
	sprintf(DateiName,"Texturen/%i/%s.bmp",TexGr,Name);   
	loadBMP(texr,texg,texb,DateiName);
	sprintf(DateiName,"Texturen/%i/%s.bmp",TexGr,AlphaName);   
	loadBMP(texa,texa,texa,DateiName);
    glBindTexture(GL_TEXTURE_2D,Texture);
	createTextureAlpha2(texr,texg,texb,texa);

    glNewList(LabelIndex,GL_COMPILE_AND_EXECUTE);
    glBindTexture(GL_TEXTURE_2D,Texture);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
	glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
	glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
	glEnd();     
	glDisable(GL_TEXTURE_2D);
	glEndList();

    Aspect=(texr.nch+1.0)/(texr.nrh+1.0);

	texr.free_FMatrix();
	texg.free_FMatrix();
	texb.free_FMatrix();
	texa.free_FMatrix();

	ax=alt_ax=soll_ax=0;
	ay=alt_ay=soll_ay=0;
	bx=alt_bx=soll_bx=0;
	by=alt_by=soll_by=0;

    Alpha=alt_Alpha=soll_Alpha=HIDDEN;
	InAnimation=0; 

    labelType=1;

}

void Label::Init(GLint TexGr,
		char Name[]){
	FMatrix texr,texg,texb;     // Matrix-Bilder, in die die Textur kommt
    if (!LabelIndex) {
        LabelIndex=glGenLists(1);
	}
    if (!Texture)
        glGenTextures(1,&Texture);
	char DateiName[60];
	sprintf(DateiName,"Texturen/%i/%s.bmp",TexGr,Name); 
	loadBMP(texr,texg,texb,DateiName);
    glBindTexture(GL_TEXTURE_2D,Texture);
	createTextureAlpha(texr,texg,texb);

    glNewList(LabelIndex,GL_COMPILE_AND_EXECUTE);
    glBindTexture(GL_TEXTURE_2D,Texture);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
	glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
	glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
	glEnd();     
	glDisable(GL_TEXTURE_2D);
	glEndList();

    Aspect=(texr.nch+1.0)/(texr.nrh+1.0);

	texr.free_FMatrix();
	texg.free_FMatrix();
	texb.free_FMatrix();

	ax=0; alt_ax=0; soll_ax=0;
	ay=0, alt_ay=0; soll_ay=0;
	bx=0; alt_bx=0; soll_bx=0;
	by=0; alt_by=0; soll_by=0;

    Alpha=alt_Alpha=soll_Alpha=HIDDEN;
	InAnimation=0; 

    labelType=1;
}

void Label::InitLogo() {
    if (!LabelIndex) {
        LabelIndex=glGenLists(1);
	}
    Texture=LogoTexture;
    glNewList(LabelIndex,GL_COMPILE_AND_EXECUTE);
    glBindTexture(GL_TEXTURE_2D,Texture);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
	glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
	glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
	glEnd();     
	glDisable(GL_TEXTURE_2D);
	glEndList();

    Aspect=4;

	ax=0; alt_ax=0; soll_ax=0;
	ay=0, alt_ay=0; soll_ay=0;
	bx=0; alt_bx=0; soll_bx=0;
	by=0; alt_by=0; soll_by=0;

    Alpha=alt_Alpha=soll_Alpha=HIDDEN;
	InAnimation=0; 

    labelType=1;
}

void Label::InitLetter(GLint TexGr,
		char Name[]){
	FMatrix texr,texg,texb;     // Matrix-Bilder, in die die Textur kommt
    if (!LabelIndex) {
        LabelIndex=glGenLists(1);
	}
    if (!Texture)
        glGenTextures(1,&Texture);
	char DateiName[60];
	sprintf(DateiName,"Texturen/buchstaben/%i/%s.bmp",TexGr,Name); 
	loadBMP(texr,texg,texb,DateiName);
    glBindTexture(GL_TEXTURE_2D,Texture);
	createTextureAlpha(texr,texg,texb);

    glNewList(LabelIndex,GL_COMPILE_AND_EXECUTE);
    glBindTexture(GL_TEXTURE_2D,Texture);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
	glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
	glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
	glEnd();     
	glDisable(GL_TEXTURE_2D);
	glEndList();

    Aspect=(texr.nch+1.0)/(texr.nrh+1.0);

	texr.free_FMatrix();
	texg.free_FMatrix();
	texb.free_FMatrix();

	ax=0; alt_ax=0; soll_ax=0;
	ay=0, alt_ay=0; soll_ay=0;
	bx=0; alt_bx=0; soll_bx=0;
	by=0; alt_by=0; soll_by=0;

    Alpha=alt_Alpha=soll_Alpha=HIDDEN;
	InAnimation=0; 

    labelType=1;
}

void Label::Init(GLint TexGr,
		char Name[],
		char Land){
	Land='c';
	FMatrix texr,texg,texb;     // Matrix-Bilder, in die die Textur kommt
    if (!LabelIndex) {
        LabelIndex=glGenLists(1);
	}
    if (!Texture)
        glGenTextures(1,&Texture);
	char DateiName[60];
	sprintf(DateiName,"Texturen/%i/%s.bmp",TexGr,Name); 
	loadBMP(texr,texg,texb,DateiName);
    glBindTexture(GL_TEXTURE_2D,Texture);
	createTexture(texr,texg,texb);

    glNewList(LabelIndex,GL_COMPILE_AND_EXECUTE);
    glBindTexture(GL_TEXTURE_2D,Texture);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
	glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
	glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
	glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
	glEnd();     
	glDisable(GL_TEXTURE_2D);
	glEndList();

    Aspect=(texr.nch+1.0)/(texr.nrh+1.0);

	texr.free_FMatrix();
	texg.free_FMatrix();
	texb.free_FMatrix();

	ax=0; alt_ax=0; soll_ax=0;
	ay=0, alt_ay=0; soll_ay=0;
	bx=0; alt_bx=0; soll_bx=0;
	by=0; alt_by=0; soll_by=0;

    Alpha=alt_Alpha=soll_Alpha=HIDDEN;
	InAnimation=0; 

    labelType=1;
}

void Label::Init(){
    if (!LabelIndex) {
        LabelIndex=glGenLists(1);
	}
    glNewList(LabelIndex,GL_COMPILE_AND_EXECUTE);
	glBegin(GL_QUADS);
	glVertex2f(0.0,0.0);
	glVertex2f(1.0,0.0);
	glVertex2f(1.0,1.0);
	glVertex2f(0.0,1.0);
	glEnd();     
	glEndList();

	ax=alt_ax=soll_ax=8;
	ay=alt_ay=soll_ay=6;
	bx=alt_bx=soll_bx=8.1;
	by=alt_by=soll_by=6.1;

    Alpha=alt_Alpha=soll_Alpha=HIDDEN;
    //Alpha=alt_Alpha=soll_Alpha=APPEAR;
	InAnimation=0; 

    Aspect=0.0;

    labelType=3;
}

void Label::CopyFrom(Label Vorbild) {
    LabelIndex=Vorbild.LabelIndex;
    labelType=Vorbild.labelType;
    Aspect=Vorbild.Aspect;
	ax=alt_ax=soll_ax=0;
	ay=alt_ay=soll_ay=0;
	bx=alt_bx=soll_bx=0;
	by=alt_by=soll_by=0;
    Alpha=alt_Alpha=soll_Alpha=HIDDEN;
	InAnimation=0; 
	Signal=0;
}

void Label::draw(){
	if (Alpha) {
		glPushMatrix();
		glTranslatef(ax,ay,0);
		glScalef(bx-ax,by-ay,1);
		glColor4f(1.0,1.0,1.0,Alpha);
        glCallList(LabelIndex);
		glPopMatrix();
	}
}

void Label::Positioning(GLfloat ax_,GLfloat ay_,GLfloat bx_,GLfloat by_) {
	// Nur wenn neue Position
	/*
	   if (soll_ax != ax_ ||
	   soll_ay != ay_ ||
	   soll_bx != bx_ ||
	   soll_by != by_) {
	   */ 
	{
		//printf("%f %f %f %f\n %f %f %f %f\n",
		//ax_,ay_,bx_,by_,soll_ax,soll_ay,soll_bx,soll_by);

		// Korrigiere Aspekt
        if (Aspect!=0.0 && Aspect!=(bx_-ax_)/(by_-ay_)) {
			GLfloat cx=(ax_+bx_)*.5;
            ax_=cx-Aspect*(by_-ay_)*.5;
            bx_=cx+Aspect*(by_-ay_)*.5;
		}

		soll_ax=ax_;
		soll_ay=ay_;
		soll_bx=bx_;
		soll_by=by_;

        if (labelType==3) {
			soll_Alpha=TRANSPARENT;
		} else {
            soll_Alpha=APPEAR;
		}  

        if (Alpha==HIDDEN) {

			ax=((soll_ax-8)/1.5)+8;
			ay=((soll_ay-6)/1.5)+6;
			bx=((soll_bx-8)/1.5)+8;
			by=((soll_by-6)/1.5)+6;

			/*
			   ax=((24.0*rand())/RAND_MAX)-4;
			   ay=((14.0*rand())/RAND_MAX)-1;
			   bx=ax+2*(bx_-ax_);
			   by=ay+2*(by_-ay_);     
			   */
		}

		Signal=0;

        StartAnimation();

		//printf("  %f %f %f %f\n   %f %f %f %f\n",
		//ax_,ay_,bx_,by_,soll_ax,soll_ay,soll_bx,soll_by);

	}
}

void Label::PositionFix(GLfloat ax_,GLfloat ay_,GLfloat bx_,GLfloat by_) {

    if (Aspect!=0.0 && Aspect!=(bx_-ax_)/(by_-ay_)) {
		GLfloat cx=(ax_+bx_)*.5;
        ax_=cx-Aspect*(by_-ay_)*.5;
        bx_=cx+Aspect*(by_-ay_)*.5;
	}

	ax=soll_ax=ax_;
	ay=soll_ay=ay_;
	bx=soll_bx=bx_;
	by=soll_by=by_;

    Alpha=soll_Alpha=APPEAR;
	Signal=0;
}

//deactivated
void Label::Disactive() {
    soll_Alpha=HIDDEN;

	soll_ax=((ax-8)*1.5)+8;
	soll_ay=((ay-6)*1.5)+6;
	soll_bx=((bx-8)*1.5)+8;
	soll_by=((by-6)*1.5)+6;

	/*  
		soll_ax=((24.0*rand())/RAND_MAX)-4;
		soll_ay=((14.0*rand())/RAND_MAX)-1;
		soll_bx=soll_ax+.5*(bx-ax);
		soll_by=soll_ay+.5*(by-ay);     
		*/
    if (soll_Alpha!=Alpha) StartAnimation();
}

//selected
void Label::Selected() {
    Alpha=SELECTED;
    soll_Alpha=APPEAR;
    if (soll_Alpha!=Alpha) StartAnimation();
}

//Superimposed
void Label::Eingeblendet() {
    soll_Alpha=APPEAR;
    if (soll_Alpha!=Alpha) StartAnimation();
}

//fully Visible
void Label::FullyVisible() {
    soll_Alpha=FULL_VISIBLE;
    if (soll_Alpha!=Alpha) StartAnimation();
}

void Label::StartAnimation(){
	InAnimation=1;
    ElapseTime=0;
	alt_ax=ax;
	alt_ay=ay;
	alt_bx=bx;
	alt_by=by;
	alt_Alpha=Alpha;
}  
/*
   GLint Schild::Animiere(GLint Zeit){
   if (!InAnimation) {return 0;}
   if (Zeit>=ANIMATION_TIME) {
   ax=soll_ax;
   ay=soll_ay;
   bx=soll_bx;
   by=soll_by;
   Alpha=soll_Alpha;
   InAnimation=0;
   return 1;
   } else {
   GLfloat Faktor=(.5-.5*cos(M_PI*Zeit/ANIMATION_TIME));
   ax=(soll_ax-alt_ax)*Faktor+alt_ax;
   ay=(soll_ay-alt_ay)*Faktor+alt_ay;
   bx=(soll_bx-alt_bx)*Faktor+alt_bx;
   by=(soll_by-alt_by)*Faktor+alt_by;
   Alpha=(soll_Alpha-alt_Alpha)*Faktor+alt_Alpha;
   return 0;
   }
   }
   */
GLint Label::Animate(GLint Faktor){
	if (!InAnimation) {return 0;}
    ElapseTime+=Faktor;
    if (ElapseTime>=ANIMATION_TIME) {
		ax=soll_ax;
		ay=soll_ay;
		bx=soll_bx;
		by=soll_by;
		Alpha=soll_Alpha;
		InAnimation=0;
		return 1;
	} else {
        GLfloat Faktor=(.5-.5*cos(M_PI*ElapseTime/ANIMATION_TIME));
		ax=(soll_ax-alt_ax)*Faktor+alt_ax;
		ay=(soll_ay-alt_ay)*Faktor+alt_ay;
		bx=(soll_bx-alt_bx)*Faktor+alt_bx;
		by=(soll_by-alt_by)*Faktor+alt_by;
		Alpha=(soll_Alpha-alt_Alpha)*Faktor+alt_Alpha;
		return 0;
	}
}



GLint Label::MouseButton(int Taste,int Richtung,int x,int y) {
	GLfloat xf=16.0*x/glutGet(GLUT_WINDOW_WIDTH);
	GLfloat yf=12.0-12.0*y/glutGet(GLUT_WINDOW_HEIGHT);

	if (soll_Alpha>0.0 &&
			Signal!=0 &&
			ax<=xf && xf<=bx && ay<=yf && yf<=by) {
		if (Taste==GLUT_LEFT_BUTTON) {
			if (Richtung==GLUT_DOWN) {
                Selected();
				return -1;
			} else {
				return Signal;
			}
		} else {
			return -1;
		}
	} else {
		return 0;
	}
}

void Label::SetSignal(GLint NewSignal) {
    Signal=NewSignal;
}
