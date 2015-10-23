#ifndef EVAL_MATH_FUNC_H
#define EVAL_MATH_FUNC_H

#include <iostream>
#include <vector>
#include "helper.h"

class func {
private:
	std::string name_;
	int numParams_;
public:

	func(std::string name, int numParams);

	std::string getName();

	int getNumParams();

	virtual long double run(std::vector<long double> params);
};

#endif
