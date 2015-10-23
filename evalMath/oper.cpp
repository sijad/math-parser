#include "oper.h"

oper::oper(std::string oper, int precedence, bool leftAssoc) {
	this->operName = oper;
	this->precedence = precedence;
	this->leftAssoc = leftAssoc;
};

std::string oper::getOper() {
	return operName;
};

int oper::getPrecedence() {
	return precedence;
};

bool oper::isLeftAssoc() {
	return leftAssoc;
};

long double oper::run(long double n1, long double n2) {
	return 0;
}
