/****************************************************************************
 **
 **  Kamera.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 *****************************************************************************/

#include <math.h>
#include <stdio.h> //2CHANGE wieder raus wenn kein printf mehr drin
#include "Kugel.h"
#include "Kamera.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GLfloat BewegFaktor=.3;
GLfloat DrehFaktor=.3;
GLfloat Positionen[12][6]; // Array zum Abspeichern der Kamerapositionen

//camera

/* --------- Konstruktor ---------- */
Camera::Camera() {
	// Generieren der vordefinierten Kamerapositionen
	Alpha=60.0;Beta=60.0;
	Pos_x=-100.0;Pos_y=-50.0;Pos_z=50.0;
	FOV=38.6;
    savePosition(0);

	Alpha=0;Beta=0;
	Pos_x=0;Pos_y=0;Pos_z=400;
	FOV=30.7;
    savePosition(1);

	Alpha=80;Beta=90;
	Pos_x=-170;Pos_y=0;Pos_z=30;
	FOV=38.6;
    savePosition(2);

	Alpha=80;Beta=-90;
	Pos_x=170;Pos_y=0;Pos_z=30;
	FOV=38.6;
    savePosition(3);

	Alpha=53;Beta=90;
	Pos_x=-220;Pos_y=0;Pos_z=120;
	FOV=38.6;
    savePosition(4);

	Alpha=53;Beta=-90;
	Pos_x=220;Pos_y=0;Pos_z=120;
	FOV=38.6;
    savePosition(5);

	Alpha=48;Beta=123.5;
	Pos_x=-229;Pos_y=121;Pos_z=176;
	FOV=38.6;
    savePosition(7);

	Alpha=48;Beta=56.5;
	Pos_x=-229;Pos_y=-121;Pos_z=176;
	FOV=38.6;
    savePosition(6);

    Target_Pos_x=-60;
    Target_Pos_y=-30;
    ScenicFlight(0);
    Alpha=Target_Alpha;
    Beta=Target_Beta;
    Pos_x=Target_Pos_x;
    Pos_y=Target_Pos_y;
    Pos_z=Target_Pos_z;

    Aspect=1.333333;

    Persecution=-1;

	Alpha=100;Beta=0;
	Pos_x=0;Pos_y=-200;Pos_z=20;
	FOV=38.6;

}


void Camera::draw() {
	glMatrixMode(GL_PROJECTION); // Kameraparameter!
	glLoadIdentity();            // zuruecksetzen
    gluPerspective(FOV,Aspect,Close,Remote);

	glMatrixMode(GL_MODELVIEW);  // Blickpunkt!
	glLoadIdentity();            // Kamera an den Ursprung setzen

	glRotatef(Alpha,-1,0,0);     // um Alpha nach oben und Beta nach Rechts drehen
	glRotatef(Beta,0,0,1);
	// an die gewuenschte Position setzen
	glTranslatef(-Pos_x,-Pos_y,-Pos_z); 

	//glEnable(GL_LIGHTING);
}

//setzt die Kamera an eine neue Position
void Camera::newPosition(GLfloat Position[]) {
    Target_Pos_x = Position[0];
    Target_Pos_y = Position[1];
    Target_Pos_z = Position[2];
    Target_Alpha = Position[3];
    Target_Beta  = Position[4];
    Target_FOV   = Position[5];
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

//gibt die aktuelle Kameraposition zur"uck
//GLfloat* Kamera::Position() {
//  GLfloat temp[] ={Soll_Pos_x,Soll_Pos_y,Soll_Pos_z,Soll_Alpha,Soll_Beta,Soll_FOV};
//  return temp;
//}

GLfloat Camera::Pos_xCM() {
	return Pos_x;
}

GLfloat Camera::Pos_yCM() {
	return Pos_y;
}

GLfloat Camera::Pos_zCM() {
	return Pos_z;
}

//schreibt die aktuelle Kameraposition in die Tabelle ab
void Camera::savePosition(GLint Platz) {
	Positionen[Platz][0]=Pos_x;
	Positionen[Platz][1]=Pos_y;
	Positionen[Platz][2]=Pos_z;
	Positionen[Platz][3]=Alpha;
	Positionen[Platz][4]=Beta;
	Positionen[Platz][5]=FOV;
	//2DEL
	//printf("%i: %f %f %f %f %f %f \n",Platz,Pos_x,Pos_y,Pos_z,Alpha,Beta,FOV);
}

// l"adt eine Kameraposition aus der Tabelle
void Camera::loadPosition(GLint Platz) {
    setToPosition(Positionen[Platz]);
    Persecution=-1;
}

// Bewegt die Kamera in Blickrichtung
void Camera::Move_In(GLfloat Faktor) {
    Target_Pos_x+=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*sin(Target_Beta/57.29578);
    Target_Pos_y+=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*cos(Target_Beta/57.29578);
    Target_Pos_z-=2*BewegFaktor*Faktor*cos(Target_Alpha/57.29578);
	//  if (Pos_z>400) {Pos_z=400;}
    if (Target_Pos_z<2.8) {Target_Pos_z=2.9;}
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Bewegt die Kamera gegen die Blickrichtung
void Camera::Move_Out(GLfloat Faktor) {
    Target_Pos_x-=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*sin(Target_Beta/57.29578);
    Target_Pos_y-=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*cos(Target_Beta/57.29578);
    Target_Pos_z+=2*BewegFaktor*Faktor*cos(Target_Alpha/57.29578);
	//  if (Pos_z>400) {Pos_z=400;}
    if (Target_Pos_z<2.8) {Target_Pos_z=2.8;}
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Bewegt die Kamera in Blickrichtung, aber unter Beibehaltung der H"ohe
void Camera::Move_Front(GLfloat Faktor) {
    Target_Pos_x+=2*BewegFaktor*Faktor*sin(Target_Beta/57.29578);
    Target_Pos_y+=2*BewegFaktor*Faktor*cos(Target_Beta/57.29578);
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Bewegt die Kamera gegen die Blickrichtung, aber unter Beibehaltung der H"ohe
void Camera::Move_Back(GLfloat Faktor) {
    Target_Pos_x-=2*BewegFaktor*Faktor*sin(Target_Beta/57.29578);
    Target_Pos_y-=2*BewegFaktor*Faktor*cos(Target_Beta/57.29578);
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Bewegt die Kamera nach rechts
void Camera::Move_Right(GLfloat Faktor) {
    Target_Pos_x+=BewegFaktor*Faktor*cos(Target_Beta/57.29578);
    Target_Pos_y-=BewegFaktor*Faktor*sin(Target_Beta/57.29578);
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Bewegt die Kamera nach links
void Camera::Move_Left(GLfloat Faktor) {
    Target_Pos_x-=BewegFaktor*Faktor*cos(Target_Beta/57.29578);
    Target_Pos_y+=BewegFaktor*Faktor*sin(Target_Beta/57.29578);
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Bewegt die Kamera nach oben
void Camera::Move_Up(GLfloat Faktor) {
    Target_Pos_z+=BewegFaktor*Faktor;
	//  if (Pos_z>400) {Pos_z=400;}
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Bewegt die Kamera nach unten
void Camera::Move_Down(GLfloat Faktor) {
    Target_Pos_z-=BewegFaktor*Faktor;
    if (Target_Pos_z<2.8) {Target_Pos_z=2.8;}
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

// Vergr"o"sert den Zoom
void Camera::Zoom_In(GLfloat Faktor) {
    Target_FOV-=BewegFaktor*Faktor;
    if (Target_FOV<1) {Target_FOV=1;}
    Persecution=-1;
}

// Verkleinert den Zoom
void Camera::Zoom_Out(GLfloat Faktor) {
    Target_FOV+=BewegFaktor*Faktor;
    Persecution=-1;
}

// Vergr"o"sert den Vertigo
void Camera::Vertigo_In(GLfloat Faktor) {
    Target_Pos_x-=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*sin(Target_Beta/57.29578);
    Target_Pos_y-=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*cos(Target_Beta/57.29578);
    Target_Pos_z+=2*BewegFaktor*Faktor*cos(Target_Alpha/57.29578);
    Target_FOV=2077*cos(Target_Alpha/57.29578)/Target_Pos_z;
    if (Target_FOV<1) {Target_FOV=1;}
    Persecution=-1;
}

// Verkleinert den Vertigo
void Camera::Vertigo_Out(GLfloat Faktor) {
    Target_Pos_x+=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*sin(Target_Beta/57.29578);
    Target_Pos_y+=2*BewegFaktor*Faktor*sin(Target_Alpha/57.29578)*cos(Target_Beta/57.29578);
    Target_Pos_z-=2*BewegFaktor*Faktor*cos(Target_Alpha/57.29578);
    Target_FOV=2077*cos(Target_Alpha/57.29578)/Target_Pos_z;
    Persecution=-1;
}

// Dreht die Kamera nach rechts
void Camera::TurnRight(GLfloat Faktor) {
    Target_Beta+=Faktor*DrehFaktor;
    Persecution=-1;
}

// Dreht die Kamera nach links
void Camera::TurnLeft(GLfloat Faktor) {
    Target_Beta-=Faktor*DrehFaktor;
    Persecution=-1;
}

// Dreht die Kamera nach oben
void Camera::TurnUp(GLfloat Faktor) {
    Target_Alpha+=Faktor*DrehFaktor;
    if (Target_Alpha>90) {Target_Alpha=90;}
    if (Target_Alpha<0) {Target_Alpha=0;}
    Persecution=-1;
}

// Dreht die Kamera nach unten
void Camera::TurnDown(GLfloat Faktor) {
    Target_Alpha-=Faktor*DrehFaktor;
    if (Target_Alpha>90) {Target_Alpha=90;}
    if (Target_Alpha<0) {Target_Alpha=0;}
    Persecution=-1;
}

void Camera::SwingLeft(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
    GLfloat Abstand=sqrt((Mitte_x-Target_Pos_x)*(Mitte_x-Target_Pos_x)+(Mitte_y-Target_Pos_y)*(Mitte_y-Target_Pos_y));
	if (Abstand<5) Abstand=5;
    Target_Beta+=Faktor*DrehFaktor*7.338/sqrt(Abstand);
    Target_Pos_x=Mitte_x-Abstand*sin(Target_Beta/57.29578);
    Target_Pos_y=Mitte_y-Abstand*cos(Target_Beta/57.29578);
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

void Camera::SwingRight(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
    GLfloat Abstand=sqrt((Mitte_x-Target_Pos_x)*(Mitte_x-Target_Pos_x)+(Mitte_y-Target_Pos_y)*(Mitte_y-Target_Pos_y));
	if (Abstand<5) Abstand=5;
    Target_Beta-=Faktor*DrehFaktor*7.338/sqrt(Abstand);
    Target_Pos_x=Mitte_x-Abstand*sin(Target_Beta/57.29578);
    Target_Pos_y=Mitte_y-Abstand*cos(Target_Beta/57.29578);
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

void Camera::SwingUp(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
    GLfloat Abstand=sqrt((Mitte_x-Target_Pos_x)*(Mitte_x-Target_Pos_x)+(Mitte_y-Target_Pos_y)*(Mitte_y-Target_Pos_y)+(Target_Pos_z-2.8)*(Target_Pos_z-2.8));
	if (Abstand==0) {
        Target_Alpha=0;
	} else {
        Target_Alpha+=Faktor*DrehFaktor*7.338/sqrt(Abstand);
        if (Target_Alpha<0) {Target_Alpha=0;}
        if (Target_Alpha>90) {Target_Alpha=90;}
	}
    Target_Pos_x=Mitte_x-Abstand*sin(Target_Beta/57.29578)*sin(Target_Alpha/57.29578);
    Target_Pos_y=Mitte_y-Abstand*cos(Target_Beta/57.29578)*sin(Target_Alpha/57.29578);
    Target_Pos_z=2.8+Abstand*cos(Target_Alpha/57.29578);
	//  if (Pos_z>400) {Pos_z=400;}
    if (Target_Pos_z<2.8) {Target_Pos_z=2.8;}
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

void Camera::SwingDown(GLfloat Faktor, GLfloat Mitte_x, GLfloat Mitte_y) {
    GLfloat Abstand=sqrt((Mitte_x-Target_Pos_x)*(Mitte_x-Target_Pos_x)+(Mitte_y-Target_Pos_y)*(Mitte_y-Target_Pos_y)+(Target_Pos_z-2.8)*(Target_Pos_z-2.8));
	if (Abstand==0) {
        Target_Alpha=0;
	} else {
        Target_Alpha-=Faktor*DrehFaktor*7.338/sqrt(Abstand);
        if (Target_Alpha<0) {Target_Alpha=0;}
        if (Target_Alpha>90) {Target_Alpha=90;}
	}
    Target_Pos_x=Mitte_x-Abstand*sin(Target_Beta/57.29578)*sin(Target_Alpha/57.29578);
    Target_Pos_y=Mitte_y-Abstand*cos(Target_Beta/57.29578)*sin(Target_Alpha/57.29578);
    Target_Pos_z=2.8+Abstand*cos(Target_Alpha/57.29578);
	//  if (Pos_z>400) {Pos_z=400;}
    if (Target_Pos_z<2.8) {Target_Pos_z=2.8;}
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

void Camera::setToPosition(GLfloat Soll_Pos[6]) {
    Target_Pos_x = Soll_Pos[0];
    Target_Pos_y = Soll_Pos[1];
    Target_Pos_z = Soll_Pos[2];
    Target_Alpha = Soll_Pos[3];
    Target_Beta  = Soll_Pos[4];
    Target_FOV   = Soll_Pos[5];

	Beta=fmod(Beta,360);
    Target_Beta=fmod(Target_Beta,360);

    if (Target_Beta>Beta+180) {Target_Beta-=360;}
    if (Target_Beta<Beta-180) {Target_Beta+=360;}
	BlickTiefeNeuBestimmen();
    Persecution=-1;
}

void Camera::setToPosition(GLfloat SollPosx,
		GLfloat SollPosy,
		GLfloat SollPosz,
		GLfloat SollAlpha,
		GLfloat SollBeta,
		GLfloat SollFOV) {
    Target_Pos_x = SollPosx;
    Target_Pos_y = SollPosy;
    Target_Pos_z = SollPosz;
    Target_Alpha = SollAlpha;
    Target_Beta  = SollBeta;
    Target_FOV   = SollFOV;

	Beta=fmod(Beta,360);
    Target_Beta=fmod(Target_Beta,360);

    if (Target_Beta>Beta+180) {Target_Beta-=360;}
    if (Target_Beta<Beta-180) {Target_Beta+=360;}
    Persecution=-1;
}

void Camera::EyesOn(GLfloat Blickpunkt[2]) {
    EyesOn(Blickpunkt[0],Blickpunkt[1]);
}

void Camera::EyesOn(GLfloat Blickpunkt_x,GLfloat Blickpunkt_y) {
	GLfloat SollPosx=50*(Pos_x-Blickpunkt_x)/
		sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
				(Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
		Blickpunkt_x;
	GLfloat SollPosy=50*(Pos_y-Blickpunkt_y)/
		sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
				(Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
		Blickpunkt_y;
	GLfloat SollPosz=20;
	GLfloat SollAlpha=71.0167;
	GLfloat SollBeta=atan((Blickpunkt_x-SollPosx)/(Blickpunkt_y-SollPosy))*180/M_PI;
	if (SollPosy>Blickpunkt_y) {SollBeta-=180;}
	GLfloat SollFOV=38.6;

    setToPosition(SollPosx,SollPosy,SollPosz,SollAlpha,SollBeta,SollFOV);
    Persecution=-1;
}

void Camera::EyesOn2(GLfloat Blickpunkt[2]) {
    EyesOn2(Blickpunkt[0],Blickpunkt[1]);
}

void Camera::EyesOn2(GLfloat Blickpunkt_x,GLfloat Blickpunkt_y) {
	GLfloat SollPosx=80*(Pos_x-Blickpunkt_x)/
		sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
				(Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
		Blickpunkt_x;
	GLfloat SollPosy=80*(Pos_y-Blickpunkt_y)/
		sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
				(Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
		Blickpunkt_y;
	GLfloat SollPosz=50;
	GLfloat SollAlpha=72;
	GLfloat SollBeta=atan((Blickpunkt_x-SollPosx)/(Blickpunkt_y-SollPosy))*180/M_PI;
	if (SollPosy>Blickpunkt_y) {SollBeta-=180;}
	GLfloat SollFOV=38.6;

    setToPosition(SollPosx,SollPosy,SollPosz,SollAlpha,SollBeta,SollFOV);
    Persecution=-1;
}

void Camera::EyesOn3(GLfloat Blickpunkt[2]) {
    EyesOn3(Blickpunkt[0],Blickpunkt[1]);
}

void Camera::EyesOn3(GLfloat Blickpunkt_x,GLfloat Blickpunkt_y) {
	GLfloat SollPosx=80*(Pos_x-Blickpunkt_x)/
		sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
				(Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
		Blickpunkt_x;
	GLfloat SollPosy=80*(Pos_y-Blickpunkt_y)/
		sqrt((Blickpunkt_x-Pos_x)*(Blickpunkt_x-Pos_x)+
				(Blickpunkt_y-Pos_y)*(Blickpunkt_y-Pos_y))+
		Blickpunkt_y;
	GLfloat SollPosz=50;
	GLfloat SollAlpha=58;
	GLfloat SollBeta=atan((Blickpunkt_x-SollPosx)/(Blickpunkt_y-SollPosy))*180/M_PI;
	if (SollPosy>Blickpunkt_y) {SollBeta-=180;}
	GLfloat SollFOV=38.6;

    setToPosition(SollPosx,SollPosy,SollPosz,SollAlpha,SollBeta,SollFOV);
    Persecution=-1;
}

void Camera::Ride(GLfloat Faktor) {
    if (Persecution!=-1) {
        if (Ball[Persecution].Pos_x()==3000.0) {
            Persecution=-1;
		} else {
            GLint Verfolgung2=Persecution;
            EyesOn3(Ball[Persecution].Pos_xCM(),Ball[Persecution].Pos_yCM());
            Persecution=Verfolgung2;
		}
	}

	for (int i=0;i<Faktor;i++) {

        if (Target_Beta-Beta<-180){Beta-=360;}
        if (Target_Beta-Beta> 180){Beta+=360;}

        d_Pos_x = d_Pos_x * 0.9 + 0.003 * (Target_Pos_x-Pos_x);
        d_Pos_y = d_Pos_y * 0.9 + 0.003 * (Target_Pos_y-Pos_y);
        d_Pos_z = d_Pos_z * 0.9 + 0.003 * (Target_Pos_z-Pos_z);
        d_Alpha = d_Alpha * 0.9 + 0.003 * (Target_Alpha-Alpha);
        d_Beta  = d_Beta  * 0.9 + 0.003 * (Target_Beta-Beta);
        d_FOV   = d_FOV   * 0.9 + 0.003 * (Target_FOV-FOV);

		Pos_x += d_Pos_x;
		Pos_y += d_Pos_y;
		Pos_z += d_Pos_z;
		Alpha += d_Alpha;
		Beta  += d_Beta;
		FOV   += d_FOV;

		BlickTiefeNeuBestimmen();

	}
}

void Camera::Track(GLint Kugel) {
    Persecution=Kugel;
}

void Camera::BlickTiefeNeuBestimmen() {
	GLfloat ax=fabs(Pos_x),ay=fabs(Pos_y),az=Pos_z;

	if (ax<150) {
		if (ay<80) {
            Close=az-5;
		} else {
            Close=sqrt((ay-80)*(ay-80)+(az-5)*(az-5));
		}
	} else {
		if (ay<80) {
            Close=sqrt((ax-150)*(ax-150)+(az-5)*(az-5));
		} else {
            Close=sqrt((ax-150)*(ax-150)+(ay-80)*(ay-80)+(az-5)*(az-5));
		}
	}    

    Close*=.8;

    if (Close<1) {Close=1;}

    Remote=sqrt((ax+150)*(ax+150)+(ay+80)*(ay+80)+az*az);
	// printf ("Nah:  %f\nFern: %f\n\n",Nah,Fern); 2DEL

}

/*
 * 飞行视角
 */
void Camera::ScenicFlight(GLint Faktor){
    if (Target_Pos_y==0) {Target_Pos_y=.00001;}
	//Soll_Beta=Faktor*.1+atan(Soll_Pos_x/Soll_Pos_y)*180/M_PI;
	//if (Soll_Pos_y>0) {Soll_Beta-=180;}
    Target_Beta+=.1*Faktor;
    Target_Pos_x=(-30*sin(Target_Beta*M_PI/180)-280)*sin(Target_Beta*M_PI/180);
    Target_Pos_y=(-30*sin(Target_Beta*M_PI/180)-280)*cos(Target_Beta*M_PI/180);
    Target_Pos_z=100-50*sin(Target_Beta*M_PI/180);
    Target_FOV=36.8;
    Target_Alpha=atan(sqrt(Target_Pos_x*Target_Pos_x+
                Target_Pos_y*Target_Pos_y)/
            Target_Pos_z)*180/M_PI;
}
