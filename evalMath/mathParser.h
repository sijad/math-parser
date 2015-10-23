#ifndef EVAL_MATH_PARSER_H
#define EVAL_MATH_PARSER_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <string> // to_std::string and stoll

#include "helper.h"
#include "uoper.h"
#include "oper.h"
#include "func.h"
#include "tokenMaker.h"
#include "token.h"
#include "operations.h"
#include "uoperations.h"
#include "functions.h"

class mathParser {
private:
	std::string expression;
	std::vector<Token> rpn;
	std::map<std::string, std::shared_ptr<oper>> operators;
	std::map<std::string, std::shared_ptr<uoper>> uoperators;
	std::map<std::string, std::shared_ptr<func>> functions;
	std::map<std::string, long double> variables;
	const static char decSeparator = '.', minusSign = '-';
	bool isNumber(std::string st);
	Token *cloneToken(Token tkn);
	bool isOperatorWithHigherOrder(std::shared_ptr<oper> o1, Token *token2);
	std::vector<Token> shuntingYard() throw();
public:
	std::vector<Token> getRPN();
	void add_oper(std::shared_ptr<oper> newOper);
	void add_oper(std::shared_ptr<uoper> newOper);
	void add_func(std::shared_ptr<func> newFunc);
	void add_var(std::string name, long double value);
	long double eval();
	mathParser(std::string expression);
};

#endif
