//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <chessboard.h>
#include <vector>
using namespace std;

class Game;

enum zw{zwart,wit};

class SchaakStuk {
public:
    SchaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Deze functie krijg je cadeau
                                        // Je hebt die nodig om het stuk in de
                                        // GUI te tekenen
                                        // Meer info: kijk naar mainwindow.cpp, lijn 27

    zw getKleur() const { return kleur; }

    virtual vector<pair<int, int>> geldige_zetten(const Game & game);
    bool checkDimensions(const pair<int, int> & i);

    // positie van SchaakStuk
    pair<int, int> position;


private:
    zw kleur;
};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }
    bool startPosition(const Game & game) const;
    vector<pair<int, int>> geldige_zetten(const Game & game) override;
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(const Game & game) override;
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(const Game & game) override;
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(const Game & game) override;
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(const Game & game) override;
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }

    vector<pair<int, int>> geldige_zetten(const Game & game) override;
};

#endif //SCHAKEN_SCHAAKSTUK_H
