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
#include "Kugel.h"
#include "Schiedsrichter.h"
#include "Physik.h"

GLfloat altePos[16][3]; // alte Pos. der Kugeln
GLfloat neuePos[16][3]; // neue Pos. der Kugeln

GLfloat BallSpeed[16][2]; // Geschw. Kugeln
GLfloat FallFaktor = 25.0;
GLfloat VerlustTasche = 1.0;

// ---------------- Kugel versenken ----------------------------------------

//下沉
void sink(GLint nr){
	if (neuePos[nr][2] <= -2.0) { // Kugel ist unten und verschwindet
		neuePos[nr][0]=1500;
		neuePos[nr][1]=1500;
		neuePos[nr][2]=0; 
        BallSpeed[nr][0] = 0.0;
        BallSpeed[nr][1] = 0.0;

	}

	if ((neuePos[nr][2]==0)&&(neuePos[nr][0]!=1500)) { // Kugel beginnt zu fallen
		neuePos[nr][2] = -0.05;
        BallSpeed[nr][0] = BallSpeed[nr][0]*0.95; // abbremsen
        BallSpeed[nr][1] = BallSpeed[nr][1]*0.95;
	}
	else           // Kugel faellt bereits
	{

		if (neuePos[nr][0]>10){                            // rechts
			if (neuePos[nr][1]>0){                             // oben
                BallSpeed[nr][0] = 23.322-neuePos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = 12.211-neuePos[nr][1]+BallSpeed[nr][1]*0.5;
			}
			else{                                              // unten
                BallSpeed[nr][0] = 23.322-neuePos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = -12.211-neuePos[nr][1]+BallSpeed[nr][1]*0.5;
			}
		}
		if (neuePos[nr][0]<-10){                            // links
			if (neuePos[nr][1]>0){                             // oben
                BallSpeed[nr][0] = -23.322-neuePos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = 12.211-neuePos[nr][1]+BallSpeed[nr][1]*0.5;
			}
			else{                                              // unten
                BallSpeed[nr][0] = -23.322-neuePos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = -12.211-neuePos[nr][1]+BallSpeed[nr][1]*0.5;
			}
		}	
		if ((neuePos[nr][0]>-2)&&(neuePos[nr][0]<2)){               // Mitte
			if (neuePos[nr][1]>0){                             // oben
                BallSpeed[nr][0] = 0-neuePos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = 12.5547-neuePos[nr][1]+BallSpeed[nr][1]*0.5;
			}
			else{                                              // unten
                BallSpeed[nr][0] = 0-neuePos[nr][0]+BallSpeed[nr][0]*0.5;
                BallSpeed[nr][1] = -12.5547-neuePos[nr][1]+BallSpeed[nr][1]*0.5;
			} 
		}
	}

}


// ----------------------------- Kollisionsberechnung ---------------------------

//碰撞
void Collision(GLfloat neu1[],GLfloat neu2[],GLint erste,GLint zweite){

	GLfloat verlust = CollisionFactor; 



	neuePos[erste][0] = neu1[0]; // neue Position wird festgelegt
	neuePos[erste][1] = neu1[1];
	neuePos[zweite][0] = neu2[0];
	neuePos[zweite][1] = neu2[1];

	GLfloat dx2 = neu2[0]-neu1[0];
	GLfloat dy2 = neu2[1]-neu1[1];
	GLfloat Abstand2=sqrt(dx2*dx2+dy2*dy2);
	GLfloat dx = dx2/Abstand2;
	GLfloat dy = dy2/Abstand2;


    GLfloat richtung = (BallSpeed[zweite][0]-BallSpeed[erste][0])*dx2 + (BallSpeed[zweite][1]-BallSpeed[erste][1])*dy2;

	if (richtung < 0){

        GLfloat skalarp = .9*(BallSpeed[erste][0]*dx+BallSpeed[erste][1]*dy)-
            (BallSpeed[zweite][0]*dx+BallSpeed[zweite][1]*dy);
		GLfloat Kraftx = dx * skalarp;
		GLfloat Krafty = dy * skalarp;
        BallSpeed[erste][0] = (BallSpeed[erste][0] - Kraftx) * verlust; // neuer Geschw.-Vektor
        BallSpeed[erste][1] = (BallSpeed[erste][1] - Krafty) * verlust;
        BallSpeed[zweite][0] = (BallSpeed[zweite][0] + Kraftx) * verlust;
        BallSpeed[zweite][1] = (BallSpeed[zweite][1] + Krafty) * verlust;
	}
}








void Physik(GLfloat Stoss_x,GLfloat Stoss_y) {

	//printf(" Berechne Stoss ...");
	fflush(stdout);
	// ------------------------ Variablen initialisieren ------------------------  

	GLint Aufloesung = PhysicsFrequenz; // min. 100
	GLfloat Tischlaenge = 22.22; // x-Achse
	GLfloat Tischbreite = 11.11; // y-Achse

	GLfloat reibung =  FrictionFactor; // Geschw.-Abzug durch Reibung

	GLfloat bandenfaktor = GangsFactor; // Verlust an Banden







	// --------------------------- Kugelpositionen auslesen und Speed setzen ----------

	for (GLint i=0;i<16;i++) {  // erster Tabelleneintrag enthaellt Startposition
		LightingTable[0][i][0]=Ball[i].Pos_xD(); 
		LightingTable[0][i][1]=Ball[i].Pos_yD();
		LightingTable[0][i][2]=0;
		altePos[i][0]=Ball[i].Pos_xD();
		altePos[i][1]=Ball[i].Pos_yD();
		altePos[i][2]=0;
		neuePos[i][2]=0; //Kugel liegt noch auf dem Tisch
        BallSpeed[i][0]=0.0;
        BallSpeed[i][1]=0.0;
	}
    BallSpeed[0][0] = Stoss_x; // Startgeschw. der weissen Kugel
    BallSpeed[0][1] = Stoss_y;



	// ------------------------------ Berechnung nach diskreten Zeitschritten ---------------------
    int beweg = 0;  //moving
	for (int zeit=0;zeit<(20*Aufloesung);zeit++){
		beweg = 0; // noch keine Bewegung

		// neue Position berechnen


		for (int nr=0;nr<16;nr++){
			if (altePos[nr][0] == 1500.0) {
				neuePos[nr][0] = 1500.0;
			}
			else {
                neuePos[nr][0] = altePos[nr][0]+BallSpeed[nr][0]/Aufloesung;
                neuePos[nr][1] = altePos[nr][1]+BallSpeed[nr][1]/Aufloesung;
				if (altePos[nr][2]<0){
					neuePos[nr][2] = altePos[nr][2]*(1+FallFaktor/Aufloesung);   // Kugel faellt
					//beweg = 1;                                                   // und bewegt sich damit
				}
				else
				{
                    neuePos[nr][2] = (fabs(BallSpeed[nr][0])+fabs(BallSpeed[nr][1])>0)?0:1;
				}
			}
		}






		// ------------------------ Kollision mit anderer Kugel? ----------------------------------

		{
			for (int i=0;i<15;i++){          //letzte Kugel wird nicht betrachtet
				if (neuePos[i][0] != 1500.0){
					for (int i2=i+1;i2<16;i2++){   //nur verbleibende Kugeln beruecksichtigen
						if (neuePos[i2][0] != 1500.0){
							GLfloat dx = neuePos[i][0] - neuePos[i2][0];
							GLfloat dy = neuePos[i][1] - neuePos[i2][1];
							GLfloat dBetraghoch2 = dx*dx + dy*dy; // Quadratwurzel sparen
							if (dBetraghoch2 <= 1){
								// Kollision

                                Collision(neuePos[i],neuePos[i2],i,i2);

								Referee.KugelKugel(i,neuePos[i][0],i2,neuePos[i2][0]);
							}
						}
					}
				}
			}
		}

		// ------------------ Kugel in Loch? --------------------------

		GLfloat Betrax,Betray;

		for (int i=0;i<16;i++){
			if (neuePos[i][0]!=1500){
				if (neuePos[i][2]<0){
                    sink(i);
				} else {

					GLfloat x=neuePos[i][0];
					GLfloat y=neuePos[i][1];
					if ((x-23.32)*(x-23.32)+(y-12.21)*(y-12.21)<2.808) {
                        Referee.BallHole(i,33);
					}
					if ((x+23.32)*(x+23.32)+(y-12.21)*(y-12.21)<2.808) {
                        Referee.BallHole(i,35);
					}
					if ((x-23.32)*(x-23.32)+(y+12.21)*(y+12.21)<2.808) {
                        Referee.BallHole(i,32);
					}
					if ((x+23.32)*(x+23.32)+(y+12.21)*(y+12.21)<2.808) {
                        Referee.BallHole(i,30);
					}
					if (x*x+(y-12.55)*(y-12.55)<1.617) {
                        Referee.BallHole(i,34);
					}
					if (x*x+(y+12.55)*(y+12.55)<1.617) {
                        Referee.BallHole(i,31);
					}

					Betrax=fabs(neuePos[i][0]);
					Betray=fabs(neuePos[i][1]);
					if ((Betrax-23.32)*(Betrax-23.32)+(Betray-12.21)*(Betray-12.21)<2.808) {     // Ecke
                        sink(i);
						//printf("\nKugel %i versenkt",i);
					}
					if ((Betrax)*(Betrax)+(Betray-12.55)*(Betray-12.55)<1.617){                  // Mitte
                        sink(i);
						//printf("\nKugel %i versenkt",i);
					}
				}
			}
		}





		// ------------------- Kollision mit Bande? ---------------------

		// der Kuerzungsfaktor ist 1-bandenfaktor*cosinus Ausfallwinkel
		// somit stellt der bandenfaktor den max. moeglichen Faktor dar (bei senkrechter Reflexion)


		{
			for (int i=0;i<16;i++){
				if (neuePos[i][0] != 1500.0) {
					GLfloat laenge = 1;
					GLfloat faktor = 1;

					//unten

					if (neuePos[i][1]<(-Tischbreite+0.5)) {
						if (((neuePos[i][0]>-20.53)&&(neuePos[i][0]<-1.137))||((neuePos[i][0]<20.53)&&(neuePos[i][0]>1.137))){
                            Referee.BallBand(i,neuePos[i][0],21);
							neuePos[i][1]=(-Tischbreite+0.5);
                            laenge=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-bandenfaktor*(-BallSpeed[i][1]/laenge);
                            BallSpeed[i][1]=-BallSpeed[i][1]* faktor;
                            BallSpeed[i][0]=BallSpeed[i][0]* faktor;
						} else {
							// rechts
							if (neuePos[i][0]>=20.53){
								if (neuePos[i][1] <= -0.75355 * (neuePos[i][0]-20.53) + (-Tischbreite+0.62)){  
                                    Referee.BallBand(i,neuePos[i][0],21);
									//neuePos[i][1] = -0.75355 * (neuePos[i][0]-20.53) + (-Tischbreite+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// links
							if (neuePos[i][0]<=-20.53){
								if (neuePos[i][1] <= 0.75355 * (neuePos[i][0]+20.53) + (-Tischbreite+0.62)){  
                                    Referee.BallBand(i,neuePos[i][0],21);
									//neuePos[i][1] = 0.75355 * (neuePos[i][0]+20.53) + (-Tischbreite+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// Mitte rechts
							if ((neuePos[i][0]>0)&&(neuePos[i][0]<=1.137)){
								if (neuePos[i][1] <= 5.671 * (neuePos[i][0]-1.137) + (-Tischbreite+2.879)){ 
                                    Referee.BallBand(i,neuePos[i][0],21);
									//neuePos[i][1] = 5.671 * (neuePos[i][0]-1.137) + (-Tischbreite+2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = 0.984808;
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// Mitte links
							if ((neuePos[i][0]<=0)&&(neuePos[i][0]>=-1.137)){
								if (neuePos[i][1] <= -5.671 * (neuePos[i][0]+1.137) + (-Tischbreite+2.879)){ 
                                    Referee.BallBand(i,neuePos[i][0],21);
									//neuePos[i][1] = -5.671 * (neuePos[i][0]+1.137) + (-Tischbreite+2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = -0.984808;
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}

					//oben

					if (neuePos[i][1]>(Tischbreite-0.5)){
						if (((neuePos[i][0]>-20.53)&&(neuePos[i][0]<-1.137))||((neuePos[i][0]<20.53)&&(neuePos[i][0]>1.137))){
                            Referee.BallBand(i,neuePos[i][0],23);
							neuePos[i][1]=(Tischbreite-0.5);
                            laenge=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-bandenfaktor*(BallSpeed[i][1]/laenge);
                            BallSpeed[i][1]=-BallSpeed[i][1]*faktor;
                            BallSpeed[i][0]=BallSpeed[i][0]*faktor;
						} else {
							// rechts
							if (neuePos[i][0]>=20.53){
								if (neuePos[i][1] >= 0.75355 * (neuePos[i][0]-20.53) + (Tischbreite-0.62)){
                                    Referee.BallBand(i,neuePos[i][0],23);
									//neuePos[i][1] = 0.75355 * (neuePos[i][0]-20.53) + (Tischbreite-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// links
							if (neuePos[i][0]<=-20.53){
								if (neuePos[i][1] >= -0.75355 * (neuePos[i][0]+20.53) + (Tischbreite-0.62)){ 
                                    Referee.BallBand(i,neuePos[i][0],23);
									//neuePos[i][1] = -0.75355 * (neuePos[i][0]+20.53) + (Tischbreite-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// Mitte rechts
							if ((neuePos[i][0]>0)&&(neuePos[i][0]<=1.137)){
								if (neuePos[i][1] >= -5.671 * (neuePos[i][0]-1.137) + (Tischbreite-2.879)){  
                                    Referee.BallBand(i,neuePos[i][0],23);
									//neuePos[i][1] = -5.671 * (neuePos[i][0]-1.137) + (Tischbreite-2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = -0.984808;		   
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// Mitte links
							if ((neuePos[i][0]<=0)&&(neuePos[i][0]>=-1.137)){
								if (neuePos[i][1] >=  5.671 * (neuePos[i][0]+1.137) + (Tischbreite-2.879)){
                                    Referee.BallBand(i,neuePos[i][0],23);
									//neuePos[i][1] =  5.671 * (neuePos[i][0]+1.137) + (Tischbreite-2.879);
									GLfloat cos80 = 0.173648;
									GLfloat sin80 = 0.984808;	
                                    GLfloat xstrich = BallSpeed[i][0] * cos80 + BallSpeed[i][1] * sin80;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin80 + BallSpeed[i][1] * cos80;
									ystrich = -ystrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos80 - ystrich * sin80);
                                    BallSpeed[i][1] = (xstrich * sin80 + ystrich * cos80);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}

					//links

					if (neuePos[i][0]<(-Tischlaenge+0.5)) {
						if ((neuePos[i][1]>-9.37)&&(neuePos[i][1]<9.37)){
                            Referee.BallBand(i,neuePos[i][0],20);
							neuePos[i][0]=(-Tischlaenge+0.5);
                            laenge=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-bandenfaktor*(-BallSpeed[i][0]/laenge);
                            BallSpeed[i][0]=-BallSpeed[i][0]*faktor;
                            BallSpeed[i][1]=BallSpeed[i][1]*faktor;
						} else {
							// oben
							if (neuePos[i][1]>=9.37){
								if (neuePos[i][0] <= -0.75355 * (neuePos[i][1]-9.37) + (-Tischlaenge+0.62)){  
                                    Referee.BallBand(i,neuePos[i][0],20);
									//neuePos[i][0] = -0.75355 * (neuePos[i][1]-9.37) + (-Tischlaenge+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// unten
							if (neuePos[i][1]<=-9.37){
								if (neuePos[i][0] <= 0.75355 * (neuePos[i][1]+9.37) + (-Tischlaenge+0.62)){
                                    Referee.BallBand(i,neuePos[i][0],20);
									//neuePos[i][0] = 0.75355 * (neuePos[i][1]+9.37) + (-Tischlaenge+0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}

					//rechts

					if (neuePos[i][0]>(Tischlaenge-0.5)){
						if ((neuePos[i][1]>-9.37)&&(neuePos[i][1]<9.37)){
                            Referee.BallBand(i,neuePos[i][0],22);
							neuePos[i][0]=(Tischlaenge-0.5);
                            laenge=sqrt(BallSpeed[i][0]*BallSpeed[i][0]+BallSpeed[i][1]*BallSpeed[i][1]);
                            faktor = 1-bandenfaktor*(BallSpeed[i][0]/laenge);
                            BallSpeed[i][0]=-BallSpeed[i][0]*faktor;
                            BallSpeed[i][1]=BallSpeed[i][1]*faktor;
						} else {
							// oben
							if (neuePos[i][1]>=9.37){
								if (neuePos[i][0] >= 0.75355 * (neuePos[i][1]-9.37) + (Tischlaenge-0.62)){ 
                                    Referee.BallBand(i,neuePos[i][0],22);
									//neuePos[i][0] = 0.75355 * (neuePos[i][1]-9.37) + (Tischlaenge-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = -0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
							// unten
							if (neuePos[i][1]<=-9.37){
								if (neuePos[i][0] >= -0.75355 * (neuePos[i][1]+9.37) + (Tischlaenge-0.62)){  
                                    Referee.BallBand(i,neuePos[i][0],22);
									//neuePos[i][0] = -0.75355 * (neuePos[i][1]+9.37) + (Tischlaenge-0.62);
									GLfloat cos37 = 0.798636;
									GLfloat sin37 = 0.601815;
                                    GLfloat xstrich = BallSpeed[i][0] * cos37 + BallSpeed[i][1] * sin37;
                                    GLfloat ystrich = -BallSpeed[i][0] * sin37 + BallSpeed[i][1] * cos37;
									xstrich = -xstrich;
									ystrich = ystrich*VerlustTasche;
									xstrich = xstrich*VerlustTasche;
                                    BallSpeed[i][0] = (xstrich * cos37 - ystrich * sin37);
                                    BallSpeed[i][1] = (xstrich * sin37 + ystrich * cos37);
                                    neuePos[i][0]+=BallSpeed[i][0]/Aufloesung;
                                    neuePos[i][1]+=BallSpeed[i][1]/Aufloesung;
								}
							}
						}
					}
				}
			}
		}




		// ------------------------------- Tabelle aktualisieren -------------------------------

		GLint zeitpunkt = zeit*100/Aufloesung; // aktuelle Zeit berechnen (fuer Tabelle)
		{
			for (int i=0;i<16;i++){
				LightingTable[zeitpunkt][i][0] = neuePos[i][0];
				LightingTable[zeitpunkt][i][1] = neuePos[i][1];
				LightingTable[zeitpunkt][i][2] = neuePos[i][2];
			}
		}



		// -------------------------- neue Geschwindigkeit berechnen ----------------------------

		{
			for (int i=0;i<16;i++){
				if (neuePos[i][0] != 1500.0){
                    GLfloat geschw = sqrt(BallSpeed[i][0]* BallSpeed[i][0] +  BallSpeed[i][1]* BallSpeed[i][1]);
					GLfloat geschwneu = geschw - (reibung/Aufloesung);
					if (neuePos[i][2]<0){beweg=1;} // Kugel faellt und bewegt sich damit
					if (geschwneu <= 0.0) {  // Kugel bleibt stehen
                        BallSpeed[i][0] = 0.0;
                        BallSpeed[i][1] = 0.0;
					}
					else {
                        BallSpeed[i][0] = (BallSpeed[i][0] / geschw) * geschwneu; // neue Geschw. wird gesetzt
                        BallSpeed[i][1] = (BallSpeed[i][1] / geschw) * geschwneu;
						beweg = 1; // Es bewegt sich noch was...
					}
				}
			}
		}


		// ---------------------------------- Stossdauer setzen ------------------------------------

		if (beweg) {
			Stossdauer = (zeitpunkt<1999)?zeitpunkt+1:1999;
		}

		{ //  Daten umschreiben
			for (int i=0;i<16;i++){
				altePos[i][0]=neuePos[i][0];
				altePos[i][1]=neuePos[i][1];
				altePos[i][2]=neuePos[i][2];
			}
		}
	} 

	//printf(" fertig!\n\n");


}


