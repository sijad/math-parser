#ifndef EVAL_MATH_FUNCS_HPP
#define EVAL_MATH_FUNCS_HPP
#include <iostream>
#include <cmath>
#include "func.hpp"
#include "helper.hpp"

using namespace std;

class abs_func: public func {
public:
  abs_func(): func("abs", 1) {}
  virtual long double run(vector<long double> params) {
    return abs(params[0]);
  }
};

class ceil_func: public func {
public:
  ceil_func(): func("ceil", 1) {}
  virtual long double run(vector<long double> params) {
    return ceil(params[0]);
  }
};

class floor_func: public func {
public:
  floor_func(): func("floor", 1) {}
  virtual long double run(vector<long double> params) {
    return floor(params[0]);
  }
};

class round_func: public func {
public:
  round_func(): func("round", 1) {}
  virtual long double run(vector<long double> params) {
    return round(params[0]);
  }
};

class min_func: public func {
public:
  min_func(): func("min", 2) {}
  virtual long double run(vector<long double> params) {
    return fmin(params[0], params[1]);
  }
};

class max_func: public func {
public:
  max_func(): func("max", 2) {}
  virtual long double run(vector<long double> params) {
    return fmax(params[0], params[1]);
  }
};

class pow_func: public func {
public:
  pow_func(): func("pow", 2) {}
  virtual long double run(vector<long double> params) {
    return pow(params[1], params[0]);
  }
};

class sqrt_func: public func {
public:
  sqrt_func(): func("sqrt", 1) {}
  virtual long double run(vector<long double> params) {
    if(params[0] < 0) {
      throw runtime_error("Sqrt's pramatere should be positive.");
    }
    return sqrt(params[0]);
  }
};

class exp_func: public func {
public:
  exp_func(): func("exp", 1) {}
  virtual long double run(vector<long double> params) {
    return exp(params[0]);
  }
};

class ln_func: public func {
public:
  ln_func(): func("ln", 1) {}
  virtual long double run(vector<long double> params) {
    return log(params[0]);
  }
};

class log10_func: public func {
public:
  log10_func(): func("log10", 1) {}
  virtual long double run(vector<long double> params) {
    return log10(params[0]);
  }
};

class log2_func: public func {
public:
  log2_func(): func("log2", 1) {}
  virtual long double run(vector<long double> params) {
    return log2(params[0]);
  }
};

class log_func: public func {
public:
  log_func(): func("log", 2) {}
  virtual long double run(vector<long double> params) {
    return log(params[1]) / log(params[0]);
  }
};

class sin_func: public func {
public:
  sin_func(): func("sin", 1) {}
  virtual long double run(vector<long double> params) {
    return sin(params[0]);
  }
};

class cos_func: public func {
public:
  cos_func(): func("cos", 1) {}
  virtual long double run(vector<long double> params) {
    return cos(rad(params[0]));
  }
};

class tan_func: public func {
public:
  tan_func(): func("tan", 1) {}
  virtual long double run(vector<long double> params) {
    return tan(rad(params[0]));
  }
};

class cot_func: public func {
public:
  cot_func(): func("cot", 1) {}
  virtual long double run(vector<long double> params) {
    return 1/tan(rad(params[0]));
  }
};

class sinh_func: public func {
public:
  sinh_func(): func("sinh", 1) {}
  virtual long double run(vector<long double> params) {
    return sinh(rad(params[0]));
  }
};

class cosh_func: public func {
public:
  cosh_func(): func("cosh", 1) {}
  virtual long double run(vector<long double> params) {
    return cosh(rad(params[0]));
  }
};

class tanh_func: public func {
public:
  tanh_func(): func("tanh", 1) {}
  virtual long double run(vector<long double> params) {
    return tanh(rad(params[0]));
  }
};

class coth_func: public func {
public:
  coth_func(): func("coth", 1) {}
  virtual long double run(vector<long double> params) {
    return 1/tanh(rad(params[0]));
  }
};

class asin_func: public func {
public:
  asin_func(): func("asin", 1) {}
  virtual long double run(vector<long double> params) {
    return asin(rad(params[0]));
  }
};

class acos_func: public func {
public:
  acos_func(): func("acos", 1) {}
  virtual long double run(vector<long double> params) {
    return acos(rad(params[0]));
  }
};

class atan_func: public func {
public:
  atan_func(): func("atan", 1) {}
  virtual long double run(vector<long double> params) {
    return atan(rad(params[0]));
  }
};

class acot_func: public func {
public:
  acot_func(): func("acot", 1) {}
  virtual long double run(vector<long double> params) {
    return 1/atan(rad(params[0]));
  }
};

class asinh_func: public func {
public:
  asinh_func(): func("asinh", 1) {}
  virtual long double run(vector<long double> params) {
    return asinh(rad(params[0]));
  }
};

class acosh_func: public func {
public:
  acosh_func(): func("acosh", 1) {}
  virtual long double run(vector<long double> params) {
    return acosh(rad(params[0]));
  }
};

class atanh_func: public func {
public:
  atanh_func(): func("atanh", 1) {}
  virtual long double run(vector<long double> params) {
    return atanh(rad(params[0]));
  }
};

class acoth_func: public func {
public:
  acoth_func(): func("acoth", 1) {}
  virtual long double run(vector<long double> params) {
    return 1/atanh(rad(params[0]));
  }
};

class rnd_func: public func {
public:
  rnd_func(): func("rnd", 0) {}
  virtual long double run(vector<long double> params) {
    return randNum();
  }
};

class rad_func: public func {
public:
  rad_func(): func("rad", 1) {}
  virtual long double run(vector<long double> params) {
    return rad(params[0]);
  }
};

class deg_func: public func {
public:
  deg_func(): func("deg", 1) {}
  virtual long double run(vector<long double> params) {
    return deg(params[0]);
  }
};


#endif
