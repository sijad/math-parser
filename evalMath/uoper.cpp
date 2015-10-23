#include "uoper.h"

uoper::uoper(std::string name) {
	this->name_ = name;
}

std::string uoper::getOper() {
	return name_;
}

long double uoper::run(long double n1) {
	return 0;
}
