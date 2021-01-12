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

    bool move(SchaakStuk* s, const pair<int, int> &p); // Verplaats stuk s naar rij r en kolom k

    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();

    SchaakStuk* getPiece(const int r, const int k) const;
    void setPiece(const int r, const int k, SchaakStuk* s);
    void setNullptr(int r, int k, SchaakStuk *s);
    void setPawns(int &i);

private:

    SchaakStuk* bord[8][8];
};


#endif //SCHAKEN_GAME_H
