
#include "functions.h"

long double abs_func::run(std::vector<long double> params) {
	// int const mask = params[0] >> sizeof(long long double) * CHAR_BIT - 1;
	// retrun (params[0] + mask) ^ mask;

	// return (unsigned long double) params[0];
	// return (params[0] < 0)?-params[0]:params[0];
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
	// return (params[0] ^ ((params[1] ^ params[0]) & -(params[1] < params[0])));
	return std::fmin(params[0], params[1]);
}

long double max_func::run(std::vector<long double> params) {
	// return (params[0] ^ ((params[0] ^ params[1]) & -(params[0] < params[1])));
	return std::fmax(params[0], params[1]);
}

long double pow_func::run(std::vector<long double> params) {
	if(params[0] == 1 || params[1] == 1)
		return params[1];
		
	return cpow(params[1], params[0]);
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
	return std::log(10) / std::log(params[0]);
	// return std::log10(params[0]);
}

long double log2_func::run(std::vector<long double> params) {
	return std::log(2) / std::log(params[0]);
	// return std::log2(params[0]);
}

long double log_func::run(std::vector<long double> params) {
	return std::log(params[1]) / std::log(params[0]);
}

long double sin_func::run(std::vector<long double> params) {
	if(params[0] == 0 || params[0] == PI || params[0] == 2 * PI) {
		return 0;
	}else if(params[0] == PI/2) {
		return 1;
	}else if(params[0] == 1.5 * PI) {
		return -1;
	}else{
		return std::sin(params[0]);
	}
}

long double cos_func::run(std::vector<long double> params) {
	if(params[0] == PI / 2 || params[0] == 1.5 * PI) {
		return 0;
	}else if(params[0] == 0 || params[0] == 2 * PI) {
		return 1;
	}else if(params[0] == PI) {
		return -1;
	}else{
		return std::cos(params[0]);
	}
}

long double tan_func::run(std::vector<long double> params) {
	if(params[0] == 0 || params[0] == PI || params[0] == 2 * PI) {
		return 0;
	}else if(params[0] == PI/4 || params[0] == 1.25 * PI) {
		return 1;
	}else if(params[0] == 0.75 * PI || params[0] == 1.75 * PI) {
		return -1;
	}else if(params[0] == PI/2 || params[0] == 1.5 * PI) {
		return std::numeric_limits<long double>::infinity();
	}else{
		return (std::sin(params[0]) / std::cos(params[0]));
		// return std::tan(params[0]);
	}
}

long double cot_func::run(std::vector<long double> params) {
	tan_func * tanf = new tan_func();
	return 1/tanf->run(params);
}

long double sinh_func::run(std::vector<long double> params) {
	return ((std::exp(params[0]) - std::exp(-params[0]))/2);
	// return std::sinh(params[0]);
}

long double cosh_func::run(std::vector<long double> params) {
	return ((std::exp(params[0]) + std::exp(-params[0]))/2);
	// return std::cosh(params[0]);
}

long double tanh_func::run(std::vector<long double> params) {
	return ((std::exp(params[0]) - std::exp(-params[0])) / (std::exp(params[0]) + std::exp(-params[0])));
	// return std::tanh(params[0]);
}

long double coth_func::run(std::vector<long double> params) {
	return ((std::exp(params[0]) + std::exp(-params[0])) / (std::exp(params[0]) - std::exp(-params[0])));
	// return 1/std::tanh(params[0]);
}

long double asin_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
	else if(params[0]==1) return (PI/2);
	else if(params[0]==-1) return (-PI/2);
	else return std::atan(params[0]/(std::sqrt(1-(params[0] * params[0]))));
	// return std::asin(params[0]);
}

long double acos_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
	// else if(params[0]==1) return (PI/2);
	// else if(params[0]==-1) return (-PI/2);
	// else return std::atan((std::sqrt(1-(params[0] * params[0])))/params[0]);
	// return std::log(params[1] + std::sqrt((params[0]+1)) * std::sqrt((params[0]-1)) );
	// return std::acos(params[0]);
	else return std::atan(1/(std::sqrt(1-(params[0] * params[0]))));
}

long double atan_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
	return std::atan(params[0]);
}

long double acot_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
	return 1/std::atan(params[0]);
}

long double asinh_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
	return log( params[0] + std::sqrt((params[0] * params[0]) + 1) );
	// return std::asinh(params[0]);
}

long double acosh_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
	return log( params[0] + std::sqrt((params[0] * params[0]) - 1) );
	// return std::acosh(params[0]);
}

long double atanh_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
	return log( (1+params[0])/(1-params[0]) )/2;

	// return std::atanh(params[0]);
}

long double acoth_func::run(std::vector<long double> params) {
	if(params[0] < -1 || params[0] > 1) throw std::runtime_error("The Value must be between -1:1");
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
