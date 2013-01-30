class Network {
	public:
        Network();
		void Initialisiere();

        GLint TypeNewMSG(); // 0, wenn keine  Nachricht da, sonst Typ

        GLint NewID(char Empfaenger[200]);  //liefert Empfaenger-Id zurueck
        void NachrichtPartnersuche(GLint EmpfaengerId, GLint Spiel, char Name[10]); //Message Dating
		void NachrichtPartnerschaft(GLint EmpfaengerId, char Name[10]);
		void NachrichtKeinePartnerschaft(GLint EmpfaengerId, GLint Zuschauen, GLint Gegner);
		void NachrichtAnfaenger(GLint EmpfaengerId, GLint Wer); //Wer?Ich:Du
		void NachrichtKameraPosition(GLint EmpfaengerId, GLfloat Pos[6]);
		void NachrichtStoss(GLint EmpfaengerId, GLfloat Vektor[2]);
		void NachrichtSpielAbbruch(GLint EmpfaengerId);
		void NachrichtZuschauen(GLint EmpfaengerId, char Name[10]);
		void NachrichtZuschauenAbbruch(GLint EmpfaengerId);
		void NachrichtKugelPositionen(GLint EmpfaengerId, GLfloat Pos[16][3]);

		GLint SenderId;
        GLint Spiel;            //game;
        char GegnerName[10];    //opponents Name
        GLint Zuschauen;        //watch
        GLint ZuschauenGegnerId;    // Watch opponents Id;
        GLint Anfaenger;        //beginners
        GLfloat KameraPos[6];   //camera Position
        GLfloat Stoss[2];       //shock
        char ZuschauerName[10]; //Viewers Name
        GLfloat KugelPos[16][3];    //ball Position

	private:
};

#define NN_PARTNERSUCHE 1
#define NN_PARTNERSCHAFT 2
#define NN_NOPARTNERSCHAFT 3
#define NN_ANFAENGER 4
#define NN_KAMERAPOSITION 5
#define NN_STOSS 6
#define NN_SPIELABBRUCH 7
#define NN_ZUSCHAUEN 8
#define NN_ZUSCHAUENABBRUCH 9
#define NN_KUGELPOSITIONEN 10
