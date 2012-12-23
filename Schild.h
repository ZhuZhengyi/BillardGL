
class Scale {
	public:
		Scale();
		void Init();
		void InitLogo();
		void Init(GLint,char[]);
        void InitBuchstabe(GLint,char[]);
		void Init(GLint,char[],char);
		void Init(GLint,char[],char[]);
		void draw();
		void Positioning(GLfloat,GLfloat,GLfloat,GLfloat);
        void PositionFix(GLfloat,GLfloat,GLfloat,GLfloat);
		void Desaktiviere();
		void Angewaehlt();
		void Eingeblendet();
		void VollSichtbar();
        void StartAnimation();
		GLint Animate(GLint);
		GLint MouseButton(int,int,int,int);
		void SetzeZielZustand(GLint);
		void SetSignal(GLint);
		void CopyFrom(Scale);
		GLint SchildIndex;
		GLint SchildTyp;
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
		GLint Zeit;
		GLuint Textur;
};

#define AUSGEBLENDET 0.0
#define TRANSPARENT  0.2
#define EINGEBLENDET 0.6
#define ANGEWAEHLT   0.8
#define VOLLSICHTBAR 1.0

#define ANIMATIONSDAUER 100

extern GLuint LogoTexture;
