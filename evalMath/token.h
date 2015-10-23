#ifndef EVAL_MATH_TOKEN_H
#define EVAL_MATH_TOKEN_H

enum token_t {number, name, opers, uopers, lparen, rparen, comma};

struct Token {
	token_t type;
	std::string token;
};

#endif
