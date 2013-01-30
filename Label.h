
class Label {
	public:
		Label();
		void Init();
		void InitLogo();
		void Init(GLint,char[]);
        void InitLetter(GLint,char[]);
		void Init(GLint,char[],char);
		void Init(GLint,char[],char[]);
		void draw();
		void Positioning(GLfloat,GLfloat,GLfloat,GLfloat);
        void PositionFix(GLfloat,GLfloat,GLfloat,GLfloat);
        void Disactive();    //disactive
        void Selected();      //In chooses
        void Eingeblendet();    //
        void FullyVisible();    //
        void StartAnimation();  //
		GLint Animate(GLint);
		GLint MouseButton(int,int,int,int);
		void SetzeZielZustand(GLint);
		void SetSignal(GLint);
		void CopyFrom(Label);
        GLint LabelIndex;
        GLint labelType;
		GLfloat Aspect;
	private:
		GLfloat ax,ay,bx,by;
		GLfloat Alpha;
		GLfloat soll_ax,soll_ay,soll_bx,soll_by;
		GLfloat soll_Alpha;
		GLfloat alt_ax,alt_ay,alt_bx,alt_by;
		GLfloat alt_Alpha;
		GLint InAnimation;
		GLint Signal;
        GLint ElapseTime;
        GLuint Texture;
};

#define HIDDEN 0.0    //HIDDEN
#define TRANSPARENT  0.2    //
#define APPEAR 0.6    //AGREED HIDDEN
#define SELECTED   0.8    //selected
#define FULL_VISIBLE 1.0    //FULL VISIBLE

#define ANIMATION_TIME 100 //ANIMATION TIME

extern GLuint LogoTexture;
