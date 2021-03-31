#include <iostream>
#include <stdlib.h>
#include "player.h"
#include "string"
#include <math.h>
#include <time.h>

using std::cout;
using std::endl;
using std::rand;
using std::vector;
using std::string;

void printArr(int *, int, string);
void printVec(vector<int>, string);

Player::Player(int armySize, int battlefieldSize){
  this->BATTLEFIELDSIZE = battlefieldSize;
  this->ARMYSIZE = armySize;
  srand(time(NULL));
  createPureStrategies();
  for(int i = 0; i < permutations.size(); i++) {regretSum.push_back(0); strategySum.push_back(0);}
}

void Player::createPureStrategies(){
  vector<int> elements;
  for(int i = 0; i < BATTLEFIELDSIZE; i++){
    elements.push_back(0);
  }
  for(int i = 1; i < ARMYSIZE + 1; i++){
    int additions = ARMYSIZE / i;
    for(int j = 0; j < additions && j < BATTLEFIELDSIZE; j++)
      elements.push_back(i);
  }
  createPermutations(elements, BATTLEFIELDSIZE);
  return;
}

int Player::sum(vector<int> permutation){
  int sum = 0;
  for(int v : permutation){
    sum += v;
  }
  return sum;
}

double Player::sum(vector<double> vec){
  double sum;
  for(double v : vec) sum += v;
  return sum;
}

vector<double> Player::getStrategy(){
  double normalizingSum = 0;
  vector<double> strategy;
  for(int i = 0; i < regretSum.size(); i++)
    regretSum[i] > 0 ? strategy.push_back(regretSum[i]) : strategy.push_back(0);
  normalizingSum = sum(strategy);
  if(int(normalizingSum) > 0){
    for(int i = 0; i < strategy.size(); i++) strategy[i] /= normalizingSum;
  }
  else {
    for(int i = 0; i < strategy.size(); i++) strategy[i] = 1.0 / strategy.size(); 
  }
  for(int i = 0; i < strategy.size(); i++) strategySum[i] += strategy[i];
  return strategy;
}

int Player::getAction(vector<double> strategy){
  double r = static_cast<double> (rand() / static_cast<double>(RAND_MAX));
  double sum = 0;
  for(int i = 0; i < strategy.size(); i++){
    sum += strategy[i];
    if(r < sum){
      //cout << "Chose Action: " << i << endl;
      return i;
    }
  }
  //cout << "Chose Action: " << strategy.size() - 1 << endl;
  return strategy.size() - 1;
}

void Player::train(int myAction, int otherAction){
  vector<int> myStrat = convertInt(permutations[myAction]);
  vector<int> otherStrat = convertInt(permutations[otherAction]);
  vector<int> actionUtility;
  for(int i = 0; i < permutations.size(); i++){
    vector<int> possibleAction = convertInt(permutations[i]);
    int regret = 0;
    for(int j = 0; j < BATTLEFIELDSIZE; j++){
      // calculate the regret the possibleAction
      regret += (possibleAction[j] > otherStrat[j]) - (possibleAction[j] < otherStrat[j]);
    }
    actionUtility.push_back(regret);
  }
  for(int i = 0; i < regretSum.size(); i++){
    regretSum[i] += actionUtility[i] - actionUtility[myAction];
  }
}

vector<double> Player::getAvgStrategy(){
  double sum = this->sum(strategySum);
  vector<double> avgStrategy;
  if(sum > 0){
    for(int i = 0; i < strategySum.size(); i++){
      avgStrategy.push_back(strategySum[i] / sum);
    }
  }
  else{
    for(int i = 0; i < strategySum.size(); i++){
      avgStrategy.push_back(1.0 / permutations.size());
    }
  }
  return avgStrategy;

}

vector<int> Player::convertInt(int perm){
  vector<int> converted;
  int modifier = 0; 
  for(int i = 0; i < BATTLEFIELDSIZE; i++) converted.push_back(0);
  int tmpPerm = perm;
  for(int i = 0; i < BATTLEFIELDSIZE; i++){
    // example: perm = 5, BATTLEFIELDSIZE = 3
    //  i=0:
    //    converted[0] = int(5 / 10^2)
    //  i=1:
    //    converted[1] = int(5 / 10^1)
    //  i=2:
    //    converted[2] = int(5 / 10^0) = 5 
    //  converted = [0, 0, 5]
    converted[i] = int(tmpPerm / pow(10.0, static_cast<double>(BATTLEFIELDSIZE-i-1)));
    tmpPerm -= int(tmpPerm / pow(10, BATTLEFIELDSIZE - i - 1)) * pow(10, BATTLEFIELDSIZE - i - 1);
  }
  return converted;
}


void Player::createPermutations(vector<int> elements, int r){
  /* Creates all the permutations of all possible strategies and adds
   * them to the vector permutations as integers
   *  elements: All the different possible elements that can be in a permutation
   *  r: the size of each permutation
   * Note: no check is done to see if size of elements is => r
   */ 
  int rarr[r];
  for(int i = 0; i < r; i++){
    rarr[i] = r - (i + 1);
  }
  int n = elements.size();
  int indices[n];
  for(int i = 0; i < n; i++)
    indices[i] = i;
  int cycles[r];
  for(int i = n; i > n - r; i--){
    cycles[n - i] = i;
  }
  // now loop through all possible options
  while(true){
    bool finished = true;
    for(int i : rarr){
      cycles[i] -= 1;
      if(cycles[i] == 0){
        int newBack = indices[i];
        for(int j = i; j < n-1; j++){
          indices[j] = indices[j+1];
        }
        indices[n-1] = newBack;
        cycles[i] = n - i;
      }
      else {
        int j = cycles[i];
        // int negj = j * -1;
        int swapper = indices[i];
        indices[i] = indices[n-j];
        indices[n-j] = swapper;
        vector<int> permutation;
        for(int k = 0; k < r; k++){
          permutation.push_back(elements[indices[k]]);
        }
        int converted = convertPermutation(permutation);
        if(sum(permutation) == ARMYSIZE && permutationsSet.count(converted)==0){
          permutations.push_back(converted);
          permutationsSet.insert(converted);
        }
        finished = false;
        break;
      }
    }
    if(finished){
      return;
    }
  }
}

int Player::convertPermutation(vector<int> permutation){
  int sum = 0;
  for(int e : permutation) sum = sum * 10 + e;
  return sum;
}

void Player::printPermutations(){
  vector<double> boomHeadshot = getAvgStrategy();
  for(int i = 0; i < boomHeadshot.size(); i++){
    cout << "Permutation: ";
    for(double d : convertInt(permutations[i])) cout << d << ", ";
    cout << "with probability " << boomHeadshot[i] << endl;
  }
  cout << "Sum of Probabilities: " << sum(boomHeadshot) << endl;
}





void printArr(int * arr, int length, string name){
  cout << name << ": ";
  for(int i = 0; i < length; i++)
    cout << arr[i] << ", ";
  cout << endl;
}

void printVec(vector<int> vec, string name){
  cout << name << ": ";
  for(int i : vec)
    cout << i << ", ";
  cout << endl;
}
