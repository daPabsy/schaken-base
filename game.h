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

    pair<int, int> findKing(const zw & kleur) const;

    bool findPosition(const pair<int, int> & p, const vector<pair<int, int>> & toSearch, SchaakStuk * s) const;

    vector<pair<int, int>> checkForKingCheck(const vector<pair<int, int>> & possibleMoves, SchaakStuk * s, const bool king);

    bool checkKing(const int & r, const int & k) const;

    SchaakStuk * checkForPiece(const pair<int, int> & i, const zw & color);

    bool schaakmat(zw kleur);



    bool pat(zw kleur);
    void setStartBord();

    SchaakStuk * getPiece(const int r, const int k) const;
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

    // Zet moving op false --> men is bezig met een SchaakStuk te verplaatsen
    // Zet moving op true --> men is NIET bezig met een SchaakStuk te verplaatsen
    void setMovingAndPieceToMove(bool i, SchaakStuk * s) {
        moving = i;
        pieceToMove = s;
    }

    // Zet moving op false en pieceToMove op nullptr voor volgende stap
    void resetMovingAndPieceToMove() {
        moving = false;
        pieceToMove = nullptr;
    }

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

    void capturedPiece(const pair<int, int> & moveTo) const;

private:

    zw turnToMove; // Wie zijn beurt is het?
    bool moving; // Bezig met een SchaakStuk te verplaatsen?
    SchaakStuk * pieceToMove;

    SchaakStuk * bord[8][8];
};


#endif //SCHAKEN_GAME_H
