#include "game.h"
#include <iostream>

using std::cout;
using std::endl;

Game::Game(int battlefieldsize, int armysize): playerOne(armysize, battlefieldsize), playerTwo(armysize, battlefieldsize){
  BATTLEFIELDSIZE = battlefieldsize;
  ARMYSIZE = armysize;
}

void Game::play(int iterations){
  for(int i = 0; i < iterations; i++){
    vector<double> playerOneStrategy = playerOne.getStrategy();
    int playerOneAction = playerOne.getAction(playerOneStrategy);
    vector<double> playerTwoStrategy = playerTwo.getStrategy();
    int playerTwoAction = playerTwo.getAction(playerTwoStrategy);
    playerOne.train(playerOneAction, playerTwoAction);
    playerTwo.train(playerTwoAction, playerOneAction);
  }
  cout << "Player One's avg Strategy: ";
  vector<double> pOneAvgStrat = playerOne.getAvgStrategy();
  for(double prob : pOneAvgStrat) cout << prob << ", ";
  cout << endl;
  cout << "Player Two's avg Strategy: ";
  vector<double> pTwoAvgStrat = playerTwo.getAvgStrategy();
  for(double prob : pTwoAvgStrat) cout << prob << ", ";
  cout << endl;
  playerOne.printPermutations();
}
