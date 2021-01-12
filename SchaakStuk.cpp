//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"
using namespace std;

vector<pair<int, int>> SchaakStuk::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    return possibleMoves;
}

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

vector<pair<int, int>> Toren::geldige_zetten(const Game &game) {
    vector<pair<int, int>> possibleMoves;
    int r = this->position.first;
    int k = this->position.second;
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