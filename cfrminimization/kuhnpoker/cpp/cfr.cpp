#include "cfr.h"
#include "node.h"
#include <iostream>

using std::cout;
using std::endl;


Cfr::Cfr(){

}


double Cfr::runCFR(vector<int> cards, string history, double p0, double p1) {
  int plays = history.length(); 
  int player = plays % 2;
  int opponent = 1 - player;
  // Return payoff For termainal State HERE
  if(plays > 1) {
    bool terminalPass = history[plays - 1] == 'p';
    bool doubleBet = history.substr(history.length() - 2, 2) == "bb" ? true : false;
    bool isPlayerCardHigher = cards[player] > cards[opponent];
    if(terminalPass){
      if(history == "pp"){
        return isPlayerCardHigher ? 1 : -1;
      }
      else {
        return 1;
      }
    }
    else if(doubleBet) {
      return isPlayerCardHigher ? 2 : -2;
    }
  }
  string infoset = std::to_string(cards[player]) + history;
  // <Get Information set node or create if non-existant>
  Node& node = nodeMap[infoset];
  node.infoset = infoset;
  // <For each action recursively call cfr with additional history and probability>
  vector<double> strategy = node.getStrategy(player == 0 ? p0 : p1);
  double util[2];
  double nodeUtil = 0;
  for(int a = 0; a < NUM_ACTIONS; a++){
    string nextHistory = history + (a == 0 ? "p" : "b");
    util[a] = player == 0 
      ? - runCFR(cards, nextHistory, p0 * strategy[a], p1)
      : - runCFR(cards, nextHistory, p0, p1 * strategy[a]);
    nodeUtil += strategy[a] * util[a];
  }
  // <For each action, compute and accumulate counterfactual regret>
  for(int a = 0; a < NUM_ACTIONS; a++){
    double regret = util[a] - nodeUtil;
    node.regretSum[a] += (player == 0 ? p0 : p1) * regret;
  }
  return nodeUtil; 
}

void Cfr::printStrategy(){
  for(auto it = nodeMap.begin(); it != nodeMap.end(); it++){
    string out = it->second.toString();
    cout << out << endl;
  }
}


