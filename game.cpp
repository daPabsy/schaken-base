//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
#include <iostream>
using namespace std;

Game::Game() {}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de juiste plaats toe
void Game::setStartBord() {

    SchaakStuk * null = nullptr; // Maak nullptr aan van SchaakStuk object

    // Zet het schaakbord vol met nullptr's die later vervangen zullen worden met schaakstukken
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            setPiece(i, j, null );
        }
    }

    // Zet alle pionen klaar op het bord
    int i = 0;
    while ( i != 8 ) {
         setPawns(i);
    }

    // Zet witte schaakstukken klaar op schaakbord
    setPiece(0, 0, new Toren(wit));
    setPiece(0, 1, new Paard(wit));
    setPiece(0, 2, new Loper(wit));
    setPiece(0, 3, new Koningin(wit));
    setPiece(0, 4, new Koning(wit));
    setPiece(0, 7, new Loper(wit));
    setPiece(0, 6, new Paard(wit));
    setPiece(0, 5, new Toren(wit));

    // Zet zwarte schaakstukken klaar op schaakbord
    setPiece(7, 0, new Toren(zwart));
    setPiece(7, 1, new Paard(zwart));
    setPiece(7, 2, new Loper(zwart));
    setPiece(7, 3, new Koningin(zwart));
    setPiece(7, 4, new Koning(zwart));
    setPiece(7, 7, new Loper(zwart));
    setPiece(7, 6, new Paard(zwart));
    setPiece(7, 5, new Toren(zwart));


}

// Zet alle pionen klaar op het bord
void Game::setPawns(int &i) {

    setPiece(1, i, new Pion(wit));
    setPiece(6, i, new Pion(zwart));
    i++; // overloop elke plaats waar een pion kan staan

}

// Geeft terug welk schaakstuk op een bepaalde positie op het spelbord staat
SchaakStuk* Game::getPiece(const int r, const int k) {

    return bord[r][k];

}

// Verplaatst een schaakstuk naar de gegeven positie op het spelbord
void Game::setPiece(int r, int k, SchaakStuk* s) {
    //s->position.first = r; // TODO
    //s->position.second = k;
    bord[r][k] = s;
}


// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, const pair<int, int> &p) {

    bool found = false;
    // Itereer over alle geldige zetten
    for ( const pair<int, int> &i : s->geldige_zetten(*this) ) {
        if ( i == p ) {
            // Wanneer gevonden wordt boolean op true gezet en onmiddelijk returnt
            found = true;
            break;
        }
    }
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
