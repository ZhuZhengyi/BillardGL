
class Judge {
	public:
		Judge();
		void BallBall(GLint,GLfloat,GLint,GLfloat);
		void BallBand(GLint,GLfloat,GLint);
		void BallHole(GLint,GLint);
		void NewGame(GLint);
		void NewShot();
		void SetPlayerToShot(GLint);
		void SetFouls(GLint,GLint);
		GLint Decision();

		GLint CorrectBallWithPlay(GLint);
		GLint CorrectBallSunk(GLint);
		GLint CorrectBallSunkHere(GLint[16]);
		GLint ColoredBall(GLint);
		GLint ColoredBallHere(GLint[16]);
		GLint ColoredBallSum(GLint[16]);
		GLint Sum(GLint[16]);

        GLint AfterPlayerShot();
        GLint AfterGroupAllocated();
        GLint AfterSubstantiation();
        GLint AfterFoul(GLint);

	private:
        GLint BandOutsideBeforeBallTouched;
		GLint FirstTouchedBall ;
        GLint FirstTouchedBand;
        GLint FirstSunkBall;
        GLint FirstTouching;
        GLint FirstTouchedBallHeadField;
        GLint FirstTouchedInHeadField;
        GLint BallsInGame[16];
        GLint BallsSunk[16];
        GLint BallsBand[16];
        GLint FoulsPlayer1;
        GLint FoulsPlayer2;
		GLint RefereeDecision;
		GLint PlayerToStock;
		GLint Substantiation;
        GLint RecordChange;
		GLint Foul;
        GLint LageVerbesserungKopffeld;     //Location improve header
		GLint LageVerbesserung;
        GLint NeuAufbauenOderWeiterspielen; //Rebuild Or Next play
        GLint NeuAufbauenOderAchtEinsetzen; //Rebuild Or Eight insertion
        GLint Losts;
        GLint Wins;
        GLint Player1Wins;
        GLint Player2Wins;

        GLint FromHeadField;
        GLint BeginShot; //opening shock
        GLint gameType;
        GLint GroupAllocate;    //分组
        GLint LowestBall;

};

#define YES   1      //TRUE  YES
#define NONE 0      //FALSE NONE

#define PLAYER1 0
#define PLAYER2 1

#define NO 0
#define P1_ALL_P2_HALF 1
#define P1_HALF_P2_ALL 2

#define EIGHT_BALL 8
#define NINE_BALL 9
