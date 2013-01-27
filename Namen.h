// Gibt den Zust"anden Nummern 
// (die Nummern sind egal, aber Namen versteht man besser)

#define START       0          //
#define VIEWING     1          //VIEW
#define AIMING      2          //OBJECTIVES
#define SWING    3          //swing
#define SHOT       4          //shock
#define NEW_WHITE   5          //
#define JUDGEING    6        //refree

// different games
#define EIGHT_BALL     8          //8ballgame
#define NINE_BALL     9          //9ballgame
#define ZUFALL       7          //RANDOM
#define LEER         0          //EMPTY
#define TWO_BALLS   2          //two balls

#define TRAINING_MODE 101      //training gmae
#define TWO_PLAYERS 102    //TWO PLAYER GAME
#define NETWORK_PLAYER 103       //NETWORK GAME
#define COMPUTER_PLAYER 104 //COMPUTER GAME OPPONENT
#define TUTORIAL 105            //

#ifndef _WIN32
#define PATH "/usr/share/BillardGL/"
#endif

#ifndef PATH
#define PATH ""
#endif


