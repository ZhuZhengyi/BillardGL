/****************************************************************************
 **
 ** Kugel.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

#include <GL/glut.h>

class Ball {
	public:
		Ball();
		void draw(GLint);
		void drawShadow();
		void newPosition(GLfloat[]);  
		void newPosition(GLfloat,GLfloat);  
		void newPosition(GLfloat,GLfloat,GLfloat);  
		void newPositionCM(GLfloat[]);
		void newPositionCM(GLfloat,GLfloat);
		void newPositionCM(GLfloat,GLfloat,GLfloat);
		void newPositionD(GLfloat[]);
		void newPositionD(GLfloat,GLfloat);
		void newPositionD(GLfloat,GLfloat,GLfloat);
		void newPositionINCH(GLfloat[]);
		void newPositionINCH(GLfloat,GLfloat);
		void newPositionINCH(GLfloat,GLfloat,GLfloat);
		void disappear();
		void Initialisiere(GLint,GLint,GLint,GLint);
		GLfloat Pos_x();
		GLfloat Pos_y();
		GLfloat Pos_xD();
		GLfloat Pos_yD();
		GLfloat Pos_xCM();
		GLfloat Pos_yCM();
	private:
		GLfloat Position[3];
		GLint Number;
		GLint sphereIndex[30]; 
		GLint sphereIndexStatisch[30]; 
		GLint shadowIndex;
		GLint shadowIndexStatic;
		GLint schatten2Index;
		GLint Shadow;
		GLint InAnimation;
		GLint StaticExists[30];
		GLint StaticExistShadow;
		GLfloat DrehMatrix[16];
		GLfloat Shadow1_x,Shadow1_y,Shadow1_scale,Shadow1_angle;
		GLfloat Shadow2_x,Shadow2_y,Shadow2_scale,Shadow2_angle;
		GLfloat Shadow3_x,Shadow3_y,Shadow3_scale,Shadow3_angle;
		GLfloat OldTextureSize;

		GLuint Texturen[9];
};

extern GLfloat *ball_vertices[30];
extern GLfloat *ball_texcoord[30];
extern GLint *ball_indices[30];

