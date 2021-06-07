#ifndef CFR_H_
#define CFR_H_
#include <vector>
#include <string>
#include "node.h"
#include <unordered_map>

double cfr(std::vector<int> cards, std::string history, double p0, double p1);

class Cfr{
  int PASS = 0, BET = 1, NUM_ACTIONS = 2;
  std::unordered_map<std::string, Node> nodeMap; 
public:
  Cfr();
  double runCFR(std::vector<int> cards, std::string history, double p0, double p1);
  void printStrategy();
};


#endif
