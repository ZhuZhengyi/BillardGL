#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Namen.h"
#include "ParamConfig.h"

void WriteConfig(){
	FILE *f;
#ifndef _WIN32
	char dateiname[40];
	sprintf(dateiname,"%s/.BillardGL.conf.v7",getenv("HOME"));
	f=fopen(dateiname,"w+");
#endif
#ifdef _WIN32
	f=fopen("BillardGL.conf.v7","wb+");
#endif
	if (f) {
		char Spieler1temp[10];
		char Spieler2temp[10];
		char NetzwerkSpielertemp[10];
		for (int i=0;i<10;i++) {
			if (Player1[i]==' ') {
				Spieler1temp[i]='%';
			} else {
				Spieler1temp[i]=Player1[i];
			}
			if (Player2[i]==' ') {
				Spieler2temp[i]='%';
			} else {
				Spieler2temp[i]=Player2[i];
			}
			if (NetworkPlayer[i]==' ') {
				NetzwerkSpielertemp[i]='%';
			} else {
				NetzwerkSpielertemp[i]=NetworkPlayer[i];
			}
		}
		fprintf(f,"%i\n",TextureSize);
		fprintf(f,"%i\n",DisplayTextureSize);
		fprintf(f,"%i\n",TableTextureSize);
		fprintf(f,"%i\n",BallResolution);
		fprintf(f,"%f\n",MouseSpeed);
		fprintf(f,"%i\n",InvertX);
		fprintf(f,"%i\n",InvertY);
		fprintf(f,"%i\n",ScreenResolution);
		fprintf(f,"%i\n",ColorDepth);
		fprintf(f,"%i\n",Reflections);
		fprintf(f,"%i\n",Shadow);
		fprintf(f,"%i\n",TexMMM);
        fprintf(f,"%i\n",Language);
		fprintf(f,"%i\n",ShowFPS);
		fprintf(f,"%i\n",AmbientLighting);
		fprintf(f,"%i\n",TableLamps);
		fprintf(f,"%i\n",GreenLamp);
		fprintf(f,"%f\n",EffectVolumeDown);
		fprintf(f,"%f\n",MusicVolumeDown);
		fprintf(f,"%s\n",Spieler1temp);
		fprintf(f,"%s\n",Spieler2temp);
		fprintf(f,"%s\n",NetzwerkSpielertemp);
		fclose(f);
	}
}

void LoadConfig(){
	FILE *f;
#ifndef _WIN32
    char filename[40];  //filename
    sprintf(filename,"%s/.BillardGL.conf.v7",getenv("HOME"));
    f=fopen(filename,"r");
#endif
#ifdef _WIN32
	f=fopen("BillardGL.conf.v7","rb");
#endif
	if (f) {
        char Spieler1temp[10];      //player1temp
        char Spieler2temp[10];      //player2temp
        char NetzwerkSpielertemp[10]; //network_player_temp
		fscanf(f,"%i",&TextureSize);
		fscanf(f,"%i",&DisplayTextureSize);
		fscanf(f,"%i",&TableTextureSize);
		fscanf(f,"%i",&BallResolution);
		fscanf(f,"%f",&MouseSpeed);
		fscanf(f,"%i",&InvertX);
		fscanf(f,"%i",&InvertY);
		fscanf(f,"%i",&ScreenResolution);
		fscanf(f,"%i",&ColorDepth);
		fscanf(f,"%i",&Reflections);
		fscanf(f,"%i",&Shadow);
		fscanf(f,"%i",&TexMMM);
        fscanf(f,"%i",&Language);
		fscanf(f,"%i",&ShowFPS);
		fscanf(f,"%i",&AmbientLighting);
		fscanf(f,"%i",&TableLamps);
		fscanf(f,"%i",&GreenLamp);
		fscanf(f,"%f",&EffectVolumeDown);
		fscanf(f,"%f",&MusicVolumeDown);
		fscanf(f,"%s",Spieler1temp);
		fscanf(f,"%s",Spieler2temp);
		fscanf(f,"%s",NetzwerkSpielertemp);
		for (int i=0;i<10;i++) {
			if (Spieler1temp[i]=='%') {
				Player1[i]=' ';
			} else {
				Player1[i]=Spieler1temp[i];
			}
			if (Spieler2temp[i]=='%') {
				Player2[i]=' ';
			} else {
				Player2[i]=Spieler2temp[i];
			}
			if (NetworkPlayer[i]=='%') {
				NetworkPlayer[i]=' ';
			} else {
				NetworkPlayer[i]=NetzwerkSpielertemp[i];
			}
		}
	}
}

void GetCommandParam(int argc,char **argv) {

	// Titeltext
	//#ifndef _WIN32
	printf("\n BillardGL (C) 2001, 2002 Tobias Nopper, Stefan Disch, Martina Welte\n\n");
	//#endif

	//Defaultwerte
	TextureSize        = 2;
	DisplayTextureSize = 1;
	TableTextureSize   = 2;
	BallResolution      = 7;
	InvertX              = 0;
	InvertY              = 0;
    GameType                = EIGHT_BALL;
	Shadow             = 1;

	TexMMM               = 3;

	Epsilon              = 0.05;
	MouseSpeed           = 0.4;
	PhysicsFrequenz       = 400;
	FrictionFactor       = 1.2;
	GangsFactor         = 0.4;
	CollisionFactor     = 0.95;
	ZBufferDelete      = 1;
	ScreenResolution = 800;
	ColorDepth            = 16;
	Reflections         = 0;
    Language              = 0;

	ShowFPS             = 0;
	AmbientLighting       = 1;
	TableLamps          = 2;
	GreenLamp          = 0;

    FullScreen           = 0;

	EffectVolumeDown    = .5;
	MusicVolumeDown     = .5;

	sprintf(Player1,"Name 1");
	sprintf(Player2,"Name 2");
	sprintf(NetworkPlayer,"Name");

    LoadConfig();

	// Einlesen der Kommandozeilenparameter
	int i=1;
	while (i<argc) {
		if (!strcmp(argv[i],"-y")||!strcmp(argv[i],"-inverty")) {
			InvertY = 1; 
		} else if (!strcmp(argv[i],"-x")||!strcmp(argv[i],"-invertx")) {
			InvertX = 1; 
		} else if (!strcmp(argv[i],"-z")||!strcmp(argv[i],"-zbuffer")) {
			ZBufferDelete = 0; 
		} else if (!strcmp(argv[i],"-f")||!strcmp(argv[i],"-fullscreen")) {
			FullScreen = 1; 
		} else if (!strcmp(argv[i],"-w")||!strcmp(argv[i],"-windowed")) {
			FullScreen = 0; 
		} else if (!strcmp(argv[i],"-hq")||!strcmp(argv[i],"-highquality")) {
			TextureSize=2;
			DisplayTextureSize = 2;
			TableTextureSize   = 1;
			BallResolution      = 9;
			ScreenResolution = 1024;
			ColorDepth            = 32;
			Reflections = 1;
		} else if (!strcmp(argv[i],"-t")||!strcmp(argv[i],"-texturen")) {
			i++;
			if (!strcmp(argv[i],"1")||!strcmp(argv[i],"voll")) {
				TextureSize=1;
			} else if (!strcmp(argv[i],"2")||!strcmp(argv[i],"halb")) {
				TextureSize=2;
			} else if (!strcmp(argv[i],"4")||!strcmp(argv[i],"viertel")) {
				TextureSize=4;
			} else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"achtel")) {
				TextureSize=8;
			} else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"aus")) {
				TextureSize=0;
			} 
		} else if (!strcmp(argv[i],"-at")||!strcmp(argv[i],"-atexturen")) {
			i++;
			if (!strcmp(argv[i],"1")||!strcmp(argv[i],"voll")) {
				DisplayTextureSize=1;
			} else if (!strcmp(argv[i],"2")||!strcmp(argv[i],"halb")) {
				DisplayTextureSize=2;
			} else if (!strcmp(argv[i],"4")||!strcmp(argv[i],"viertel")) {
				DisplayTextureSize=4;
			} else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"achtel")) {
				DisplayTextureSize=8;
			} else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"aus")) {
				DisplayTextureSize=0;
			} 
		} else if (!strcmp(argv[i],"-tt")||!strcmp(argv[i],"-ttexturen")) {
			i++;
			if (!strcmp(argv[i],"1")||!strcmp(argv[i],"voll")) {
				TableTextureSize=1;
			} else if (!strcmp(argv[i],"2")||!strcmp(argv[i],"halb")) {
				TableTextureSize=2;
			} else if (!strcmp(argv[i],"4")||!strcmp(argv[i],"viertel")) {
				TableTextureSize=4;
			} else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"achtel")) {
				TableTextureSize=8;
			} else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"aus")) {
				TableTextureSize=0;
			} 
		} else if (!strcmp(argv[i],"-a")||!strcmp(argv[i],"-aufstellung")) {
			i++;
			if (!strcmp(argv[i],"2")||!strcmp(argv[i],"s")||!strcmp(argv[i],"simpel")||!strcmp(argv[i],"zweibaelle")) {
                GameType=TWO_BALLS;
            } else if (!strcmp(argv[i],"8")||!strcmp(argv[i],"a")||!strcmp(argv[i],"EIGHT_BALL")||!strcmp(argv[i],"8ball")||!strcmp(argv[i],"8-ball")) {
                GameType=EIGHT_BALL;
			} else if (!strcmp(argv[i],"9")||!strcmp(argv[i],"n")||!strcmp(argv[i],"neunball")||!strcmp(argv[i],"9ball")||!strcmp(argv[i],"9-ball")) {
                GameType=NINE_BALL;
			} else if (!strcmp(argv[i],"0")||!strcmp(argv[i],"l")||!strcmp(argv[i],"leer")) {
                GameType=GT_EMPTY;
			} else if (!strcmp(argv[i],"z")||!strcmp(argv[i],"zufall")) {
                GameType=GT_RANDOM;
			}
		} else if (!strcmp(argv[i],"-s")||!strcmp(argv[i],"-schatten")) {
			Shadow=0;
		} else if (!strcmp(argv[i],"-g")||!strcmp(argv[i],"-geometrie")) {
			i++;
			BallResolution=atoi(argv[i]);
		} else if (!strcmp(argv[i],"-ep")||!strcmp(argv[i],"-epsilon")) {
			i++;
			Epsilon=atof(argv[i]);
		} else if (!strcmp(argv[i],"-m")||!strcmp(argv[i],"-mousespeed")) {
			i++;
			MouseSpeed=atof(argv[i]);
		} else if (!strcmp(argv[i],"-p")||!strcmp(argv[i],"-physik")) {
			i++;
			PhysicsFrequenz=atoi(argv[i]);
		} else if (!strcmp(argv[i],"-r")||!strcmp(argv[i],"-reibung")) {
			i++;
			FrictionFactor=atof(argv[i]);
		} else if (!strcmp(argv[i],"-k")||!strcmp(argv[i],"-kollision")) {
			i++;
			CollisionFactor=atof(argv[i]);
		} else if (!strcmp(argv[i],"-b")||!strcmp(argv[i],"-banden")) {
			i++;
			GangsFactor=atof(argv[i]);
		} 

		i++;
	}

    WriteConfig();


	//#ifndef _WIN32

	//Ausgabe der Parameter
	/*
	   printf("  Ball textures : ");
	   switch (Texturgroesse) {
	   case 1: printf("High");break;
	   case 2: printf("Normal");break;
	   case 4: printf("Low");break;
	   case 8: printf("Very low");break;
	   case 0: printf("Off");break;
	   }

	   printf("\n  Menu textures : ");
	   switch (AnzeigeTexturgroesse) {
	   case 1: printf("Normal");break;
	   case 2: printf("Low");break;
	   case 4: printf("Groesse 4 - Viertel");break;
	   case 8: printf("Groesse 8 - Achtel");break;
	   case 0: printf("Aus");break;
	   }

	   printf("\n  Table texture : ");
	   switch (TischTexturgroesse) {
	   case 1: printf("High");break;
	   case 2: printf("Normal");break;
	   case 4: printf("Low");break;
	   case 8: printf("Very Low");break;
	   case 0: printf("Off");break;
	   }

	   printf("\n");

	   if (ZBufferLoeschen) {
	   printf("  ZBufferLoesch.: Ein\n");
	   } else {
	   printf("  ZBufferLoesch.: Aus\n");
	   AnzeigeTexturgroesse=0;
	   Schatten=0;
	   }

	   printf("  Ball Res.     : %i\n",KugelAufloesung);

	   printf("  Shadows       : ");
	   switch (Schatten) {
	   case 1: printf("On");break;
	   case 0: printf("Off");break;
	   }
	//  printf("  Epsilon       : %f\n",Epsilon);

	printf("\n  Mousespeed    : %f\n",MouseSpeed);

	if (InvertX) {
	printf("  InvertX       : On\n");
	} else {
	printf("  InvertX       : Off\n");
	}

	if (InvertY) {
	printf("  InvertY       : On\n");
	} else {
	printf("  InvertY       : Off\n");
	}

	printf("  Spiel         : ");
	switch (Spiel) {
	case TWO_BALLS: printf("Zwei Kugeln");break;
    case EIGHT_BALL: printf("8-Ball");break;
	case NINE_BALL: printf("9-Ball");break;
	case GT_RANDOM: printf("Zufall");break;
	case GT_EMPTY: printf("Aus");break;
	}

	//printf("\n  Physikfrequenz: %i\n",PhysikFrequenz);
	//printf("  Reibungsfaktor: %f\n",ReibungsFaktor);
	//printf("  Bandenfaktor  : %f\n",BandenFaktor);
	//printf("  Koll.faktor   : %f\n",KollisionsFaktor);
	//printf("  Bildschirmaufl: %i\n",BildschirmAufloesung);


	printf("\n");

	//#endif
	*/
}
