#include "functions.h"

long double abs_func::run(std::vector<long double> params) {
	return std::abs(params[0]);
}

long double ceil_func::run(std::vector<long double> params) {
	return std::ceil(params[0]);
}

long double floor_func::run(std::vector<long double> params) {
	return std::floor(params[0]);
}

long double round_func::run(std::vector<long double> params) {
	return std::round(params[0]);
}

long double min_func::run(std::vector<long double> params) {
	return std::fmin(params[0], params[1]);
}

long double max_func::run(std::vector<long double> params) {
	return std::fmax(params[0], params[1]);
}

long double pow_func::run(std::vector<long double> params) {
	return std::pow(params[1], params[0]);
}

long double sqrt_func::run(std::vector<long double> params) {
	if(params[0] < 0) {
		throw std::runtime_error("Sqrt's pramatere should be positive.");
	}
	return std::sqrt(params[0]);
}

long double exp_func::run(std::vector<long double> params) {
	return std::exp(params[0]);
}

long double ln_func::run(std::vector<long double> params) {
	return std::log(params[0]);
}

long double log10_func::run(std::vector<long double> params) {
	return std::log10(params[0]);
}

long double log2_func::run(std::vector<long double> params) {
	return std::log2(params[0]);
}

long double log_func::run(std::vector<long double> params) {
	return std::log(params[1]) / log(params[0]);
}

long double sin_func::run(std::vector<long double> params) {
	return std::sin(params[0]);
}

long double cos_func::run(std::vector<long double> params) {
	return std::cos(params[0]);
}

long double tan_func::run(std::vector<long double> params) {
	return std::tan(params[0]);
}

long double cot_func::run(std::vector<long double> params) {
	return 1/std::tan(params[0]);
}

long double sinh_func::run(std::vector<long double> params) {
	return std::sinh(params[0]);
}

long double cosh_func::run(std::vector<long double> params) {
	return std::cosh(params[0]);
}

long double tanh_func::run(std::vector<long double> params) {
	return std::tanh(params[0]);
}

long double coth_func::run(std::vector<long double> params) {
	return 1/std::tanh(params[0]);
}

long double asin_func::run(std::vector<long double> params) {
	return std::asin(params[0]);
}

long double acos_func::run(std::vector<long double> params) {
	return std::acos(params[0]);
}

long double atan_func::run(std::vector<long double> params) {
	return std::atan(params[0]);
}

long double acot_func::run(std::vector<long double> params) {
	return 1/std::atan(params[0]);
}

long double asinh_func::run(std::vector<long double> params) {
	return std::asinh(params[0]);
}

long double acosh_func::run(std::vector<long double> params) {
	return std::acosh(params[0]);
}

long double atanh_func::run(std::vector<long double> params) {
	return std::atanh(params[0]);
}

long double acoth_func::run(std::vector<long double> params) {
	return 1/std::atanh(params[0]);
}

long double rnd_func::run(std::vector<long double> params) {
	return randNum();
}

long double rad_func::run(std::vector<long double> params) {
	return params[0];
}

long double deg_func::run(std::vector<long double> params) {
	return deg(params[0]);
}
