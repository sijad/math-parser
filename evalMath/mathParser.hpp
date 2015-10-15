#ifndef EVAL_MATH_PARSER_HPP
#define EVAL_MATH_PARSER_HPP

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <string> // to_string and stoll

#include "helper.hpp"
#include "tokenMaker.hpp"
#include "token.hpp"
#include "oper.hpp"
#include "operations.hpp"
#include "uoper.hpp"
#include "uoperations.hpp"

#include "func.hpp"
#include "functions.hpp"

using namespace std;

class mathParser {
private:
  string expression;
  vector<Token> rpn;
  map<string, std::shared_ptr<oper>> operators;
  map<string, std::shared_ptr<uoper>> uoperators;
  map<string, std::shared_ptr<func>> functions;
  map<string, long double> variables;
  const static char decSeparator = '.', minusSign = '-';

  bool isNumber(string st) {
  	if (st.at(0) == minusSign && st.length() == 1)
  		return false;
  	for (char ch : st) {
  		if (!isdigit(ch) && ch != minusSign && ch != decSeparator)
  			return false;
  	}
  	return true;
  }

  Token *cloneToken(Token tkn) {
    Token *tkn2 = new Token();
    tkn2->type = tkn.type;
    tkn2->token = tkn.token;
    // shared_ptr<Token> ptkn = shared_ptr<Token>(tkn2);
    return tkn2;
  }

  inline const char* enumtos(token_t v)
  {
      switch (v)
      {
          case number:   return "number";
          case name:   return "name";
          case opers: return "opers";
          case uopers: return "uopers";
          case lparen: return "lparen";
          case rparen: return "rparen";
          case comma: return "comma";
      }
  }

  bool isOperatorWithHigherOrder(std::shared_ptr<oper> o1, Token *token2) {
    return (token2->type == opers && ((o1->isLeftAssoc() && o1->getPrecedence() <= operators.at(token2->token)->getPrecedence()) || (o1->getPrecedence() < operators.at(token2->token)->getPrecedence())));
  }

  vector<Token> shuntingYard() throw() {
    vector<Token> queue;
    stack<Token> stack;
    tokenMaker tokenmaker(expression, &operators, &uoperators);
    Token *prevToken = NULL, *lastFunc = NULL;
    while (tokenmaker.hasNext()) {
      Token token;
      try {
        token = tokenmaker.getNext();
      }catch(runtime_error& e) {
        cerr << e.what();
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
            throw runtime_error("Error while parsing function '" + (lastFunc->token) + "'");
          }
        break;
        case opers:
        {
          std::shared_ptr<oper> o1 = operators.at(token.token);
          Token * token2 = NULL;
          if(!stack.empty()) {
            token2 = cloneToken(stack.top());
          }else{
            token2 = NULL;
          }
          while (token2 != NULL && (isOperatorWithHigherOrder(o1, token2) || token2->type == uopers)) {
            queue.push_back(stack.top());
            stack.pop();
            if(!stack.empty()) {
              token2 = cloneToken(stack.top());
            }else{
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
            throw runtime_error("Mismatched parentheses");
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
        throw runtime_error("Mismatched parentheses");
      } else if (token.type != opers && token.type != uopers) {
        throw runtime_error("Unknown operator or function: '" + (token.token) + "'");
      }
      queue.push_back(token);
    }

    return queue;
  }

public:
  vector<Token> getRPN() {
    if (rpn.empty()) {
      rpn = shuntingYard();
    }
    return rpn;
  }

  mathParser(string expression) {
    this->expression = expression;
    add_oper(std::shared_ptr<uoper>(new plus_uoper("+")));
    add_oper(std::shared_ptr<uoper>(new minus_uoper("-")));

    add_oper(std::shared_ptr<oper>(new plus_oper("+", 20, true)));
    add_oper(std::shared_ptr<oper>(new minus_oper("-", 20, true)));
    add_oper(std::shared_ptr<oper>(new mul_oper("*", 30, true)));
    add_oper(std::shared_ptr<oper>(new dev_oper("/", 30, true)));
    add_oper(std::shared_ptr<oper>(new mod_oper("%", 30, true)));
    add_oper(std::shared_ptr<oper>(new pow_oper("^", 40, false)));

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

  void add_oper(std::shared_ptr<oper> newOper) {
    operators.insert(pair<string, std::shared_ptr<oper>>(newOper->getOper(), newOper));
  };

  void add_oper(std::shared_ptr<uoper> newOper) {
    uoperators.insert(pair<string, std::shared_ptr<uoper>>(newOper->getOper(), newOper));
  };

  void add_func(std::shared_ptr<func> newFunc) {
    functions.insert(pair<string, std::shared_ptr<func>>(newFunc->getName(), newFunc));
  };

  void add_var(string name, long double value) {
    map<string, long double>::iterator it;
    it = variables.find(str2Upper(name));
    if (it != variables.end())
      variables.erase(it);
    variables.insert(pair<string, long double>(str2Upper(name), value));
  };

  long double eval() {
    stack<long double> stack;
    for (Token token : getRPN()) {
      switch (token.type) {
        case number:
          stack.push(stold(token.token));
        break;
        case opers:
        {
          long double n1 = stack.top();
          stack.pop();
          long double n2 = stack.top();
          stack.pop();
          stack.push(operators.at(token.token)->run(n2, n1));
        }
        break;
        case uopers:
        {
          long double n = stack.top();
          stack.pop();
          stack.push(uoperators.at(token.token)->run(n));
        }
        break;
        case name:
        {
          if (variables.count(str2Upper(token.token)) > 0) {
              stack.push(variables.at(str2Upper(token.token)));
          } else if (functions.count(str2Upper(token.token)) > 0) {
              std::shared_ptr<func> f = functions.at(str2Upper(token.token));
              vector<long double> list;
              for (int i = 0; i < f->getNumParams(); i++) {
                  list.push_back(stack.top());
                  stack.pop();
              }
              long double fResult = f->run(list);
              stack.push(fResult);
          }else{
            throw runtime_error("Unknown operator, function or variable: '" + (token.token) + "'");
          }
        }
        break;
        default: break;
      }
    }
    return stack.top();
  }
};

#endif
