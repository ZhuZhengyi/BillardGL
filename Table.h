/****************************************************************************
 **
 ** Table.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

#include <GL/glut.h>

class Table {
	public:
		Table();
        void Init(GLint);
        void drawSurface();
        void drawBorder();
        void drawLine();
	private:
		GLint TableSurfaceIndex;
		GLint BorderIndex;
		GLint LinesIndex;
		GLuint TableSurfaceTexture;
        GLuint WoodBorderTexture;
};


