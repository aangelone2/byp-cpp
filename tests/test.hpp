#ifndef BYPCPP_TEST_HPP
#define BYPCPP_TEST_HPP

#include "byp-cpp/logger.hpp"
#include "byp-cpp/parser.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using i1t = vector<int>;
using z1t = vector<size_t>;
using d1t = vector<double>;
using s1t = vector<string>;
using i2t = vector<vector<int>>;
using z2t = vector<vector<size_t>>;
using d2t = vector<vector<double>>;
using s2t = vector<vector<string>>;

using iva = std::invalid_argument;

using byp::logger;
using byp::parser;

const string sep = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ";

inline void close_test()
{
  cout << sep << "Test completed successfully" << endl << endl;
}

template <typename EXC>
void assert_fail_build(const string& filename, const string& message)
{
  try
  {
    [[maybe_unused]] const parser parser(filename);
    assert(false);
  }
  catch (const EXC& err)
  {
    assert(string(err.what()) == message);
  }
}

template <typename T, typename EXC>
void assert_fail_get(const string& key, const string& message, parser& parser)
{
  try
  {
    [[maybe_unused]] T buffer = parser.get<T>(key);
    assert(false);
  }
  catch (const EXC& err)
  {
    assert(string(err.what()) == message);
  }
}

#endif
