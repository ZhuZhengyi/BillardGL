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
		GLint TableAreaIndex;
		GLint BandenIndex;
		GLint LinesIndex;
		GLuint TableAreaTexture;
		GLuint HolzBandenTextur;
};


