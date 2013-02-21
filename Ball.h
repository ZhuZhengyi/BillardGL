/****************************************************************************
 **
 ** Ball.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

#include <GL/glut.h>

class Ball {
	public:
		Ball();
		void draw(GLint);
		void drawShadow();
		void newPosition(GLfloat[]);  
        //void newPosition(GLfloat,GLfloat);
        void newPosition(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z=0.0);
		void newPositionCM(GLfloat[]);
        //void newPositionCM(GLfloat,GLfloat);
        void newPositionCM(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z=0.0);
		void newPositionD(GLfloat[]);
        //void newPositionD(GLfloat,GLfloat);
        void newPositionD(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z=0.0);
		void newPositionINCH(GLfloat[]);
        //void newPositionINCH(GLfloat,GLfloat);
        void newPositionINCH(GLfloat neuPos_x,GLfloat neuPos_y,GLfloat neuPos_z=0.0);
		void disappear();
        void Init(GLint,GLint,GLint,GLint);
		GLfloat Pos_x();
		GLfloat Pos_y();
		GLfloat Pos_xD();
		GLfloat Pos_yD();
		GLfloat Pos_xCM();
		GLfloat Pos_yCM();
	private:
        GLfloat Position[3];        //当前位置
        GLint id;                   //几号球
        GLint ballIndex[30];        //显示列表
        GLint ballIndexStatic[30];  //
        GLint shadowIndex;          //
        GLint shadowIndexStatic;    //
        GLint shadow2Index;         //
        GLint Shadow;               //
        GLint InAnimation;          //是否运动中
        GLint StaticExists[30];     //
        GLint StaticExistShadow;    //
        GLfloat DrehMatrix[16];     //
		GLfloat Shadow1_x,Shadow1_y,Shadow1_scale,Shadow1_angle;
		GLfloat Shadow2_x,Shadow2_y,Shadow2_scale,Shadow2_angle;
		GLfloat Shadow3_x,Shadow3_y,Shadow3_scale,Shadow3_angle;
        GLfloat OldTextureSize;     //

        GLuint Textures[9];         //
};

extern GLfloat *ball_vertices[30];
extern GLfloat *ball_texcoord[30];
extern GLint *ball_indices[30];

