#include "bcp.hpp"
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

using std::string;
using i1t = std::vector<int>;
using d1t = std::vector<double>;
using d2t = std::vector<std::vector<double>>;

int main()
{
  const string filename = "../tests/yaml/test-01.yml";
  auto loader = bcp_loader(filename);

  cout << "  Testing bool parsing..." << endl;
  assert(loader.read<bool>("bool_p"));

  cout << "  Testing int parsing..." << endl;
  assert(loader.read<int>("int_p") == -12);

  cout << "  Testing size_t parsing..." << endl;
  assert(loader.read<size_t>("uint_p") == 123);

  cout << "  Testing double parsing..." << endl;
  assert(loader.read<double>("double_p") == 45.82);

  cout << "  Testing string parsing..." << endl;
  assert(loader.read<string>("string_p") == "abc");

  cout << "  Testing vector<int> parsing..." << endl;
  assert(loader.read<i1t>("i1t_p") == i1t({1, -2, 3}));

  cout << "  Testing vector<int> parsing, single component..."
       << endl;
  assert(loader.read<i1t>("i1t_p1") == i1t({1}));

  cout << "  Testing vector<double> parsing..." << endl;
  assert(loader.read<d1t>("d1t_p") == d1t({1.0, -2.45, 77}));

  cout << "  Testing vector<vector<double>> parsing..."
       << endl;
  assert(loader.read<d2t>("d2t_p")
         == d2t({{1.0, 2.0}, {3.0, 4.0}}));

  cout << "Test completed successfully" << endl;
}
