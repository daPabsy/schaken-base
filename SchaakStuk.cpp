//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"
#include "mainwindow.h"
#include <iostream>
using namespace std;

// TODO alles kan wat makkelijker geschreven worden!

// Berekent geldige zetten van een schaakStuk
vector<pair<int, int>> SchaakStuk::geldige_zetten(Game & game, const bool & kills) {
    vector<pair<int, int>> possibleMoves;
    return possibleMoves; // Returnt lege vector
}


// Berekent (een deel van de) geldige zetten van een schaakStuk
// dat rechte bewegingen kan maken
vector<pair<int, int>> SchaakStuk::straightMoves(Game &game) {
    vector<pair<int, int>> possibleMoves;
    // verkrijg de rij en kolom van het SchaakStuk
    int r = this->position.first;
    int k = this->position.second;
    zw color = getKleur(); // color is type van zw enum

    // Naar beneden bewegen
    while ( r != 7 ) {
        r++;
        SchaakStuk * moveTo = game.getPiece(r, k);

        if ( checkNullptr(moveTo)) {
            possibleMoves.emplace_back(r, k);
        }
            // Wanneer het SchaakStuk een ander SchaakStuk van een andere kleur
            // tegenkomt wordt deze toegevoegd aan de mogelijke zetten en dan
            // onmiddelijk wordt de "while" loop gebroken
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
            // Hetzelfde gebeurt voor een SchaakStuk van dezelfde kleur, MAAR
            // hierbij wordt de zet niet toegevoegd
        else {
            break;
        }
    }

    r = this->position.first;
    k = this->position.second;

    // Naar boven bewegen
    while ( r != 0 ) {
        r--; // decrease
        SchaakStuk * moveTo = game.getPiece(r, k);

        if ( checkNullptr(moveTo) ) {
            possibleMoves.emplace_back(r, k);
        }
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
        else {
            break;
        }
    }

    r = this->position.first;
    k = this->position.second;

    // Naar rechts bewegen
    while ( k != 7 ) {
        k++;
        SchaakStuk * moveTo = game.getPiece(r, k);

        // Als moveTo een nullPtr is OF niet dezelfde kleur is het een geldige move
        if ( checkNullptr(moveTo) ) {
            possibleMoves.emplace_back(r, k);
        }
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
        else {
            break;
        }
    }

    r = this->position.first;
    k = this->position.second;

    // Naar links bewegen
    while ( k != 0 ) {
        k--; // decrease
        SchaakStuk * moveTo = game.getPiece(r, k);

        if ( checkNullptr(moveTo) ) {
            possibleMoves.emplace_back(r, k);
        }
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
        else {
            break;
        }
    }
    return possibleMoves;
}

// Berekent (een deel van) de geldige zetten van
// een schaakStuk dat diagonale bewegingen kan maken
vector<pair<int, int>> SchaakStuk::diagonalMoves(Game &game) {
    vector<pair<int, int>> possibleMoves;
    int r = this->position.first;
    int k = this->position.second;
    zw color = getKleur();

    // Naar rechtsBoven verplaatsen
    while (  r != 0 || k != 7 ) { // Mag niet buiten de dimensies geraken
        if ( r == 0 ) {
            break;
        }
        r--;
        k++;
        SchaakStuk * moveTo = game.getPiece(r, k);

        if ( checkNullptr(moveTo) ) {
            possibleMoves.emplace_back(r, k);
        }
            // Wanneer er een SchaakStuk van een andere kleur wordt gevonden
            // wordt deze toegevoegd aan de mogelijke zetten, maar wordt het verder
            // zoeken onmiddelijk gestopt (= SchaakStuk kan er niet over springen)
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
            // SchaakStuk kan niet over een SchaakStuk van dezelfde kleur springen
        else {
            break;
        }
    }

    r = this->position.first;
    k = this->position.second;

    // Naar linksBoven verplaatsen
    while ( r != 0 || k != 0 ) {
        if ( r == 0 || k == 0 ) {
            break;
        }
        r--;
        k--;
        SchaakStuk * moveTo = game.getPiece(r, k);

        if ( checkNullptr(moveTo) ) {
            possibleMoves.emplace_back(r, k);
        }
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
        else {
            break;
        }
    }

    r = this->position.first;
    k = this->position.second;

    // Naar rechtsBeneden verplaatsen
    while ( r != 7 || k != 7 ) {
        r++;
        k++;
        SchaakStuk * moveTo = game.getPiece(r, k);

        if ( checkNullptr(moveTo) ) {
            possibleMoves.emplace_back(r, k);
        }
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
        else {
            break;
        }
    }

    r = this->position.first;
    k = this->position.second;

    // Naar linksBeneden verplaatsen
    while ( r != 7 || k != 0 ) {
        if ( k == 0 ) {
            break;
        }
        r++;
        k--;
        SchaakStuk * moveTo = game.getPiece(r, k);

        if ( checkNullptr(moveTo) ) {
            possibleMoves.emplace_back(r, k);
        }
        else if ( moveTo->getKleur() != color ) {
            possibleMoves.emplace_back(r, k);
            break;
        }
        else {
            break;
        }
    }

    int end = 0;
    for (int i = 0; i < possibleMoves.size(); i++, end++) {
        while ( !checkDimensions(possibleMoves[i]) ) {
            i++;
        }
        if (i >= possibleMoves.size()) {
            break;
        }
        possibleMoves[end] = possibleMoves[i];
    }
    possibleMoves.resize(end);

    return possibleMoves;
}

// Checkt of de mogelijke zet niet buiten de dimensies van het chessBoard valt
bool SchaakStuk::checkDimensions(pair<int, int> i) {
    if ( (i.first < 0) || ( i.first > 7) ||  (i.second < 0) || ( i.second > 7) ) {
        return false;
    }
    return true;
}

// Checkt of de mogelijke zet een nullptr is
bool SchaakStuk::checkNullptr(SchaakStuk * s) {
    if ( s == nullptr ) {
        return true;
    }
    return false;
}

// Geeft een bool terug of een Pion op de originele startpositie staat of niet
bool Pion::startPosition(Game & game) {
    // Kleur van de pion is zwart
    if ( wit == this->getKleur() ) {
        for ( int i = 0; i < 8; i++ ) {
            if ( this == game.getPiece(6, i) && game.getPiece(5, i) == nullptr ) {
                return true;
            }
        }
    }
    // Kleur van de pion is zwart
    for ( int i = 0; i < 8; i++ ) {
        if ( this == game.getPiece(1, i) && game.getPiece(2, i) == nullptr ) {
            return true;
        }
    }
    return false;
}

// Berekent geldige zetten van een Pion
vector<pair<int, int>> Pion::geldige_zetten(Game & game, const bool & kills) {
    vector<pair<int, int>> possibleMoves;

    int fact = 1;
    if ( getKleur() == wit ) {
        fact = -1;
    }

    int r = this->position.first;
    int k = this->position.second;

    // Als de pion op de startpositie staat kan deze onmiddelijk 2 stappen zetten
    // Mag dimensies niet overschrijven + er mag nog geen ander SchaakStuk staan
    if ( 0 <= (r + (2 * fact)) << 7 && startPosition(game) && game.getPiece(r + (2 * fact), k) == nullptr ) {
        if ( !kills ) {
            possibleMoves.emplace_back(r + (2 * fact), k);
        }
    }
    // Als de pion NIET op de startpositie staat kan deze 1 stap verder zetten
    // Er mag weer geen ander SchaakStuk staan
    if ( 0 <= (r + (1 * fact)) && game.getPiece(r + (1 * fact), k) == nullptr ) {
        if ( !kills ) {
            possibleMoves.emplace_back(r + (1 * fact), k);
        }
    }

    // Pion kan ook rechts aanvallen (=SchaakStuk mag niet van dezelfde kleur zijn)
    if ( 0 <= (r + (1 * fact)) << 7 ) {
        SchaakStuk * attackRight = game.getPiece(r + (1 * fact), (k + 1));
        if ( attackRight != nullptr && attackRight->getKleur() != getKleur() ) {
            possibleMoves.emplace_back(r + (1 * fact), (k + 1));
        }
    }

    // Pion kan ook links aanvallen (=SchaakStuk mag niet van dezelfde kleur zijn)
    if ( 0 <= (r + (1 * fact)) << 7 ) {
        SchaakStuk * attackLeft = game.getPiece(r + (1 * fact), (k - 1));
        if ( attackLeft != nullptr && attackLeft->getKleur() != getKleur() ) {
            possibleMoves.emplace_back(r + (1 * fact), (k - 1));
        }
    }

    int end = 0;
    for ( int i = 0; i < possibleMoves.size(); i++, end++ ) {
        while ( !checkDimensions(possibleMoves[i]) ) {
            i++;
        }
        if ( i >= possibleMoves.size() ) {
            break;
        }
        possibleMoves[end] = possibleMoves[i];
    }
    possibleMoves.resize(end);

    return possibleMoves;
}


// Berekent geldige zetten van een Toren
vector<pair<int, int>> Toren::geldige_zetten(Game & game, const bool & kills) {

    vector<pair<int, int>> possibleMoves = straightMoves(game);


    return possibleMoves;

}

// Berekent geldige zetten van een Paard
vector<pair<int, int>> Paard::geldige_zetten(Game & game, const bool & kills) {
    vector<pair<int, int>> possibleMoves;

    // verkrijg de rij en kolom van het Paard
    int r = this->position.first;
    int k = this->position.second;
    zw color = getKleur();

    // Alle mogelijke zetten die een Paard kan uitvoeren
    pair <int, int> move1;
    move1.first = (r - 1); move1.second = (k + 2);
    possibleMoves.push_back(move1);

    pair <int, int> move2;
    move2.first = (r - 2); move2.second = (k - 1);
    possibleMoves.push_back(move2);

    pair <int, int> move3;
    move3.first = (r - 1); move3.second = (k - 2);
    possibleMoves.push_back(move3);

    pair <int, int> move4;
    move4.first = (r + 1); move4.second = (k - 2);
    possibleMoves.push_back(move4);

    pair <int, int> move5;
    move5.first = (r + 2); move5.second = (k - 1);
    possibleMoves.push_back(move5);

    pair <int, int> move6;
    move6.first = (r + 2); move6.second = (k + 1);
    possibleMoves.push_back(move6);

    pair <int, int> move7;
    move7.first = (r + 1); move7.second = (k + 2);
    possibleMoves.push_back(move7);

    pair <int, int> move8;
    move8.first = (r - 2); move8.second = (k + 1);
    possibleMoves.push_back(move8);

    // Wanneer de stap de dimensies overschrijdt OF
    // het SchaakStuk waar men naar wilt verplaatsen heeft dezelfde kleur
    // kan deze stap verwijdert worden uit de geldige zetten
    int end = 0;
    for (int i = 0; i < possibleMoves.size(); i++, end++) {
        while ( !checkDimensions(possibleMoves[i]) ) {
            i++; // Vind een element dat niet verwijdert moet worden
        }
        if (i >= possibleMoves.size()) {
            break;
        }
        possibleMoves[end] = possibleMoves[i]; // Kopieer niet te verwijderen element
    }
    possibleMoves.resize(end); // Alle elementen na de waarde van end worden verwijdert
    // Source StackOverflow

    vector<pair<int, int>> newMoves;
    for ( const pair<int, int> & i : possibleMoves ) {

        if ( checkNullptr(game.getPiece(i.first, i.second)) == true ) {
            newMoves.push_back(i);
        }
        else if ( checkNullptr(game.getPiece(i.first, i.second)) == false &&  game.getPiece(i.first, i.second)->getKleur() != color ) {
            newMoves.push_back(i);
        }

    }

    return newMoves;
}

// Berekent geldige zetten van een Loper
vector<pair<int, int>> Loper::geldige_zetten(Game & game, const bool & kills) {
    vector<pair<int, int>> possibleMoves =  diagonalMoves(game);

    return possibleMoves;
}

// Berekent geldige zetten van een koningin
vector<pair<int, int>> Koningin::geldige_zetten(Game & game, const bool & kills) {
    vector<pair<int, int>> possibleMoves;
    vector<pair<int, int>> straightmoves = straightMoves(game);
    vector<pair<int, int>> diagonalmoves = diagonalMoves(game);

    // toevoegen van 2 vectors gevonden op StackOverflow
    possibleMoves.reserve(straightmoves.size() + diagonalmoves.size()); // Reserveer geheugen voor nieuwe vector
    possibleMoves.insert(possibleMoves.end(), straightmoves.begin(), straightmoves.end());
    possibleMoves.insert(possibleMoves.end(), diagonalmoves.begin(), diagonalmoves.end());

    return possibleMoves;
}

vector<pair<int, int>> Koning::geldige_zetten(Game & game, const bool & kills) {
    vector<pair<int, int>> possibleMoves;
    int r = this->position.first;
    int k = this->position.second;
    zw color = getKleur();

    // Er wordt steeds eerst gecheckt of het een
    // nullptr is zodat dit geen fouten kan opleveren

    // Beweeg naar beneden
    if ( checkNullptr(game.getPiece(r + 1, k)) || game.getPiece(r + 1, k)->getKleur() != color ) {
        possibleMoves.emplace_back(r + 1, k);
    }

    // Beweeg naar rechts
    if ( checkNullptr(game.getPiece(r, k + 1)) || game.getPiece(r, k + 1)->getKleur() != color ) {
        possibleMoves.emplace_back(r, k + 1);
    }

    // Beweeg naar boven
    if ( checkNullptr(game.getPiece(r - 1, k)) || game.getPiece(r - 1, k)->getKleur() != color ) {
        possibleMoves.emplace_back(r - 1, k);
    }

    // Beweeg naar links
    if ( checkNullptr(game.getPiece(r, k - 1)) || game.getPiece(r, k - 1)->getKleur() != color ) {
        possibleMoves.emplace_back(r, k - 1);
    }

    // Beweeg schuinRechtsBeneden
    if ( checkNullptr(game.getPiece(r + 1, k + 1)) || game.getPiece(r + 1, k + 1)->getKleur() != color ) {
        possibleMoves.emplace_back(r + 1, k + 1);
    }

    // Beweeg schuinRechtsBoven
    if ( checkNullptr(game.getPiece(r - 1, k + 1)) || game.getPiece(r - 1, k + 1)->getKleur() != color ) {
        possibleMoves.emplace_back(r - 1, k + 1);
    }

    // Beweeg schuinLinksBoven
    if ( checkNullptr(game.getPiece(r - 1, k - 1)) || game.getPiece(r - 1, k - 1)->getKleur() != color ) {
        possibleMoves.emplace_back(r - 1, k - 1);
    }

    // Beweeg schuinLinksBeneden
    if ( checkNullptr(game.getPiece(r + 1, k - 1)) || game.getPiece(r + 1, k - 1)->getKleur() != color ) {
        possibleMoves.emplace_back(r + 1, k - 1);
    }

    // Wanneer de stap de dimensies van het chessBoard overschrijdt kan deze verwijdert worden
    int end = 0;
    for ( int i = 0; i < possibleMoves.size(); i++, end++ ) {
        while ( !checkDimensions(possibleMoves[i]) ) {
            i++;
        }
        if ( i >= possibleMoves.size() ) {
            break;
        }
        possibleMoves[end] = possibleMoves[i];
    }
    possibleMoves.resize(end);


    return possibleMoves;
}