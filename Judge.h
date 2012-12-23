
class Judge {
	public:
		Judge();
		void KugelKugel(GLint,GLfloat,GLint,GLfloat);
		void BallBand(GLint,GLfloat,GLint);
		void BallHole(GLint,GLint);
		void NewGame(GLint);
		void NewStoke();
		void SetPlayerToStock(GLint);
		void SetzeFouls(GLint,GLint);
		GLint Entscheidung();

		GLint CorrectBallWithPlay(GLint);
		GLint CorrectBallSunk(GLint);
		GLint CorrectBallSunkHere(GLint[16]);
		GLint ColoredBall(GLint);
		GLint ColoredBallHere(GLint[16]);
		GLint ColoredBallSum(GLint[16]);
		GLint Sum(GLint[16]);

		GLint FrageNachSpielerAmStoss();
		GLint FrageNachGruppenVerteilung();
		GLint FrageNachBegruendung();
		GLint FrageNachFouls(GLint);

	private:
		GLint BandeAusserhalbKopffeldvorKugelBeruehrt;
		GLint FirstTouchedBall ;
		GLint ErsteBeruehrteBande;
		GLint ErsteVersenkteKugel;
		GLint ErsteBeruehrung;
		GLint ErsteBeruehrteKugelImKopffeld;
		GLint ErsteBeruehrungImKopffeld;
		GLint KugelnImSpiel[16];
		GLint KugelnVersenkt[16];
		GLint KugelnAnBande[16];

		GLint FoulsHintereinanderSpieler1;
		GLint FoulsHintereinanderSpieler2;

		GLint SchiedsrichterEntscheidung;

		GLint PlayerToStock;

		GLint Substantiation;

		GLint AufnahmeWechsel;
		GLint Foul;
		GLint LageVerbesserungKopffeld;
		GLint LageVerbesserung;
		GLint NeuAufbauenOderWeiterspielen;
		GLint NeuAufbauenOderAchtEinsetzen;
		GLint Verloren;
		GLint Gewonnen;
		GLint Spieler1Gewonnen;
		GLint Spieler2Gewonnen;


		GLint AusKopffeld;
		GLint Eroeffnungsstoss;
		GLint Game;
		GLint GruppenVerteilung;
		GLint NiedrigsteKugel;

};

#define JA   1      //TRUE  YES
#define NEIN 0      //FALSE NO

#define SPIELER1 0
#define SPIELER2 1

#define KEINE 0
#define S1_GANZE_S2_HALBE 1
#define S1_HALBE_S2_GANZE 2

#define ACHTBALL 8
#define NEUNBALL 9
