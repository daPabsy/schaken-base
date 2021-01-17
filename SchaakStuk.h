//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <chessboard.h>
using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:

    SchaakStuk(zw kleur, bool startPosition): kleur(kleur), startPosition(startPosition) {}

    virtual Piece piece() const=0;      // Deze functie krijg je cadeau
    // Je hebt die nodig om het stuk in de
    // GUI te tekenen
    // Meer info: kijk naar mainwindow.cpp, lijn 27

    zw getKleur() const { return kleur; }

    virtual vector<pair<int, int>> geldige_zetten(Game & game, const bool & kills);

    vector<pair<int, int>> diagonalMoves(Game & game);
    vector<pair<int, int>> straightMoves(Game & game);
    bool checkDimensions(pair<int, int> i);
    bool checkNullptr(SchaakStuk * s);

    // Positie van SchaakStuk wordt opgeslagen in een paar van integers
    pair<int, int> position;

    // Zet de bool startPosition op false
    void setStartPosition() { startPosition = false; }

    // Geeft de waarde van de bool startPosition weer
    bool getStartPosition() { return startPosition; }

private:
    zw kleur;
    bool startPosition; // Staat het SchaakStuk in de startposite?
};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur, bool startPosition):SchaakStuk(kleur, startPosition) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game & game, const bool & kills) override;
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur, bool startPosition):SchaakStuk(kleur, startPosition) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game & game, const bool & kills) override;
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur, bool startPosition):SchaakStuk(kleur, startPosition) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game & game, const bool & kills) override;
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur, bool startPosition):SchaakStuk(kleur, startPosition) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game & game, const bool & kills) override;
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur, bool startPosition):SchaakStuk(kleur, startPosition) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game & game, const bool & kills) override;

    void castle(Game & game, const zw & color, vector<pair<int, int>> & possibleMoves);

    pair<int, int> whiteCastleRight(Game & game, const zw & color);
    pair<int, int> whiteCastleLeft(Game & game, const zw & color);

    pair<int, int> blackCastleRight(Game & game, const zw & color);
    pair<int, int> blackCastleLeft(Game & game, const zw & color);


};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur, bool startPosition):SchaakStuk(kleur, startPosition) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(Game & game, const bool & kills) override;
};

#endif //SCHAKEN_SCHAAKSTUK_H
