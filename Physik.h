/****************************************************************************
 **
 ** Physik.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

void Physik(GLfloat,GLfloat);
void Collision(GLfloat[],GLfloat[],GLint,GLint);

extern GLfloat CollisionFactor,FrictionFactor,GangsFactor;
extern GLint PhysicsFrequenz, Stossdauer;

extern class Ball Ball[16];
extern class Referee Referee;

extern GLfloat LightingTable[2000][16][3];
