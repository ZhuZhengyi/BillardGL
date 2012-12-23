/****************************************************************************
 **
 ** MouseKey.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

void MouseClick(int,int,int,int);
void MouseMove(int,int);
void KeyPress(unsigned char,int,int);
void KeyRelease(unsigned char,int,int);
void SpecialKeyPress(int,int,int);
void SpecialKeyRelease(int,int,int);

extern class Ball Ball[16];
extern class Camera Camera;
extern class Display Display;
extern class Menu Menu;
extern class Judge Judge;

extern GLint DelayCompensation;
extern GLint InvertX;
extern GLint InvertY;
extern GLfloat MouseSpeed,AusholStaerke;
extern GLint   BackgroundColor;
extern GLint PolygonMode_mode;
extern GLint PolygonMode_view;
extern GLint StartTime,AusholStartTime,Stossdauer,Ausholstaerke;
extern GLint xnor;
extern int OriginalWindow,CurrentWindow;
extern GLint GameType,StateMachine, FullScreen;
extern GLint KEY_UP,KEY_DOWN;
extern GLint KEY_RIGHT,KEY_LEFT;
extern GLint KEY_SHIFT, KEY_CTRL;
extern GLint KEY_PAGE_UP,KEY_PAGE_DOWN;
extern GLint KEY_Pos1,KEY_END;

extern GLint MouseLookLast_x,MouseLookLast_y;
extern GLfloat LightingTable[2000][16][3];
extern GLint MouseButtonIntercepted;

extern GLint LageVerbesserungKopffeld; //Situation improving header
extern GLint LageVerbesserung; //situation improving
extern GLint AllerersterStoss; //first stoke/kick
