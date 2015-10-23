#ifndef EVAL_MATH_UOPERS_H
#define EVAL_MATH_UOPERS_H
#include "uoper.h"

class plus_uoper: public uoper {
public:
	plus_uoper(std::string op) : uoper(op) {}
	long double run(long double n);
};

class minus_uoper: public uoper {
public:
	minus_uoper(std::string op) : uoper(op) {}
	virtual long double run(long double n);
};
#endif
