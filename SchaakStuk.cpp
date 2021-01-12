//  Student: Deputter Pablo
//  Rolnummer: s0205440
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "game.h"
using namespace std;


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
