#include <iostream>
#include <stdlib.h>
#include "player.h"
#include "game.h"
using std::cout;
using std::endl;
using std::rand;

int main() {
  // cout << "hello world\n" << endl;
  Game game = Game(3, 5);
  game.play(50000);
}
