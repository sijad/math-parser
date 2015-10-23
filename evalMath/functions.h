#ifndef EVAL_MATH_FUNCS_H
#define EVAL_MATH_FUNCS_H
#include <iostream>
#include <cmath>
#include "func.h"
#include "helper.h"

class abs_func: public func {
public:
	abs_func(): func("abs", 1) {}
	long double run(std::vector<long double> params);
};

class ceil_func: public func {
public:
	ceil_func(): func("ceil", 1) {}
	long double run(std::vector<long double> params);
};

class floor_func: public func {
public:
	floor_func(): func("floor", 1) {}
	long double run(std::vector<long double> params);
};

class round_func: public func {
public:
	round_func(): func("round", 1) {}
	long double run(std::vector<long double> params);
};

class min_func: public func {
public:
	min_func(): func("min", 2) {}
	long double run(std::vector<long double> params);
};

class max_func: public func {
public:
	max_func(): func("max", 2) {}
	long double run(std::vector<long double> params);
};

class pow_func: public func {
public:
	pow_func(): func("pow", 2) {}
	long double run(std::vector<long double> params);
};

class sqrt_func: public func {
public:
	sqrt_func(): func("sqrt", 1) {}
	long double run(std::vector<long double> params);
};

class exp_func: public func {
public:
	exp_func(): func("exp", 1) {}
	long double run(std::vector<long double> params);
};

class ln_func: public func {
public:
	ln_func(): func("ln", 1) {}
	long double run(std::vector<long double> params);
};

class log10_func: public func {
public:
	log10_func(): func("log10", 1) {}
	long double run(std::vector<long double> params);
};

class log2_func: public func {
public:
	log2_func(): func("log2", 1) {}
	long double run(std::vector<long double> params);
};

class log_func: public func {
public:
	log_func(): func("log", 2) {}
	long double run(std::vector<long double> params);
};

class sin_func: public func {
public:
	sin_func(): func("sin", 1) {}
	long double run(std::vector<long double> params);
};

class cos_func: public func {
public:
	cos_func(): func("cos", 1) {}
	long double run(std::vector<long double> params);
};

class tan_func: public func {
public:
	tan_func(): func("tan", 1) {}
	long double run(std::vector<long double> params);
};

class cot_func: public func {
public:
	cot_func(): func("cot", 1) {}
	long double run(std::vector<long double> params);
};

class sinh_func: public func {
public:
	sinh_func(): func("sinh", 1) {}
	long double run(std::vector<long double> params);
};

class cosh_func: public func {
public:
	cosh_func(): func("cosh", 1) {}
	long double run(std::vector<long double> params);
};

class tanh_func: public func {
public:
	tanh_func(): func("tanh", 1) {}
	long double run(std::vector<long double> params);
};

class coth_func: public func {
public:
	coth_func(): func("coth", 1) {}
	long double run(std::vector<long double> params);
};

class asin_func: public func {
public:
	asin_func(): func("asin", 1) {}
	long double run(std::vector<long double> params);
};

class acos_func: public func {
public:
	acos_func(): func("acos", 1) {}
	long double run(std::vector<long double> params);
};

class atan_func: public func {
public:
	atan_func(): func("atan", 1) {}
	long double run(std::vector<long double> params);
};

class acot_func: public func {
public:
	acot_func(): func("acot", 1) {}
	long double run(std::vector<long double> params);
};

class asinh_func: public func {
public:
	asinh_func(): func("asinh", 1) {}
	long double run(std::vector<long double> params);
};

class acosh_func: public func {
public:
	acosh_func(): func("acosh", 1) {}
	long double run(std::vector<long double> params);
};

class atanh_func: public func {
public:
	atanh_func(): func("atanh", 1) {}
	long double run(std::vector<long double> params);
};

class acoth_func: public func {
public:
	acoth_func(): func("acoth", 1) {}
	long double run(std::vector<long double> params);
};

class rnd_func: public func {
public:
	rnd_func(): func("rnd", 0) {}
	long double run(std::vector<long double> params);
};

class rad_func: public func {
public:
	rad_func(): func("rad", 1) {}
	long double run(std::vector<long double> params);
};

class deg_func: public func {
public:
	deg_func(): func("deg", 1) {}
	long double run(std::vector<long double> params);
};


#endif
