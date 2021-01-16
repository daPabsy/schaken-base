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
    Game();
    ~Game();

    // Alles te maken met het zetten van het startBord
    void setStartBord();
    SchaakStuk * getPiece(const int & r, const int & k) const;
    void setPiece(const int & r, const int & k, SchaakStuk * s);
    void setNullptr(const int & r, const int & k, SchaakStuk * s);
    void setPawns(int & i);


    // Alles te maken met het verplaatsen van een SchaakStuk
    bool move(SchaakStuk* s, const pair<int, int> &p); // Verplaats stuk s naar rij r en kolom k
    void capturedPiece(const pair<int, int> & moveTo) const;


    // Alles te maken met schaak
    bool schaak(const zw & kleur);
    pair<int, int> findKing(const zw & kleur) const;
    bool findPosition(const pair<int, int> & p, const vector<pair<int, int>> & toSearch, SchaakStuk * s) const;
    vector<pair<int, int>> checkForKingCheck(const vector<pair<int, int>> & possibleMoves, SchaakStuk * s);
    bool checkKing(const int & r, const int & k) const;


    // Schaakmat
    bool schaakmat(const zw & kleur);


    // Pat
    bool pat(const zw & kleur);


    vector<pair<int, int>> getThreats(const vector<pair<int, int>> & moves, const zw & color, SchaakStuk * s);



//    // En Passage
//    bool passageCapture(pair<int, int> moveTo, SchaakStuk * s, const zw & color);
//
//    // Verander waarde van passant
//    void setPassant(const pair<int, int> & p) {
//        passant = true; counter = 0; passantPosition = p;
//    }
//
//    // Verkrijg de bool van passant
//    bool getPassantBool() {
//        return passant;
//    }
//
//    // Verkrijg de waarde van passant
//    pair<int, int> & getPassantValue() { return passantPosition; }
//
//    // Reset de passant waarde
//    void resetPassant() {
//        if ( counter == 0 ) {
//            counter = 1;
//        }
//        else if ( counter == 1 ) {
//            counter = 2;
//        }
//        else if ( counter == 2 ) {
//            counter = 0;
//            passant = false;
//            passantPosition = make_pair(0, 0);
//        }
//    }



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

private:
    zw turnToMove; // Wie zijn beurt is het?
    bool moving; // Bezig met een SchaakStuk te verplaatsen?
    SchaakStuk * pieceToMove; // Te bewegen SchaakStuk tijdens een move

//    bool passant; // Staat er een SchaakStuk in een positie om via passant "veroverd" te worden?
//    int counter;
//    pair<int, int> passantPosition; // Positie van SchaakStuk dat "en passant" staat

    SchaakStuk * bord[8][8];
};


#endif //SCHAKEN_GAME_H
