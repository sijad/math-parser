#ifndef EVAL_MATH_UOPER_H
#define EVAL_MATH_UOPER_H

#include <iostream>

class uoper {
private:
	std::string name_;
public:
	uoper(std::string uoper);
	std::string getOper();
	virtual long double run(long double n1);
};

#endif
