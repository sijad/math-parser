#ifndef EVAL_MATH_OPER_H
#define EVAL_MATH_OPER_H

#include <iostream>

class oper {
private:
	std::string operName;
	int precedence;
	bool leftAssoc;
public:
	oper(std::string oper, int precedence, bool leftAssoc);

	std::string getOper();

	int getPrecedence();

	bool isLeftAssoc();

	virtual long double run(long double n1, long double n2);
};

#endif
