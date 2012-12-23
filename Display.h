/****************************************************************************
 **
 ** Display.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

class Display {
	public:
		Display();
        void Init();
        void draw();
		void setShockStaerke(GLfloat);
	private:
		//GLint AusschlagIndex;
		GLfloat ShockStrength;
};






