#ifndef EVAL_MATH_UOPER_HPP
#define EVAL_MATH_UOPER_HPP

#include <iostream>

using namespace std;

class uoper {
private:
  string operName;
public:
  uoper(string oper) {
    this->operName = oper;
  };

  string getOper() {
    return operName;
  };

  virtual long double run(long double n1) {
    return 0;
  }
};

#endif
