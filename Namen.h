// Gibt den Zust"anden Nummern 
// (die Nummern sind egal, aber Namen versteht man besser)

#define START        0          //
#define BETRACHTEN   1          //VIEW
#define ZIELEN       2          //OBJECTIVES
#define AUSHOLEN     3          //reach back
#define STOSS        4          //shock
#define WEISSNEU     5          //
#define SCHIEDSRICHTER 6        //refree

// Verschiedene Spiele different games
#define ACHTBALL     8          //8ballgame
#define NEUNBALL     9          //9ballgame
#define ZUFALL       7          //RANDOM
#define LEER         0          //EMPTY
#define ZWEIBAELLE   2

#define TRAININGSSPIEL 101      //training gmae
#define ZWEISPIELERSPIEL 102    //TWO PLAYER GAME
#define NETZWERKSPIEL 103       //NETWORK GAME
#define COMPUTERGEGNERSPIEL 104 //COMPUTER GAME OPPONENT
#define TUTORIAL 105            //

#ifndef _WIN32
#define PFAD "/usr/share/BillardGL/"
#endif

#ifndef PFAD
#define PFAD ""
#endif


