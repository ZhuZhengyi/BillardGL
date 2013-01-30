/****************************************************************************
 **
 ** Menu.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

#include "language.h"

#define AUS 0
#define HOME_SCREEN 1
#define MAIN_MENU 2
#define TRAINING 3
#define TWO_PLAYERS 4
#define NETWORK_MAIN 5
#define NETWORK_NEW 6
#define NETWORK_JOIN 7
#define EXIT 8
#define OFF_GAME 9
#define SETUP 10
#define SETUP_CONTROL 11
#define SETUP_VIDEO 12
#define SETUP_VIDEO_NONETICE 13
#define SETUP_AUDIO 14
#define LANGUAGE 15
#define PLAYING 20

#define HELP 30
#define HELP_REGELN1 31
#define HELP_REGELN2 32
#define HELP_REGELN3 33
#define HELP_REGELN4 34
#define HELP_REGELN5 35
#define HELP_REGELN6 36
#define HELP_REGELN7 37
#define HELP_REGELN8 38
#define HELP_EINFUEHRUNG1 41
#define HELP_EINFUEHRUNG2 42
#define HELP_EINFUEHRUNG3 43
#define HELP_EINFUEHRUNG4 44
#define HELP_EINFUEHRUNG5 45
#define HELP_EINFUEHRUNG6 46
#define HELP_EINFUEHRUNG7 47
#define HELP_EINFUEHRUNG8 48
#define HELP_KEY_SET 49

#define SPIELENDE 99

#define S_SB_LOGO 100
#define S_SB_NAMEN 101
#define S_LOGO 102

#define S_MAINMENU_TRAINING 110
#define S_MAINMENU_TWO_PLAYERS 111
#define S_MAINMENU_NETWORK_PLAYER 112
#define S_MAINMENU_SETUP_ 113
#define S_MAINMENU_EXIT 114
#define S_MAINMENU_COMPUTERGEGNER 115
#define S_MAINMENU_HELP 116

#define S_TR_EIGHT_BALL 120
#define S_TR_NINE_BALL 121
#define S_TR_VIERZEHNPLUSEINS 122
#define S_TR_BACK 123

#define S_ZW_EIGHT_BALL 130
#define S_ZW_NINE_BALL 131
#define S_ZW_VIERZEHNPLUSEINS 132
#define S_ZW_BACK 133

#define S_NE_BEGIN 140
#define S_NE_TEILNEHMEN 141
#define S_NE_BACK 142

#define S_NB_EIGHT_BALL 150
#define S_NB_NINE_BALL 151
#define S_NB_VIERZEHNPLUSEINS 152
#define S_NB_BACK  153

#define S_NT_IPADRESSE 160
#define S_NT_CONNECT 161
#define S_NT_BACK   162

#define S_SETUP_BALLTEXTURES 170
#define S_SETUP_TABLE_TEXTURES 180
#define S_SETUP_ANZEIGETEXTURES 190
#define S_SETUP_TEXTURINTERPOLATION 195
#define S_SETUP_BALLGEOMETRIE   201
#define S_SETUP_MOUSESPEED      202
#define S_SETUP_XINVERT   203
#define S_SETUP_YINVERT   204
#define S_SETUP_LANGUAGE   205
#define S_SETUP_BACK 220
#define S_SETUP_BACK_AS 221
#define S_SETUP_UEBERNEHMEN 222     //PICK-UP
#define S_SETUP_CONTROL 223
#define S_SETUP_CONTROLBACK 224
#define S_SETUP_CONTROLUEBERNEHMEN 225
#define S_SETUP_AUDIO 226
#define S_SETUP_AUDIOBACK 227
#define S_SETUP_AUDIOUEBERNEHMEN 228
#define S_SETUP_VIDEO 800
#define S_SETUP_VIDEOBACK 801
#define S_SETUP_VIDEOUEBERNEHMEN 802
#define S_SETUP_RESOLUTION 803
#define S_SETUP_COLOR_DEPTH 804
#define S_SETUP_REFLEKTIONEN 805
#define S_SETUP_QUALITAET 806
#define S_SETUP_SHADOWS 807
#define S_SETUP_AMBIENCE_LIGHTING 808
#define S_SETUP_TABLE_LAMPEN 809
#define S_SETUP_GRUENELAMPE 810
#define S_SETUP_FPS 811

#define S_AS_WEITERSPIELEN 230
#define S_AS_MAIN_MENU 231
#define S_AS_SETUP 232
#define S_AS_EXIT 233
#define S_AS_HELP 234

#define S_BE_YESEXIT       850
#define S_BE_BACK         851
#define S_BE_BACK_AS       852

#define S_SP_LOGO    500
#define S_SP_BALL    510
#define S_SP_WEITERSPIELEN 530  //CONTINUE PLAYING
#define S_SP_ACHTEINSETZEN 531
#define S_SP_NEUAUFBAUEN 532    //Rebuild
#define S_SP_MAIN_MENU 540
#define S_SP_NEW_GAME 541

#define S_SP_NEWEIGHT_BALLAUFSTELLUNG 550
#define S_SP_NEWNINE_BALLAUFSTELLUNG 551

#define S_PLAYER1HERHOEREN 601
#define S_PLAYER2HERHOEREN 602
#define S_NETWORK_PLAYERERHERHOEREN 603

#define S_H_KEY_ASSIGNMENTS 300
#define S_H_BILLARDREGELN 301   //POOL RULES
#define S_H_TUTORIAL 302
#define S_H_ZUHELP_ 303
#define S_H_E1_N 304
#define S_H_E2_N 305
#define S_H_E2_L 306
#define S_H_E3_N 307
#define S_H_E3_L 308
#define S_H_E4_N 309
#define S_H_E4_L 310
#define S_H_E5_N 311
#define S_H_E5_L 312
#define S_H_E6_N 313
#define S_H_E6_L 314
#define S_H_R1_N 315
#define S_H_R2_N 316
#define S_H_R2_L 317
#define S_H_R3_N 318
#define S_H_R3_L 319
#define S_H_R4_N 320
#define S_H_R4_L 321
#define S_H_R5_N 322
#define S_H_R5_L 323
#define S_H_R6_N 324
#define S_H_R6_L 325


#define ANIMATION_TIME 100

class Menu {
	public:
		Menu();
		void Init(GLint);
		void draw();
		void Update(GLint);

        GLint MouseClick(int,int,int,int);
		GLint KeyboardButton (unsigned char,int,int);
		void NewMenuState();
		void SignalExecution(GLint);
		void setMenuState(GLint); 
		void SetFPS(GLint);
        void LoadLanguage(GLint);
	private:
		void StarteAnimation();
        GLint AnimationsTime;
		GLint InAnimation;

        GLint MenuState;
        GLint AusSpiel; //fromGame

        Label MenuBackground;

        Label logo;
        Label namen;    //

        Label halbe;    //half
        Label volle;    //full

        Label ball[16];

        Label GameStar;

        Label* SchildArray[300];
        TextItem* TextItemArray[1000];

        TextItem dummyTextfeld;

		GLint TDL;
		//GLint TTA;

		GLint SchildAnzahl;
		GLint TextfeldAnzahl;

        GLint E_BallTextureSize;        //球显示精度
        GLint E_AnzeigeTexturgroesse;   //
        GLint E_TableTextureSize;       //桌面图像精度
        GLint E_KugelAufloesung;        //球分辨率
		GLfloat E_MouseSpeed;
		GLint E_InvertX;
		GLint E_InvertY;
        GLint MenuGesperrt;     //menu locked/disabled
        GLint E_Reflection;
        GLint E_ColorDepth;
        GLint E_ScreenResolution;
        GLint Quality;
        GLint E_Shadows;

        GLint E_AmbientLighting;
        GLint E_TableLampes;
        GLint E_GreenLampe;
        GLint E_ShowFPS;

		GLint E_TexMMM;

};


extern GLint StateMachine;
extern GLint GameType;
extern class Camera Camera;

extern GLint TextureSize,
	   DisplayTextureSize,
	   TableTextureSize,
	   BallResolution,
	   InvertX,
	   InvertY,
	   Shadow,
	   GameMode,
       PlayerOnShock;

extern GLfloat MouseSpeed;
extern GLint   BallsSunk[16];
extern GLint   BallsInGame[16];

extern class Ball Ball[16];  
extern class Table Table;
extern class ShotStrength ShotStrength;
extern class Judge Judge;
extern class Lighting Lighting;

extern GLint JudgeDecision;     //裁决
extern GLint PlayerOnShock;     //击球者
extern GLint RecodingChanges;   //记分
extern GLint Foul;  //犯规
extern GLint LageVerbesserungKopffeld;
extern GLint LageVerbesserung;
extern GLint NeuAufbauenOderWeiterspielen;
extern GLint NeuAufbauenOderAchtEinsetzen;
extern GLint Player1Win;
extern GLint Player2Win;
extern GLint AllerersterStoss;

extern GLint ShowFPS,TableLamps,GreenLamp;
extern GLfloat EffectVolumeDown,MusicVolumeDown;

extern GLint TexMMM;

extern GLint DelayCompensation;

extern GLint xnor;

extern char Player1[10],Player2[10],NetworkPlayer[10],NetworkTeam[10];


























