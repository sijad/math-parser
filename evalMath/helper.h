#ifndef EVAL_MATH_HELPER_H
#define EVAL_MATH_HELPER_H

#include <iostream>
#include <ctime>
#include <cmath>
#include <random>
#include <type_traits>

#define FOR_EACH(i, c)                              \
  if (bool FOR_EACH_state1 = false) {} else         \
    for (auto && FOR_EACH_state2 = (c);             \
         !FOR_EACH_state1; FOR_EACH_state1 = true)  \
      for (auto i = FOR_EACH_state2.begin();        \
           i != FOR_EACH_state2.end(); ++i)

#define FOR_EACH_ENUMERATE(count, i, c)                                \
  if (bool FOR_EACH_state1 = false) {} else                            \
    for (auto && FOR_EACH_state2 = (c);                                \
         !FOR_EACH_state1; FOR_EACH_state1 = true)                     \
      if (size_t FOR_EACH_privateCount = 0) {} else                    \
        if (const size_t& count = FOR_EACH_privateCount) {} else       \
          for (auto i = FOR_EACH_state2.begin();                       \
               i != FOR_EACH_state2.end(); ++FOR_EACH_privateCount, ++i)


// const long double PI = 3.14159265358979323846264338327950288419716939937510L;
const long double PI = std::acos(-1.0L);
// const long double PI = std::atan(1.0L) * 4;

long double rad(long double a);

long double deg(long double a);

std::string &ltrim(std::string &s);

std::string &rtrim(std::string &s);

std::string &trim(std::string &s);

std::string str2Upper(std::string str);

long double randNum();

#endif
