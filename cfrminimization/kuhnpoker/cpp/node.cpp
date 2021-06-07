#include "utils.h"
#include "node.h"
#include <iostream>
using std::cout;
using std::endl;

Node::Node() {
  for(int i = 0; i < NUM_ACTIONS; i++){
    regretSum.push_back(0.0);
    strategy.push_back(0.0);
    strategySum.push_back(0.0);
  }
}

vector<double> Node::getStrategy(double realizationWeight) {
  double normalizingSum = 0;
  for(int a = 0; a < NUM_ACTIONS; a++){
    strategy[a] = regretSum[a] > 0 ? regretSum[a] : 0;
    normalizingSum += strategy[a];
  }
  for(int a = 0; a < NUM_ACTIONS; a++){
    if(normalizingSum > 0)
      strategy[a] /= normalizingSum;
    else
      strategy[a] = 1.0 / NUM_ACTIONS;
    strategySum[a] += realizationWeight * strategy[a];
  }
  return strategy;
} 

vector<double> Node::getAverageStrategy(){
  vector<double> avgStrategy;
  avgStrategy.push_back(0.0);
  avgStrategy.push_back(0.0);
  double normalizingSum = 0.0;
  for(int a = 0; a < NUM_ACTIONS; a++){
    normalizingSum += strategySum[a];
  }
  for(int a = 0; a < NUM_ACTIONS; a++){
    if(normalizingSum > 0){
      avgStrategy[a] = strategySum[a] / normalizingSum;
    }
    else {
      avgStrategy.push_back(1.0 / NUM_ACTIONS);
    }
  }
  return avgStrategy;
}

string Node::toString() {
  vector<double> avgStrategy = getAverageStrategy();
  string avgStratString = vec_to_string(avgStrategy);
  return infoset + ": " + avgStratString;
}
