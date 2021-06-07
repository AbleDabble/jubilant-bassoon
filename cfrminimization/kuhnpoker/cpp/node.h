#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <iostream>
#include <vector>


using std::string;
using std::vector;

class Node {
  int PASS = 0, BET = 1, NUM_ACTIONS = 2;
public:
  Node(); 
  string infoset;
  vector<double> getStrategy(double realizationWeight); 
  vector<double> getAverageStrategy();
  string toString();
  vector<double> regretSum, strategy, strategySum; 
};

#endif
