#ifndef EVAL_MATH_FUNC_HPP
#define EVAL_MATH_FUNC_HPP

#include <iostream>

using namespace std;

class func {
private:
  string name;
public:
  int numParams;

  func(string name, int numParams) {
    this->name = str2Upper(name);
    this->numParams = numParams;
  }

  string getName() {
    return name;
  }

  int getNumParams() {
    return numParams;
  }

  virtual long double run(vector<long double> params) {
    return 0;
  }
};

#endif
