#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Chosen.h"
#include "Judge.h"

Judge::Judge() {
	//
    Substantiation=0;
}

void Judge::NewGame(GLint _Spiel){
	//printf(" Schiedsrichter: NeuesSpiel %i\n",_Spiel);

    gameType=_Spiel;

    BeginShot=YES;
    FromHeadField=YES;        //From header field
    GroupAllocate=NO;
    FoulsPlayer1=0;
    FoulsPlayer2=0;

    RecordChange=NONE;
    Foul=NONE;
    LageVerbesserungKopffeld=NONE;
    LageVerbesserung=NONE;
    NeuAufbauenOderWeiterspielen=NONE;
    NeuAufbauenOderAchtEinsetzen=NONE;
    Player1Wins=NONE;
    Player2Wins=NONE;

    PlayerToStock=((rand()/(RAND_MAX+0.0))>.5)?1:0;

    if (gameType==EIGHT_BALL) {
		for (GLint i=0;i<16;i++) {
            BallsInGame[i]=YES;
		}
	} 
    if (gameType==NINE_BALL) {
		for (GLint i=0;i<10;i++) {
            BallsInGame[i]=YES;
		}
		for (GLint i2=10;i2<16;i2++) {
            BallsInGame[i2]=NONE;
		}    
	} 
}

void Judge::NewShot(){
	//printf(" Schiedsrichter: NeuerStoss\n");

    RefereeDecision=-1;

    FirstTouchedBall =0;
    FirstTouchedBand=0;
    FirstSunkBall=0;
    FirstTouching=0;
    FirstTouchedBallHeadField=NONE;
    FirstTouchedInHeadField=NONE;

    Substantiation = 0;

    BandOutsideBeforeBallTouched = NONE;

	for (GLint i=0;i<16;i++) {
        if (BallsSunk[i]) {BallsInGame[i]=NONE;}
        BallsSunk[i]=NONE;
        BallsBand[i]=NONE;
	}

    if (RecordChange) {
        PlayerToStock=1-PlayerToStock;
	}

    RecordChange=NONE;
    Foul=NONE;
    LageVerbesserungKopffeld=NONE;      //Situation improving header
    LageVerbesserung=NONE;              //Situation improving
    NeuAufbauenOderWeiterspielen=NONE;  //Rebuild Or Next play
    NeuAufbauenOderAchtEinsetzen=NONE;  //Rebuild Or Eight insertion
    Losts=NONE;
    Wins=NONE;
    Player1Wins=NONE;
    Player2Wins=NONE;

    if (gameType==NINE_BALL) {
		for (GLint i2=9;i2>0;i2--) {
            if (BallsInGame[i2]) {
                LowestBall=i2;
			}
		}
	}


	//printf(" Eroeffnungsstoss : %i\n",Eroeffnungsstoss);
	//printf(" SpielerAmStoss   : %i\n",SpielerAmStoss);
	//printf(" Spiel            : %i\n",Spiel);
	//printf(" GruppenVerteilung: %i\n",GruppenVerteilung);
    //printf(" NiedrigsteBall  : %i\n",NiedrigsteBall);

}

void Judge::BallBall(GLint,GLfloat,
        GLint Ball2,GLfloat Ball2x){
    if (!FirstTouchedBall ) {
        FirstTouchedBall =Ball2;
        if (Ball2x<-63.5) {
            FirstTouchedBallHeadField=YES;
		}
	}
}

void Judge::BallBand(GLint Ball,GLfloat Ballx,
		GLint Bande){
    BallsBand[Ball]=YES;

    if (!FirstTouchedBall  && ((Bande==20) ||
                (Bande==21) && (Ballx<-63.5) ||
                (Bande==23) && (Ballx<-63.5))) {
        BandOutsideBeforeBallTouched = YES;
	}
}

void Judge::BallHole(GLint Ball,GLint){
    BallsSunk[Ball]=YES;

    if (!FirstSunkBall) {
        FirstSunkBall=Ball;
	}
}


GLint Judge::Decision(){

    if (RefereeDecision==-1) {

        if (BeginShot) {
            //printf("check %i %i\n",FarbigeBallDabei(BallnVersenkt),FarbigeBallSumme(BallnAnBande));
            if (!ColoredBallHere(BallsSunk) &&
                    ColoredBallSum(BallsBand)<4) {
                Foul = YES;
                Substantiation=450;
				//printf("Foul kein gescheiter eroeff\n");
                NeuAufbauenOderWeiterspielen = YES;
				//printf("NeuAufbauenOderWeiterspielen kein gescheiter eroeff\n");
			}
            if ((ColoredBallHere(BallsSunk) ||
                        (ColoredBallSum(BallsBand)>=4)) &&
                    BallsSunk[0]) {
                Foul = YES;
                if (!Substantiation) Substantiation=451;
				//printf("Foul weiss bei eroff versenkt\n");
                if (gameType==EIGHT_BALL) {
                    LageVerbesserungKopffeld = YES;
					//printf("LageVerbesserungKopffeld weiss bei eroff versenkt\n");
				}
			}
		}

        if (!FirstTouchedBall ) {
            Foul=YES;
            if (!Substantiation) Substantiation=452;
		}

        if (!CorrectBallWithPlay(FirstTouchedBall )) {
            Foul = YES;
            if (!Substantiation) Substantiation=453;
			//printf("Foul keine korrekte kugel angespielt\n");
		}

        if (CorrectBallWithPlay(FirstTouchedBall ) &&
                !CorrectBallSunkHere(BallsSunk)) {
            RecordChange = YES;
			//printf("AufnahmeWechsel nix gescheites versenkt\n");
            if (!Sum(BallsBand)) {
                Foul = YES;
                if (!Substantiation) Substantiation=454;
				//printf("Foul nix gescheites versenkt, keine Bande\n");
			}
		} 

        if (FromHeadField &&
                FirstTouchedBallHeadField &&
                !BandOutsideBeforeBallTouched) {
            Foul = YES;
            if (!Substantiation) Substantiation=455;
			//printf("Foul im kopff angespielt\n");
		}

        if (! BeginShot && BallsSunk[0]) {
            Foul = YES;
			//printf("Foul weiss versenkt\n");
            if (!Substantiation) Substantiation=456;
            LageVerbesserung = YES;
			//printf("LageVerbesserung weiss bei eroeff1\n");
		}

		if (Foul) {
            RecordChange = YES;
			if (!LageVerbesserungKopffeld) {
                LageVerbesserung = YES;
			}
			//printf("AufnahmeWechsel wegen Foul\n");
		}

        if (gameType==EIGHT_BALL) {

            if (BeginShot && BallsSunk[8]) {
                NeuAufbauenOderAchtEinsetzen = YES;
                BallsSunk[8]=NONE;
                BallsInGame[8]=YES;
				//printf("NeuAufbauenOderAchtEinsetzen 8 bei eroeff vers\n");
			}	

			if (NeuAufbauenOderAchtEinsetzen) {
                NeuAufbauenOderWeiterspielen=NONE;
			}

            if (BallsSunk[8] && !CorrectBallSunk(8) && !BeginShot) {
                Losts = YES;
				//printf("Verloren 8\n");
			}

            if (FirstTouchedBall ==8 && !CorrectBallWithPlay(8)){
                LageVerbesserung = YES;
			}

            if (BallsSunk[8] && CorrectBallSunk(8) && !Foul) {
                Wins = YES;
				//printf("Gewonnen\n");
			}

			if (!Foul && //Gruppenbestimung
                    !GroupAllocate &&
                    !BeginShot &&
                    FirstSunkBall &&
                    FirstTouchedBall  != 8 &&
                    FirstSunkBall != 8) {
                if ((PlayerToStock == PLAYER1) &&
                        (FirstSunkBall < 8) ||
                        (PlayerToStock == PLAYER2) &&
                        (FirstSunkBall > 8)) {
                    GroupAllocate = P1_ALL_P2_HALF;
                    //printf("Gruppenverteilung:  P1_ALL_P2_HALF\n");
				}
                if ((PlayerToStock == PLAYER1) &&
                        (FirstSunkBall > 8) ||
                        (PlayerToStock == PLAYER2) &&
                        (FirstSunkBall < 8)) {
                    GroupAllocate = P1_HALF_P2_ALL;
                    //printf("Gruppenverteilung:  P1_HALF_P2_ALL\n");
				}      
			}
		}

        if (gameType==NINE_BALL) {
            if (Foul && BallsSunk[9]) {
                NineChosen();
                BallsSunk[9]=NONE;
                BallsInGame[9]=YES;
			}

			if (Foul) {
                if (PlayerToStock==PLAYER1) {
                    FoulsPlayer1+=1;
				} else {
                    FoulsPlayer2+=1;
				}
			} else {
                if (PlayerToStock==PLAYER1) {
                    FoulsPlayer1=0;
				} else {
                    FoulsPlayer2=0;
				}
			}

            if ((PlayerToStock==PLAYER1) &&
                    (FoulsPlayer1 == 3) ||
                    (PlayerToStock==PLAYER2) &&
                    (FoulsPlayer2 == 3)) {
                Losts = YES;
				//printf("Verloren durch drei Fouls hintereinander\n");
			}

            if (BallsSunk[9] && !Foul) {
                Wins = YES;
				//printf("Gewonnen\n");
			}
		}

        BeginShot = NONE;
        FromHeadField = NONE;

        if (Wins) {
            if (PlayerToStock==PLAYER1) {
                Player1Wins=YES;
			} else {
                Player2Wins=YES;
			}
		} 
        if (Losts){
            if (PlayerToStock==PLAYER1) {
                Player2Wins=YES;
			} else {
                Player1Wins=YES;
			}
		}

        RefereeDecision=(RecordChange |
				(Foul * 2) |
				(LageVerbesserungKopffeld * 4) |
				(LageVerbesserung * 8) |
				(NeuAufbauenOderWeiterspielen * 16) |
				(NeuAufbauenOderAchtEinsetzen * 32) |
                (Player1Wins * 64) |
                (Player2Wins * 128));

		//printf("SchiedsrichterEntscheidung   :%i\n",SchiedsrichterEntscheidung);
		//printf("AufnahmeWechsel              :%i\n",AufnahmeWechsel);
		//printf("Foul                         :%i\n",Foul);
		//printf("LageVerbesserungKopffeld     :%i\n",LageVerbesserungKopffeld);
		//printf("LageVerbesserung             :%i\n",LageVerbesserung);
		//printf("NeuAufbauenOderWeiterspielen :%i\n",NeuAufbauenOderWeiterspielen);
		//printf("NeuAufbauenOderAchtEinsetzen :%i\n",NeuAufbauenOderAchtEinsetzen);
		//printf("Verloren                     :%i\n",Verloren);
		//printf("Gewonnen                     :%i\n",Gewonnen);

	}

    return RefereeDecision;

}

GLint Judge::CorrectBallWithPlay(GLint Ball){
    switch (gameType) {
        case EIGHT_BALL: {
           if (GroupAllocate == NO && Ball != 8 ) {
               return YES;
           }
           if (GroupAllocate == P1_ALL_P2_HALF) {
               if (PlayerToStock == PLAYER1) {
                   if ((Ball) < 8 ||
                           (!BallsInGame[1] &&
                            !BallsInGame[2] &&
                            !BallsInGame[3] &&
                            !BallsInGame[4] &&
                            !BallsInGame[5] &&
                            !BallsInGame[6] &&
                            !BallsInGame[7] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
               if (PlayerToStock == PLAYER2) {
                   if (Ball > 8 ||
                           (!BallsInGame[9] &&
                            !BallsInGame[10] &&
                            !BallsInGame[11] &&
                            !BallsInGame[12] &&
                            !BallsInGame[13] &&
                            !BallsInGame[14] &&
                            !BallsInGame[15] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
           }
           if (GroupAllocate == P1_HALF_P2_ALL) {
               if (PlayerToStock == PLAYER2) {
                   if (Ball < 8 ||
                           (!BallsInGame[1] &&
                            !BallsInGame[2] &&
                            !BallsInGame[3] &&
                            !BallsInGame[4] &&
                            !BallsInGame[5] &&
                            !BallsInGame[6] &&
                            !BallsInGame[7] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
               if (PlayerToStock == PLAYER1) {
                   if (Ball > 8 ||
                           (!BallsInGame[9] &&
                            !BallsInGame[10] &&
                            !BallsInGame[11] &&
                            !BallsInGame[12] &&
                            !BallsInGame[13] &&
                            !BallsInGame[14] &&
                            !BallsInGame[15] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
           }
        } break;
        case NINE_BALL:
        {
           if (Ball==LowestBall) {
               return YES;
           }
        } break;
    }
    return NONE;
}

GLint Judge::CorrectBallSunk(GLint Ball){
    switch (gameType) {
        case EIGHT_BALL: {
           if (GroupAllocate == NO && Ball != 8 ) {
               return YES;
           }
           if (GroupAllocate == P1_ALL_P2_HALF) {
               if (PlayerToStock == PLAYER1) {
                   if (Ball < 8 ||
                           (!BallsInGame[1] &&
                            !BallsInGame[2] &&
                            !BallsInGame[3] &&
                            !BallsInGame[4] &&
                            !BallsInGame[5] &&
                            !BallsInGame[6] &&
                            !BallsInGame[7] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
               if (PlayerToStock == PLAYER2) {
                   if (Ball > 8 ||
                           (!BallsInGame[9] &&
                            !BallsInGame[10] &&
                            !BallsInGame[11] &&
                            !BallsInGame[12] &&
                            !BallsInGame[13] &&
                            !BallsInGame[14] &&
                            !BallsInGame[15] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
           }
           if (GroupAllocate == P1_HALF_P2_ALL) {
               if (PlayerToStock == PLAYER2) {
                   if (Ball < 8 ||
                           (!BallsInGame[1] &&
                            !BallsInGame[2] &&
                            !BallsInGame[3] &&
                            !BallsInGame[4] &&
                            !BallsInGame[5] &&
                            !BallsInGame[6] &&
                            !BallsInGame[7] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
               if (PlayerToStock == PLAYER1) {
                   if (Ball > 8 ||
                           (!BallsInGame[9] &&
                            !BallsInGame[10] &&
                            !BallsInGame[11] &&
                            !BallsInGame[12] &&
                            !BallsInGame[13] &&
                            !BallsInGame[14] &&
                            !BallsInGame[15] &&
                            Ball == 8)) {
                       return YES;
                   }
               }
           }
       } break;
		case NINE_BALL: {
                           return YES;
					   } break;
	}
    return NONE;
}

GLint Judge::CorrectBallSunkHere(GLint Ball[16]){
    GLint Dabei=NONE;
	for (GLint i=0;i<16;i++) {
        if (Ball[i]) {
            Dabei|=CorrectBallSunk(i);
		}
	}
	return Dabei;
}

GLint Judge::ColoredBall(GLint Ball){
    if (gameType==EIGHT_BALL) {
        if (0<Ball && Ball<8 || 8<Ball && Ball<16) {
            return YES;
		}
	}
    if (gameType==NINE_BALL) {
        if (0<Ball && Ball<10){
            return YES;
		}
	}
    return NONE;
}

GLint Judge::ColoredBallHere(GLint Ball[16]){
    GLint Dabei=NONE;
	for (GLint i=0;i<16;i++) {
        if (Ball[i]) {
            Dabei|=ColoredBall(i);
		}
	}
	return Dabei;
}

GLint Judge::ColoredBallSum(GLint Ball[16]){
    GLint S=NONE;
	for (GLint i=0;i<16;i++) {
        if (Ball[i]) {
            S+=ColoredBall(i);
		}
	}
	return S;
}

GLint Judge::Sum(GLint Ball[16]){
	GLint S=0;
	for (GLint i=0;i<16;i++) {
        S+=Ball[i];
	}
	return S;
}

//Question After players at kick
GLint Judge::AfterPlayerShot(){
    if (RecordChange) { //To measure change
        return 1-PlayerToStock;
	}
    return PlayerToStock;
}

//Question After distribution groups
GLint Judge::AfterGroupAllocated(){
    return GroupAllocate;
}

//Question After Substantiation
GLint Judge::AfterSubstantiation(){
    return Substantiation;
}

//Question After Fouls
GLint Judge::AfterFoul(GLint player){
    if (player==PLAYER1) {
        return FoulsPlayer1;
	}
    if (player==PLAYER2) {
        return FoulsPlayer2;
	}
	return 0;
}

void Judge::SetPlayerToShot(GLint player) {
    PlayerToStock=player;
}

void Judge::SetFouls(GLint player,GLint Fouls) {
    if (player==PLAYER1) {
        FoulsPlayer1=Fouls;
	} else {
        FoulsPlayer2=Fouls;
	}
}
