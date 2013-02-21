/****************************************************************************
 **
 ** Display.h   Stefan Disch, Tobias Nopper, Martina Welte 2001
 **
 ****************************************************************************/  

class ShotStrength {
	public:
		ShotStrength();
        void Init();
        void draw();
		void setShotStrength(GLfloat);
	private:
		//GLint AusschlagIndex;
		GLfloat shotStrength;
};






