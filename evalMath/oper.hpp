#ifndef EVAL_MATH_OPER_HPP
#define EVAL_MATH_OPER_HPP

#include <iostream>

using namespace std;

class oper {
private:
  string operName;
  int precedence;
  bool leftAssoc;
public:
  oper(string oper, int precedence, bool leftAssoc) {
    this->operName = oper;
    this->precedence = precedence;
    this->leftAssoc = leftAssoc;
  };

  string getOper() {
    return operName;
  };

  int getPrecedence() {
    return precedence;
  };

  bool isLeftAssoc() {
    return leftAssoc;
  };

  virtual long double run(long double n1, long double n2) {
    return 0;
  }
};

#endif
