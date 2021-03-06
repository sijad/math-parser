#include "operations.h"

long double plus_oper::run(long double n1, long double n2) {
	return n1 + n2;
}

long double minus_oper::run(long double n1, long double n2) {
	return n1 - n2;
}

long double mul_oper::run(long double n1, long double n2) {
	return n1 * n2;
}

long double dev_oper::run(long double n1, long double n2) {
	return n1 / n2;
}

long double mod_oper::run(long double n1, long double n2) {
	return fmod(n1, n2);
}

long double pow_oper::run(long double n1, long double n2) {
	if(n1 == 1 || n2 == 1)
		return n2;
		
	return cpow(n1, n2);
}
