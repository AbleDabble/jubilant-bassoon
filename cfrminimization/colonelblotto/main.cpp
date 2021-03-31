#include <iostream>
#include <stdlib.h>
#include "player.h"
#include "game.h"
using std::cout;
using std::endl;
int main() {
  cout << "Sometimes my genius, it generates its own gravity" << endl;
  Game game = Game(3, 5);
  game.play(50000);
}
