#include "helper.h"

long double rad(long double a) {
	return a*PI/180;
}

long double deg(long double a) {
	return (a * 180)/PI;
}

std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

std::string str2Upper(std::string str) {
	std::string s = str;
	transform(s.begin(), s.end(), s.begin(), toupper);
	return s;
}

long double randNum() {
	static std::default_random_engine generator(time(NULL));
	static std::uniform_real_distribution<float> distribution(0.0,1.0);
	return distribution(generator);
}
