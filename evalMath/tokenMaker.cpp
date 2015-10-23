#include "tokenMaker.h"

tokenMaker::tokenMaker(std::string input, std::map<std::string, std::shared_ptr<oper>> *operators, std::map<std::string, std::shared_ptr<uoper>> *uoperators) {
	prevToken = "";
	pos = 0;
	this->input = trim(input);
	this->operators = operators;
	this->uoperators = uoperators;
}

char tokenMaker::nextChar() {
	char ch;
	size_t pp = pos;
	while (pp < input.length()) {
		ch = input.at(pos);
		if (!isspace(ch))
			return ch;
		++pp;
	}
	return ' ';
}

bool tokenMaker::hasNext() {
	return (pos < input.length());
}

int tokenMaker::getPos() {
	return pos;
}

Token tokenMaker::getNext() throw() {
	Token tkn;

	if (pos >= input.length()) {
		throw std::runtime_error("Invalid Action");
	}

	token_t ttype;
	std::stringstream token;
	char ch = input.at(pos);

	while(isspace(ch) && pos < input.length()) {
		ch = input.at(++pos);
	}

	if (isdigit(ch)) {
		while ((isdigit(ch) || ch == decSeparator) && (pos < input.length())) {
			token << input.at(pos++);
			ch = (pos == input.length()) ? 0 : input.at(pos);
		}
		ttype = number;
	} else if (uoperators->count(std::string(1, ch)) == 1 && !isspace(nextChar()) && (prevToken.empty() || "(" == prevToken || "," == prevToken || operators->count(prevToken) == 1 || uoperators->count(prevToken) == 1)) {
		token << ch;
		pos++;
		ttype = uopers;
	} else if (isalpha(ch) || ch == '_') {
		while ((isalpha(ch) || isdigit(ch) || ch == '_') && pos < input.length()) {
			token << input.at(pos++);
			ch = (pos == input.length()) ? 0 : input.at(pos);
		}
		ttype = name;
	} else if (ch == '(') {
		token << input.at(pos++);
		ttype = lparen;
	} else if (ch == ')') {
		token << input.at(pos++);
		ttype = rparen;
	} else if (ch == ',') {
		token << input.at(pos++);
		ttype = comma;
	} else {
		while (!isalpha(ch) && !isdigit(ch) && ch != '_' && !isspace(ch) && ch != '(' && ch != ')' && ch != ',' && (pos < input.length())) {
			token << input.at(pos);
			pos++;
			ch = (pos == input.length()) ? 0 : input.at(pos);
			if (uoperators->count(std::string(1,ch)) == 1) {
				break;
			}
		}
		ttype = opers;
		if (!operators->count(token.str())) {
			throw std::runtime_error("Operator '" + token.str() + "' not recognized at position " + std::to_string(pos - token.str().length() + 1));
		}
	}

	prevToken = token.str();
	tkn.type = ttype;
	tkn.token = prevToken;

	return tkn;
}
