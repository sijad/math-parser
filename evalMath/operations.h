#ifndef EVAL_MATH_OPERS_H
#define EVAL_MATH_OPERS_H
#include "oper.h"
#include "helper.h"
#include <cmath>
class plus_oper: public oper {
public:
	plus_oper() : oper("+", 20, true) {}
	long double run(long double n1, long double n2);
};
class minus_oper: public oper {
public:
	minus_oper() : oper("-", 20, true) {}
	long double run(long double n1, long double n2);
};
class mul_oper: public oper {
public:
	mul_oper() : oper("*", 30, true) {}
	long double run(long double n1, long double n2);
};
class dev_oper: public oper {
public:
	dev_oper() : oper("/", 30, true) {}
	long double run(long double n1, long double n2);
};
class mod_oper: public oper {
public:
	mod_oper() : oper("%", 30, true) {}
	long double run(long double n1, long double n2);
};
class pow_oper: public oper {
public:
	pow_oper() : oper("^", 40, false) {}
	long double run(long double n1, long double n2);
};

#endif
