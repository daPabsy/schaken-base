//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include "SchaakStuk.h"
using namespace std;


class Game {
// variabelen om de status van het spel/bord te bewaren

public:

    // Constructor van game, moving wordt standaar op false gezet
    Game();
    ~Game();

    bool move(SchaakStuk* s, const pair<int, int> &p); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();

    // TODO
    SchaakStuk* getPiece(const int r, const int k) const;
    void setPiece(const int r, const int k, SchaakStuk * s);
    void setNullptr(int r, int k, SchaakStuk * s);
    void setPawns(int & i);

    // Als moving true is wordt het te verplaatsen SchaakStuk
    // teruggegeven, wanneer dit niet zo is wordt er een nullptr teruggegeven
    SchaakStuk * getMoving() {
        if ( moving ) {
            return pieceToMove;
        }
        return nullptr;
    }

    // Zet moving op false --> men is bezig met een SchaakStuk te verplaatsen
    // Zet moving op true --> men is NIET bezig met een SchaakStuk te verplaatsen
    void setMovingAndPieceToMove(bool i, SchaakStuk * s) {
        moving = i;
        pieceToMove = s;
    }

    void resetMovingAndPieceToMove() {
        moving = false;
        pieceToMove = nullptr;
    }

private:

    // i.v.m. wanneer er verplaatst moet worden
    zw turnToMove;
    bool moving;
    SchaakStuk * pieceToMove;

    SchaakStuk * bord[8][8];
};


#endif //SCHAKEN_GAME_H
