#include "utils.h"
#include "node.h"
#include <stdlib.h>
#include <time.h>
#include <unordered_map>
#include "cfr.h"

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::rand;
using std::srand;


void train(int iterations){
  //vector<int> cards(1, 4);
  vector<int> cards;
  cards.push_back(1);
  cards.push_back(2);
  cards.push_back(3);
  double util = 0.0; 
  srand(time(NULL));

  Cfr cfr;
  for(int i = 0; i < iterations; i++){
    // Shuffle 
    for(int j = 0; j < cards.size(); j++) {
      int cardInd = rand() % 3;
      int tmp = cards[j];
      cards[j] = cards[cardInd];
      cards[cardInd] = tmp;
    }
    util += cfr.runCFR(cards, "", 1, 1);

  }
  cfr.printStrategy();
}




int main(int argc, char ** argv){
 int iterations = 10000000;
  train(iterations);
}
