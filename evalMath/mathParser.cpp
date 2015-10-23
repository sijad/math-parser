#include "mathParser.h"

bool mathParser::isNumber(std::string st) {
	if (st.at(0) == minusSign && st.length() == 1)
		return false;
	for (char ch : st) {
		if (!isdigit(ch) && ch != minusSign && ch != decSeparator)
			return false;
	}
	return true;
}

Token *mathParser::cloneToken(Token tkn) {
	Token *tkn2 = new Token();
	tkn2->type = tkn.type;
	tkn2->token = tkn.token;
	return tkn2;
}

bool mathParser::isOperatorWithHigherOrder(std::shared_ptr<oper> o1, Token *token2) {
	return (token2->type == opers && ((o1->isLeftAssoc() && o1->getPrecedence() <= operators.at(token2->token)->getPrecedence()) || (o1->getPrecedence() < operators.at(token2->token)->getPrecedence())));
}

std::vector<Token> mathParser::shuntingYard() throw() {
	std::vector<Token> queue;
	std::stack<Token> stack;
	tokenMaker tokenmaker(expression, &operators, &uoperators);
	Token *prevToken = NULL, *lastFunc = NULL;
	while (tokenmaker.hasNext()) {
		Token token;
		try {
			token = tokenmaker.getNext();
		} catch(std::runtime_error& e) {
			std::cerr << e.what();
		}
		switch (token.type) {
		case number:
			queue.push_back(token);
			break;
		case name:
			if (functions.count(str2Upper(token.token)) > 0) {
				if (prevToken != NULL && (prevToken->type == number || (prevToken->type == name && functions.count(str2Upper(prevToken->token)) > 0))) {
					while (!stack.empty() && stack.top().type == uopers) {
						queue.push_back(stack.top());
						stack.pop();
					}
					Token newtkn;
					newtkn.type = opers;
					newtkn.token = "*";
					stack.push(newtkn);
				}
				stack.push(token);
				lastFunc = cloneToken(token);
			} else if (variables.count(str2Upper(token.token)) > 0) {
				queue.push_back(token);
			} else {
				if (prevToken != NULL && prevToken->type == number) {
					while (!stack.empty() && stack.top().type == uopers) {
						queue.push_back(stack.top());
						stack.pop();
					}
					queue.push_back(token);
					Token newtkn;
					newtkn.type = opers;
					newtkn.token = "*";
					queue.push_back(newtkn);
				} else {
					queue.push_back(token);
				}
			}
			break;
		case comma:
			while (!stack.empty() && stack.top().type != lparen) {
				queue.push_back(stack.top());
				stack.pop();
			}
			if (stack.empty()) {
				throw std::runtime_error("Error while parsing function '" + (lastFunc->token) + "'");
			}
			break;
		case opers: {
			std::shared_ptr<oper> o1 = operators.at(token.token);
			Token * token2 = NULL;
			if(!stack.empty()) {
				token2 = cloneToken(stack.top());
			} else {
				token2 = NULL;
			}
			while (token2 != NULL && (isOperatorWithHigherOrder(o1, token2) || token2->type == uopers)) {
				queue.push_back(stack.top());
				stack.pop();
				if(!stack.empty()) {
					token2 = cloneToken(stack.top());
				} else {
					token2 = NULL;
				}
			}
			stack.push(token);
		}
		break;
		case lparen:
			if (prevToken != NULL) {
				if (prevToken->type == number || (prevToken->type == name && functions.count(str2Upper(prevToken->token)) == 0)) {
					while(!stack.empty() && stack.top().type == uopers) {
						queue.push_back(stack.top());
						stack.pop();
					}
					Token newtkn;
					newtkn.type = opers;
					newtkn.token = "*";
					stack.push(newtkn);
				}
			}
			stack.push(token);
			break;
		case rparen:
			while(!stack.empty() && stack.top().type != lparen) {
				queue.push_back(stack.top());
				stack.pop();
			}
			if (stack.empty()) {
				throw std::runtime_error("Mismatched parentheses");
			}
			stack.pop();
			if (!stack.empty() && functions.count(str2Upper(stack.top().token)) > 0) {
				queue.push_back(stack.top());
				stack.pop();
			}
			while (!stack.empty() && stack.top().type == uopers) {
				queue.push_back(stack.top());
				stack.pop();
			}
			break;
		case uopers:
			stack.push(token);
			break;
		}
		prevToken = cloneToken(token);
	}

	while (!stack.empty()) {
		Token token = stack.top();
		stack.pop();
		if (token.type == lparen || token.type == rparen) {
			throw std::runtime_error("Mismatched parentheses");
		} else if (token.type != opers && token.type != uopers) {
			throw std::runtime_error("Unknown operator or function: '" + (token.token) + "'");
		}
		queue.push_back(token);
	}

	return queue;
}

std::vector<Token> mathParser::getRPN() {
	if (rpn.empty()) {
		rpn = shuntingYard();
	}
	return rpn;
}

void mathParser::add_oper(std::shared_ptr<oper> newOper) {
	operators.insert(std::pair<std::string, std::shared_ptr<oper>>(newOper->getOper(), newOper));
};

void mathParser::add_oper(std::shared_ptr<uoper> newOper) {
	uoperators.insert(std::pair<std::string, std::shared_ptr<uoper>>(newOper->getOper(), newOper));
};

void mathParser::add_func(std::shared_ptr<func> newFunc) {
	functions.insert(std::pair<std::string, std::shared_ptr<func>>(newFunc->getName(), newFunc));
};

void mathParser::add_var(std::string name, long double value) {
	std::map<std::string, long double>::iterator it;
	it = variables.find(str2Upper(name));
	if (it != variables.end())
		variables.erase(it);
	variables.insert(std::pair<std::string, long double>(str2Upper(name), value));
};

long double mathParser::eval() {
	std::stack<long double> stack;
	for (Token token : getRPN()) {
		switch (token.type) {
		case number:
			stack.push(stold(token.token));
			break;
		case opers: {
			long double n1 = stack.top();
			stack.pop();
			long double n2 = stack.top();
			stack.pop();
			stack.push(operators.at(token.token)->run(n2, n1));
		}
		break;
		case uopers: {
			long double n = stack.top();
			stack.pop();
			stack.push(uoperators.at(token.token)->run(n));
		}
		break;
		case name: {
			if (variables.count(str2Upper(token.token)) > 0) {
				stack.push(variables.at(str2Upper(token.token)));
			} else if (functions.count(str2Upper(token.token)) > 0) {
				std::shared_ptr<func> f = functions.at(str2Upper(token.token));
				std::vector<long double> list;
				for (int i = 0; i < f->getNumParams(); i++) {
					list.push_back(stack.top());
					stack.pop();
				}
				long double fResult = f->run(list);
				stack.push(fResult);
			} else {
				throw std::runtime_error("Unknown operator, function or variable: '" + (token.token) + "'");
			}
		}
		break;
		default:
			break;
		}
	}
	return stack.top();
}

mathParser::mathParser(std::string expression) {
	this->expression = expression;
	add_oper(std::shared_ptr<uoper>(new plus_uoper("+")));
	add_oper(std::shared_ptr<uoper>(new minus_uoper("-")));

	add_oper(std::shared_ptr<oper>(new plus_oper()));
	add_oper(std::shared_ptr<oper>(new minus_oper()));
	add_oper(std::shared_ptr<oper>(new mul_oper()));
	add_oper(std::shared_ptr<oper>(new dev_oper()));
	add_oper(std::shared_ptr<oper>(new mod_oper()));
	add_oper(std::shared_ptr<oper>(new pow_oper()));

	add_func(std::shared_ptr<func>(new abs_func()));
	add_func(std::shared_ptr<func>(new ceil_func()));
	add_func(std::shared_ptr<func>(new floor_func()));
	add_func(std::shared_ptr<func>(new round_func()));
	add_func(std::shared_ptr<func>(new min_func()));
	add_func(std::shared_ptr<func>(new max_func()));
	add_func(std::shared_ptr<func>(new pow_func()));
	add_func(std::shared_ptr<func>(new sqrt_func()));
	add_func(std::shared_ptr<func>(new exp_func()));
	add_func(std::shared_ptr<func>(new ln_func()));
	add_func(std::shared_ptr<func>(new log10_func()));
	add_func(std::shared_ptr<func>(new log2_func()));
	add_func(std::shared_ptr<func>(new log_func()));
	add_func(std::shared_ptr<func>(new sin_func()));
	add_func(std::shared_ptr<func>(new cos_func()));
	add_func(std::shared_ptr<func>(new tan_func()));
	add_func(std::shared_ptr<func>(new cot_func()));
	add_func(std::shared_ptr<func>(new sinh_func()));
	add_func(std::shared_ptr<func>(new cosh_func()));
	add_func(std::shared_ptr<func>(new tanh_func()));
	add_func(std::shared_ptr<func>(new coth_func()));
	add_func(std::shared_ptr<func>(new asin_func()));
	add_func(std::shared_ptr<func>(new acos_func()));
	add_func(std::shared_ptr<func>(new atan_func()));
	add_func(std::shared_ptr<func>(new acot_func()));
	add_func(std::shared_ptr<func>(new asinh_func()));
	add_func(std::shared_ptr<func>(new acosh_func()));
	add_func(std::shared_ptr<func>(new atanh_func()));
	add_func(std::shared_ptr<func>(new acoth_func()));
	add_func(std::shared_ptr<func>(new rnd_func()));
	add_func(std::shared_ptr<func>(new rad_func()));
	add_func(std::shared_ptr<func>(new deg_func()));
	add_var("pi", PI);
}
