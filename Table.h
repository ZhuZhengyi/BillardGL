/****************************************************************************
 **
 ** Table.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

#include <GL/glut.h>

class Table {
	public:
		Table();
		void Initialisiere(GLint);
		void maleArea();
		void maleBanden();
		void maleLinien();
	private:
		GLint TableAreaIndex;
		GLint BandenIndex;
		GLint LinesIndex;
		GLuint TableAreaTexture;
		GLuint HolzBandenTextur;
};


