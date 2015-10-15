#ifndef EVAL_MATH_UOPERS_HPP
#define EVAL_MATH_UOPERS_HPP
#include <iostream>
#include <cmath>
#include "uoper.hpp"
using namespace std;
class plus_uoper: public uoper {
public:
  plus_uoper(string op) : uoper(op) {}
  virtual long double run(long double n) {
    return n;
  }
};
class minus_uoper: public uoper {
public:
  minus_uoper(string op) : uoper(op) {}
  virtual long double run(long double n) {
    return n * -1;
  }
};
#endif
