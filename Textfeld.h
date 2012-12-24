class TextItem {
	public:
		TextItem();
		GLint dummyInit(GLint);
		void Initialisiere(GLint);
		void Initialisiere(GLint,char[]);
		void InitialisiereKDL(GLint,char[]);
		void draw();
		void Positioniere(GLfloat,GLfloat,GLfloat,GLint);
		void PositioniereFix(GLfloat,GLfloat,GLfloat,GLint);
		void SetText(char[]);
		void SetTextKDL(char[]);
		GLint Scale(char);
		char* Text();

		void Desaktiviere();
		void Angewaehlt();
		void Eingeblendet();
		void VollSichtbar();
		GLint Animiere(GLint);
		void SetzeSignal(GLint);
		GLint MouseButton(int,int,int,int);

		void SetMaxWidth(GLfloat);

		void Weghoeren();
		void Herhoeren();

		GLfloat TextboxHeight();

		void GenerateDisplayList();

		GLint dummyDisplayListAnfang();

	private:
		void StarteAnimation();
		char Zeichenkette[2000];
		GLfloat x,y,Hoehe,Aspekt,Alpha;
		GLfloat alt_x,alt_y,alt_Hoehe,alt_Alpha;
		GLfloat soll_x,soll_y,soll_Hoehe,soll_Alpha;
		GLint Ausrichtung;
		GLint InAnimation;
		GLint Signal;
		GLint Zeit; 
		GLint DisplayListArray;
		GLuint TextureArray[512];
		GLint TextfeldIndex;
		GLint Horchen;
		GLint Zeilen;

		GLfloat MaxBreite;

};

#define A_EGAL   0
#define A_LINKS  1
#define A_MITTE  2
#define A_RECHTS 3

#define HIDDEN 0.0
#define TRANSPARENT  0.2
#define EINGEBLENDET 0.6
#define SELECTED   0.8
#define FULL_VISIBLE 1.0

#define ANIMATION_TIME 100


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

