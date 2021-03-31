#ifndef PLAYER_H
#define PLAYER_H
#include <unordered_set>
#include <vector>
//using std::cout;
//using std::endl;
//using std::rand;
using std::vector;
using std::unordered_set;
class Player
{
  private: 
    vector<int> permutations; 
    unordered_set<int> permutationsSet; // check for duplicates
    int BATTLEFIELDSIZE;
    vector<int> regretSum;
    vector<double> strategySum;
    int permutationSize;
    int ARMYSIZE;
    // functions
    void createPermutations(vector<int> elements, int r);
    void createPureStrategies();
    int sum(vector<int> permutation);
    double sum(vector<double> vec);
    int convertPermutation(vector<int> permutation);
    vector<int> createActionUtility(int otherAction, int myAction);
    vector<int> convertInt(int);

  public:
    Player(int armySize, int numBattlefields);
    vector<double> getStrategy();
    void train(int myAction, int otherAction);
    vector<double> getAvgStrategy();
    int getAction(vector<double> strategy);
    void printPermutations();
};

#endif
