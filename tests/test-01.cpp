#include "bcp.hpp"
#include <cassert>

using std::string;
using i1t = std::vector<int>;
using d1t = std::vector<double>;
using d2t = std::vector<std::vector<double>>;

int main()
{
  const string filename = "../tests/test-01.yaml";
  auto loader = bcp_loader(filename);

  const int bool_p = loader.read<bool>("bool_p");
  assert(bool_p);

  const int int_p = loader.read<int>("int_p");
  assert(int_p == -12);

  const size_t uint_p = loader.read<size_t>("uint_p");
  assert(uint_p == 123);

  const double double_p = loader.read<double>("double_p");
  assert(double_p == 45.82);

  const string string_p = loader.read<string>("string_p");
  assert(string_p == "abc");

  const i1t i1t_p = loader.read<i1t>("i1t_p");
  assert(i1t_p == i1t({1, -2, 3}));

  const i1t i1t_p1 = loader.read<i1t>("i1t_p1");
  assert(i1t_p1 == i1t({1}));

  const d1t d1t_p = loader.read<d1t>("d1t_p");
  assert(d1t_p == d1t({1.0, -2.45, 77}));

  const d2t d2t_p = loader.read<d2t>("d2t_p");
  assert(d2t_p == d2t({{1.0, 2.0}, {3.0, 4.0}}));
}
