void StartHandling();
void ViewingHandling();
void AimHandling();
void BackswingHandling();
void ShockHandling();
void NewWhiteHandling();
void MenuHandling();
void JudgeHandling();

extern GLint KEY_UP,KEY_DOWN,
	   KEY_RIGHT,KEY_LEFT,KEY_SHIFT,
	   KEY_CTRL,KEY_PAGE_UP,KEY_PAGE_DOWN,KEY_Pos1,
	   KEY_END,Factor,AusholStartTime,StartTime,
	   shot_time,StateMachine,FrameTimePoint,Anfangsstoss,
	   WeisseVersetzbar;
extern GLfloat MaxAusholStaerke,AusholStaerke;
extern GLint   BallsSunk[16];
extern GLint   BallsInGame[16];
extern GLfloat LightingTable[2000][16][3];

extern class Camera Camera;
extern class Ball Ball[16];
extern class ShotStrength ShotStrength;
extern class Menu Menu;
extern class Judge Judge;

extern GLint JudgeDecision;
extern GLint PlayerOnShock;
extern GLint RecodingChanges;
extern GLint Foul;
extern GLint LageVerbesserungKopffeld;
extern GLint LageVerbesserung;
extern GLint NeuAufbauenOderWeiterspielen;
extern GLint NeuAufbauenOderAchtEinsetzen;
extern GLint Player1Win;
extern GLint Player2Win;
extern GLint AllerersterStoss;
