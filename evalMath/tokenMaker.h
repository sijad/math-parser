#ifndef EVAL_MATH_TOKENMAKER_H
#define EVAL_MATH_TOKENMAKER_H

#include <iostream>
#include <sstream>
#include <cctype>
#include <map>
#include <string>
#include <stdexcept>

#include "helper.h"
#include "token.h"
#include "oper.h"
#include "uoper.h"

class tokenMaker {
private:
	size_t pos;
	std::string input, prevToken;
	std::map<std::string, std::shared_ptr<oper>> *operators;
	std::map<std::string, std::shared_ptr<uoper>> *uoperators;
	const static char decSeparator = '.', minusSign = '-';
	char nextChar();
public:
	tokenMaker(std::string input, std::map<std::string, std::shared_ptr<oper>> *operators, std::map<std::string, std::shared_ptr<uoper>> *uoperators);
	bool hasNext();
	int getPos();
	Token getNext() throw();
};

#endif
