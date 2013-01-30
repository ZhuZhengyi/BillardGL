#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "LA.h"
#include "bmp.h"
#include "createTexture.h"
#include "TextItem.h"

GLint ti_left[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
	0,  9, 11,  9,  9,  8,  8,  7,  8,  7,  7,  7,  6,  8,  9,  7, 
	9,  7,  8,  7,  7,  7,  8,  7,  7,  7,  9,  6,  8,  7,  7,  7, 
	9,  7,  9,  8,  9,  9,  9,  8,  8,  8,  7,  8,  8,  7,  8,  7, 
	9,  8,  9,  7,  6,  8,  6,  7,  7,  6,  6, 10,  7,  7,  9,  5, 
	5,  8,  9,  8,  8,  8,  6,  7,  8,  8,  8,  8,  8,  7,  8,  7, 
	9,  8,  9,  8,  7,  8,  7,  7,  7,  7,  7,  7,  9,  6,  8,  0, 

	0,  0,  0,  8,  7, 10,  8,  8,  3,  7,  0,  9,  7,  0,  0,  0, 
	0,  7,  8,  8,  7, 10,  7,  8,  3,  9,  0, 10,  7,  0,  0,  0, 
	0,  9, 11,  8, 10,  8, 10,  9,  4,  8,  7,  9,  7,  0,  7,  0, 
	0,  8,  8,  8,  7,  8,  8,  9,  7,  7,  7,  9,  8,  8,  8,  7, 
	8,  7,  8,  7,  7,  7,  7,  8,  8,  8,  8,  8,  4,  7,  3,  4, 
	6,  9,  8,  8,  8,  8,  8,  0,  7,  8,  8,  8,  8,  6,  8,  8, 
	8,  8,  8,  8,  8,  8,  8,  7,  7,  7,  7,  7,  4,  6,  3,  3, 
	9,  9,  8,  8,  8,  8,  8,  0,  7,  8,  8,  8,  8,  6,  8,  6
};

GLint ti_right[]={
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
	10, 15, 22, 28, 29, 33, 33, 15, 15, 14, 20, 29, 14, 21, 14, 23, 
	31, 17, 26, 26, 30, 26, 27, 25, 27, 27, 15, 14, 28, 28, 28, 25, 
	37, 32, 29, 30, 32, 24, 24, 34, 32, 14, 21, 30, 23, 39, 32, 34,
	29, 36, 29, 27, 25, 32, 30, 43, 30, 28, 27, 19, 23, 16, 27, 26, 
	15, 28, 29, 24, 28, 27, 20, 27, 27, 13, 13, 26, 13, 38, 26, 27, 
	28, 28, 20, 23, 19, 27, 25, 37, 26, 26, 24, 19, 12, 19, 28,  0, 

	0,  0,  0, 28, 25, 43, 28, 28, 18, 47,  0, 17, 43,  0,  0,  0, 
	0, 16, 16, 25, 25, 23, 26, 22, 18, 44,  0, 17, 42,  0,  0,  0, 
	0, 15, 28, 31, 29, 30, 13, 28, 17, 37, 20, 27, 29,  0, 36,  0, 
	0, 30, 20, 20, 17, 27, 29, 15, 15, 13, 20, 27, 42, 41, 42, 24, 
	32, 32, 32, 31, 31, 31, 40, 30, 24, 24, 24, 24, 15, 17, 18, 17, 
	32, 33, 35, 35, 34, 35, 35,  0, 35, 32, 32, 32, 32, 27, 28, 27, 
	28, 28, 28, 28, 28, 28, 43, 24, 27, 27, 27, 27, 14, 17, 18, 17, 
	28, 27, 28, 28, 28, 28, 28,  0, 28, 26, 26, 26, 26, 25, 28, 25
};

TextItem::TextItem() {
	//
    x=y=Height=Aspekt=Alpha = 0;
    old_x=old_y=old_Height=old_Alpha = 0;
    soll_x=soll_y=soll_Height=soll_Alpha = 0;
    align = 0;
	InAnimation = 0;
	Signal = 0;
    life_time = 0;
    DisplayListArray = 0;
	for (GLint i=0;i<512;i++)
        TextureArray[i] = 0;
    TextItemIndex = 0;
	Horchen = 0;
    lines=0;

    MaxWidth=0;

}

GLint TextItem::dummyInit(GLint TexGr){
	FMatrix tex;
    if (!DisplayListArray)
        DisplayListArray=glGenLists(512);

    if (!TextureArray[0])
        glGenTextures(512,&TextureArray[0]);

	char DateiName[80];
	sprintf(DateiName,"Texturen/%i/buchstaben.bmp",TexGr); 
	loadBMP(tex,tex,tex,DateiName);
	GLint Rastergroesse=(tex.nch+1)/16;

    for (GLint letter=0;letter<256;letter++) {
        GLint x = letter % 16;
        GLint y = letter / 16;

        if (ti_right[letter] && letter!=32) {
            glBindTexture(GL_TEXTURE_2D,TextureArray[letter]);
			createTextureText(tex,x,y,Rastergroesse);
		}

        glNewList(DisplayListArray+letter,GL_COMPILE_AND_EXECUTE);
        if (ti_right[letter] && letter!=32) {
            glBindTexture(GL_TEXTURE_2D,TextureArray[letter]);
			//glEnable(GL_TEXTURE_2D);
			//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glBegin(GL_QUADS);
            //    printf ("%i %i %i\n",letter,x,y);
			glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
			glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
			glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
			glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
			glEnd();     
			//glDisable(GL_TEXTURE_2D);
		}
		glEndList();
	}

	sprintf(DateiName,"Texturen/%i/buchstabenalpha.bmp",TexGr); 
	loadBMP(tex,tex,tex,DateiName);
	Rastergroesse=(tex.nch+1)/16;

    for (GLint letter2=0;letter2<256;letter2++) {
        GLint x = letter2 % 16;
        GLint y = letter2 / 16;

        if (ti_right[letter2] && letter2!=32) {
            glBindTexture(GL_TEXTURE_2D,TextureArray[256+letter2]);
			createTextureText2(tex,x,y,Rastergroesse);
		}

        glNewList(DisplayListArray+256+letter2,GL_COMPILE_AND_EXECUTE);
        if (ti_right[letter2] && letter2!=32) {
            glBindTexture(GL_TEXTURE_2D,TextureArray[256+letter2]);
			//glEnable(GL_TEXTURE_2D);
			//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glBegin(GL_QUADS);
            //    printf ("%i %i %i\n",letter,x,y);
			glTexCoord2f(0.0,0.0);glVertex2f(0.0,0.0);
			glTexCoord2f(1.0,0.0);glVertex2f(1.0,0.0);
			glTexCoord2f(1.0,1.0);glVertex2f(1.0,1.0);
			glTexCoord2f(0.0,1.0);glVertex2f(0.0,1.0);
			glEnd();     
			//glDisable(GL_TEXTURE_2D);
		}
		glEndList();
	}

	tex.free_FMatrix();

    x=y=Height=Aspekt=Alpha=0.0;
    old_x=old_y=old_Height=old_Alpha=0.0;
    soll_x=soll_y=soll_Height=soll_Alpha=0.0;
    align=A_LINKS;
	InAnimation=0;
	Signal=0;
    life_time=0;
    text[0]='\0';
	Horchen=0;
    return DisplayListArray;
}

void TextItem::Initialisiere(GLint DLA){
    DisplayListArray=DLA;
    x=y=Height=Aspekt=Alpha=0.0;
    old_x=old_y=old_Height=old_Alpha=0.0;
    soll_x=soll_y=soll_Height=soll_Alpha=0.0;
    align=A_LINKS;
	InAnimation=0;
	Signal=0;
    life_time=0;
    text[0]='\0';
	Horchen=0;
}  

void TextItem::Initialisiere(GLint DLA, char TextZ[]){
	Initialisiere(DLA);
    SetText(TextZ);
}

void TextItem::InitialisiereKDL(GLint DLA, char TextZ[]){
	Initialisiere(DLA);
    SetTextKDL(TextZ);
}

void TextItem::draw(){
	if (Alpha<.03) {return;}
	glPushMatrix();
	glTranslatef(x,y,0);
    glScalef(Height,Height,1);
	glColor4f(1.0,1.0,1.0,Alpha);
    glCallList(TextItemIndex);
	glPopMatrix();

}

void TextItem::PositioniereFix(GLfloat X,GLfloat Y,GLfloat H,GLint A){

    if (A) align=A;

    switch (align) {
		case A_LINKS: { soll_x = X; } break;
		case A_MITTE: { soll_x = X-.5*Aspekt*H; } break;
		case A_RECHTS:{ soll_x = X-Aspekt*H; } break;
	}

	soll_y     = Y;
    soll_Height = H;
    soll_Alpha = APPEAR;

	x=soll_x;
	y=soll_y;
    Height=soll_Height;

	Signal=0;

}

void TextItem::Positioniere(GLfloat X,GLfloat Y,GLfloat H,GLint A){

    if (A) align=A;

    switch (align) {
		case A_LINKS: { soll_x = X; } break;
		case A_MITTE: { soll_x = X-.5*Aspekt*H; } break;
		case A_RECHTS:{ soll_x = X-Aspekt*H; } break;
	}

	soll_y     = Y;
    soll_Height = H;
    soll_Alpha = APPEAR;

	if (Alpha==HIDDEN) {

		x=((soll_x-8)/1.5)+8;
		y=((soll_y-6)/1.5)+6;
        Height=soll_Height/1.5;

		/*
		   ax=((24.0*rand())/RAND_MAX)-4;
		   ay=((14.0*rand())/RAND_MAX)-1;
		   bx=ax+2*(bx_-ax_);
		   by=ay+2*(by_-ay_);     
		   */
	}

	Signal=0;

    StartAnimation();
}


void TextItem::SetText(char TextZ[]){
	int i=0;
	while (TextZ[i] && i<1999) {
        text[i]=TextZ[i];
		i++;
	}
    text[i]=0;
    GenerateDisplayList();
}

void TextItem::SetTextKDL(char TextZ[]){
	int i=0;
	while (TextZ[i] && i<1999) {
        text[i]=TextZ[i];
		i++;
	}
    text[i]=0;
}

GLint TextItem::Label(char Taste){
	if (Horchen) {
		if (Taste>=32 &&
				Taste!=8 && Taste!=127 &&
				Taste!=12 && Taste!=10 ) {//normale Zeichen
			GLint i;
            for (i=0;i<9 && text[i];i++) {}
            if (i<9) sprintf(text,"%s%c",text,Taste);
            GenerateDisplayList();
			return 1;
		} else if (Taste==8 || Taste==127) { // loeschen
			for (GLint i=0;i<9;i++) 
                if (!text[i+1]) text[i]='\0';
            GenerateDisplayList();
			return 1;
		} else if (Taste==13 || Taste==10) { // enter
            soll_Alpha=APPEAR;
			Horchen=0;
            if (soll_Alpha!=Alpha) StartAnimation();
			//GeneriereDisplayList();
			return 1;
		}
	}
	return 0;
}

char* TextItem::Text(){return text;}

//deactivated
void TextItem::DisActivated(){
	soll_Alpha=HIDDEN;

	soll_x=((x-8)*1.5)+8;
	soll_y=((y-6)*1.5)+6;
    soll_Height=Height*1.5;

	Horchen = 0;

    if (soll_Alpha!=Alpha) StartAnimation();
}

//turning a deaf ear
void TextItem::Weghoeren(){
    if (Alpha && soll_Alpha) Appear();
	Horchen = 0;
}

//Listen up
void TextItem::Herhoeren(){
    FullyVisible();
	Horchen = 1;
}

//In chooses
void TextItem::Selected(){
	Alpha=SELECTED;
    soll_Alpha=APPEAR;
    if (soll_Alpha!=Alpha) StartAnimation();
}

//Superimposed
void TextItem::Appear(){
    soll_Alpha=APPEAR;
    if (soll_Alpha!=Alpha) StartAnimation();
}

//fully Visible
void TextItem::FullyVisible(){
	soll_Alpha=FULL_VISIBLE;
    if (soll_Alpha!=Alpha) StartAnimation();
}

GLint TextItem::Animiere(GLint Faktor){
	if (!InAnimation) {return 0;}
    life_time+=Faktor;
    if (life_time>=ANIMATION_TIME) {
		x=soll_x;
		y=soll_y;
        Height=soll_Height;
		Alpha=soll_Alpha;
		InAnimation=0;
		return 1;
	} else {
        GLfloat Faktor=(.5-.5*cos(M_PI*life_time/ANIMATION_TIME));
        x=(soll_x-old_x)*Faktor+old_x;
        y=(soll_y-old_y)*Faktor+old_y;
        Height=(soll_Height-old_Height)*Faktor+old_Height;
        Alpha=(soll_Alpha-old_Alpha)*Faktor+old_Alpha;
		//    printf("%i: %f\n",Zeit,Alpha);
		return 0;
	}
}

void TextItem::SetSignal(GLint NewSignal){
    Signal=NewSignal;
}

void TextItem::StartAnimation(){
	InAnimation=1;
    life_time=0;
    old_x=x;
    old_y=y;
    old_Height=Height;
    old_Alpha=Alpha;
}

void TextItem::GenerateDisplayList(){
    if (!TextItemIndex) {
        TextItemIndex=glGenLists(1);
	}

    if (!MaxWidth) {
        glNewList(TextItemIndex,GL_COMPILE_AND_EXECUTE);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		Aspekt=0.0;
        lines=1;
		GLint p=0;
		GLint c=0;
        while ((c=text[p++])) {
			if (c<0) c+=256;
            Aspekt+=(ti_right[c]-ti_left[c]+4)/64.0;
            glTranslatef(-ti_left[c]/64.0,0,0);
            glCallList(DisplayListArray+c+256);
            glTranslatef((ti_right[c]+4)/64.0,0,0);
		}
		glPopMatrix();
		glPushMatrix();
        lines=1;
		p=0;
        while ((c=text[p++])) {
			if (c<0) c+=256;
            glTranslatef(-ti_left[c]/64.0,0,0);
            glCallList(DisplayListArray+c);
            glTranslatef((ti_right[c]+4)/64.0,0,0);
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glEndList();
	}


    if (MaxWidth) {
        glNewList(TextItemIndex,GL_COMPILE_AND_EXECUTE);
		glEnable(GL_TEXTURE_2D);
		Aspekt=0.0;
        lines=1;

		GLint Anfang=0;
		GLint Zeichen=0;
		GLint Pos=0;
		GLint LeerzeichenAnzahl=0;
		GLint LetztesLeerzeichen=0;
        lines=0;
		GLfloat ZeilenBreite=0.0;
		GLfloat ZeilenBreiteBisLetztesLeerzeichen=0.0;
        while (text[Pos]) {

			Anfang=Pos;
			LeerzeichenAnzahl=0;
			LetztesLeerzeichen=0;
			ZeilenBreite=0.0;

            while ((Zeichen=text[Pos]) && ZeilenBreite<MaxWidth*1.05) {
				if (Zeichen==32) {
					ZeilenBreiteBisLetztesLeerzeichen=ZeilenBreite;
					LetztesLeerzeichen=Pos;
					LeerzeichenAnzahl++;
				}
				//printf("%c",Zeichen);fflush(stdout);
				if (Zeichen<0) Zeichen+=256;
                ZeilenBreite+=(ti_right[Zeichen]-ti_left[Zeichen]+4)/64.0;
				Pos++;
			}

            if (text[Pos]) { // noch nicht am Ende: Blocksatz
                GLfloat delta=(MaxWidth-ZeilenBreiteBisLetztesLeerzeichen)/(LeerzeichenAnzahl-1.0);
				//printf("%f\n",delta);
				glPushMatrix();
                glTranslatef(0,-lines*.7,0);
				GLint c;
				Pos=Anfang;
                while ((c=text[Pos++])&& Pos<=LetztesLeerzeichen) {
					if (c<0) c+=256;
                    glTranslatef(-ti_left[c]/64.0,0,0);
                    glCallList(DisplayListArray+c+256);
                    glTranslatef((ti_right[c]+4)/64.0,0,0);
					if (c==32) glTranslatef(delta,0,0);
				}
				glPopMatrix();
				glPushMatrix();
                glTranslatef(0,-lines*.7,0);
				Pos=Anfang;
                while ((c=text[Pos++])&& Pos<=LetztesLeerzeichen) {
					if (c<0) c+=256;
                    glTranslatef(-ti_left[c]/64.0,0,0);
                    glCallList(DisplayListArray+c);
                    glTranslatef((ti_right[c]+4)/64.0,0,0);
					if (c==32) glTranslatef(delta,0,0);
				}
				glPopMatrix();
                lines++;
			} else { // am Ende: Linksbuendig
				GLfloat delta=0;
                if (ZeilenBreite>MaxWidth)
                    delta=(MaxWidth-ZeilenBreite)/(LeerzeichenAnzahl+0.0);
				glPushMatrix();
                glTranslatef(0,-lines*.7,0);
				GLint c;
				Pos=Anfang;
                while ((c=text[Pos++])) {
					if (c<0) c+=256;
                    glTranslatef(-ti_left[c]/64.0,0,0);
                    glCallList(DisplayListArray+c+256);
                    glTranslatef((ti_right[c]+4)/64.0,0,0);
					if (c==32) glTranslatef(delta,0,0);
				}
				glPopMatrix();
				glPushMatrix();
                glTranslatef(0,-lines*.7,0);
				Pos=Anfang;
                while ((c=text[Pos++])) {
					if (c<0) c+=256;
                    glTranslatef(-ti_left[c]/64.0,0,0);
                    glCallList(DisplayListArray+c);
                    glTranslatef((ti_right[c]+4)/64.0,0,0);
					if (c==32) glTranslatef(delta,0,0);
				}
				glPopMatrix();
                lines++;
				break;
			}
		}

		glDisable(GL_TEXTURE_2D);

		glEndList();

	}

}

GLint TextItem::MouseButton(int Taste,int Richtung,int x_,int y_) {
	GLfloat xf=16.0*x_/glutGet(GLUT_WINDOW_WIDTH);
	GLfloat yf=12.0-12.0*y_/glutGet(GLUT_WINDOW_HEIGHT);
	if (soll_Alpha>0.0 &&
			Signal!=0 &&
            x<=xf && xf<=x+Height*Aspekt && y<=yf && yf<=y+Height) {
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

GLfloat TextItem::TextboxHeight() {
    return .7*lines;
}


void TextItem::SetMaxWidth(GLfloat mb) {
	if (mb<0) mb=0;
    MaxWidth=mb;
}
