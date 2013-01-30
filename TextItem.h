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
        GLint Label(char);
		char* Text();

        void DisActivated();
        void Selected();
        void Appear();
        void FullyVisible();
		GLint Animiere(GLint);
        void SetSignal(GLint);
		GLint MouseButton(int,int,int,int);

		void SetMaxWidth(GLfloat);

		void Weghoeren();
		void Herhoeren();

		GLfloat TextboxHeight();

		void GenerateDisplayList();

		GLint dummyDisplayListAnfang();

	private:
        void StartAnimation();
        char text[2000];
        GLfloat x,y,Height,Aspekt,Alpha;
        GLfloat old_x,old_y,old_Height,old_Alpha;
        GLfloat soll_x,soll_y,soll_Height,soll_Alpha;
        GLint align;
		GLint InAnimation;
		GLint Signal;
        GLint life_time;
		GLint DisplayListArray;
		GLuint TextureArray[512];
        GLint TextItemIndex;
		GLint Horchen;
        GLint lines;

        GLfloat MaxWidth;

};

#define A_EGAL   0
#define A_LINKS  1
#define A_MITTE  2
#define A_RECHTS 3

#define HIDDEN 0.0
#define TRANSPARENT  0.2
#define APPEAR 0.6
#define SELECTED   0.8
#define FULL_VISIBLE 1.0

#define ANIMATION_TIME 100


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

