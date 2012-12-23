
//void Beleuchtung(GLint,GLint,GLint,GLint,GLint,GLint);

class Lighting {
	public:
		Lighting();
		void Init(GLint,GLint,GLint,GLint);
        void draw();
	private:
		GLint LightingIndex;
};
