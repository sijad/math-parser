#ifndef EVAL_MATH_HELPER_HPP
#define EVAL_MATH_HELPER_HPP

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
const long double PI = acos(-1.0L);

static inline long double rad(long double a) {
  return a*PI/180;
}

static inline long double deg(long double a) {
  return (a * 180)/PI;
}

static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

static inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}

static inline std::string str2Upper(std::string str) {
  std::string s = str;
  transform(s.begin(), s.end(), s.begin(), toupper);
  return s;
}

static inline long double randNum() {
  static std::default_random_engine generator(time(NULL));
  static std::uniform_real_distribution<float> distribution(0.0,1.0);
  return distribution(generator);
}

#endif
