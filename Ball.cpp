/****************************************************************************
 **
 **  Kugel.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "LA.h"                // Zum Handling von .bmp-Files bzw. Matrix-Bildern
#include "bmp.h"

#include "Ball.h"

#include "createTexture.h"   // Funktion zum Generieren einer Textur aus einem 
// Matrix-Bild (aus "Ubungen)

#include "Shadow.h"   // zeichnet Schatten

//ball

// leerer Konstruktor (OpenGL macht hier dumm)...
Ball::Ball() {
	Position[0]=0;
	Position[1]=0;
	Position[2]=0;
    Number=-1;
	for (GLint i=0;i<30;i++) {
        sphereIndex[i]=0;           //ball index
		sphereIndexStatisch[i]=0; 
        StaticExists[i]=0;
	}
    shadowIndex=0;
    shadowIndexStatic=0;
    Shadow=0;
	InAnimation=0;
    StaticExistShadow=0;
	//GLfloat DrehMatrix[16];
    Shadow1_x=0;
    Shadow1_y=0;
    Shadow1_scale=0;
    Shadow1_angle=0;
    Shadow2_x=0;
    Shadow2_y=0;
    Shadow2_scale=0;
    Shadow2_angle=0;
    Shadow3_x=0;
    Shadow3_y=0;
    Shadow3_scale=0;
    Shadow3_angle=0;
    OldTextureSize=1;

	/* */
	Texturen[1]=0;
	Texturen[2]=0;
	Texturen[4]=0;
	Texturen[8]=0;
}

GLint exp2(GLint a) { //b=2^a
	return 1<<a;
}

// ... stattdessen kommt hier alles in Initialisiere
/*
 * init ball
 *
 * @Nr: ball id
 * @TextureSize:
 * @MaxAufloesung: Max Display Resolution
 * @Schatten_: shadow
 */
void Ball::Init(GLint Nr, GLint TextureSize, GLint MaxAufloesung, GLint Schatten_) {

    Shadow=Schatten_;

	FMatrix tex_r,tex_g,tex_b;     // Matrix-Bilder, in die die Textur kommt

	char Name[40];                  // Wie hei"st die zu ladene .bmp-Datei?
    sprintf(Name,"Texturen/%i/%i.bmp",TextureSize,Nr);

	if (!sphereIndex[3]) {
		Position[0]=Position[1]=3000.0; // Kugel nicht sichtbar

		glPushMatrix();                 // Drehmatrix auf die Einheitsmatrix setzen;
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX,DrehMatrix);
		glPopMatrix();
	}

    Number=Nr;                      // KugelNummer setzen

    //Display resolution
	for (int Aufloesung=3; Aufloesung<=MaxAufloesung;Aufloesung+=2) {

		if (!sphereIndex[Aufloesung]||
                (OldTextureSize!=TextureSize)) {

			//printf(".");fflush(stdout);

			sphereIndex[Aufloesung]=glGenLists(1); 
			sphereIndexStatisch[Aufloesung]=glGenLists(1); 

            if ((TextureSize==0)||(Number==0)) { // Keine Textur?

				glNewList(sphereIndex[Aufloesung],GL_COMPILE_AND_EXECUTE);
				GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
				GLfloat mat_specular[]={0.5,0.5,0.5,1.0};
				//GLfloat mat_specular[]={0.0,0.0,0.0,0.0};
				GLfloat mat_shininess = 80.0;

				glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
				glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
				glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
				glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_NORMAL_ARRAY);
				glNormalPointer(GL_FLOAT, 0, ball_vertices[Aufloesung]);
				glVertexPointer(3, GL_FLOAT, 0, ball_vertices[Aufloesung]);
				glDrawElements(GL_TRIANGLES,20*3*Aufloesung*Aufloesung, GL_UNSIGNED_INT,ball_indices[Aufloesung]);
				glDisableClientState(GL_VERTEX_ARRAY);
                glDisableClientState(GL_NORMAL_ARRAY);
				glEndList();

			} else {                        // sonst

				GLint TG=exp2((7-Aufloesung)/2);
                if (TG<TextureSize) TG=TextureSize;
				if (TG>8) TG=1;
				if (!Texturen[TG]) 
					glGenTextures(1,&Texturen[TG]);
				glBindTexture(GL_TEXTURE_2D,Texturen[TG]);
				sprintf(Name,"Texturen/%i/%i.bmp",TG,Nr); 
				loadBMP(tex_r,tex_g,tex_b,Name);
				GLfloat *texcoord;
				if (tex_r.nrh!=tex_r.nch) {
					GLfloat Aspekt=(tex_r.nch+1.0)/(tex_r.nrh+1.0);
					texcoord = (GLfloat*) malloc (20*(Aufloesung+1)*(Aufloesung+2)*sizeof(GLfloat));
					for (GLint a=0;a<20*(Aufloesung+1)*(Aufloesung+2);a+=2) {
						texcoord[a]=ball_texcoord[Aufloesung][a]/Aspekt;
						texcoord[a+1]=ball_texcoord[Aufloesung][a+1];
					}
				} 
				createTexture(tex_r,tex_g,tex_b);

				glNewList(sphereIndex[Aufloesung],GL_COMPILE_AND_EXECUTE);
				GLfloat mat_diffuse[]={1.0,1.0,1.0,1.0};
				GLfloat mat_specular[]={0.5,0.5,0.5,1.0};
				//GLfloat mat_specular[]={0.0,0.0,0.0,0.0};
				GLfloat mat_shininess = 80.0;

				glMaterialfv(GL_FRONT, GL_AMBIENT,mat_diffuse);
				glMaterialfv(GL_FRONT, GL_DIFFUSE,mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR,mat_specular);
				glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
				//createTexture(tex_r,tex_g,tex_b,Nearest,0);
				glBindTexture(GL_TEXTURE_2D,Texturen[TG]);
				glEnable(GL_TEXTURE_2D);
				glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
				glEnableClientState(GL_VERTEX_ARRAY);
                glEnableClientState(GL_NORMAL_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glNormalPointer(GL_FLOAT, 0, ball_vertices[Aufloesung]);
				glVertexPointer(3, GL_FLOAT, 0, ball_vertices[Aufloesung]);
				if (tex_r.nrh!=tex_r.nch) {
					glTexCoordPointer(2, GL_FLOAT, 0, texcoord);
				} else {
					glTexCoordPointer(2, GL_FLOAT, 0, ball_texcoord[Aufloesung]);
				}
				glDrawElements(GL_TRIANGLES,20*3*Aufloesung*Aufloesung, GL_UNSIGNED_INT,ball_indices[Aufloesung]);
				glDisableClientState(GL_VERTEX_ARRAY);
                glDisableClientState(GL_NORMAL_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisable(GL_TEXTURE_2D);
				glEndList();
				tex_r.free_FMatrix();
				tex_g.free_FMatrix();
				tex_b.free_FMatrix();
				if (tex_r.nrh!=tex_r.nch) {
					free(texcoord);
				}

			}

            StaticExists[Aufloesung]=0;
            StaticExistShadow=0;
			InAnimation=1;
		}
	}

    if (!shadowIndex) {
        shadowIndex=glGenLists(1);
        shadowIndexStatic=glGenLists(1);

        glNewList(shadowIndex,GL_COMPILE_AND_EXECUTE);
        ShadowCircle(18, .7, 1.2, 0.2, 0.0);
		glEndList();

        Shadow=Schatten_;

        Shadow1_x=0;
        Shadow1_y=0;
        Shadow1_scale=1;
        Shadow1_angle=0;
        Shadow2_x=0;
        Shadow2_y=0;
        Shadow2_scale=1;
        Shadow2_angle=0;
        Shadow3_x=0;
        Shadow3_y=0;
        Shadow3_scale=1;
        Shadow3_angle=0;
	}

	if (!schatten2Index) {
		schatten2Index=glGenLists(1);

		glNewList(schatten2Index,GL_COMPILE_AND_EXECUTE);
        ShadowCircle(14, 0.1, 0.5, 0.5, 0.0);
		glEndList();
	}

    OldTextureSize=TextureSize;

}


// Draws the ball using the Display List
void Ball::draw(GLint Aufloesung) {
	if (Position[0]!=3000) {

		if (InAnimation) {
			glPushMatrix();                // Matrix auf Stack
			glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;
			// Kugel auf die Position verschieben
			glTranslatef(Position[0],Position[1],Position[2]);
			glMultMatrixf(DrehMatrix);     // Kugel mit der Drehmatrix drehen
			glCallList(sphereIndex[Aufloesung]);       // Kugel zeichnen
			glPopMatrix();                 // Matrix wiederherstellen
			InAnimation=0;
			for (int i=0;i<30;i++) {
                StaticExists[i]=0;
			}

        } else if (StaticExists[Aufloesung]) {

			/*
			   glPushMatrix();
			   glTranslatef(0,0,-5.715);
			   glScalef(1,1,-1);
			   glFrontFace(GL_CW);
			   glDisable(GL_DEPTH_TEST);
			   glCallList(sphereIndexStatisch[Aufloesung]);
			   glEnable(GL_DEPTH_TEST);
			   glFrontFace(GL_CCW);
			   glPopMatrix();
			   */

			glCallList(sphereIndexStatisch[Aufloesung]);

		} else {

			glNewList(sphereIndexStatisch[Aufloesung],GL_COMPILE_AND_EXECUTE);

			glPushMatrix();                // Matrix auf Stack

			glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;

			// Kugel auf die Position verschieben
			glTranslatef(Position[0],Position[1],Position[2]);

			glMultMatrixf(DrehMatrix);     // Kugel mit der Drehmatrix drehen

			glCallList(sphereIndex[Aufloesung]);       // Kugel zeichnen

			glPopMatrix();                 // Matrix wiederherstellen

			glEndList();

            StaticExists[Aufloesung]=1;
		}
	}
}

//shadow
void Ball::drawShadow() {
    if (Shadow&&(Position[0]!=3000)&&(Position[2]>=0)) {
		if (InAnimation) {
			glPushMatrix();
			glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;
			glTranslatef(Position[0],Position[1],Position[2]-1);

			glCallList(schatten2Index); //TEST

			glPushMatrix();
            glTranslatef(Shadow1_x,Shadow1_y,0);
            glRotatef(Shadow1_angle,0,0,1);
            glScalef(Shadow1_scale,1,1);
            glCallList(shadowIndex);
			glPopMatrix();

			glPushMatrix();
            glTranslatef(Shadow2_x,Shadow2_y,0);
            glRotatef(Shadow2_angle,0,0,1);
            glScalef(Shadow2_scale,1,1);
            glCallList(shadowIndex);
			glPopMatrix();

			glPushMatrix();
            glTranslatef(Shadow3_x,Shadow3_y,0);
            glRotatef(Shadow3_angle,0,0,1);
            glScalef(Shadow3_scale,1,1);
            glCallList(shadowIndex);
			glPopMatrix();
			glPopMatrix();

            StaticExistShadow=0;

        } else if (StaticExistShadow) {

            glCallList(shadowIndexStatic);

		} else {

            glNewList(shadowIndexStatic,GL_COMPILE_AND_EXECUTE);
			glPushMatrix();
			glScalef(2.8575,2.8575,2.8575);// Skalieren auf Zentimetersystem;
			glTranslatef(Position[0],Position[1],Position[2]-1);

			glCallList(schatten2Index); //TEST

			glPushMatrix();
            glTranslatef(Shadow1_x,Shadow1_y,0);
            glRotatef(Shadow1_angle,0,0,1);
            glScalef(Shadow1_scale,1,1);
            glCallList(shadowIndex);
			glPopMatrix();

			glPushMatrix();
            glTranslatef(Shadow2_x,Shadow2_y,0);
            glRotatef(Shadow2_angle,0,0,1);
            glScalef(Shadow2_scale,1,1);
            glCallList(shadowIndex);
			glPopMatrix();

			glPushMatrix();
            glTranslatef(Shadow3_x,Shadow3_y,0);
            glRotatef(Shadow3_angle,0,0,1);
            glScalef(Shadow3_scale,1,1);
            glCallList(shadowIndex);
			glPopMatrix();
			glPopMatrix();
			glEndList();

            StaticExistShadow=1;
		}
	}
}


void Ball::newPosition(GLfloat neuPos[]) {

	GLfloat dx=neuPos[0]-Position[0]; // Differenzvektor bestimmen
	GLfloat dy=neuPos[1]-Position[1];

	//printf("%i %f %f\n",Nummer,Position[0],Position[1]);

	if (dx || dy) {

		glPushMatrix();                   // Matrix auf Stack

		glLoadIdentity();                 // Einheitsmatrix laden

		// um die L"ange des Diff.vektors (umgerechnet in Gradma"s) um die
		// Achse senkrecht zum Differenzvektor rotieren
		glRotatef(sqrt(dx*dx+dy*dy)*20.051016*2,-dy,dx,0.0);

		glMultMatrixf(DrehMatrix);        // Die alte Drehmatrix dazumultiplizieren

		// Die neue Drehmatrix abspeichern
		glGetFloatv(GL_MODELVIEW_MATRIX,DrehMatrix);

		glPopMatrix();                    // Matrix wiederherstellen

		Position[0]=neuPos[0];            // neue Position setzen
		Position[1]=neuPos[1];
		Position[2]=(neuPos[2]>0)?0:neuPos[2];

        if (Shadow) {
            Shadow1_x=neuPos[0]/34;
            Shadow1_x=(Shadow1_x)?Shadow1_x:.0001;
            Shadow1_y=neuPos[1]/34;
            Shadow1_scale=sqrt(Shadow1_x*Shadow1_x+Shadow1_y*Shadow1_y+1);
            Shadow1_angle=57.3*atan(Shadow1_y/Shadow1_x);

            Shadow2_x=(neuPos[0]-22.22)/34;
            Shadow2_x=(Shadow2_x)?Shadow2_x:.0001;
            Shadow2_y=Shadow1_y;
            Shadow2_scale=sqrt(Shadow2_x*Shadow2_x+Shadow2_y*Shadow2_y+1);
            Shadow2_angle=57.3*atan(Shadow2_y/Shadow2_x);

            Shadow3_x=(neuPos[0]+22.22)/34;
            Shadow3_x=(Shadow3_x)?Shadow3_x:.0001;
            Shadow3_y=Shadow1_y;
            Shadow3_scale=sqrt(Shadow3_x*Shadow3_x+Shadow3_y*Shadow3_y+1);
            Shadow3_angle=57.3*atan(Shadow3_y/Shadow3_x);
		}
	}
	InAnimation=1;
}

/* Das gleiche noch viele hundert Mal (in verschiedenen Masseinheiten etc.)*/
void Ball::newPosition(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
	GLfloat Pos[]={neuPos_x,neuPos_y,neuPos_z};
    newPosition(Pos);
}

void Ball::newPosition(GLfloat neuPos_x,GLfloat neuPos_y) {
	GLfloat Pos[]={neuPos_x,neuPos_y,0.0};
    newPosition(Pos);
}

void Ball::newPositionCM(GLfloat neuPos[]) {
	GLfloat Pos[]={neuPos[0]/2.8575,neuPos[1]/2.8575,neuPos[2]/2.8575};
    newPosition(Pos);
}

void Ball::newPositionCM(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
	GLfloat Pos[]={neuPos_x/2.8575,neuPos_y/2.8575,neuPos_z/2.8575};
    newPosition(Pos);
}

void Ball::newPositionCM(GLfloat neuPos_x,GLfloat neuPos_y) {
	GLfloat Pos[]={neuPos_x/2.8575,neuPos_y/2.8575,0.0};
    newPosition(Pos);
}

void Ball::newPositionD(GLfloat neuPos[]) {
	GLfloat Pos[]={neuPos[0]*2,neuPos[1]*2,neuPos[2]*2};
    newPosition(Pos);
}

void Ball::newPositionD(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
	GLfloat Pos[]={neuPos_x*2,neuPos_y*2,neuPos_z*2};
    newPosition(Pos);
}

void Ball::newPositionD(GLfloat neuPos_x,GLfloat neuPos_y) {
	GLfloat Pos[]={neuPos_x*2,neuPos_y*2,0.0};
    newPosition(Pos);
}

void Ball::newPositionINCH(GLfloat neuPos[]) {
	GLfloat Pos[]={neuPos[0]/1.125,neuPos[1]/1.125,neuPos[2]/1.125};
    newPosition(Pos);
}

void Ball::newPositionINCH(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z) {
	GLfloat Pos[]={neuPos_x/1.125,neuPos_y/1.125,neuPos_z/1.125};
    newPosition(Pos);
}

void Ball::newPositionINCH(GLfloat neuPos_x,GLfloat neuPos_y) {
	GLfloat Pos[]={neuPos_x/1.125,neuPos_y/1.125,0.0};
    newPosition(Pos);
}

//fade out
// l"a"st die Kugel verschwinden disappear
void Ball::disappear() {
	GLfloat Pos[]={3000.0,3000.0,0.0};
    newPosition(Pos);
}

// Liefert die Kugelposition in verschiedenen Ma"seinheiten zur"uck
GLfloat Ball::Pos_x() {
	return Position[0];
}

GLfloat Ball::Pos_y() {
	return Position[1];
}

GLfloat Ball::Pos_xD() {
	return Position[0]*.5;
}

GLfloat Ball::Pos_yD() {
	return Position[1]*.5;
}

GLfloat Ball::Pos_xCM() {
	return Position[0]*2.8575;
}

GLfloat Ball::Pos_yCM() {
	return Position[1]*2.8575;
}
