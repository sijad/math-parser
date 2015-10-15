#ifndef EVAL_MATH_OPERS_HPP
#define EVAL_MATH_OPERS_HPP
#include <iostream>
#include <cmath>
#include "oper.hpp"

using namespace std;

class plus_oper: public oper {
public:
  plus_oper(string op, int precedence, bool leftAssoc) : oper(op, precedence, leftAssoc) {}
  virtual long double run(long double n1, long double n2) {
    return n1 + n2;
  }
};
class minus_oper: public oper {
public:
  minus_oper(string op, int precedence, bool leftAssoc) : oper(op, precedence, leftAssoc) {}
  virtual long double run(long double n1, long double n2) {
    return n1 - n2;
  }
};
class mul_oper: public oper {
public:
  mul_oper(string op, int precedence, bool leftAssoc) : oper(op, precedence, leftAssoc) {}
  virtual long double run(long double n1, long double n2) {
    return n1 * n2;
  }
};
class dev_oper: public oper {
public:
  dev_oper(string op, int precedence, bool leftAssoc) : oper(op, precedence, leftAssoc) {}
  virtual long double run(long double n1, long double n2) {
    return n1 / n2;
  }
};
class mod_oper: public oper {
public:
  mod_oper(string op, int precedence, bool leftAssoc) : oper(op, precedence, leftAssoc) {}
  virtual long double run(long double n1, long double n2) {
    return fmod(n1, n2);
  }
};
class pow_oper: public oper {
public:
  pow_oper(string op, int precedence, bool leftAssoc) : oper(op, precedence, leftAssoc) {}
  virtual long double run(long double n1, long double n2) {
    return pow(n1, n2);
  }
};

#endif
