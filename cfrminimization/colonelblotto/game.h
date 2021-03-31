#ifndef GAME_H
#define GAME_H
#include "player.h"

class Game {
  private:
    Player playerOne;
    Player playerTwo;
    int BATTLEFIELDSIZE;
    int ARMYSIZE;
  public:
    Game(int battlefieldSize, int armySize);
    void play(int iterations);
};


#endif
