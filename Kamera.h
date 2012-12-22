/****************************************************************************
**
** Kamera.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
**
****************************************************************************/  

#include <GL/glut.h>

class Camera {
public:
    Camera();
    void draw();
    void newPosition(GLfloat[5]);
    GLfloat* Position();
    void savePosition(GLint);
    void loadPosition(GLint);
    void Move_Front(GLfloat);   //向前移
    void Move_Back(GLfloat);    //向后移
    void Move_In(GLfloat);      //向里移
    void Move_Out(GLfloat);     //向后移
    void Move_Right(GLfloat);
    void Move_Left(GLfloat);
    void Move_Up(GLfloat);
    void Move_Down(GLfloat);
    void Zoom_In(GLfloat);
    void Zoom_Out(GLfloat);
    void Vertigo_In(GLfloat);
    void Vertigo_Out(GLfloat);
    void TurnRight(GLfloat);
    void TurnLeft(GLfloat);
    void TurnUp(GLfloat);
    void TurnDown(GLfloat);
    void SwingRight(GLfloat,GLfloat,GLfloat);
    void SwingLeft(GLfloat,GLfloat,GLfloat);
    void SwingUp(GLfloat,GLfloat,GLfloat);
    void SwingDown(GLfloat,GLfloat,GLfloat);
    void Track(GLint                  );
    void EyesOn(GLfloat[2]);
    void EyesOn(GLfloat,GLfloat);
    void EyesOn2(GLfloat[2]);
    void EyesOn2(GLfloat,GLfloat);
    void EyesOn3(GLfloat[2]);
    void EyesOn3(GLfloat,GLfloat);
    void Ride(GLfloat);
    void ScenicFlight(GLint);
    void setToPosition(GLfloat[6]);
    void setToPosition(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
    void BlickTiefeNeuBestimmen();
    GLfloat Pos_xCM();
    GLfloat Pos_yCM();
    GLfloat Pos_zCM();
    GLfloat Aspect;
    GLint Persecution;
    GLfloat Pos_x,Pos_y,Pos_z,Alpha,Beta,FOV;
private:
    GLfloat Target_Pos_x,Target_Pos_y,Target_Pos_z,Target_Alpha,Target_Beta,Target_FOV;
    GLfloat d_Pos_x,d_Pos_y,d_Pos_z,d_Alpha,d_Beta,d_FOV;
    GLfloat Close,Remote;
    GLint CameraNumber;
};

extern class Ball Ball[16];


