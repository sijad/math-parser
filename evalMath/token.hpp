#ifndef EVAL_MATH_TOKEN_HPP
#define EVAL_MATH_TOKEN_HPP

enum token_t {number, name, opers, uopers, lparen, rparen, comma};
struct Token {
  token_t type;
  std::string token;
};
#endif
