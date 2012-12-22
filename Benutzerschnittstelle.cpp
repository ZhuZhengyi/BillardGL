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

#include "Kugel.h"
#include "Kamera.h"
#include "Anzeige.h"
#include "Schild.h"
#include "Textfeld.h"
#include "Menu.h"
#include "Schiedsrichter.h"

#include "Namen.h"
#include "Zeit.h"
#include "SpielfeldAufbau.h"
#include "Handling.h"
#include "Einsetzen.h"

#include "Benutzerschnittstelle.h"

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
		   StateMaschin=BETRACHTEN;
		   Menu.NeuerMenuZustand();
		   break; 
		   case BETRACHTEN: {
		   if (LageVerbesserungKopffeld|LageVerbesserung) {
		   StateMaschin=WEISSNEU;
		   Menu.NeuerMenuZustand();
		   }
		   } break; 
		   case ZIELEN:       
		   StateMaschin=BETRACHTEN; 
		   Menu.NeuerMenuZustand();
		   break;
		   case AUSHOLEN:        
		   StateMaschin=ZIELEN; 
		   Menu.NeuerMenuZustand();
		   Anzeige.setzeStossStaerke(0);
		   break;
		   case STOSS: {
		   if (xnor) {
		   StateMaschin=BETRACHTEN; 
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
				case BETRACHTEN: {  
                                     StateMachine=ZIELEN;
									 Menu.NewMenuState();
                                     Camera.EyesOn(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
								 } break;
				case ZIELEN: {
                                 AusholStartTime=ElapsedTime();
                                 StateMachine=AUSHOLEN;
								 Menu.NewMenuState();
							 } break;      
				case STOSS: {
								if (xnor) {
									for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln ans Ziel
                                        Ball[Kugelnr].newPositionD(LightingTable[Stossdauer][Kugelnr]);
                                        if (BallsInGame[Kugelnr] && !BallsSunk[Kugelnr] && (Ball[Kugelnr].Pos_x()==3000)) {
                                            BallsSunk[Kugelnr]=1;
										}
										Menu.NewMenuState();
									}
                                    if (Ball[0].Pos_x()==3000) {
                                        StateMachine=WEISSNEU;
										WeisseEinsetzen();
									} else {
                                        StateMachine=BETRACHTEN;
										Menu.NewMenuState();
									}
                                    Display.setShockStaerke(0);
								}
							} break;
				case WEISSNEU: {
                                   StateMachine=BETRACHTEN;
								   Menu.NewMenuState();	
							   } break;
				case SCHIEDSRICHTER: {
										 if (LageVerbesserungKopffeld|LageVerbesserung) {
											 WeisseEinsetzen();
                                             StateMachine=WEISSNEU;
											 Menu.NewMenuState();
										 } else {
                                             StateMachine=BETRACHTEN;
											 Menu.NewMenuState();
										 }
									 } break;
			}
		}

        if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP && StateMachine==AUSHOLEN) {
            GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
            GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
			GLfloat Abstand=sqrt(dx*dx+dy*dy);
            Stoke(dx*AusholStaerke/Abstand,dy*AusholStaerke/Abstand);
            StateMachine=STOSS;
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
        if ((StateMachine==ZIELEN)||(StateMachine==AUSHOLEN)) {
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
        if ((StateMachine==ZIELEN)||(StateMachine==AUSHOLEN)) {
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

	if (!Menu.KeyboardTaste(keyPressed,x,y)) {
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
                                   StateMachine=BETRACHTEN;
								   Menu.NewMenuState();
								   break; 
							   case BETRACHTEN: {
													if (LageVerbesserungKopffeld|LageVerbesserung) {
                                                        StateMachine=WEISSNEU;
														Menu.NewMenuState();
													}
												} break; 
							   case ZIELEN:       
                                                StateMachine=BETRACHTEN;
												Menu.NewMenuState();
												break;
							   case AUSHOLEN:        
                                                StateMachine=ZIELEN;
												Menu.NewMenuState();
                                                Display.setShockStaerke(0);
												break;
							   case STOSS: {
											   if (xnor) {
                                                   StateMachine=BETRACHTEN;
												   Menu.NewMenuState();
												   for (int i=1;i<16;i++) {
                                                       if (BallsInGame[i] && !BallsSunk[i] && (Ball[i].Pos_x()==3000)) {
                                                           BallsSunk[i]=1;
													   }
												   }
												   Menu.NewMenuState();
                                                   Display.setShockStaerke(0);
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
                              StateMachine=STOSS;
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
                          Menu.setMenuState(AUSSPIEL);
					  } break;

			case 'q': {
						  if (xnor==4) {
                              StateMachine=START;
                              Menu.setMenuState(STARTBILDSCHIRM);
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
						  Spiel=ZUFALL;  
						  BoardLayout();
					  }
				  } break;//z
		case 'a': {
					  if (xnor==4) {
						  Spiel=ACHTBALL;
						  BoardLayout();
                          Referee.NewGame(Spiel);
					  }
				  } break;//a
		case 'n': {
					  if (xnor==1) {
						  xnor=2;
					  }
					  if (xnor==4) {
						  Spiel=NEUNBALL;
						  BoardLayout();
                          Referee.NewGame(Spiel);
					  } 
				  } break;//n
		case '9': {
					  if (xnor==4) {
						  Spiel=NEUNBALL;
						  BoardLayout();
                          Referee.NewGame(Spiel);
					  }
				  } break;//9
		case 's': {
					  if (xnor==4) {
						  Spiel=ZWEIBAELLE;
						  BoardLayout();
					  }
				  } break;//s
		case 'l': {
					  if (xnor==4) {
						  Spiel=LEER;
						  BoardLayout();
					  }
				  } break;//l
		case 'd': {    
					  if (xnor==4) {
                          GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
                          GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
						  GLfloat Abstand=sqrt(dx*dx+dy*dy);
                          Stoke(dx*80.0/Abstand,dy*80.0/Abstand);
					  }
				  } break;//d
		case 'e': {    
					  if (xnor==4) {
                          GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
                          GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
						  GLfloat Abstand=sqrt(dx*dx+dy*dy);
                          Stoke(dx*80.0/Abstand,dy*80.0/Abstand);
                          StateMachine=STOSS;
						  Menu.NewMenuState();
                          Camera.EyesOn2(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
						  //Kamera.Verfolge(0);
                          DelayCompensation=1;
					  }
				  } break;//e
		case ' ': {  
                      switch (StateMachine) {
						  case BETRACHTEN:   
                              StateMachine=ZIELEN;
							  Menu.NewMenuState();
                              Camera.EyesOn(Ball[0].Pos_xCM(),Ball[0].Pos_yCM());
							  break;
						  case ZIELEN:       
                              AusholStartTime=ElapsedTime();
                              StateMachine=AUSHOLEN;
							  Menu.NewMenuState();
							  break;      
						  case STOSS: {
										  if (xnor) {
											  for (int Kugelnr=0;Kugelnr<16;Kugelnr++) { // Alle Kugeln ans Ziel
                                                  Ball[Kugelnr].newPositionD(LightingTable[Stossdauer][Kugelnr]);
											  }
                                              if (Ball[0].Pos_x()==3000) {
                                                  StateMachine=WEISSNEU;
												  WeisseEinsetzen();
												  Menu.NewMenuState();
											  } else {
                                                  StateMachine=BETRACHTEN;
												  Menu.NewMenuState();
											  } 
										  }
									  } break;
						  case WEISSNEU: {    
                                             StateMachine=BETRACHTEN;
											 Menu.NewMenuState();
										 } break;
						  case SCHIEDSRICHTER: {
												   if (LageVerbesserungKopffeld|LageVerbesserung) {
													   WeisseEinsetzen();
                                                       StateMachine=WEISSNEU;
													   Menu.NewMenuState();
												   } else {
                                                       StateMachine=BETRACHTEN;
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
            (StateMachine==AUSHOLEN)) {
        GLfloat dx=Ball[0].Pos_xCM()-Camera.Pos_xCM();
        GLfloat dy=Ball[0].Pos_yCM()-Camera.Pos_yCM();
		GLfloat Abstand=sqrt(dx*dx+dy*dy);
        Stoke(dx*AusholStaerke/Abstand,dy*AusholStaerke/Abstand);
        StateMachine=STOSS;
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
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
						Menu.NewMenuState();
					}
                    Camera.loadPosition(0);
				}
				break;
			case GLUT_KEY_F2:    
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
						Menu.NewMenuState();
					}
                    Camera.loadPosition(1);
				}
				break;
			case GLUT_KEY_F3:    
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
						Menu.NewMenuState();
					}
                    Camera.loadPosition(2);
				}
				break;
			case GLUT_KEY_F4:    
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
						Menu.NewMenuState();
					}
                    Camera.loadPosition(3);
				}
				break;
			case GLUT_KEY_F5:    
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
						Menu.NewMenuState();
					}
                    Camera.loadPosition(4);
				}
				break;
			case GLUT_KEY_F6:    
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
						Menu.NewMenuState();
					}
                    Camera.loadPosition(5);
				}
				break;
			case GLUT_KEY_F7:    
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
						Menu.NewMenuState();
					}
                    Camera.loadPosition(6);
				}
				break;
			case GLUT_KEY_F8:    
                if (StateMachine!=AUSHOLEN) {
                    if (StateMachine!=STOSS && StateMachine!=WEISSNEU && StateMachine!=SCHIEDSRICHTER) {
                        StateMachine=BETRACHTEN;
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
                      KEY_Bild_ON=1;
					  break;
			case GLUT_KEY_PAGE_DOWN:
                      KEY_Bild_Ab=1;
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
                      KEY_Bild_ON=0;
					  break;
			case GLUT_KEY_PAGE_DOWN:
                      KEY_Bild_Ab=0;
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
