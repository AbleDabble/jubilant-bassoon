#ifndef UTILS_H_
#define UTILS_H_
#include <string> 
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

using std::string;
using std::vector;
using std::copy;
using std::ostream;
using std::ostringstream; 
using std::ostream_iterator;

template<typename T>
string vec_to_string(vector<T> vec){
  ostringstream oss;
  copy(vec.begin(), vec.end() - 1, ostream_iterator<T>(oss, ","));
  oss << vec.back();
  return oss.str();
}

#endif 
