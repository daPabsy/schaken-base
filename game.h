//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include "SchaakStuk.h"
using namespace std;

// TODO setters wat op orde zetten

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

    // Verkrijg het te verplaatsen SchaakStuk ALS moving true is
    SchaakStuk * getMoving() const {
        if ( moving ) {
            return pieceToMove;
        }
        return nullptr;
    }

    void setMovingAndPieceToMove(bool i, SchaakStuk * s);

    void resetMovingAndPieceToMove();

    // Verkrijg wies beurt het is
    zw getTurnMove() const { return turnToMove; }

    // Verander wies beurt het is
    void setTurnMove() {
        if ( getTurnMove() == zwart ) {
            turnToMove = wit;
            return;
        }
        turnToMove = zwart;
    }

private:

    zw turnToMove;
    bool moving;
    SchaakStuk * pieceToMove;

    SchaakStuk * bord[8][8];
};


#endif //SCHAKEN_GAME_H
