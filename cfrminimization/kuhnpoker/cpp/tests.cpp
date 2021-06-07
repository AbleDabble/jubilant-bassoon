#include <iostream>
#include <vector>
#include "node.h"
#include "cfr.h"
#include "utils.h"

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::rand;
using std::srand;


void runTests(){
  Node n("fuck");
  vector<double> t1 = n.getAverageStrategy();
  string t1_out = vec_to_string(t1);
  cout << "Test 1 (getAverageStrategy): " << t1_out << endl;
  string t2_out = n.toString();
  cout << "Test 2 (toString): " << t2_out << endl;
  cout << "Testing Done" << endl;
}


int main() {
  runTests();
}
