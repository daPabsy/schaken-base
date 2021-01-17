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


    bool promotion(SchaakStuk * s);

    void moveCastle(SchaakStuk * s, const pair<int, int> & p, const zw & color);

    bool threatsCastle(const vector<pair<int, int>> & emptyPositions, const zw & color);


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

    // Veranderen van kleur bij openen nieuw bestand
    void setTurnMoveNew(const zw & color) { turnToMove = color; }


//    // Verkrijg de passage bool
//    bool getPassant() const { return passage; }
//
//    pair<int, int> getPassantPosition() { return passagePosition; }
//
//    // Zet passage
//    void setPassant(const pair<int, int> & p) { passage = true; counter = 1; passagePosition = p; }
//
//    // Reset passage
//    void resetPassant() {
//        if ( counter == 0 ) {
//            passage = false;
//            passagePosition = make_pair(0, 0);
//        }
//        else if ( counter == 1 ) {
//            counter += 1;
//        }
//        else if ( counter == 2) {
//            counter = 0;
//            passage = false;
//            passagePosition = make_pair(0, 0);
//        }
//    }


private:
    zw turnToMove; // Wie zijn beurt is het?
    bool moving; // Bezig met een SchaakStuk te verplaatsen?
    SchaakStuk * pieceToMove; // Te bewegen SchaakStuk tijdens een move

//    bool passage; // Passage?
//    // Wanneer een pion een passage zet wordt de counter op 1 gezet, wanneer de counter op 2 staat wordt de passage gereset
//    int counter;
//    pair<int, int> passagePosition; // Positie van pion die net 2 stappen zette

    SchaakStuk * bord[8][8];
};


#endif //SCHAKEN_GAME_H
