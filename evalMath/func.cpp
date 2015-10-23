#include "func.h"

func::func(std::string name, int numParams) {
	this->name_ = str2Upper(name);
	this->numParams_ = numParams;
}

std::string func::getName() {
	return name_;
}

int func::getNumParams() {
	return numParams_;
}

long double func::run(std::vector<long double> params) {
	return 0;
}
