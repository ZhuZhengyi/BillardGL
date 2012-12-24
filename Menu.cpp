/****************************************************************************
 **
 **  Menu.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 *****************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h> //2CHANGE wieder raus wenn kein printf mehr drin
#include <GL/glut.h>

#include "LA.h"                // Zum Handling von .bmp-Files bzw. Matrix-Bildern
#include "bmp.h"
#include "Camera.h"
#include "Ball.h"
#include "Table.h"
#include "Display.h"
#include "Judge.h"
#include "Schild.h"
#include "Textfeld.h"
#include "Lighting.h"

#include "BoardLayout.h"
#include "ParamConfig.h"
#include "Chosen.h"
#include "balltable.h"
#include "MouseKey.h"
#include "BillardGL.h"

#include "Menu.h"

#include "Namen.h"

//#include "createTexture.h"   // Funktion zum Generieren einer Textur aus einem 
// Matrix-Bild (aus "Ubungen)


/* --------- Konstruktor ---------- */
Menu::Menu() {
    //
    for (GLint TextfeldNr=0; TextfeldNr < 1000 ; TextfeldNr++ ) {
        TextItemArray[TextfeldNr] = 0;
    }

    TDL=0;
}

void Menu::Update(GLint Faktor) {

    if (!InAnimation) {
        return;
    } else {

        AnimationsTime+=Faktor;
        if (AnimationsTime>=ANIMATION_TIME) {
            AnimationsTime=ANIMATION_TIME;
            InAnimation=0;
        }

        for (GLint SchildNr=0;SchildNr<SchildAnzahl;SchildNr++) {
            SchildArray[SchildNr]->Animate(Faktor);
        }

        for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
            if( TextItemArray[TextfeldNr] )
                TextItemArray[TextfeldNr]->Animiere(Faktor);
        }

    }
}

void Menu::draw()
{

    glMatrixMode(GL_PROJECTION);        // 选择投影矩阵
    glLoadIdentity();                   // 重置投影矩阵
    gluOrtho2D(0.0,16.0,0.0,12.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (GLint SchildNr=0;SchildNr<SchildAnzahl;SchildNr++) {
        SchildArray[SchildNr]->draw();
    }

    for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
        if( TextItemArray[TextfeldNr] )
            TextItemArray[TextfeldNr]->draw();
    }

}

void Menu::LoadLanguage(GLint Sprache)
{
    char wort[2000];
    char temp[2000];
    int index;

    FILE *f;
    char dateiname[1000];
#ifndef _WIN32
    sprintf(dateiname,"%slang/%i.lang",PATH,Sprache);
    f=fopen(dateiname,"r");
#endif
#ifdef _WIN32
    sprintf(dateiname,"lang/%i.lang",Sprache);
    f=fopen(dateiname,"rb");
#endif
    if (f) {
        GLint nummer;
        while (!feof(f)) {
            for (int j=0 ; j<2000 ; j++ ) {
                temp[j]=0;
                wort[j]=0;
            }
            fgets(temp,2000,f);
            int i=0;
            while (temp[i]) i++;
            while ((temp[--i]==10 || temp[i]==13 || temp[i]==32) && i) temp[i]=0;
            if (sscanf(temp,"%d %n",&nummer,&index)<1) continue;

            //printf("."); fflush(stdout);

            i=0;
            while (temp[index+i]) {
                wort[i]=temp[index+i];
                i++;
            }
            wort[index+i]=0;

            if (temp[0]) {
                if (TextItemArray[nummer]) {
                    TextItemArray[nummer]->SetTextKDL(wort);
                } else {
                    TextItemArray[nummer] = new TextItem();
                    TextItemArray[nummer]->InitialisiereKDL(TDL,wort);
                }
            }
        }
        fclose(f);
    }
}

void Menu::Init(GLint Texturgroesse)
{

    if (!TDL) {
        TDL=dummyTextfeld.dummyInit(Texturgroesse);
        return;
    }

    //printf(" Loading languages\n");
    LoadLanguage(900); //Deutsch zuerst
    LoadLanguage(901); //drueber Englisch als default
    LoadLanguage(999); //Sprachenuebersicht

    if (Language) LoadLanguage(Language);

    //Tutorial-Texta auf Breite 31.2
    for (GLint tf=640 ; tf < 700 ; tf++ ) {
        if (!TextItemArray[tf]) continue;
        TextItemArray[tf]->SetMaxWidth(31.2);
    }

    //Regeln-Text auf Breite 24
    for (GLint tf2=700 ; tf2 < 800 ; tf2++ ) {
        if (!TextItemArray[tf2]) continue;
        TextItemArray[tf2]->SetMaxWidth(26);
    }

    //printf("\n\n Generating Menu Display Lists\n");

    for (GLint dl=0 ; dl < 1000 ; dl++ ) {
        if (!TextItemArray[dl]) continue;
        TextItemArray[dl]->GenerateDisplayList();
        //printf("."); fflush(stdout);
    }

    //printf("\n\n");

    TextItemArray[T_SPIELER1NAME]->SetText(Player1);

    TextItemArray[T_SPIELER2NAME]->SetText(Player2);

    if (TextItemArray[T_FPS])
        TextItemArray[T_FPS]->SetText("0 fps");
    else {
        TextItemArray[T_FPS] = new TextItem();
        TextItemArray[T_FPS]->Initialisiere(TDL,"0 fps");
    }

    SchildAnzahl=0;

    MenuBackground.Init();
    SchildArray[SchildAnzahl++]=&MenuBackground;

    logo.InitLogo();
    SchildArray[SchildAnzahl++]=&logo;

    ball[0].Init(1,"a00","aalpha");
    SchildArray[SchildAnzahl++]=&ball[0];
    ball[1].Init(1,"a1","aalpha");
    SchildArray[SchildAnzahl++]=&ball[1];
    ball[2].Init(1,"a2","aalpha");
    SchildArray[SchildAnzahl++]=&ball[2];
    ball[3].Init(1,"a3","aalpha");
    SchildArray[SchildAnzahl++]=&ball[3];
    ball[4].Init(1,"a4","aalpha");
    SchildArray[SchildAnzahl++]=&ball[4];
    ball[5].Init(1,"a5","aalpha");
    SchildArray[SchildAnzahl++]=&ball[5];
    ball[6].Init(1,"a6","aalpha");
    SchildArray[SchildAnzahl++]=&ball[6];
    ball[7].Init(1,"a7","aalpha");
    SchildArray[SchildAnzahl++]=&ball[7];
    ball[8].Init(1,"a8","aalpha");
    SchildArray[SchildAnzahl++]=&ball[8];
    ball[9].Init(1,"a9","aalpha");
    SchildArray[SchildAnzahl++]=&ball[9];
    ball[10].Init(1,"a10","aalpha");
    SchildArray[SchildAnzahl++]=&ball[10];
    ball[11].Init(1,"a11","aalpha");
    SchildArray[SchildAnzahl++]=&ball[11];
    ball[12].Init(1,"a12","aalpha");
    SchildArray[SchildAnzahl++]=&ball[12];
    ball[13].Init(1,"a13","aalpha");
    SchildArray[SchildAnzahl++]=&ball[13];
    ball[14].Init(1,"a14","aalpha");
    SchildArray[SchildAnzahl++]=&ball[14];
    ball[15].Init(1,"a15","aalpha");
    SchildArray[SchildAnzahl++]=&ball[15];

    volle.Init(Texturgroesse,"volle","aalpha2");
    SchildArray[SchildAnzahl++]=&volle;
    halbe.Init(Texturgroesse,"halbe","aalpha2");
    SchildArray[SchildAnzahl++]=&halbe;

    //GameStar.Initialisiere(1,"gamestar",1); //Gamestar
    //SchildArray[SchildAnzahl++]=&GameStar;


    if (!MenuState) {MenuState=HOME_SCREEN;}

    NewMenuState();
    StarteAnimation();

    MenuGesperrt=0;

}

GLint Menu::MouseClick(int Button,int Richtung,int x,int y){

    StarteAnimation();

    GLint Signal=0;
    GLint SchildNr=0;
    GLint TextfeldNr=0;

    while (!Signal && SchildNr<SchildAnzahl) {
        Signal=SchildArray[SchildNr++]->MouseButton(Button,Richtung,x,y);
    }

    for (TextfeldNr=0 ; TextfeldNr<1000; TextfeldNr++) {
        if (Signal) break;
        if (TextItemArray[TextfeldNr])
            Signal=TextItemArray[TextfeldNr]->MouseButton(Button,Richtung,x,y);
    }

    if (Signal>0) {
        SignalExecution(Signal);
    }

    if (MenuState==HOME_SCREEN &&
            Richtung==GLUT_UP) {
        if (Language) setMenuState(MAIN_MENU);
        else setMenuState(LANGUAGE);
        return 1;
    }

    if (MenuGesperrt ||
            MenuState!=PLAYING) {
        return 1;
    }

    return Signal;
}

void Menu::StarteAnimation() {
    InAnimation=1;
    AnimationsTime=0;
}

void Menu::setMenuState(GLint NeuerZustand) {
    MenuState=NeuerZustand;
    NewMenuState();
}

void Menu::NewMenuState(){

    for (GLint SchildNr=0;SchildNr<SchildAnzahl;SchildNr++) {
        SchildArray[SchildNr]->Disactive();
    }

    for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
        if( TextItemArray[TextfeldNr] )
            TextItemArray[TextfeldNr]->Desaktiviere();
    }

    if (ShowFPS) TextItemArray[T_FPS]->Positioniere(0,11.7,.3,A_LINKS);

    switch (MenuState) {

    case HOME_SCREEN: {

        //GameStar.Positioniere(6,5,10,6);
        //GameStar.Positioniere(6,5,10,6);

        logo.PositionFix(4,6,12,8);
        //logo.Positioniere(4,6,12,8);

        //TextfeldArray[790]->Positioniere(3.8,5,1,A_RECHTS);
        //TextfeldArray[790]->Positioniere(3.8,5,1,A_RECHTS);
        //TextfeldArray[791]->Positioniere(10.2,5,1,A_LINKS);
        //TextfeldArray[791]->Positioniere(10.2,5,1,A_LINKS);

        TextItemArray[T_NAMEN1]->Positioniere(8,1.4,.5,A_MITTE);
        TextItemArray[T_NAMEN2]->Positioniere(8,1.0,.5,A_MITTE);
        TextItemArray[T_NOWARRANTY]->Positioniere(8,0,.5,A_MITTE);
        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

    } break;

    case LANGUAGE: {

        MenuBackground.Positioning(2,2.5,14,8.5);
        logo.Positioning(5,9,11,11);
        logo.FullyVisible();

        TextItemArray[T_SPRACHAUSWAHL]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_SPRACHAUSWAHL]->VollSichtbar();
        GLfloat Pos_y=7;
        for (GLint TextfeldNr=900;TextfeldNr<1000;TextfeldNr++) {
            if ( TextItemArray[TextfeldNr] ) {
                TextItemArray[TextfeldNr]->Positioniere(8,Pos_y,.71,A_MITTE);
                TextItemArray[TextfeldNr]->SetzeSignal(TextfeldNr);
                Pos_y-=.5;
            }
        }

        if (Language) {
            TextItemArray[T_BACK]->Positioniere(8,1,1,A_MITTE);
            TextItemArray[T_BACK]->SetzeSignal(S_MAINMENU_SETUP_);
        }
        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
    } break;

    case MAIN_MENU: {

        MenuBackground.Positioning(2,2.5,14,8.5);

        logo.Positioning(5,9,11,11);
        logo.FullyVisible();
        logo.SetSignal(S_LOGO);

        TextItemArray[T_MAIN_MENU]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_MAIN_MENU]->VollSichtbar();

        TextItemArray[T_TRAINING]->Positioniere(5.5,6,1,A_MITTE);
        TextItemArray[T_TRAINING]->SetzeSignal(S_MAINMENU_TRAINING);

        TextItemArray[T_TWO_PLAYERS]->Positioniere(10.5,6,1,A_MITTE);
        TextItemArray[T_TWO_PLAYERS]->SetzeSignal(S_MAINMENU_TWO_PLAYERS);

        TextItemArray[T_HELP_]->Positioniere(5.5,4,1,A_MITTE);
        TextItemArray[T_HELP_]->SetzeSignal(S_MAINMENU_HELP);

        TextItemArray[T_SETUP_]->Positioniere(10.5,4,1,A_MITTE);
        TextItemArray[T_SETUP_]->SetzeSignal(S_MAINMENU_SETUP_);

        TextItemArray[T_EXIT]->Positioniere(8,1,1,A_MITTE);
        TextItemArray[T_EXIT]->SetzeSignal(S_MAINMENU_EXIT);

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
    } break;

    case TRAINING: {

        MenuBackground.Positioning(4,5,12,8.5);

        logo.Positioning(4,9,12,11);
        logo.FullyVisible();

        TextItemArray[T_TRAINING]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_TRAINING]->VollSichtbar();

        TextItemArray[T_EIGHT_BALL]->Positioniere(6.5,6,1,A_MITTE);
        TextItemArray[T_EIGHT_BALL]->SetzeSignal(S_TR_EIGHT_BALL);

        TextItemArray[T_NINE_BALL]->Positioniere(9.5,6,1,A_MITTE);
        TextItemArray[T_NINE_BALL]->SetzeSignal(S_TR_NINE_BALL);

        TextItemArray[T_BACK]->Positioniere(8,1,1,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_TR_BACK);

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
    } break;

    case TWO_PLAYERS: {
        MenuBackground.Positioning(3,2.5,13,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_TWO_PLAYERS]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_TWO_PLAYERS]->VollSichtbar();
        TextItemArray[T_SPIELER1]->Positioniere(8,6,1,A_RECHTS);
        TextItemArray[T_SPIELER1]->SetzeSignal(S_SPIELER1HERHOEREN);
        TextItemArray[T_SPIELER1NAME]->Positioniere(8.2,6,1,A_LINKS);
        TextItemArray[T_SPIELER1NAME]->SetzeSignal(S_SPIELER1HERHOEREN);
        TextItemArray[T_SPIELER2]->Positioniere(8,5,1,A_RECHTS);
        TextItemArray[T_SPIELER2]->SetzeSignal(S_SPIELER2HERHOEREN);
        TextItemArray[T_SPIELER2NAME]->Positioniere(8.2,5,1,A_LINKS);
        TextItemArray[T_SPIELER2NAME]->SetzeSignal(S_SPIELER2HERHOEREN);
        TextItemArray[T_EIGHT_BALL]->Positioniere(5,3,1,A_MITTE);
        TextItemArray[T_EIGHT_BALL]->SetzeSignal(S_ZW_EIGHT_BALL);
        TextItemArray[T_NINE_BALL]->Positioniere(11,3,1,A_MITTE);
        TextItemArray[T_NINE_BALL]->SetzeSignal(S_ZW_NINE_BALL);
        TextItemArray[T_BACK]->Positioniere(8,1,1,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_ZW_BACK);

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
    } break;

    case SETUP: {
        MenuBackground.Positioning(4,2.5,12,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_SETUP_]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_SETUP_]->VollSichtbar();
        TextItemArray[T_CONTROL]->Positioniere(8,6.5,1,A_MITTE);
        TextItemArray[T_CONTROL]->SetzeSignal(S_SETUP_CONTROL);
        TextItemArray[T_VIDEO]->Positioniere(8,5.5,1,A_MITTE);
        TextItemArray[T_VIDEO]->SetzeSignal(S_SETUP_VIDEO);
        TextItemArray[T_AUDIO]->Positioniere(8,4.5,1,A_MITTE);
        TextItemArray[T_LANGUAGE]->Positioniere(8,3.5,1,A_MITTE);
        TextItemArray[T_LANGUAGE]->SetzeSignal(S_SETUP_LANGUAGE);
        TextItemArray[T_BACK]->Positioniere(8,1,1,A_MITTE);
        if (AusSpiel) {
            TextItemArray[T_BACK]->SetzeSignal(S_SETUP_BACK_AS);
        } else {
            TextItemArray[T_BACK]->SetzeSignal(S_SETUP_BACK);
        }

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

    } break;

    case SETUP_CONTROL: {
        MenuBackground.Positioning(2,3.5,14,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_SETUP_]->Positioniere(4,8,1,A_LINKS);
        TextItemArray[T_SETUP_]->VollSichtbar();
        TextItemArray[T_CONTROL]->Positioniere(12,8,1,A_RECHTS);
        TextItemArray[T_CONTROL]->VollSichtbar();

        TextItemArray[T_MAUSGESCHWINDIGKEIT]->Positioniere(8,6,.71,A_RECHTS);
        TextItemArray[T_MAUSGESCHWINDIGKEIT]->SetzeSignal(S_SETUP_MOUSESPEED);
        TextItemArray[T_XACHSEINVERTIERT]->Positioniere(8,5.5,.71,A_RECHTS);
        TextItemArray[T_XACHSEINVERTIERT]->SetzeSignal(S_SETUP_XINVERT);
        TextItemArray[T_YACHSEINVERTIERT]->Positioniere(8,5,.71,A_RECHTS);
        TextItemArray[T_YACHSEINVERTIERT]->SetzeSignal(S_SETUP_YINVERT);

        if (E_InvertX) {
            TextItemArray[T_X_AN]->Positioniere(8.2,5.5,.71,A_LINKS);
            TextItemArray[T_X_AN]->SetzeSignal(S_SETUP_XINVERT);
        } else {
            TextItemArray[T_X_AUS]->Positioniere(8.2,5.5,.71,A_LINKS);
            TextItemArray[T_X_AUS]->SetzeSignal(S_SETUP_XINVERT);
        }
        if (E_InvertY) {
            TextItemArray[T_Y_AN]->Positioniere(8.2,5,.71,A_LINKS);
            TextItemArray[T_Y_AN]->SetzeSignal(S_SETUP_YINVERT);
        } else {
            TextItemArray[T_Y_AUS]->Positioniere(8.2,5,.71,A_LINKS);
            TextItemArray[T_Y_AUS]->SetzeSignal(S_SETUP_YINVERT);
        }
        if (E_MouseSpeed<=.293) {
            TextItemArray[T_MG_LANGSAM]->Positioniere(8.2,6,.71,A_LINKS);
            TextItemArray[T_MG_LANGSAM]->SetzeSignal(S_SETUP_MOUSESPEED);
        } else if (E_MouseSpeed<=.41) {
            TextItemArray[T_MG_NORMAL]->Positioniere(8.2,6,.71,A_LINKS);
            TextItemArray[T_MG_NORMAL]->SetzeSignal(S_SETUP_MOUSESPEED);
        } else if (E_MouseSpeed<=.575) {
            TextItemArray[T_MG_SCHNELL]->Positioniere(8.2,6,.71,A_LINKS);
            TextItemArray[T_MG_SCHNELL]->SetzeSignal(S_SETUP_MOUSESPEED);
        } else {
            TextItemArray[T_MG_SEHRSCHNELL]->Positioniere(8.2,6,.71,A_LINKS);
            TextItemArray[T_MG_SEHRSCHNELL]->SetzeSignal(S_SETUP_MOUSESPEED);
        }
        if( E_MouseSpeed==MouseSpeed &&
                E_InvertX==InvertX &&
                E_InvertY==InvertY) {
            TextItemArray[T_BACK]->Positioniere(8,1,1,A_MITTE);
            TextItemArray[T_BACK]->SetzeSignal(S_SETUP_CONTROLBACK);
        } else {
            TextItemArray[T_UEBERNEHMEN]->Positioniere(12,1,1,A_RECHTS);
            TextItemArray[T_UEBERNEHMEN]->SetzeSignal(S_SETUP_CONTROLUEBERNEHMEN);
            TextItemArray[T_ABBRECHEN]->Positioniere(4,1,1,A_LINKS);
            TextItemArray[T_ABBRECHEN]->SetzeSignal(S_SETUP_CONTROLBACK);
        }

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
    } break;

    case SETUP_VIDEO: {
        if (E_KugelAufloesung==3 &&
                E_BallTextureSize==8 &&
                E_TableTextureSize==0 &&
                E_AnzeigeTexturgroesse==2 &&
                E_Reflection==0 &&
                E_ScreenResolution==640 &&
                E_ColorDepth==16 &&
                E_Shadows==0 &&
                E_TableLampes==1 &&
                E_TexMMM==0 &&
                E_GreenLampe==0) {Quality=1;}
        else if (E_KugelAufloesung==5 &&
                 E_BallTextureSize==4 &&
                 E_TableTextureSize==4 &&
                 E_AnzeigeTexturgroesse==2 &&
                 E_Reflection==0 &&
                 E_ScreenResolution==640 &&
                 E_ColorDepth==16 &&
                 E_Shadows==1 &&
                 E_TableLampes==1 &&
                 E_TexMMM==2 &&
                 E_GreenLampe==0) {Quality=2;}
        else if (E_KugelAufloesung==7 &&
                 E_BallTextureSize==2 &&
                 E_TableTextureSize==2 &&
                 E_AnzeigeTexturgroesse==1 &&
                 E_Reflection==0 &&
                 E_ScreenResolution==800 &&
                 E_ColorDepth==16 &&
                 E_Shadows==1 &&
                 E_TableLampes==2 &&
                 E_TexMMM==3 &&
                 E_GreenLampe==0) {Quality=3;}
        else if (E_KugelAufloesung==7 &&
                 E_BallTextureSize==2 &&
                 E_TableTextureSize==1 &&
                 E_AnzeigeTexturgroesse==1 &&
                 E_Reflection==1 &&
                 E_ScreenResolution==1024 &&
                 E_ColorDepth==16 &&
                 E_Shadows==1 &&
                 E_TableLampes==2 &&
                 E_TexMMM==7 &&
                 E_GreenLampe==1) {Quality=4;}
        else if (E_KugelAufloesung==11 &&
                 E_BallTextureSize==1 &&
                 E_TableTextureSize==1 &&
                 E_AnzeigeTexturgroesse==1 &&
                 E_Reflection==1 &&
                 E_ScreenResolution==1024 &&
                 E_ColorDepth==32 &&
                 E_Shadows==1 &&
                 E_TableLampes==3 &&
                 E_TexMMM==7 &&
                 E_GreenLampe==1) {Quality=5;}
        else Quality=0;

        MenuBackground.Positioning(2,1.7,14,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_SETUP_]->Positioniere(4,8,1,A_LINKS);
        TextItemArray[T_SETUP_]->VollSichtbar();
        TextItemArray[T_VIDEO]->Positioniere(12,8,1,A_RECHTS);
        TextItemArray[T_VIDEO]->VollSichtbar();

        TextItemArray[T_QUALITAET]->Positioniere(8,7,1,A_RECHTS);
        TextItemArray[T_QUALITAET]->SetzeSignal(S_SETUP_QUALITAET);

        TextItemArray[T_BALLGEOMETRIE]->Positioniere(8,6.5,.6,A_RECHTS);
        TextItemArray[T_BALLGEOMETRIE]->SetzeSignal(S_SETUP_BALLGEOMETRIE);
        TextItemArray[T_BALLTEXTURES]->Positioniere(8,6.1,.6,A_RECHTS);
        TextItemArray[T_BALLTEXTURES]->SetzeSignal(S_SETUP_BALLTEXTURES);
        TextItemArray[T_TABLE_TEXTURES]->Positioniere(8,5.7,.6,A_RECHTS);
        TextItemArray[T_TABLE_TEXTURES]->SetzeSignal(S_SETUP_TABLE_TEXTURES);
        TextItemArray[T_MENUTEXTURES]->Positioniere(8,5.3,.6,A_RECHTS);
        TextItemArray[T_MENUTEXTURES]->SetzeSignal(S_SETUP_ANZEIGETEXTURES);
        TextItemArray[T_REFLEKTIONEN]->Positioniere(8,4.9,.6,A_RECHTS);
        TextItemArray[T_REFLEKTIONEN]->SetzeSignal(S_SETUP_REFLEKTIONEN);
        TextItemArray[T_RESOLUTION]->Positioniere(8,4.5,.6,A_RECHTS);
        TextItemArray[T_RESOLUTION]->SetzeSignal(S_SETUP_RESOLUTION);
        TextItemArray[T_COLOR_DEPTH]->Positioniere(8,4.1,.6,A_RECHTS);
        TextItemArray[T_COLOR_DEPTH]->SetzeSignal(S_SETUP_COLOR_DEPTH);
        TextItemArray[T_SHADOWS]->Positioniere(8,3.7,.6,A_RECHTS);
        TextItemArray[T_SHADOWS]->SetzeSignal(S_SETUP_SHADOWS);
        TextItemArray[T_TEXTURINTERPOLATION]->Positioniere(8,3.3,.6,A_RECHTS);
        TextItemArray[T_TEXTURINTERPOLATION]->SetzeSignal(S_SETUP_TEXTURINTERPOLATION);
        //TextfeldArray[T_AMBIENCE_LIGHTING]->Positioniere(8,2.9,.6,A_RECHTS);
        //TextfeldArray[T_AMBIENCE_LIGHTING]->SetzeSignal(S_SETUP_AMBIENCE_LIGHTING);
        TextItemArray[T_TABLE_LAMPEN]->Positioniere(8,2.9,.6,A_RECHTS);
        TextItemArray[T_TABLE_LAMPEN]->SetzeSignal(S_SETUP_TABLE_LAMPEN);
        TextItemArray[T_TABLE_COLORBLEEDING]->Positioniere(8,2.5,.6,A_RECHTS);
        TextItemArray[T_TABLE_COLORBLEEDING]->SetzeSignal(S_SETUP_GRUENELAMPE);
        TextItemArray[T_FRAMERATE]->Positioniere(8,2.1,.6,A_RECHTS);
        TextItemArray[T_FRAMERATE]->SetzeSignal(S_SETUP_FPS);

        //switch (E_AmbientesLicht) {
        //case 1: {
        //  TextfeldArray[T_AMBIENCE_LIGHTINGEIN]->Positioniere(8.2,2.9,.6,A_LINKS);
        //  TextfeldArray[T_AMBIENCE_LIGHTINGEIN]->SetzeSignal(S_SETUP_AMBIENCE_LIGHTING);
        //} break;
        //case 0: {
        //  TextfeldArray[T_AMBIENCE_LIGHTINGAUS]->Positioniere(8.2,2.9,.6,A_LINKS);
        //  TextfeldArray[T_AMBIENCE_LIGHTINGAUS]->SetzeSignal(S_SETUP_AMBIENCE_LIGHTING);
        //} break;
        //}

        switch (E_TableLampes) {
        case 1: {
            TextItemArray[T_TABLE_LAMPEN1]->Positioniere(8.2,2.9,.6,A_LINKS);
            TextItemArray[T_TABLE_LAMPEN1]->SetzeSignal(S_SETUP_TABLE_LAMPEN);
        } break;
        case 2: {
            TextItemArray[T_TABLE_LAMPEN2]->Positioniere(8.2,2.9,.6,A_LINKS);
            TextItemArray[T_TABLE_LAMPEN2]->SetzeSignal(S_SETUP_TABLE_LAMPEN);
        } break;
        case 3: {
            TextItemArray[T_TABLE_LAMPEN3]->Positioniere(8.2,2.9,.6,A_LINKS);
            TextItemArray[T_TABLE_LAMPEN3]->SetzeSignal(S_SETUP_TABLE_LAMPEN);
        } break;
        }

        switch (E_GreenLampe) {
        case 1: {
            TextItemArray[T_TABLE_COLORBLEEDINGEIN]->Positioniere(8.2,2.5,.6,A_LINKS);
            TextItemArray[T_TABLE_COLORBLEEDINGEIN]->SetzeSignal(S_SETUP_GRUENELAMPE);
        } break;
        case 0: {
            TextItemArray[T_TABLE_COLORBLEEDINGAUS]->Positioniere(8.2,2.5,.6,A_LINKS);
            TextItemArray[T_TABLE_COLORBLEEDINGAUS]->SetzeSignal(S_SETUP_GRUENELAMPE);
        } break;
        }

        switch (E_ShowFPS) {
        case 1: {
            TextItemArray[T_FRAMERATEEIN]->Positioniere(8.2,2.1,.6,A_LINKS);
            TextItemArray[T_FRAMERATEEIN]->SetzeSignal(S_SETUP_FPS);
        } break;
        case 0: {
            TextItemArray[T_FRAMERATEAUS]->Positioniere(8.2,2.1,.6,A_LINKS);
            TextItemArray[T_FRAMERATEAUS]->SetzeSignal(S_SETUP_FPS);
        } break;
        }

        switch (E_Shadows) {
        case 1: {
            TextItemArray[T_S_EIN]->Positioniere(8.2,3.7,.6,A_LINKS);
            TextItemArray[T_S_EIN]->SetzeSignal(S_SETUP_SHADOWS);
        } break;
        case 0: {
            TextItemArray[T_S_AUS]->Positioniere(8.2,3.7,.6,A_LINKS);
            TextItemArray[T_S_AUS]->SetzeSignal(S_SETUP_SHADOWS);
        } break;
        }


        switch (E_TexMMM) {
        case 0: {
            TextItemArray[T_TI_AUS]->Positioniere(8.2,3.3,.6,A_LINKS);
            TextItemArray[T_TI_AUS]->SetzeSignal(S_SETUP_TEXTURINTERPOLATION);
        } break;
        case 2: {
            TextItemArray[T_TI_NIEDRIG]->Positioniere(8.2,3.3,.6,A_LINKS);
            TextItemArray[T_TI_NIEDRIG]->SetzeSignal(S_SETUP_TEXTURINTERPOLATION);
        } break;
        case 7: {
            TextItemArray[T_TI_HOCH]->Positioniere(8.2,3.3,.6,A_LINKS);
            TextItemArray[T_TI_HOCH]->SetzeSignal(S_SETUP_TEXTURINTERPOLATION);
        } break;
        default: {
            TextItemArray[T_TI_NORMAL]->Positioniere(8.2,3.3,.6,A_LINKS);
            TextItemArray[T_TI_NORMAL]->SetzeSignal(S_SETUP_TEXTURINTERPOLATION);
        } break;
        }

        switch (Quality) {
        case 1: {
            TextItemArray[T_Q_SEHRSCHNELL]->Positioniere(8.2,7,1,A_LINKS);
            TextItemArray[T_Q_SEHRSCHNELL]->SetzeSignal(S_SETUP_QUALITAET);
        }break;
        case 2: {
            TextItemArray[T_Q_SCHNELL]->Positioniere(8.2,7,1,A_LINKS);
            TextItemArray[T_Q_SCHNELL]->SetzeSignal(S_SETUP_QUALITAET);
        }break;
        case 3: {
            TextItemArray[T_Q_NORMAL]->Positioniere(8.2,7,1,A_LINKS);
            TextItemArray[T_Q_NORMAL]->SetzeSignal(S_SETUP_QUALITAET);
        }break;
        case 4: {
            TextItemArray[T_Q_HOCH]->Positioniere(8.2,7,1,A_LINKS);
            TextItemArray[T_Q_HOCH]->SetzeSignal(S_SETUP_QUALITAET);
        }break;
        case 5: {
            TextItemArray[T_Q_SEHRHOCH]->Positioniere(8.2,7,1,A_LINKS);
            TextItemArray[T_Q_SEHRHOCH]->SetzeSignal(S_SETUP_QUALITAET);
        }break;
        default: {
            TextItemArray[T_Q_BENUTZER]->Positioniere(8.2,7,1,A_LINKS);
            TextItemArray[T_Q_BENUTZER]->SetzeSignal(S_SETUP_QUALITAET);
        }break;
        }

        switch (E_ScreenResolution) {
        case 640: {
            TextItemArray[T_AUF_640x480]->Positioniere(8.2,4.5,.6,A_LINKS);
            TextItemArray[T_AUF_640x480]->SetzeSignal(S_SETUP_RESOLUTION);
        }break;
        case 1024: {
            TextItemArray[T_AUF_1024x768]->Positioniere(8.2,4.5,.6,A_LINKS);
            TextItemArray[T_AUF_1024x768]->SetzeSignal(S_SETUP_RESOLUTION);
        }break;
        case 1280: {
            TextItemArray[T_AUF_1280x960]->Positioniere(8.2,4.5,.6,A_LINKS);
            TextItemArray[T_AUF_1280x960]->SetzeSignal(S_SETUP_RESOLUTION);
        }break;
        case 1600: {
            TextItemArray[T_AUF_1600x1200]->Positioniere(8.2,4.5,.6,A_LINKS);
            TextItemArray[T_AUF_1600x1200]->SetzeSignal(S_SETUP_RESOLUTION);
        }break;
        default: {
            TextItemArray[T_AUF_800x600]->Positioniere(8.2,4.5,.6,A_LINKS);
            TextItemArray[T_AUF_800x600]->SetzeSignal(S_SETUP_RESOLUTION);
        }break;
        }

        switch (E_Reflection) {
        case 1: {
            TextItemArray[T_REF_EIN]->Positioniere(8.2,4.9,.6,A_LINKS);
            TextItemArray[T_REF_EIN]->SetzeSignal(S_SETUP_REFLEKTIONEN);
        }break;
        default: {
            TextItemArray[T_REF_AUS]->Positioniere(8.2,4.9,.6,A_LINKS);
            TextItemArray[T_REF_AUS]->SetzeSignal(S_SETUP_REFLEKTIONEN);
        }break;
        }

        switch (E_ColorDepth) {
        case 32: {
            TextItemArray[T_FT_32]->Positioniere(8.2,4.1,.6,A_LINKS);
            TextItemArray[T_FT_32]->SetzeSignal(S_SETUP_COLOR_DEPTH);
        }break;
        default: {
            TextItemArray[T_FT_16]->Positioniere(8.2,4.1,.6,A_LINKS);
            TextItemArray[T_FT_16]->SetzeSignal(S_SETUP_COLOR_DEPTH);
        }break;
        }
        switch (E_AnzeigeTexturgroesse) {
        case 1: {
            TextItemArray[T_MT_NORMAL]->Positioniere(8.2,5.3,.6,A_LINKS);
            TextItemArray[T_MT_NORMAL]->SetzeSignal(S_SETUP_ANZEIGETEXTURES);
        }break;
        case 2: {
            TextItemArray[T_MT_NIEDRIG]->Positioniere(8.2,5.3,.6,A_LINKS);
            TextItemArray[T_MT_NIEDRIG]->SetzeSignal(S_SETUP_ANZEIGETEXTURES);
        }break;
        }
        switch (E_BallTextureSize) {
        case 1: {
            TextItemArray[T_BT_HOCH]->Positioniere(8.2,6.1,.6,A_LINKS);
            TextItemArray[T_BT_HOCH]->SetzeSignal(S_SETUP_BALLTEXTURES);
        }break;
        case 2: {
            TextItemArray[T_BT_NORMAL]->Positioniere(8.2,6.1,.6,A_LINKS);
            TextItemArray[T_BT_NORMAL]->SetzeSignal(S_SETUP_BALLTEXTURES);
        }break;
        case 4: {
            TextItemArray[T_BT_NIEDRIG]->Positioniere(8.2,6.1,.6,A_LINKS);
            TextItemArray[T_BT_NIEDRIG]->SetzeSignal(S_SETUP_BALLTEXTURES);
        }break;
        case 8: {
            TextItemArray[T_BT_SEHRNIEDRIG]->Positioniere(8.2,6.1,.6,A_LINKS);
            TextItemArray[T_BT_SEHRNIEDRIG]->SetzeSignal(S_SETUP_BALLTEXTURES);
        }break;
        }
        switch (E_TableTextureSize) {
        case 1: {
            TextItemArray[T_TT_HOCH]->Positioniere(8.2,5.7,.6,A_LINKS);
            TextItemArray[T_TT_HOCH]->SetzeSignal(S_SETUP_TABLE_TEXTURES);
        }break;
        case 2: {
            TextItemArray[T_TT_NORMAL]->Positioniere(8.2,5.7,.6,A_LINKS);
            TextItemArray[T_TT_NORMAL]->SetzeSignal(S_SETUP_TABLE_TEXTURES);
        }break;
        case 4: {
            TextItemArray[T_TT_NIEDRIG]->Positioniere(8.2,5.7,.6,A_LINKS);
            TextItemArray[T_TT_NIEDRIG]->SetzeSignal(S_SETUP_TABLE_TEXTURES);
        }break;
        case 8: {
            TextItemArray[T_TT_SEHRNIEDRIG]->Positioniere(8.2,5.7,.6,A_LINKS);
            TextItemArray[T_TT_SEHRNIEDRIG]->SetzeSignal(S_SETUP_TABLE_TEXTURES);
        }break;
        case 0: {
            TextItemArray[T_TT_AUS]->Positioniere(8.2,5.7,.6,A_LINKS);
            TextItemArray[T_TT_AUS]->SetzeSignal(S_SETUP_TABLE_TEXTURES);
        }break;
        }

        switch (E_KugelAufloesung) {
        case 3: {
            TextItemArray[T_BG_SEHRNIEDRIG]->Positioniere(8.2,6.5,.6,A_LINKS);
            TextItemArray[T_BG_SEHRNIEDRIG]->SetzeSignal(S_SETUP_BALLGEOMETRIE);
        }break;
        case 5: {
            TextItemArray[T_BG_NIEDRIG]->Positioniere(8.2,6.5,.6,A_LINKS);
            TextItemArray[T_BG_NIEDRIG]->SetzeSignal(S_SETUP_BALLGEOMETRIE);
        }break;
        case 7: {
            TextItemArray[T_BG_NORMAL]->Positioniere(8.2,6.5,.6,A_LINKS);
            TextItemArray[T_BG_NORMAL]->SetzeSignal(S_SETUP_BALLGEOMETRIE);
        }break;
        case 11: {
            TextItemArray[T_BG_HOCH]->Positioniere(8.2,6.5,.6,A_LINKS);
            TextItemArray[T_BG_HOCH]->SetzeSignal(S_SETUP_BALLGEOMETRIE);
        }break;
        }

        if( E_BallTextureSize==TextureSize &&
                E_AnzeigeTexturgroesse==DisplayTextureSize &&
                E_TableTextureSize==TableTextureSize &&
                E_KugelAufloesung==BallResolution &&
                E_ScreenResolution==ScreenResolution &&
                E_ColorDepth==ColorDepth &&
                E_Reflection==Reflections &&
                E_Shadows==Shadow &&
                E_AmbientLighting==AmbientLighting &&
                E_TableLampes==TableLamps &&
                E_TexMMM==TexMMM &&
                E_GreenLampe==GreenLamp) {
            TextItemArray[T_BACK]->Positioniere(8,.7,1,A_MITTE);
            TextItemArray[T_BACK]->SetzeSignal(S_SETUP_VIDEOBACK);
        } else {
            TextItemArray[T_UEBERNEHMEN]->Positioniere(4,0.7,1,A_LINKS);
            TextItemArray[T_UEBERNEHMEN]->SetzeSignal(S_SETUP_VIDEOUEBERNEHMEN);
            TextItemArray[T_ABBRECHEN]->Positioniere(12,0.7,1,A_RECHTS);
            TextItemArray[T_ABBRECHEN]->SetzeSignal(S_SETUP_VIDEOBACK);
        }
        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
    } break;

    case SETUP_VIDEO_NOTICE: {
        MenuBackground.Positioning(2,3.5,14,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_HINWEIS]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_HINWEIS]->VollSichtbar();

        TextItemArray[T_HINWEIS1]->Positioniere(8,6,.7,A_MITTE);
        TextItemArray[T_HINWEIS2]->Positioniere(8,5.5,.7,A_MITTE);

        TextItemArray[T_OK]->Positioniere(8,1,1,A_MITTE);
        TextItemArray[T_OK]->SetzeSignal(S_SETUP_VIDEOUEBERNEHMEN);

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);
    } break;

    case HELP: {
        MenuBackground.Positioning(4.5,3.5,11.5,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_HELP_]->VollSichtbar();

        TextItemArray[T_H_TUTORIAL]->Positioniere(8,6.5,1,A_MITTE);
        TextItemArray[T_H_TUTORIAL]->SetzeSignal(S_H_TUTORIAL);

        TextItemArray[T_H_KEY_ASSIGNMENTS]->Positioniere(8,5.5,1,A_MITTE);
        TextItemArray[T_H_KEY_ASSIGNMENTS]->SetzeSignal(S_H_KEY_ASSIGNMENTS);

        TextItemArray[T_H_BILLARDREGELN]->Positioniere(8,4.5,1,A_MITTE);
        TextItemArray[T_H_BILLARDREGELN]->SetzeSignal(S_H_BILLARDREGELN);

        TextItemArray[T_BACK]->Positioniere(8,1,1,A_MITTE);
        if (AusSpiel) {
            TextItemArray[T_BACK]->SetzeSignal(S_BE_BACK_AS);
        } else {
            TextItemArray[T_BACK]->SetzeSignal(S_BE_BACK);
        }

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

    } break;

    case HELP_KEY_SET: {
        MenuBackground.Positioning(.5,1,15.5,10.5);
        logo.Positioning(0,11,4,12);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(4,11.4,.6,A_LINKS);
        TextItemArray[T_HELP_]->VollSichtbar();
        TextItemArray[T_H_KEY_ASSIGNMENTS]->Positioniere(4,11,.6,A_LINKS);
        TextItemArray[T_H_KEY_ASSIGNMENTS]->VollSichtbar();

        TextItemArray[600]->Positioniere(1.25,9.5,.7,A_LINKS);
        TextItemArray[601]->Positioniere(1.5,9.166666,.5,A_LINKS);
        TextItemArray[602]->Positioniere(1.25,8.5,.7,A_LINKS);
        TextItemArray[603]->Positioniere(1.5,8.166666,.5,A_LINKS);
        TextItemArray[604]->Positioniere(1.25,7.5,.7,A_LINKS);
        TextItemArray[605]->Positioniere(1.5,7.166666,.5,A_LINKS);

        TextItemArray[606]->Positioniere(1.25,5.5,.7,A_LINKS);
        TextItemArray[607]->Positioniere(1.5,5.166666,.5,A_LINKS);
        TextItemArray[608]->Positioniere(1.25,4.5,.7,A_LINKS);
        TextItemArray[609]->Positioniere(1.5,4.166666,.5,A_LINKS);
        TextItemArray[610]->Positioniere(1.25,3.5,.7,A_LINKS);
        TextItemArray[611]->Positioniere(1.5,3.166666,.5,A_LINKS);
        TextItemArray[612]->Positioniere(1.25,2.5,.7,A_LINKS);
        TextItemArray[613]->Positioniere(1.5,2.166666,.5,A_LINKS);

        TextItemArray[614]->Positioniere(8.25,5.5,.7,A_LINKS);
        TextItemArray[615]->Positioniere(8.5,5.166666,.5,A_LINKS);
        TextItemArray[616]->Positioniere(8.25,4.5,.7,A_LINKS);
        TextItemArray[617]->Positioniere(8.5,4.166666,.5,A_LINKS);
        TextItemArray[618]->Positioniere(8.25,3.5,.7,A_LINKS);
        TextItemArray[619]->Positioniere(8.5,3.166666,.5,A_LINKS);
        TextItemArray[620]->Positioniere(8.25,2.5,.7,A_LINKS);
        TextItemArray[621]->Positioniere(8.5,2.166666,.5,A_LINKS);

        TextItemArray[T_BACK]->Positioniere(8,.1,1,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_H_ZUHELP_);
    } break;

    case HELP_REGELN1: {
        MenuBackground.Positioning(.5,.7,15.5,11);
        logo.Positioning(0,11,4,12);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(4,11.4,.6,A_LINKS);
        TextItemArray[T_HELP_]->VollSichtbar();
        TextItemArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
        TextItemArray[T_H_BILLARDREGELN]->VollSichtbar();

        TextItemArray[710]->Positioniere(1,10,1,A_LINKS);

        TextItemArray[711]->Positioniere(1.25,9.5,.7,A_LINKS);
        TextItemArray[712]->Positioniere(1.5,9.166666,.5,A_LINKS);
        TextItemArray[713]->Positioniere(1.25,8.5,.7,A_LINKS);
        TextItemArray[714]->Positioniere(1.5,8.166666,.5,A_LINKS);
        TextItemArray[715]->Positioniere(1.25,7.5,.7,A_LINKS);
        TextItemArray[716]->Positioniere(1.5,7.166666,.5,A_LINKS);
        TextItemArray[717]->Positioniere(1.25,6.5,.7,A_LINKS);
        TextItemArray[718]->Positioniere(1.5,6.166666,.5,A_LINKS);
        TextItemArray[719]->Positioniere(1.25,5.5,.7,A_LINKS);
        TextItemArray[720]->Positioniere(1.5,5.166666,.5,A_LINKS);
        TextItemArray[721]->Positioniere(1.25,4.5,.7,A_LINKS);
        TextItemArray[722]->Positioniere(1.5,4.166666,.5,A_LINKS);
        TextItemArray[723]->Positioniere(1.25,3.5,.7,A_LINKS);
        TextItemArray[724]->Positioniere(1.5,3.166666,.5,A_LINKS);
        TextItemArray[725]->Positioniere(1.25,2.5,.7,A_LINKS);
        TextItemArray[726]->Positioniere(1.5,2.166666,.5,A_LINKS);
        TextItemArray[727]->Positioniere(1.25,1.5,.7,A_LINKS);
        TextItemArray[728]->Positioniere(1.5,1.166666,.5,A_LINKS);

        TextItemArray[T_BACK]->Positioniere(8,0,.7,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_H_ZUHELP_);
        TextItemArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
        TextItemArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R1_N);
        //TextfeldArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
        //TextfeldArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R1_L);
    } break;

    case HELP_REGELN2: {
        MenuBackground.Positioning(.5,.7,15.5,11);
        logo.Positioning(0,11,4,12);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(4,11.4,.6,A_LINKS);
        TextItemArray[T_HELP_]->VollSichtbar();
        TextItemArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
        TextItemArray[T_H_BILLARDREGELN]->VollSichtbar();

        GLfloat ypos=10;
        TextItemArray[740]->Positioniere(1,ypos,1,A_LINKS);
        ypos-=.7*TextItemArray[740]->TextboxHeight();
        TextItemArray[741]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[741]->TextboxHeight();
        TextItemArray[742]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[742]->TextboxHeight()+.5;
        TextItemArray[743]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[743]->TextboxHeight();
        TextItemArray[744]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[744]->TextboxHeight()+.5;
        TextItemArray[745]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[745]->TextboxHeight();
        TextItemArray[746]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[746]->TextboxHeight()+.5;

        TextItemArray[T_BACK]->Positioniere(8,0,.7,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_H_ZUHELP_);
        TextItemArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
        TextItemArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R2_N);
        TextItemArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
        TextItemArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R2_L);
    } break;

    case HELP_REGELN3: {
        MenuBackground.Positioning(.5,.7,15.5,11);
        logo.Positioning(0,11,4,12);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(4,11.4,.6,A_LINKS);
        TextItemArray[T_HELP_]->VollSichtbar();
        TextItemArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
        TextItemArray[T_H_BILLARDREGELN]->VollSichtbar();

        GLfloat ypos=10;
        TextItemArray[747]->Positioniere(1,ypos,1,A_LINKS);
        ypos-=.7*TextItemArray[747]->TextboxHeight();
        TextItemArray[748]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[748]->TextboxHeight();
        TextItemArray[749]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[749]->TextboxHeight()+.5;
        TextItemArray[750]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[750]->TextboxHeight();
        TextItemArray[751]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[751]->TextboxHeight()+.2;
        TextItemArray[752]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[752]->TextboxHeight()+.2;
        TextItemArray[753]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[753]->TextboxHeight()+.2;
        TextItemArray[754]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[754]->TextboxHeight()+.5;

        TextItemArray[T_BACK]->Positioniere(8,0,.7,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_H_ZUHELP_);
        TextItemArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
        TextItemArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R3_N);
        TextItemArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
        TextItemArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R3_L);
    } break;

    case HELP_REGELN4: {
        MenuBackground.Positioning(.5,.7,15.5,11);
        logo.Positioning(0,11,4,12);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(4,11.4,.6,A_LINKS);
        TextItemArray[T_HELP_]->VollSichtbar();
        TextItemArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
        TextItemArray[T_H_BILLARDREGELN]->VollSichtbar();

        GLfloat ypos=10;
        TextItemArray[747]->Positioniere(1,ypos,1,A_LINKS);
        ypos-=.7*TextItemArray[747]->TextboxHeight();
        TextItemArray[755]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[755]->TextboxHeight();
        TextItemArray[756]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[756]->TextboxHeight()+.5;
        TextItemArray[757]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[757]->TextboxHeight();
        TextItemArray[758]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[758]->TextboxHeight()+.5;
        TextItemArray[759]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[759]->TextboxHeight();
        TextItemArray[760]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[760]->TextboxHeight()+.5;
        TextItemArray[761]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[761]->TextboxHeight();
        TextItemArray[762]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[762]->TextboxHeight()+.5;

        TextItemArray[T_BACK]->Positioniere(8,0,.7,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_H_ZUHELP_);
        TextItemArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
        TextItemArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R4_N);
        TextItemArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
        TextItemArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R4_L);
    } break;

    case HELP_REGELN5: {
        MenuBackground.Positioning(.5,.7,15.5,11);
        logo.Positioning(0,11,4,12);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(4,11.4,.6,A_LINKS);
        TextItemArray[T_HELP_]->VollSichtbar();
        TextItemArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
        TextItemArray[T_H_BILLARDREGELN]->VollSichtbar();

        GLfloat ypos=10;
        TextItemArray[770]->Positioniere(1,ypos,1,A_LINKS);
        ypos-=.7*TextItemArray[770]->TextboxHeight();
        TextItemArray[771]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[771]->TextboxHeight();
        TextItemArray[772]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[772]->TextboxHeight()+.5;
        TextItemArray[773]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[773]->TextboxHeight();
        TextItemArray[774]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[774]->TextboxHeight()+.2;
        TextItemArray[775]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[775]->TextboxHeight();


        TextItemArray[T_BACK]->Positioniere(8,0,.7,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_H_ZUHELP_);
        TextItemArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
        TextItemArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R5_N);
        TextItemArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
        TextItemArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R5_L);
    } break;

    case HELP_REGELN6: {
        MenuBackground.Positioning(.5,.7,15.5,11);
        logo.Positioning(0,11,4,12);
        logo.FullyVisible();
        TextItemArray[T_HELP_]->Positioniere(4,11.4,.6,A_LINKS);
        TextItemArray[T_HELP_]->VollSichtbar();
        TextItemArray[T_H_BILLARDREGELN]->Positioniere(4,11,.6,A_LINKS);
        TextItemArray[T_H_BILLARDREGELN]->VollSichtbar();

        GLfloat ypos=10;
        TextItemArray[770]->Positioniere(1,ypos,1,A_LINKS);
        ypos-=.7*TextItemArray[770]->TextboxHeight();
        TextItemArray[776]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[776]->TextboxHeight();
        TextItemArray[777]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[777]->TextboxHeight()+.5;
        TextItemArray[778]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[778]->TextboxHeight();
        TextItemArray[779]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[779]->TextboxHeight()+.5;
        TextItemArray[780]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[780]->TextboxHeight();
        TextItemArray[781]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[781]->TextboxHeight()+.5;
        TextItemArray[782]->Positioniere(1.25,ypos,.7,A_LINKS);
        ypos-=.5*TextItemArray[782]->TextboxHeight();
        TextItemArray[783]->Positioniere(1.5,ypos,.5,A_LINKS);
        ypos-=.5*TextItemArray[783]->TextboxHeight()+.5;

        TextItemArray[T_BACK]->Positioniere(8,0,.7,A_MITTE);
        TextItemArray[T_BACK]->SetzeSignal(S_H_ZUHELP_);
        //TextfeldArray[T_H_NAECHSTESEITE]->Positioniere(15.8,0,.7,A_RECHTS);
        //TextfeldArray[T_H_NAECHSTESEITE]->SetzeSignal(S_H_R5_N);
        TextItemArray[T_H_LETZTESEITE]->Positioniere(.2,0,.7,A_LINKS);
        TextItemArray[T_H_LETZTESEITE]->SetzeSignal(S_H_R6_L);
    } break;

    case EXIT: {
        MenuBackground.Positioning(4.5,4.5,11.5,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_EXIT]->Positioniere(8,8,1,A_MITTE);
        TextItemArray[T_EXIT]->VollSichtbar();
        TextItemArray[T_JAEXIT]->Positioniere(8,6,1,A_MITTE);
        TextItemArray[T_JAEXIT]->SetzeSignal(S_BE_JAEXIT);
        TextItemArray[T_BACK]->Positioniere(8,1,1,A_MITTE);
        if (AusSpiel) {
            TextItemArray[T_BACK]->SetzeSignal(S_BE_BACK_AS);
        } else {
            TextItemArray[T_BACK]->SetzeSignal(S_BE_BACK);
        }

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

    } break;

    case OFF_GAME: {
        MenuBackground.Positioning(3.5,0.5,12.5,8.5);
        logo.Positioning(4,9,12,11);
        logo.FullyVisible();
        TextItemArray[T_WEITERSPIELEN]->Positioniere(8,7,1,A_MITTE);
        TextItemArray[T_WEITERSPIELEN]->SetzeSignal(S_AS_WEITERSPIELEN);
        TextItemArray[T_HELP_]->Positioniere(8,5.5,1,A_MITTE);
        TextItemArray[T_HELP_]->SetzeSignal(S_AS_HELP);
        TextItemArray[T_TABLE_VERLASSEN]->Positioniere(8,4,1,A_MITTE);
        TextItemArray[T_TABLE_VERLASSEN]->SetzeSignal(S_AS_MAIN_MENU);
        TextItemArray[T_SETUP_]->Positioniere(8,2.5,1,A_MITTE);
        TextItemArray[T_SETUP_]->SetzeSignal(S_AS_SETUP);
        TextItemArray[T_EXIT]->Positioniere(8,1,1,A_MITTE);
        TextItemArray[T_EXIT]->SetzeSignal(S_AS_EXIT);

        TextItemArray[T_HOMEPAGE]->Positioniere(15.9,0,.5,A_RECHTS);
        TextItemArray[T_VERSION]->Positioniere(.1,0,.5,A_LINKS);

    } break;

    case PLAYING: {
        //    menuhintergrund.Positioniere(0,11,16,12);

        if (GameMode==TRAINING_MODE) {
            logo.Positioning(0,11,4,12);
        } else if (GameMode==TUTORIAL) {
            logo.Positioning(12,0,16,1);
        } else {
            logo.Positioning(6,11,10,12);
        }
        logo.SetSignal(S_SP_LOGO);

        switch (GameMode) {
        case TUTORIAL: {
            GLfloat posy=11.5;
            GLint Bereich=0;
            //TextfeldArray[T_H_TUTORIAL]->Positioniere(15.75,0,1,A_RECHTS);//
            switch (StateMachine) {
            case VIEWING: {
                if (AllerersterStoss)
                    Bereich=640;
                else
                    Bereich=690;
            } break;
            case AIMING: {
                Bereich=650;
            } break;
            case AUSHOLEN: {
                Bereich=660;
            } break;
            case SHOCK: {
                Bereich=670;
            } break;
            case NEW_WHITE: {
                Bereich=680;
            } break;
            }
            for (GLint i=Bereich;i<Bereich+10;i++) {
                if (TextItemArray[i]) {
                    TextItemArray[i]->Positioniere(0.2,posy,.5,A_LINKS);
                    TextItemArray[i]->VollSichtbar();
                    posy-=.5*TextItemArray[i]->TextboxHeight()+.2;
                }
            }
            MenuBackground.Positioning(0,posy+.5,16,12);
        } break;

        case TRAINING_MODE: {
            TextItemArray[T_TRAINING]->Positioniere(15.75,0,1,A_RECHTS);//
            TextItemArray[T_NEWEIGHT_BALLAUFSTELLUNG]->Positioniere(15.75,11.5,.5,A_RECHTS);
            TextItemArray[T_NEWEIGHT_BALLAUFSTELLUNG]->SetzeSignal(S_SP_NEWEIGHT_BALLAUFSTELLUNG);
            TextItemArray[T_NEWNINE_BALLAUFSTELLUNG]->Positioniere(15.75,11.2,.5,A_RECHTS);
            TextItemArray[T_NEWNINE_BALLAUFSTELLUNG]->SetzeSignal(S_SP_NEWNINE_BALLAUFSTELLUNG);
        } break;
        case TWO_PLAYERS: {
            TextItemArray[T_TWO_PLAYERS]->Positioniere(15.75,0,1,A_RECHTS);//12,11,16,12);
            if (Judge.FrageNachSpielerAmStoss()==0) {
                TextItemArray[T_SPIELER1NAME]->Positioniere(0.2,11,1,A_LINKS);
                TextItemArray[T_SPIELER2NAME]->Positioniere(15.9,11.5,.5,A_RECHTS);
                if (GameType==EIGHT_BALL) {
                    if (Judge.FrageNachGruppenVerteilung()==1) {
                        volle.Positioning(0.2,10,1.2,11);
                        halbe.Positioning(15.4,11,15.9,11.5);
                    }
                    if (Judge.FrageNachGruppenVerteilung()==2) {
                        halbe.Positioning(0.2,10,1.2,11);
                        volle.Positioning(15.4,11,15.9,11.5);
                    }
                }
                if (GameType==NINE_BALL) {
                    if (Judge.FrageNachFouls(0)==1) {
                        TextItemArray[T_ZUSATZTEXTLINKS]->SetText("1 Foul");
                        TextItemArray[T_ZUSATZTEXTLINKS]->Positioniere(.2,10,1,A_LINKS);
                    }
                    if (Judge.FrageNachFouls(0)==2) {
                        TextItemArray[T_ZUSATZTEXTLINKS]->SetText("2 Fouls");
                        TextItemArray[T_ZUSATZTEXTLINKS]->Positioniere(.2,10,1,A_LINKS);
                    }
                    if (Judge.FrageNachFouls(0)==3) {
                        TextItemArray[T_ZUSATZTEXTLINKS]->SetText("3 Fouls");
                        TextItemArray[T_ZUSATZTEXTLINKS]->Positioniere(.2,10,1,A_LINKS);
                    }
                    if (Judge.FrageNachFouls(1)==1) {
                        TextItemArray[T_ZUSATZTEXTRECHTS]->SetText("1 Foul");
                        TextItemArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.9,11,.5,A_RECHTS);
                    }
                    if (Judge.FrageNachFouls(1)==2) {
                        TextItemArray[T_ZUSATZTEXTRECHTS]->SetText("2 Fouls");
                        TextItemArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.9,11,.5,A_RECHTS);
                    }
                    if (Judge.FrageNachFouls(1)==3) {
                        TextItemArray[T_ZUSATZTEXTRECHTS]->SetText("3 Fouls");
                        TextItemArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.9,11,.5,A_RECHTS);
                    }
                }
            } else {
                TextItemArray[T_SPIELER1NAME]->Positioniere(0.1,11.5,.5,A_LINKS);
                TextItemArray[T_SPIELER2NAME]->Positioniere(15.8,11,1,A_RECHTS);
                if (GameType==EIGHT_BALL) {
                    if (Judge.FrageNachGruppenVerteilung()==1) {
                        volle.Positioning(0.1,11,.5,11.5);
                        halbe.Positioning(14.8,10,15.8,11);
                    }
                    if (Judge.FrageNachGruppenVerteilung()==2) {
                        halbe.Positioning(0.1,11,.5,11.5);
                        volle.Positioning(14.8,10,15.8,11);
                    }
                }
                if (GameType==NINE_BALL) {
                    if (Judge.FrageNachFouls(0)==1) {
                        TextItemArray[T_ZUSATZTEXTLINKS]->SetText("1 Foul");
                        TextItemArray[T_ZUSATZTEXTLINKS]->Positioniere(.1,11,.5,A_LINKS);
                    }
                    if (Judge.FrageNachFouls(0)==2) {
                        TextItemArray[T_ZUSATZTEXTLINKS]->SetText("2 Fouls");
                        TextItemArray[T_ZUSATZTEXTLINKS]->Positioniere(.1,11,.5,A_LINKS);
                    }
                    if (Judge.FrageNachFouls(0)==3) {
                        TextItemArray[T_ZUSATZTEXTLINKS]->SetText("3 Fouls");
                        TextItemArray[T_ZUSATZTEXTLINKS]->Positioniere(.1,11,.5,A_LINKS);
                    }
                    if (Judge.FrageNachFouls(1)==1) {
                        TextItemArray[T_ZUSATZTEXTRECHTS]->SetText("1 Foul");
                        TextItemArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.8,10,1,A_RECHTS);
                    }
                    if (Judge.FrageNachFouls(1)==2) {
                        TextItemArray[T_ZUSATZTEXTRECHTS]->SetText("2 Fouls");
                        TextItemArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.8,10,1,A_RECHTS);
                    }
                    if (Judge.FrageNachFouls(1)==3) {
                        TextItemArray[T_ZUSATZTEXTRECHTS]->SetText("3 Fouls");
                        TextItemArray[T_ZUSATZTEXTRECHTS]->Positioniere(15.8,10,1,A_RECHTS);
                    }
                }
            }
        } break;

            /*
                                                      case NETWORK_PLAYER: {
                                                      netzwerkspiel.Positioniere(12,0,16,1);//12,11,16,12);
                                                      if (Schiedsrichter.FrageNachSpielerAmStoss()==0) {
                                                      spieler1.Positioniere(0,11,4,12);
                                                      spieler2.Positioniere(14,11.25,16,11.75);
                                                      } else {
                                                      spieler1.Positioniere(0,11.25,2,11.75);
                                                      spieler2.Positioniere(12,11,16,12);
                                                      }
                                                      } break;
                                                      */
        }


        switch (StateMachine) {
        case VIEWING: {
            TextItemArray[T_VIEWING]->Positioniere(0.25,0,1,A_LINKS);
        } break;
        case AIMING: {
            TextItemArray[T_ZIELEN]->Positioniere(0.25,0,1,A_LINKS);
        } break;
        case AUSHOLEN: {
            TextItemArray[T_AUSHOLEN]->Positioniere(0.25,0,1,A_LINKS);
        } break;
        case SHOCK: {
            TextItemArray[T_STOSS]->Positioniere(0.25,0,1,A_LINKS);
        } break;
        case NEW_WHITE: {
            TextItemArray[T_WEISSENEUSETZEN]->Positioniere(0.25,0,1,A_LINKS);
        } break;
        case JUDGEING: {
            TextItemArray[T_STOSS]->Positioniere(0.25,0,1,A_LINKS);
            if (Foul) {
                TextItemArray[T_FOUL]->Positioniere(8,9,1.5,A_MITTE);
                if (Judge.FrageNachBegruendung())
                    TextItemArray[Judge.FrageNachBegruendung()]->Positioniere(8,8.5,.75,A_MITTE);
            }
            if (!Player1Win && !Player2Win) {
                TextItemArray[T_ISTAMTISCH]->Positioniere(8,5,1,A_MITTE);
                if (Judge.FrageNachSpielerAmStoss()==0) {
                    TextItemArray[T_SPIELER1NAME]->Positioniere(8,6,1.5,A_MITTE);
                    TextItemArray[T_SPIELER1NAME]->VollSichtbar();
                } else {
                    TextItemArray[T_SPIELER2NAME]->Positioniere(8,6,1.5,A_MITTE);
                    TextItemArray[T_SPIELER2NAME]->VollSichtbar();
                }
                if (!NeuAufbauenOderWeiterspielen &&
                        !NeuAufbauenOderAchtEinsetzen) {
                    if (LageVerbesserungKopffeld) {
                        TextItemArray[T_IMKOPFFELD]->Positioniere(8,3,1,A_MITTE);
                    }
                    if (LageVerbesserung|LageVerbesserungKopffeld) {
                        TextItemArray[T_UNDHATLAGEVERBESSERUNG]->Positioniere(8,4,1,A_MITTE);
                    }
                } else if (NeuAufbauenOderAchtEinsetzen) {
                    MenuGesperrt=1;
                    if (Foul) {
                        TextItemArray[T_FOUL]->Positioniere(8,9,1.5,A_MITTE);
                        if (Judge.FrageNachBegruendung())
                            TextItemArray[Judge.FrageNachBegruendung()]->Positioniere(8,8.5,.75,A_MITTE);
                    }
                    TextItemArray[T_ISTAMTISCH]->Positioniere(8,6,1,A_MITTE);
                    if (Judge.FrageNachSpielerAmStoss()==0) {
                        TextItemArray[T_SPIELER1NAME]->Positioniere(8,7,1.5,A_MITTE);
                        TextItemArray[T_SPIELER1NAME]->VollSichtbar();
                    } else {
                        TextItemArray[T_SPIELER2NAME]->Positioniere(8,7,1.5,A_MITTE);
                        TextItemArray[T_SPIELER2NAME]->VollSichtbar();
                    }
                    TextItemArray[T_WOLLENSIE]->Positioniere(8,4,1,A_MITTE);
                    TextItemArray[T_NEUAUFBAUEN]->Positioniere(5.5,2.5,1,A_MITTE);
                    TextItemArray[T_NEUAUFBAUEN]->SetzeSignal(S_SP_NEUAUFBAUEN);
                    TextItemArray[T_DIEACHTEINSETZEN]->Positioniere(10.5,2.5,1,A_MITTE);
                    TextItemArray[T_DIEACHTEINSETZEN]->SetzeSignal(S_SP_ACHTEINSETZEN);
                } else if (NeuAufbauenOderWeiterspielen) {
                    MenuGesperrt=1;
                    if (Foul) {
                        TextItemArray[T_FOUL]->Positioniere(8,9,1.5,A_MITTE);
                        if (Judge.FrageNachBegruendung())
                            TextItemArray[Judge.FrageNachBegruendung()]->Positioniere(8,8.5,.75,A_MITTE);
                    }
                    TextItemArray[T_ISTAMTISCH]->Positioniere(8,6,1,A_MITTE);
                    if (Judge.FrageNachSpielerAmStoss()==0) {
                        TextItemArray[T_SPIELER1NAME]->Positioniere(8,7,1.5,A_MITTE);
                        TextItemArray[T_SPIELER1NAME]->VollSichtbar();
                    } else {
                        TextItemArray[T_SPIELER2NAME]->Positioniere(8,7,1.5,A_MITTE);
                        TextItemArray[T_SPIELER2NAME]->VollSichtbar();
                    }
                    TextItemArray[T_WOLLENSIE]->Positioniere(8,4,1,A_MITTE);
                    TextItemArray[T_NEUAUFBAUEN]->Positioniere(5.5,2.5,1,A_MITTE);
                    TextItemArray[T_NEUAUFBAUEN]->SetzeSignal(S_SP_NEUAUFBAUEN);
                    TextItemArray[T_WEITERSPIELEN]->Positioniere(10.5,2.5,1,A_MITTE);
                    TextItemArray[T_WEITERSPIELEN]->SetzeSignal(S_SP_WEITERSPIELEN);
                }
            }
            if (Player1Win||Player2Win) {
                MenuGesperrt=1;
                TextItemArray[T_HATGEWONNEN]->Positioniere(8,5,1,A_MITTE);

                TextItemArray[T_NEW_GAME]->Positioniere(5.5,3,1,A_MITTE);
                TextItemArray[T_NEW_GAME]->SetzeSignal(S_SP_NEW_GAME);
                TextItemArray[T_TABLE_VERLASSEN]->Positioniere(10.5,3,1,A_MITTE);
                TextItemArray[T_TABLE_VERLASSEN]->SetzeSignal(S_SP_MAIN_MENU);

                if (Player1Win) {
                    TextItemArray[T_SPIELER1NAME]->Positioniere(8,6,1.5,A_MITTE);
                    TextItemArray[T_SPIELER1NAME]->VollSichtbar();
                }
                if (Player2Win) {
                    TextItemArray[T_SPIELER2NAME]->Positioniere(8,6,1.5,A_MITTE);
                    TextItemArray[T_SPIELER2NAME]->VollSichtbar();
                }
            }
        } break;
        }

        GLint i;
        if (GameType==EIGHT_BALL) {
            for (i=0;i<8;i++) {
                if (!BallsSunk[i]&&BallsInGame[i]) {
                    ball[i].Positioning(6+.5*i,.5,6+.5*(i+1),1);
                    ball[i].SetSignal(S_SP_BALL+i);
                }
            }
            for (i=8;i<16;i++) {
                if (!BallsSunk[i]&&BallsInGame[i]) {
                    ball[i].Positioning(6+.5*(i-8),0,6+.5*(i-7),.5);
                    ball[i].SetSignal(S_SP_BALL+i);
                }
            }
        } else {
            for (i=0;i<5;i++) {
                if (!BallsSunk[i]&&BallsInGame[i]) {
                    ball[i].Positioning(6.75+.5*i,.5,6.75+.5*(i+1),1);
                    ball[i].SetSignal(S_SP_BALL+i);
                }
            }
            for (i=5;i<10;i++) {
                if (!BallsSunk[i]&&BallsInGame[i]) {
                    ball[i].Positioning(6.75+.5*(i-5),0,6.75+.5*(i-4),.5);
                    ball[i].SetSignal(S_SP_BALL+i);
                }
            }
        }
    } break;

    }
    StarteAnimation();
}

void Menu::SignalExecution(GLint Signal) {
    DelayCompensation=1;
    switch (Signal) {
    case S_LOGO: {
        setMenuState(HOME_SCREEN);
    } break;
    case S_MAINMENU_TRAINING: {
        setMenuState(TRAINING);
    } break;
    case S_MAINMENU_TWO_PLAYERS: {
        setMenuState(TWO_PLAYERS);
    } break;
    case S_MAINMENU_NETWORK_PLAYER: {
        setMenuState(NETWORK_MAIN);
    } break;
    case S_MAINMENU_SETUP_: {
        AusSpiel=0;
        setMenuState(SETUP);
    } break;
    case S_MAINMENU_HELP: {
        AusSpiel=0;
        setMenuState(HELP);
    } break;
    case S_MAINMENU_EXIT: {
        AusSpiel=0;
        setMenuState(EXIT);
    } break;
    case S_TR_EIGHT_BALL: {
        Foul=0;
        LageVerbesserungKopffeld=1;
        LageVerbesserung=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        Player1Win=0;
        Player2Win=0;
        MenuGesperrt=0;
        GameMode=TRAINING_MODE;
        StateMachine=NEW_WHITE;
        GameType=EIGHT_BALL;
        BoardLayout();
        Judge.NewGame(GameType);
        JudgeDecision=0;
        Camera.loadPosition(4);
        setMenuState(PLAYING);
    } break;
    case S_TR_NINE_BALL: {
        Foul=0;
        LageVerbesserungKopffeld=1;
        LageVerbesserung=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        Player1Win=0;
        Player2Win=0;
        MenuGesperrt=0;
        GameMode=TRAINING_MODE;
        StateMachine=NEW_WHITE;
        GameType=NINE_BALL;
        BoardLayout();
        Judge.NewGame(GameType);
        JudgeDecision=0;
        Camera.loadPosition(4);
        setMenuState(PLAYING);
    } break;
    case S_TR_VIERZEHNPLUSEINS: {
    } break;
    case S_TR_BACK: {
        setMenuState(MAIN_MENU);
    } break;
    case S_ZW_EIGHT_BALL: {
        sprintf(Player1,"%s",TextItemArray[T_SPIELER1NAME]->Text());
        sprintf(Player2,"%s",TextItemArray[T_SPIELER2NAME]->Text());
        WriteConfig();
        Foul=0;
        LageVerbesserungKopffeld=1;
        LageVerbesserung=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        Player1Win=0;
        Player2Win=0;
        MenuGesperrt=0;
        GameMode=TWO_PLAYERS;
        StateMachine=JUDGEING;
        GameType=EIGHT_BALL;
        BoardLayout();
        Judge.NewGame(GameType);
        JudgeDecision=0;
        Camera.loadPosition(4);
        setMenuState(PLAYING);
    } break;
    case S_ZW_NINE_BALL: {
        sprintf(Player1,"%s",TextItemArray[T_SPIELER1NAME]->Text());
        sprintf(Player2,"%s",TextItemArray[T_SPIELER2NAME]->Text());
        WriteConfig();
        Foul=0;
        LageVerbesserungKopffeld=1;
        LageVerbesserung=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        Player1Win=0;
        Player2Win=0;
        MenuGesperrt=0;
        GameMode=TWO_PLAYERS;
        StateMachine=JUDGEING;
        GameType=NINE_BALL;
        BoardLayout();
        Judge.NewGame(GameType);
        JudgeDecision=0;
        Camera.loadPosition(4);
        setMenuState(PLAYING);
    } break;
    case S_ZW_VIERZEHNPLUSEINS: {
    } break;
    case S_ZW_BACK: {
        setMenuState(MAIN_MENU);
    } break;
    case S_NE_BEGIN: {
        setMenuState(NETWORK_NEW);
    } break;
    case S_NE_TEILNEHMEN: {
        setMenuState(NETWORK_JOIN);
    } break;
    case S_NE_BACK: {
        setMenuState(MAIN_MENU);
    } break;
    case S_NB_EIGHT_BALL: {
    } break;
    case S_NB_NINE_BALL: {
    } break;
    case S_NB_VIERZEHNPLUSEINS: {
    } break;
    case S_NB_BACK: {
    } break;
    case S_NT_IPADRESSE: {
    } break;
    case S_NT_CONNECT: {
    } break;
    case S_NT_BACK: {
    } break;
    case S_SETUP_CONTROL: {
        E_MouseSpeed=MouseSpeed;
        E_InvertX=InvertX;
        E_InvertY=InvertY;
        setMenuState(SETUP_CONTROL);
    } break;
    case S_SETUP_LANGUAGE: {
        setMenuState(LANGUAGE);
    } break;
    case S_SETUP_VIDEO: {
        E_BallTextureSize=TextureSize;
        E_AnzeigeTexturgroesse=DisplayTextureSize;
        E_TableTextureSize=TableTextureSize;
        E_KugelAufloesung=BallResolution;
        E_ScreenResolution=ScreenResolution;
        E_ColorDepth=ColorDepth;
        E_Reflection=Reflections;
        E_Shadows=Shadow;
        E_AmbientLighting=AmbientLighting;
        E_TableLampes=TableLamps;
        E_GreenLampe=GreenLamp;
        E_ShowFPS=ShowFPS;
        E_TexMMM=TexMMM;
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_BALLTEXTURES: {
        switch (E_BallTextureSize) {
        case 1: E_BallTextureSize=2; break;
        case 2: E_BallTextureSize=4; break;
        case 4: E_BallTextureSize=8; break;
        case 8: E_BallTextureSize=1; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_TABLE_TEXTURES: {
        switch (E_TableTextureSize) {
        case 1: E_TableTextureSize=2; break;
        case 2: E_TableTextureSize=4; break;
        case 4: E_TableTextureSize=8; break;
        case 8: E_TableTextureSize=0; break;
        case 0: E_TableTextureSize=1; break;
        default: E_TableTextureSize=4; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_ANZEIGETEXTURES: {
        switch (E_AnzeigeTexturgroesse) {
        case 1: E_AnzeigeTexturgroesse=2; break;
        case 2: E_AnzeigeTexturgroesse=1; break;
        default: E_AnzeigeTexturgroesse=1; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_RESOLUTION: {
        switch (E_ScreenResolution) {
        case 640: E_ScreenResolution=1600; break;
        case 800: E_ScreenResolution=640; break;
        case 1024: E_ScreenResolution=800; break;
        case 1280: E_ScreenResolution=1024; break;
        case 1600: E_ScreenResolution=1280; break;
        default: E_ScreenResolution=800; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_COLOR_DEPTH: {
        switch (E_ColorDepth) {
        case 16: E_ColorDepth=32; break;
        default: E_ColorDepth=16; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_REFLEKTIONEN: {
        switch (E_Reflection) {
        case 0: E_Reflection=1; break;
        default:  E_Reflection=0; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_SHADOWS: {
        switch (E_Shadows) {
        case 0: E_Shadows=1; break;
        default:  E_Shadows=0; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_TEXTURINTERPOLATION: {
        switch (E_TexMMM) {
        case 0: E_TexMMM=7; break;
        case 2: E_TexMMM=0; break;
        case 3: E_TexMMM=2; break;
        default:  E_TexMMM=3; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_AMBIENCE_LIGHTING: {
        switch (E_AmbientLighting) {
        case 1: E_AmbientLighting=0; break;
        default:  E_AmbientLighting=1; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_TABLE_LAMPEN: {
        switch (E_TableLampes) {
        case 1: E_TableLampes=2; break;
        case 2: E_TableLampes=3; break;
        case 3: E_TableLampes=1; break;
        default:  E_TableLampes=1; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_GRUENELAMPE: {
        switch (E_GreenLampe) {
        case 1: E_GreenLampe=0; break;
        default:  E_GreenLampe=1; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_FPS: {
        switch (E_ShowFPS) {
        case 1: ShowFPS=E_ShowFPS=0; break;
        default: ShowFPS=E_ShowFPS=1; break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_BALLGEOMETRIE: {
        switch (E_KugelAufloesung) {
        case 1: {
            E_KugelAufloesung=7;
        } break;
        case 2: {
            E_KugelAufloesung=7;
        } break;
        case 3: {
            E_KugelAufloesung=11;
        } break;
        case 5: {
            E_KugelAufloesung=3;
        } break;
        case 7: {
            E_KugelAufloesung=5;
        } break;
        case 9: {
            E_KugelAufloesung=7;
        } break;
        case 11: {
            E_KugelAufloesung=7;
        } break;
        default: {
            E_KugelAufloesung=7;
        } break;
        }
        setMenuState(SETUP_VIDEO);
    } break;
    case S_SETUP_MOUSESPEED: {
        if (E_MouseSpeed<=.21) {
            E_MouseSpeed=.8;
        } else if (E_MouseSpeed<=.29) {
            E_MouseSpeed=.8;
        } else if (E_MouseSpeed<=.41) {
            E_MouseSpeed=.28;
        } else if (E_MouseSpeed<=.575) {
            E_MouseSpeed=.4;
        } else {
            E_MouseSpeed=.565;
        }
        setMenuState(SETUP_CONTROL);
    } break;
    case S_SETUP_XINVERT: {
        if (E_InvertX) {
            E_InvertX=0;
        } else {
            E_InvertX=1;
        }
        setMenuState(SETUP_CONTROL);
    } break;
    case S_SETUP_YINVERT: {
        if (E_InvertY) {
            E_InvertY=0;
        } else {
            E_InvertY=1;
        }
        setMenuState(SETUP_CONTROL);
    } break;


    case S_SETUP_QUALITAET: {
        switch(Quality) {
        case 1: {
            E_KugelAufloesung=11;
            E_BallTextureSize=1;
            E_TableTextureSize=1;
            E_AnzeigeTexturgroesse=1;
            E_Reflection=1;
            E_ScreenResolution=1024;
            E_ColorDepth=32;
            E_Shadows=1;
            E_TableLampes=3;
            E_GreenLampe=1;
            E_TexMMM=7;
        } break;
        case 2: {
            E_KugelAufloesung=3;
            E_BallTextureSize=8;
            E_TableTextureSize=0;
            E_AnzeigeTexturgroesse=2;
            E_Reflection=0;
            E_ScreenResolution=640;
            E_ColorDepth=16;
            E_Shadows=0;
            E_TableLampes=1;
            E_GreenLampe=0;
            E_TexMMM=0;
        } break;
        case 3: {
            E_KugelAufloesung=5;
            E_BallTextureSize=4;
            E_TableTextureSize=4;
            E_AnzeigeTexturgroesse=2;
            E_Reflection=0;
            E_ScreenResolution=640;
            E_ColorDepth=16;
            E_Shadows=1;
            E_TableLampes=1;
            E_GreenLampe=0;
            E_TexMMM=2;
        } break;
        case 4: {
            E_KugelAufloesung=7;
            E_BallTextureSize=2;
            E_TableTextureSize=2;
            E_AnzeigeTexturgroesse=1;
            E_Reflection=0;
            E_ScreenResolution=800;
            E_ColorDepth=16;
            E_Shadows=1;
            E_TableLampes=2;
            E_GreenLampe=0;
            E_TexMMM=3;
        } break;
        case 5: {
            E_KugelAufloesung=7;
            E_BallTextureSize=2;
            E_TableTextureSize=1;
            E_AnzeigeTexturgroesse=1;
            E_Reflection=1;
            E_ScreenResolution=1024;
            E_ColorDepth=16;
            E_Shadows=1;
            E_TableLampes=2;
            E_GreenLampe=1;
            E_TexMMM=7;
        } break;
        default: {
            E_KugelAufloesung=7;
            E_BallTextureSize=2;
            E_TableTextureSize=2;
            E_AnzeigeTexturgroesse=1;
            E_Reflection=0;
            E_ScreenResolution=800;
            E_ColorDepth=16;
            E_Shadows=1;
            E_TableLampes=2;
            E_GreenLampe=0;
            E_TexMMM=3;
        } break;
        }
        setMenuState(SETUP_VIDEO);
    } break;

    case S_SETUP_VIDEOUEBERNEHMEN: {

        GLint TexMMMgeaendert=0;

        if (TexMMM!=E_TexMMM) {
            TexMMMgeaendert=1;
            TexMMM=E_TexMMM;
        }

        if (TextureSize!=E_BallTextureSize ||
                BallResolution!=E_KugelAufloesung ||
                TexMMMgeaendert ||
                Shadow!=E_Shadows) {

            initializeBallTables(E_KugelAufloesung);

            for (GLint j=0;j<16;j++) {  // Initialisierung der Baelle + Laden der Texturen
                Ball[j].Init(j,E_BallTextureSize,E_KugelAufloesung,E_Shadows);
            }
        }

        if (TableTextureSize!=E_TableTextureSize ||
                TexMMMgeaendert){
            Table.Init(E_TableTextureSize);
        }

        if (Reflections!=E_Reflection ||
                AmbientLighting!=E_AmbientLighting ||
                TableLamps!=E_TableLampes ||
                GreenLamp!=E_GreenLampe) {
            Lighting.Init(E_AmbientLighting,E_TableLampes,E_GreenLampe,E_Reflection);
        }

        if (DisplayTextureSize!=E_AnzeigeTexturgroesse||
                TexMMMgeaendert){
            Init(E_AnzeigeTexturgroesse);
        }

        GLint NeueAufloesung=0;
        if (ColorDepth!=E_ColorDepth || ScreenResolution!=E_ScreenResolution)
            NeueAufloesung=1;

        BallResolution=E_KugelAufloesung;
        TextureSize=E_BallTextureSize;
        DisplayTextureSize=E_AnzeigeTexturgroesse;
        TableTextureSize=E_TableTextureSize;
        Reflections=E_Reflection;
        ScreenResolution=E_ScreenResolution;
        ColorDepth=E_ColorDepth;
        Shadow=E_Shadows;
        TableTextureSize=E_TableTextureSize;
        AmbientLighting=E_AmbientLighting;
        TableLamps=E_TableLampes;
        GreenLamp=E_GreenLampe;
        ShowFPS=E_ShowFPS;

        WriteConfig();

        if (NeueAufloesung)
            setMenuState(SETUP_VIDEO_NOTICE);
        else
            setMenuState(SETUP_VIDEO);

    } break;
    case S_SETUP_VIDEOBACK: {
        setMenuState(SETUP);
    } break;
    case S_SETUP_CONTROLUEBERNEHMEN: {
        InvertX=E_InvertX;
        InvertY=E_InvertY;
        MouseSpeed=E_MouseSpeed;
        WriteConfig();
        setMenuState(SETUP);
    } break;
    case S_SETUP_CONTROLBACK: {
        setMenuState(SETUP);
    } break;
    case S_SETUP_BACK: {
        setMenuState(MAIN_MENU);
    } break;
    case S_SETUP_BACK_AS: {
        setMenuState(OFF_GAME);
    } break;
    case S_BE_JAEXIT: {
        exit(0);
    } break;
    case S_BE_BACK: {
        setMenuState(MAIN_MENU);
    } break;
    case S_BE_BACK_AS: {
        setMenuState(OFF_GAME);
    } break;
    case S_AS_WEITERSPIELEN: {
        setMenuState(PLAYING);
    } break;
    case S_AS_MAIN_MENU: {
        AusSpiel=0;
        StateMachine=START;
        setMenuState(MAIN_MENU);
    } break;
    case S_AS_HELP: {
        AusSpiel=1;
        setMenuState(HELP);
    } break;
    case S_AS_SETUP: {
        AusSpiel=1;
        setMenuState(SETUP);
    } break;
    case S_AS_EXIT: {
        AusSpiel=1;
        setMenuState(EXIT);
    } break;
    case S_SP_LOGO: {
        AusSpiel=1;
        setMenuState(OFF_GAME);
    } break;
    case S_SP_BALL+0: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(0);
        }
    } break;
    case S_SP_BALL+1: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[1].Pos_xCM(),Ball[1].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(1);
        }
    } break;
    case S_SP_BALL+2: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[2].Pos_xCM(),Ball[2].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(2);
        }
    } break;
    case S_SP_BALL+3: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[3].Pos_xCM(),Ball[3].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(3);
        }
    } break;
    case S_SP_BALL+4: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[4].Pos_xCM(),Ball[4].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(4);
        }
    } break;
    case S_SP_BALL+5: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[5].Pos_xCM(),Ball[5].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(5);
        }
    } break;
    case S_SP_BALL+6: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[6].Pos_xCM(),Ball[6].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(6);
        }
    } break;
    case S_SP_BALL+7: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[7].Pos_xCM(),Ball[7].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(7);
        }
    } break;
    case S_SP_BALL+8: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[8].Pos_xCM(),Ball[8].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(8);
        }
    } break;
    case S_SP_BALL+9: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[9].Pos_xCM(),Ball[9].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(9);
        }
    } break;
    case S_SP_BALL+10: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[10].Pos_xCM(),Ball[10].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(10);
        }
    } break;
    case S_SP_BALL+11: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[11].Pos_xCM(),Ball[11].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(11);
        }
    } break;
    case S_SP_BALL+12: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[12].Pos_xCM(),Ball[12].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(12);
        }
    } break;
    case S_SP_BALL+13: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[13].Pos_xCM(),Ball[13].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(13);
        }
    } break;
    case S_SP_BALL+14: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[14].Pos_xCM(),Ball[14].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(14);
        }
    } break;
    case S_SP_BALL+15: {
        if (StateMachine==VIEWING ||
                StateMachine==NEW_WHITE) {
            Camera.EyesOn3(Ball[15].Pos_xCM(),Ball[15].Pos_yCM());
        } else if (StateMachine==SHOCK) {
            Camera.Track(15);
        }
    } break;
    case S_SP_WEITERSPIELEN: {
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        MenuGesperrt=0;
        NewMenuState();
    } break;
    case S_SP_ACHTEINSETZEN: {
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        MenuGesperrt=0;
        EightChosen();
        NewMenuState();
    } break;
    case S_SP_NEUAUFBAUEN: {
        Foul=0;
        LageVerbesserungKopffeld=1;
        LageVerbesserung=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        Player1Win=0;
        Player2Win=0;
        MenuGesperrt=0;
        StateMachine=JUDGEING;
        GLint Spieler=Judge.FrageNachSpielerAmStoss();
        GLint Fouls0=Judge.FrageNachFouls(0);
        GLint Fouls1=Judge.FrageNachFouls(1);
        Judge.NewGame(GameType);
        //SchiedsrichterEntscheidung=0; nur nicht!
        Judge.SetPlayerToStock(Spieler);
        Judge.SetzeFouls(0,Fouls0);
        Judge.SetzeFouls(1,Fouls1);
        BoardLayout();
        Camera.loadPosition(4);
        NewMenuState();
    } break;
    case S_SP_MAIN_MENU:{
        AusSpiel=0;
        StateMachine=START;
        setMenuState(MAIN_MENU);
    } break;
    case S_SP_NEW_GAME:{
        Foul=0;
        LageVerbesserungKopffeld=1;
        LageVerbesserung=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        Player1Win=0;
        Player2Win=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        MenuGesperrt=0;
        StateMachine=JUDGEING;
        GLint Spieler=Judge.FrageNachSpielerAmStoss();
        Judge.NewGame(GameType);
        JudgeDecision=0;
        Judge.SetPlayerToStock(1-Spieler);
        BoardLayout();
        Camera.loadPosition(4);
        NewMenuState();
    } break;
    case S_SP_NEWEIGHT_BALLAUFSTELLUNG:{
        if (StateMachine==VIEWING||
                StateMachine==NEW_WHITE) {
            GameType=EIGHT_BALL;
            BoardLayout();
        }
    } break;
    case S_SP_NEWNINE_BALLAUFSTELLUNG:{
        if (StateMachine==VIEWING||
                StateMachine==NEW_WHITE) {
            GameType=NINE_BALL;
            BoardLayout();
        }
    } break;
    case S_SPIELER1HERHOEREN:{
        for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
            if (TextItemArray[TextfeldNr])
                TextItemArray[TextfeldNr]->Weghoeren();
        }
        TextItemArray[T_SPIELER1NAME]->Herhoeren();
    } break;
    case S_SPIELER2HERHOEREN:{
        for (GLint TextfeldNr=0;TextfeldNr<1000;TextfeldNr++) {
            if (TextItemArray[TextfeldNr])
                TextItemArray[TextfeldNr]->Weghoeren();
        }
        TextItemArray[T_SPIELER2NAME]->Herhoeren();
    } break;
    case S_NETWORK_PLAYERERHERHOEREN:{
        //for (GLint TextfeldNr=0;TextfeldNr<TextfeldAnzahl;TextfeldNr++) {
        //  TextfeldArray[TextfeldNr]->Weghoeren();
        //}
        //T_NetzwerkSpielerName.Herhoeren();
    } break;
    case S_H_KEY_ASSIGNMENTS: {
        setMenuState(HELP_KEY_SET);
    } break;
    case S_H_BILLARDREGELN: {
        setMenuState(HELP_REGELN1);
    } break;
    case S_H_TUTORIAL: {
        Foul=0;
        LageVerbesserungKopffeld=0;
        LageVerbesserung=0;
        NeuAufbauenOderWeiterspielen=0;
        NeuAufbauenOderAchtEinsetzen=0;
        Player1Win=0;
        Player2Win=0;
        MenuGesperrt=0;
        GameMode=TUTORIAL;
        StateMachine=VIEWING;
        GameType=EIGHT_BALL;
        BoardLayout();
        Judge.NewGame(GameType);
        JudgeDecision=0;
        Camera.loadPosition(4);
        setMenuState(PLAYING);
    } break;
    case S_H_ZUHELP_: {
        setMenuState(HELP);
    } break;
    case S_H_E1_N: {
        setMenuState(HELP_EINFUEHRUNG2);
    } break;
    case S_H_E2_N: {
        setMenuState(HELP_EINFUEHRUNG3);
    } break;
    case S_H_E2_L: {
        setMenuState(HELP_EINFUEHRUNG1);
    } break;
    case S_H_E3_N: {
        setMenuState(HELP_EINFUEHRUNG4);
    } break;
    case S_H_E3_L: {
        setMenuState(HELP_EINFUEHRUNG2);
    } break;
    case S_H_E4_N: {
        setMenuState(HELP_EINFUEHRUNG5);
    } break;
    case S_H_E4_L: {
        setMenuState(HELP_EINFUEHRUNG3);
    } break;
    case S_H_E5_N: {
        setMenuState(HELP_EINFUEHRUNG6);
    } break;
    case S_H_E5_L: {
        setMenuState(HELP_EINFUEHRUNG4);
    } break;
    case S_H_E6_N: {
        setMenuState(HELP_EINFUEHRUNG7);
    } break;
    case S_H_E6_L: {
        setMenuState(HELP_EINFUEHRUNG5);
    } break;
    case S_H_R1_N: {
        setMenuState(HELP_REGELN2);
    } break;
    case S_H_R2_N: {
        setMenuState(HELP_REGELN3);
    } break;
    case S_H_R2_L: {
        setMenuState(HELP_REGELN1);
    } break;
    case S_H_R3_N: {
        setMenuState(HELP_REGELN4);
    } break;
    case S_H_R3_L: {
        setMenuState(HELP_REGELN2);
    } break;
    case S_H_R4_N: {
        setMenuState(HELP_REGELN5);
    } break;
    case S_H_R4_L: {
        setMenuState(HELP_REGELN3);
    } break;
    case S_H_R5_N: {
        setMenuState(HELP_REGELN6);
    } break;
    case S_H_R5_L: {
        setMenuState(HELP_REGELN4);
    } break;
    case S_H_R6_N: {
        setMenuState(HELP_REGELN7);
    } break;
    case S_H_R6_L: {
        setMenuState(HELP_REGELN5);
    } break;

    default:{
        if (Signal>=900 && Signal<990) {
            LoadLanguage(Signal);
            for (GLint dl=0 ; dl < 1000 ; dl++ ) {
                if (!TextItemArray[dl]) continue;
                TextItemArray[dl]->GenerateDisplayList();
                printf("."); fflush(stdout);
            }
            if (Language) setMenuState(SETUP);
            else SignalExecution(S_H_TUTORIAL);
            //SetzeMenuZustand(MAIN_MENU);
            Language=Signal;
            WriteConfig();
        }
    } break;
    }
}

GLint Menu::KeyboardButton (unsigned char Button,int,int){

    GLint Reaktion=0;
    GLint TextfeldNr=0;

    while (!Reaktion && TextfeldNr<1000) {
        if( TextItemArray[TextfeldNr] )
            Reaktion = TextItemArray[TextfeldNr]->Scale(Button);

        //if (Reaktion) {
        //  printf("\nReaktion von %i\n",TextfeldNr);
        //  printf("%s",TextfeldArray[TextfeldNr]->Text());
        //}

        TextfeldNr++;
    }

    if (Reaktion) return 1;

    if (MenuGesperrt ||
            MenuState!=PLAYING) {
        return 1;
    }

    //Esc-Sequenzen ;)

    switch (MenuState) {

    case HOME_SCREEN: {
        switch (Button) {
        case 27: {
            MenuState=MAIN_MENU;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case MAIN_MENU:{
        switch (Button) {
        case 27: {
            MenuState=EXIT;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case TRAINING:{
        switch (Button) {
        case 27: {
            MenuState=MAIN_MENU;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case TWO_PLAYERS:{
        switch (Button) {
        case 27: {
            MenuState=MAIN_MENU;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case NETWORK_MAIN:{
        switch (Button) {
        case 27: {
            MenuState=MAIN_MENU;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case NETWORK_NEW:{
        switch (Button) {
        case 27: {
            MenuState=NETWORK_MAIN;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case NETWORK_JOIN:{
        switch (Button) {
        case 27: {
            MenuState=NETWORK_MAIN;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case EXIT:{
        switch (Button) {
        case 27: {
            MenuState=MAIN_MENU;
            NewMenuState();
            return 1;
        } break;
        }
    } break;

    case OFF_GAME:{
    } break;

    case SETUP:{
    } break;

    }

    return 0;
}

void Menu::SetFPS(GLint fps) {
    char temp[]={0,0,0,0,0,0,0,0,0,0};
    sprintf(temp,"%i fps",fps);
    TextItemArray[T_FPS]->SetText(temp);
}
