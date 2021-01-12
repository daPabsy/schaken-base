//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include <game.h>
using namespace std;

// Berekent geldige zetten van een schaakstuk
vector<pair<int, int>> SchaakStuk::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    return possibleMoves; // Returnt lege vector
}

// Berekent geldige zetten van een Pion
vector<pair<int, int>> Pion::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    int fact = 1;
    if ( getKleur() == zwart ) {
        fact = -1;
    }
    int r = this->position.first;
    int k = this->position.second;
    possibleMoves.emplace_back((r+1)*fact, (r+2)*fact );

    return possibleMoves;

}

// Berekent geldige zetten van een Toren
vector<pair<int, int>> Toren::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;

    // verkrijg de rij en kolom van de Toren
    int r = this->position.first;
    int k = this->position.second;
    zw color = getKleur(); // color is type van zw enum

    while ( r != 7 ) {
        r++;
        SchaakStuk * moveTo = game.getPiece(r, k);

        // Als moveTo een nullPtr is OF niet dezelfde kleur is het een geldige move
        if ( moveTo == nullptr || moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
        }
        else {
            continue;
        }

    }

    while ( r != 0 ) {
        r--; // decrease
        SchaakStuk * moveTo = game.getPiece(r, k);

        // Als moveTo een nullPtr is OF niet dezelfde kleur is het een geldige move
        if ( moveTo == nullptr || moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
        }
        else {
            continue;
        }

    }

    while ( k != 0 ) {
        k++; // decrease
        SchaakStuk * moveTo = game.getPiece(r, k);

        // Als moveTo een nullPtr is OF niet dezelfde kleur is het een geldige move
        if ( moveTo == nullptr || moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
        }
        else {
            continue;
        }

    }

    while ( k != 0 ) {
        k--; // decrease
        SchaakStuk * moveTo = game.getPiece(r, k);

        // Als moveTo een nullPtr is OF niet dezelfde kleur is het een geldige move
        if ( moveTo == nullptr || moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
        }
        else {
            continue;
        }

    }

    return possibleMoves;




}

vector<pair<int, int>> Paard::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    return possibleMoves;
}


vector<pair<int, int>> Loper::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    return possibleMoves;
}

vector<pair<int, int>> Koning::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    return possibleMoves;
}

vector<pair<int, int>> Koningin::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    return possibleMoves;
}