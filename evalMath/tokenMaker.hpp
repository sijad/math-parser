#ifndef EVAL_MATH_TOKENMAKER_HPP
#define EVAL_MATH_TOKENMAKER_HPP

#include <iostream>
#include <sstream>
#include <cctype>
#include <map>
#include <string>
#include <stdexcept>

#include "helper.hpp"
#include "token.hpp"
#include "oper.hpp"
#include "uoper.hpp"

using namespace std;
class tokenMaker {
private:
  int pos;
  string input, prevToken;
  map<string, std::shared_ptr<oper>> *operators;
  map<string, std::shared_ptr<uoper>> *uoperators;
  const static char decSeparator = '.', minusSign = '-';

  char nextChar() {
    char ch;
    int pp = pos;
    while (pp < input.length()) {
        ch = input.at(pos);
        if (!isspace(ch))
            return ch;
        ++pp;
    }
    return ' ';
  }

public:
  tokenMaker(string input, map<string, std::shared_ptr<oper>> *operators, map<string, std::shared_ptr<uoper>> *uoperators) {prevToken = "";pos = 0; this->input = trim(input); this->operators = operators; this->uoperators = uoperators;}
  bool hasNext() {return (pos < input.length());}
  int getPos() {return pos;}

  Token getNext() throw() {
    Token tkn;

    if (pos >= input.length()) {
      throw runtime_error("Invalid Action");
    }

    token_t ttype;
    stringstream token;
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
    } else if (uoperators->count(string(1, ch)) == 1 && !isspace(nextChar()) && (prevToken.empty() || "(" == prevToken || "," == prevToken || operators->count(prevToken) == 1 || uoperators->count(prevToken) == 1)) {
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
        if (uoperators->count(string(1,ch)) == 1) {
          break;
        }
      }
      ttype = opers;
      if (!operators->count(token.str())) {
        throw runtime_error("Operator '" + token.str() + "' not recognized at position " + to_string(pos - token.str().length() + 1));
      }
    }

    prevToken = token.str();
    tkn.type = ttype;
    tkn.token = prevToken;

    return tkn;
  }
};

#endif
