//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"
#include <iostream>
#include <algorithm> // Voor te zoeken in vectoren
using namespace std;

Game::Game() {
    turnToMove = wit; // Wit begint met zetten
    moving = false;
    pieceToMove = nullptr;
}

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
    vector<pair<int, int>> possibleMoves;

    if ( schaak(getTurnMove()) ) {

        possibleMoves = checkForKingCheck(s->geldige_zetten(*this, false), s, checkKing(p.first, p.second)); // Verkrijg geldige zetten als King schaak staat
    }
    else {
        possibleMoves = s->geldige_zetten(*this, false); // Verkrijg geldige zetten als King niet schaak staat
    }

    // Kijk of de zet geldig is
    if ( find(possibleMoves.begin(), possibleMoves.end(), p ) != possibleMoves.end() ) {
        found = true; // Wanneer gevonden kan het SchaakStuk verplaatst worden
        setNullptr(s->position.first, s->position.second, nullptr); // Originele plaats wordt vervangen met nullptr
        capturedPiece(p); // Ander SchaakStuk verovert?
        setPiece(p.first, p.second, s); // Verplaatst SchaakStuk
        setTurnMove(); // Verander van beurt
        cout << "Piece moved!" << endl;
    }
    // Wanneer er geen geldige zet wordt gekozen blijft de huidige kleur aan de beurt
    else {
        cout << "Select a valid move!" << endl;
    }
    // Men is niet meer bezig met verplaatsen en moet dus opnieuw een SchaakStuk selecteren om te verplaatsen
    resetMovingAndPieceToMove();
    return found;
}

// Kijkt na of de positie waar het SchaakStuk naar wilt bewegen een
// SchaakStuk is van de tegenstander en verwijdert deze als nodig
void Game::capturedPiece(const pair<int, int> & moveTo)const {
    if ( getPiece(moveTo.first, moveTo.second) == nullptr ) {
        return;
    }
    else if ( getPiece(moveTo.first, moveTo.second)->getKleur() != turnToMove ) {
        cout << "Captured a piece!" << endl;
        delete getPiece(moveTo.first, moveTo.second); // TODO foutmelding destructor
    }
    return;
}

// Geeft true als koning van de speler die aan de beurt is schaak staat
bool Game::schaak(zw kleur)  {
    bool found = false;

    pair<int, int> king = findKing(kleur); // Zoek de positie van de koning

    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            // Overloop alle SchaakStukken van de tegenstander
            if ( getPiece(i, j) != nullptr && getPiece(i, j)->getKleur() != kleur ) {
                // Is positie van een van de geldige zetten van de tegenstander gelijk aan die van "onze" koning
                    if ( findPosition(king, getPiece(i, j)->geldige_zetten(*this, false), getPiece(i, j)) ) {
                        found = true;
                        break;
                    }

            }
        }
    }
    return found;
}

// Zoek de positie van de koning van de kleur die momenteel aan de beurt is
pair<int, int> Game::findKing(const zw & kleur) const {
    pair<int, int> kingPosition;
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( getPiece(i, j) != nullptr && // Mag geen nullptr zijn anders seg fault
                 getPiece(i, j)->getKleur() == kleur && // Moet van kleur zijn die mom. aan de beurt is
                 getPiece(i, j)->piece().type() == Piece::King ) { // Moet van type King zijn
                kingPosition = make_pair(i, j);
                break;
            }
        }
    }
    return kingPosition;
}

// Zoekt een opgegeven paar van integers (=positie) in een vector van
// paren van integers
bool Game::findPosition(const pair<int, int> & p, const vector<pair<int, int>> & toSearch, SchaakStuk * s) const {
    bool found = false;
    // Itereer over alle paren en zoek de opgegeven positie
    for ( const pair<int, int> & i : toSearch ) {
//        if ( s->piece().type() == 2 ) {
//            cout << "POSITION ENEMY: " << i.first << " " << i.second << endl;
//            if ( getPiece(i.first, i.second) != nullptr && getPiece(i.first, i.second)->getKleur() == getTurnMove() ) {
//                cout << "PIECE: " << getPiece(i.first, i.second)->piece().type() << endl;
//
//            }
//        }
        if ( i == p ) {
            found = true; // Wanneer gevonden zet de returnwaarde op true
            break;
        }
    }
    return found;
}

vector<pair<int, int>> Game::checkForKingCheck(const vector<pair<int, int>> & possibleMoves, SchaakStuk * s, const bool king)  {

    // Originele positie van het SchaakStuk dat we steeds gaan verschuiven
    pair<int, int> originalPosition;
    originalPosition.first = s->position.first;
    originalPosition.second = s->position.second;

    vector<pair<int, int>> newMoves;

    // Verkrijg de kleur die NIET aan de beurt is
    zw color = wit;
    if ( getTurnMove() == wit ) {
        color = zwart;
    }

    for ( const pair<int, int> & i : possibleMoves ) {

        // Verkrijg het SchaakStuk dat we gaan "veroveren"
        SchaakStuk * oldPiece = checkForPiece(i, color);

        // Zet SchaakStuk op een van de mogelijke posities
        setPiece(i.first, i.second, s);

        // Zet een nullptr op orignele positie, anders zijn er bv 2 Kings
        setNullptr(originalPosition.first, originalPosition.second, nullptr);

        if ( schaak(getTurnMove()) ) { // Check of de king nog steeds schaak staat

            cout << "SCHAAK" << endl;

            capturedPiece(i);
            // Verplaatst SchaakStuk wordt terug naar zijn originele plaatst verzet
            setPiece(originalPosition.first, originalPosition.second, s);

            if ( oldPiece == nullptr ) {
                setNullptr(i.first, i.second, oldPiece);
            }
            else {
                // Verplaats oud SchaakStuk terug naar zijn originele plaats
                setPiece(i.first, i.second, oldPiece );
            }
        }

        else {

            cout << "NO SCHAAK" << endl;

            capturedPiece(i);
            newMoves.push_back(i);
            // Verplaatst SchaakStuk wordt terug naar zijn originele plaatst verzet
            setPiece(originalPosition.first, originalPosition.second, s);
            if ( oldPiece == nullptr ) {
                setNullptr(i.first, i.second, oldPiece);
            }
            else {
                // Verplaats oud SchaakStuk terug naar zijn originele plaats
                setPiece(i.first, i.second, oldPiece );
            }
        }

    }
    return newMoves;
}

SchaakStuk * Game::checkForPiece(const pair<int, int> & i, const zw & color) {

    SchaakStuk * oldPiece;

    if ( getPiece(i.first, i.second) == nullptr ) {

        oldPiece = nullptr;
    }
    else {
        if ( getPiece(i.first, i.second)->piece().type() == Piece::Pawn ) {
            oldPiece = new Pion(color);
        }
        else if ( getPiece(i.first, i.second)->piece().type() == Piece::Rook ) {
            oldPiece = new Toren(color);
        }
        else if ( getPiece(i.first, i.second)->piece().type() == Piece::Knight ) {
            oldPiece = new Paard(color);
        }
        else if ( getPiece(i.first, i.second)->piece().type() == Piece::Bishop ) {
            oldPiece = new Loper(color);
        }
        else if ( getPiece(i.first, i.second)->piece().type() == Piece::Queen ) {
            oldPiece = new Koningin(color);
        }
    }
    return oldPiece;
}

bool Game::checkKing(const int & r, const int & k) const {

    if (getPiece(r, k) != nullptr &&
        getPiece(r, k)->getKleur() == getTurnMove() &&
        getPiece(r, k)->piece().type() == Piece::King ) {
        return true;
    }
    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {

    for ( int i = 0; i < 8; i++ ) {

        for ( int i=0; i < 9 )

    }

    return false;
}



// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}




