/****************************************************************************
 **
 **  Benutzerschnittstelle.cpp   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 *****************************************************************************/

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "BillardGL.h"

#include "Ball.h"
#include "Camera.h"
#include "ShotStrength.h"
#include "Label.h"
#include "TextItem.h"
#include "Menu.h"
#include "Judge.h"

#include "Namen.h"
#include "ElapsedTime.h"
#include "BoardLayout.h"
#include "Handling.h"
#include "Chosen.h"

#include "MouseKey.h"

GLint MouseButton=0;

//mouse

//Callback Funktion: Reaktion auf Mausclicks
void MouseClick(int button, int state, int x, int y)
{

    if (Menu.MouseClick(button,state,x,y)!=0) {
        MouseButtonIntercepted=1;
        //printf("Abgefangen\n");
    } else {
        MouseButtonIntercepted=0;
        //printf("AbgefangenAus\n");
        MouseLookLast_x=x;
        MouseLookLast_y=y;

        //  Kamera.FahrtAus();

        /*
           if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
           switch (StateMaschin) {
           case START:
           StateMaschin=VIEWING;
           Menu.NeuerMenuZustand();
           break;
           case VIEWING: {
           if (LageVerbesserungKopffeld|LageVerbesserung) {
           StateMaschin=NEW_WHITE;
           Menu.NeuerMenuZustand();
           }
           } break;
           case AIMING:
           StateMaschin=VIEWING;
           Menu.NeuerMenuZustand();
           break;
           case SWING:
           StateMaschin=AIMING;
           Menu.NeuerMenuZustand();
           Anzeige.setzeStossStaerke(0);
           break;
           case SHOT: {
           if (xnor) {
           StateMaschin=VIEWING;
           Menu.NeuerMenuZustand();
           for (int i=1;i<16;i++) {
           if (KugelnImSpiel[i] && !KugelnVersenkt[i] && (Kugel[i].Pos_x()==3000)) {
           KugelnVersenkt[i]=1;
           }
           }
           Menu.NeuerMenuZustand();
           Anzeige.setzeStossStaerke(0);
           }
           } break;
           }
           }
           */

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) MouseButton=GLUT_LEFT_BUTTON;
        if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) MouseButton=GLUT_RIGHT_BUTTON;

        if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
            MouseButton=GLUT_LEFT_BUTTON;
            switch (StateMachine) {
            case VIEWING: {
                StateMachine=AIMING;
                Menu.NewMenuState();
                Camera.EyesOn(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            } break;
            case AIMING: {
                AusholStartTime=ElapsedTime();
                StateMachine=SWING;
                Menu.NewMenuState();
            } break;
            case SHOT: {
                if (xnor) {
                    for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln ans Ziel
                        Ball[Kugelnr].newPositionD(LightingTable[shot_time][Kugelnr]);
                        if (BallsInGame[Kugelnr] && !BallsSunk[Kugelnr] && (Ball[Kugelnr].Pos_x()==3000)) {
                            BallsSunk[Kugelnr]=1;
                        }
                        Menu.NewMenuState();
                    }
                    if (Ball[0].Pos_x()==3000) {
                        StateMachine=NEW_WHITE;
                        WhiteChosen();
                    } else {
                        StateMachine=VIEWING;
                        Menu.NewMenuState();
                    }
                    ShotStrength.setShotStrength(0);
                }
            } break;
            case NEW_WHITE: {
                StateMachine=VIEWING;
                Menu.NewMenuState();
            } break;
            case JUDGEING: {
                if (LageVerbesserungKopffeld|LageVerbesserung) {
                    WhiteChosen();
                    StateMachine=NEW_WHITE;
                    Menu.NewMenuState();
                } else {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
            } break;
            }
        }

        if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP && StateMachine==SWING) {
            GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
            GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
            GLfloat Abstand=sqrt(dx*dx+dy*dy);
            Shot(dx*AusholStaerke/Abstand,dy*AusholStaerke/Abstand);
            StateMachine=SHOT;
            Menu.NewMenuState();
            //Kamera.Verfolge(0);
            Camera.EyesOn2(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            //    Kamera.FahrtEin();
            DelayCompensation=1;
        }

    }
}

//Bewegung -> movement

//Callback Funktion: Reaktion auf Mausbewegung
void MouseMove(int x, int y) {
    if (MouseButtonIntercepted) return;
    if (StateMachine==START) return;
    if (MouseButton==GLUT_LEFT_BUTTON) {
        if ((StateMachine==AIMING)||(StateMachine==SWING)) {
            if (InvertX) {
                Camera.SwingRight(MouseSpeed*(x-MouseLookLast_x),Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            } else {
                Camera.SwingLeft(MouseSpeed*(x-MouseLookLast_x),Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            }
            if (InvertY) {
                Camera.SwingUp(MouseSpeed*(y-MouseLookLast_y),Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            } else {
                Camera.SwingDown(MouseSpeed*(y-MouseLookLast_y),Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            }
        } else {
            if (InvertX) {
                Camera.TurnLeft(MouseSpeed*(x-MouseLookLast_x));
            } else {
                Camera.TurnRight(MouseSpeed*(x-MouseLookLast_x));
            }
            if (InvertY) {
                Camera.TurnUp(MouseSpeed*(y-MouseLookLast_y));
            } else {
                Camera.TurnDown(MouseSpeed*(y-MouseLookLast_y));
            }
        }
    } else if (MouseButton==GLUT_RIGHT_BUTTON) {
        if ((StateMachine==AIMING)||(StateMachine==SWING)) {
            if (InvertX) {
                Camera.SwingRight(MouseSpeed*(x-MouseLookLast_x),Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            } else {
                Camera.SwingLeft(MouseSpeed*(x-MouseLookLast_x),Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
            }
            if (InvertY) {
                Camera.Move_In(MouseSpeed*(y-MouseLookLast_y));
            } else {
                Camera.Move_Out(MouseSpeed*(y-MouseLookLast_y));
            }
        } else {
            if (InvertX) {
                Camera.Move_Left(MouseSpeed*(x-MouseLookLast_x));
            } else {
                Camera.Move_Right(MouseSpeed*(x-MouseLookLast_x));
            }
            if (InvertY) {
                Camera.Move_In(MouseSpeed*(y-MouseLookLast_y));
            } else {
                Camera.Move_Out(MouseSpeed*(y-MouseLookLast_y));
            }
        }
    }

    MouseLookLast_x=x;
    MouseLookLast_y=y;
}

//Taste
//Callback Funktion: Reaktion auf Tastendruck
void KeyPress( unsigned char keyPressed, int x, int y )
{
    //printf("%c: %i\n",keyPressed,keyPressed);

    if (!Menu.KeyboardButton(keyPressed,x,y)) {
        switch( keyPressed ) {
        case 'h': {
            if (xnor==4) {
                BackgroundColor=1-BackgroundColor;
                glClearColor(BackgroundColor,BackgroundColor,BackgroundColor,0);
            }
        } break;                           //h: Hintergrundfarbe invertieren
        case 'v': {
            if (xnor==4) {
                switch (PolygonMode_view) {      //v: Vorne/Hinten/Beides
                case GL_FRONT:
                    PolygonMode_view=GL_BACK;
                    break;
                case GL_BACK:
                    PolygonMode_view=GL_FRONT_AND_BACK;
                    break;
                case GL_FRONT_AND_BACK:
                    PolygonMode_view=GL_FRONT;
                    break;
                }
                glPolygonMode(PolygonMode_view,PolygonMode_mode);
            }
        } break;
        case 'w': {
            if (xnor==4) {
                switch (PolygonMode_mode) {     //w: Punkte/Linien/Fl"achen
                case GL_FILL: PolygonMode_mode=GL_POINT;break;
                case GL_POINT: PolygonMode_mode=GL_LINE;break;
                case GL_LINE: PolygonMode_mode=GL_FILL;break;
                }
                glPolygonMode(PolygonMode_view,PolygonMode_mode);
            }
        } break;

        case '1': Camera.savePosition(0);break; //1
        case '2': Camera.savePosition(1);break; //2
        case '3': Camera.savePosition(2);break; //3
        case '4': Camera.savePosition(3);break; //4
        case '5': Camera.savePosition(4);break; //5
        case '6': Camera.savePosition(5);break; //6
        case '7': Camera.savePosition(6);break; //7
        case '8': Camera.savePosition(7);break; //8

        case '\b': {
            switch (StateMachine) {
            case START:
                StateMachine=VIEWING;
                Menu.NewMenuState();
                break;
            case VIEWING: {
                if (LageVerbesserungKopffeld|LageVerbesserung) {
                    StateMachine=NEW_WHITE;
                    Menu.NewMenuState();
                }
            } break;
            case AIMING:
                StateMachine=VIEWING;
                Menu.NewMenuState();
                break;
            case SWING:
                StateMachine=AIMING;
                Menu.NewMenuState();
                ShotStrength.setShotStrength(0);
                break;
            case SHOT: {
                if (xnor) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                    for (int i=1;i<16;i++) {
                        if (BallsInGame[i] && !BallsSunk[i] && (Ball[i].Pos_x()==3000)) {
                            BallsSunk[i]=1;
                        }
                    }
                    Menu.NewMenuState();
                    ShotStrength.setShotStrength(0);
                }
            } break;
            }
        } break;

        case 'r': {
            if (xnor==3) {
                xnor=4;
            } else if (!AllerersterStoss) {
                StartTime=ElapsedTime();
                //Frames=0;
                StateMachine=SHOT;
                Menu.NewMenuState();
                for (int Kugelnr=0;Kugelnr<16;Kugelnr++) {
                    Ball[Kugelnr].newPositionD(LightingTable[0][Kugelnr]);
                }
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            }
        } break;           //r


        case 'c': {
            if (xnor==4) {
                glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            }
        } break; //c

        case 27 : {
            Menu.setMenuState(OFF_GAME);
        } break;

        case 'q': {
            if (xnor==4) {
                StateMachine=START;
                Menu.setMenuState(HOME_SCREEN);
            }
        } break;

        case 'f': {
            /*
                             (FullScreen=1-FullScreen);
                             if (FullScreen) {
                             glutFullScreen();
                             } else {
                             glutReshapeWindow(800, 600);
                             }
                             */
        } break;
            /*
                      //      if (xnor==4) {
                      (FullScreen=1-FullScreen);
                      if (FullScreen) {
                      glutFullScreen();
                      //glutGameModeString("640x480:16@60");
                      //glutEnterGameMode();
                      //AktuellesFenster=glutGetWindow();
                      //glutIgnoreKeyRepeat(1);
                      //glutMouseFunc(Maus);
                      //glutMotionFunc(Bewegung);
                      //glutKeyboardFunc(Taste);
                      //glutKeyboardUpFunc(TasteLos);
                      //glutSpecialFunc(Sondertaste);
                      //glutSpecialUpFunc(SondertasteLos);
                      //glutIdleFunc(timerEvent);
                      //glutDisplayFunc(updateGL);
                      //glutVisibilityFunc(Sichtbar);
                      //      CreateMenu();
                      } else {
                      glutReshapeWindow(800, 600);
                      if (OriginalFenster != 0 && AktuellesFenster != OriginalFenster) {
                      glutLeaveGameMode();
                      AktuellesFenster=OriginalFenster;
                      }
                      }
                      }
                      } break;
                      */
        case 127: {
            KEY_CTRL=1;
        } break;
        case 'x': {
            if (xnor==0) {
                xnor=1;
            }
        } break;
        case 'o': {
            if (xnor==2) {
                xnor=3;
            }
        } break;
        case 'z': {
            if (xnor==4) {
                GameType=GT_RANDOM;
                BoardLayout();
            }
        } break;//z
        case 'a': {
            if (xnor==4) {
                GameType=EIGHT_BALL;
                BoardLayout();
                Judge.NewGame(GameType);
            }
        } break;//a
        case 'n': {
            if (xnor==1) {
                xnor=2;
            }
            if (xnor==4) {
                GameType=NINE_BALL;
                BoardLayout();
                Judge.NewGame(GameType);
            }
        } break;//n
        case '9': {
            if (xnor==4) {
                GameType=NINE_BALL;
                BoardLayout();
                Judge.NewGame(GameType);
            }
        } break;//9
        case 's': {
            if (xnor==4) {
                GameType=TWO_BALLS;
                BoardLayout();
            }
        } break;//s
        case 'l': {
            if (xnor==4) {
                GameType=GT_EMPTY;
                BoardLayout();
            }
        } break;//l
        case 'd': {
            if (xnor==4) {
                GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
                GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
                GLfloat Abstand=sqrt(dx*dx+dy*dy);
                Shot(dx*80.0/Abstand,dy*80.0/Abstand);
            }
        } break;//d
        case 'e': {
            if (xnor==4) {
                GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
                GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
                GLfloat Abstand=sqrt(dx*dx+dy*dy);
                Shot(dx*80.0/Abstand,dy*80.0/Abstand);
                StateMachine=SHOT;
                Menu.NewMenuState();
                Camera.EyesOn2(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
                //Kamera.Verfolge(0);
                DelayCompensation=1;
            }
        } break;//e
        case ' ': {
            switch (StateMachine) {
            case VIEWING:
                StateMachine=AIMING;
                Menu.NewMenuState();
                Camera.EyesOn(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
                break;
            case AIMING:
                AusholStartTime=ElapsedTime();
                StateMachine=SWING;
                Menu.NewMenuState();
                break;
            case SHOT: {
                if (xnor) {
                    for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln ans Ziel
                        Ball[Kugelnr].newPositionD(LightingTable[shot_time][Kugelnr]);
                    }
                    if (Ball[0].Pos_x()==3000) {
                        StateMachine=NEW_WHITE;
                        WhiteChosen();
                        Menu.NewMenuState();
                    } else {
                        StateMachine=VIEWING;
                        Menu.NewMenuState();
                    }
                }
            } break;
            case NEW_WHITE: {
                StateMachine=VIEWING;
                Menu.NewMenuState();
            } break;
            case JUDGEING: {
                if (LageVerbesserungKopffeld|LageVerbesserung) {
                    WhiteChosen();
                    StateMachine=NEW_WHITE;
                    Menu.NewMenuState();
                } else {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
            } break;
            }
        }
        }
    }
}

//KeyRelease
void KeyRelease( unsigned char keyPressed, int,int) {

    if ((keyPressed==' ')&&
            (StateMachine==SWING)) {
        GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
        GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
        GLfloat Abstand=sqrt(dx*dx+dy*dy);
        Shot(dx*AusholStaerke/Abstand,dy*AusholStaerke/Abstand);
        StateMachine=SHOT;
        Menu.NewMenuState();
        Camera.EyesOn2(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
        //Kamera.Verfolge(0);
        DelayCompensation=1;
    }
    if (keyPressed==127) {
        KEY_CTRL=0;
    }

}

//Special key
void SpecialKeyPress(int Taste,int x, int y) {

    x=y;

    //printf("%i\n",Taste);

    //  Kamera.FahrtAus();

    if (StateMachine!=START) {

        switch (Taste) {
        case GLUT_KEY_F1:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(0);
            }
            break;
        case GLUT_KEY_F2:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(1);
            }
            break;
        case GLUT_KEY_F3:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(2);
            }
            break;
        case GLUT_KEY_F4:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(3);
            }
            break;
        case GLUT_KEY_F5:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(4);
            }
            break;
        case GLUT_KEY_F6:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(5);
            }
            break;
        case GLUT_KEY_F7:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(6);
            }
            break;
        case GLUT_KEY_F8:
            if (StateMachine!=SWING) {
                if (StateMachine!=SHOT && StateMachine!=NEW_WHITE && StateMachine!=JUDGEING) {
                    StateMachine=VIEWING;
                    Menu.NewMenuState();
                }
                Camera.loadPosition(7);
            }
            break;

        case 108: {
            KEY_SHIFT=1;
        } break;
        case GLUT_KEY_UP:
            KEY_UP=1;
            break;
        case GLUT_KEY_DOWN:
            KEY_DOWN=1;
            break;
        case GLUT_KEY_RIGHT:
            KEY_RIGHT=1;
            break;
        case GLUT_KEY_LEFT:
            KEY_LEFT=1;
            break;
        case GLUT_KEY_PAGE_UP:
            KEY_PAGE_UP=1;
            break;
        case GLUT_KEY_PAGE_DOWN:
            KEY_PAGE_DOWN=1;
            break;
        case GLUT_KEY_HOME:
            if (xnor) KEY_Pos1=1;
            break;
        case GLUT_KEY_END:
            if (xnor) KEY_END=1;
            break;
        }
    }
}

//Special release key
void SpecialKeyRelease(int Taste,int x, int y) {

    x=y;

    if (StateMachine!=START) {

        switch (Taste) {
        case 108: {
            KEY_SHIFT=0;
        } break;
        case GLUT_KEY_UP:
            KEY_UP=0;
            break;
        case GLUT_KEY_DOWN:
            KEY_DOWN=0;
            break;
        case GLUT_KEY_RIGHT:
            KEY_RIGHT=0;
            break;
        case GLUT_KEY_LEFT:
            KEY_LEFT=0;
            break;
        case GLUT_KEY_PAGE_UP:
            KEY_PAGE_UP=0;
            break;
        case GLUT_KEY_PAGE_DOWN:
            KEY_PAGE_DOWN=0;
            break;
        case GLUT_KEY_HOME:
            KEY_Pos1=0;
            break;
        case GLUT_KEY_END:
            KEY_END=0;
            break;
        }
    }
}
