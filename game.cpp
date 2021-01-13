//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
#include <iostream>
#include <algorithm> // Voor te zoeken in vectoren
using namespace std;

Game::Game() {}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {

    SchaakStuk * null = nullptr; // Maak nullptr aan van SchaakStuk object

    // Zet het schaakbord vol met nullptr's die later vervangen zullen worden met schaakstukken
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            setNullptr(i, j, null );
        }
    }

    // Zet alle pionen klaar op het bord
    int i = 0;
    while ( i != 8 ) {
         setPawns(i);
    }

    // Zet witte schaakstukken klaar op schaakbord
    setPiece(0, 0, new Toren(zwart));
    setPiece(0, 1, new Paard(zwart));
    setPiece(0, 2, new Loper(zwart));
    setPiece(0, 3, new Koningin(zwart));
    setPiece(0, 4, new Koning(zwart));
    setPiece(0, 5, new Loper(zwart));
    setPiece(0, 6, new Paard(zwart));
    setPiece(0, 7, new Toren(zwart));

    // Zet zwarte schaakstukken klaar op schaakbord
    setPiece(7, 0, new Toren(wit));
    setPiece(7, 1, new Paard(wit));
    setPiece(7, 2, new Loper(wit));
    setPiece(7, 3, new Koningin(wit));
    setPiece(7, 4, new Koning(wit));
    setPiece(7, 5, new Loper(wit));
    setPiece(7, 6, new Paard(wit));
    setPiece(7, 7, new Toren(wit));


}

// Zet alle pionen klaar op het bord
void Game::setPawns(int &i) {

    setPiece(1, i, new Pion(zwart));
    setPiece(6, i, new Pion(wit));
    i++; // overloop elke plaats waar een pion kan staan

}


// Geeft terug welk schaakstuk op een bepaalde positie op het spelbord staat
SchaakStuk* Game::getPiece(const int r, const int k) const {
    return bord[r][k];

}

// Verplaatst een schaakstuk naar de gegeven positie op het spelbord
void Game::setPiece(int r, int k, SchaakStuk* s) {
    s->position.first = r;
    s->position.second = k;
    bord[r][k] = s;
}

// Verplaatst een nullptr naar de gegeven positie op het spelbord
void Game::setNullptr(int r, int k, SchaakStuk* s) {
    bord[r][k] = s;
}


// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk * s, const pair<int, int> & p) {
    bool found = false;
    vector<pair<int, int>> possibleMoves = s->geldige_zetten(*this); // Verkrijg geldige zetten
    cout << "MOVETO: " << p.first << " " << p.second << endl;
    cout << "MOVEFROM: " << s->position.first << " " << s->position.second << endl;
    cout << "POSSIBLE MOVES: " << endl;
    for ( int i = 0; i < possibleMoves.size(); i++ ) {
        cout << possibleMoves[i].first << " " << possibleMoves[i].second << endl;
    }

    if ( find(possibleMoves.begin(), possibleMoves.end(), p ) != possibleMoves.end() ) {
        found = true;
        setNullptr(s->position.first, s->position.second, nullptr);
        setPiece(p.first, p.second, s);
        cout << "Piece moved!" << endl;
    }
    resetMovingAndPieceToMove();
    return found;
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}
