
//void Beleuchtung(GLint,GLint,GLint,GLint,GLint,GLint);

class Lighting {
	public:
		Lighting();
		void Initialisiere(GLint,GLint,GLint,GLint);
        void draw();
	private:
		GLint LightingIndex;
};
