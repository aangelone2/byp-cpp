#include "bcp.hpp"
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using i1t = vector<int>;
using i2t = vector<vector<int>>;
using iva = std::invalid_argument;

int main()
{
  const string filename = "../tests/yaml/test-02.yml";
  auto loader = bcp_loader(filename);

  cout << "  Testing no-space key..." << endl;
  try
  {
    assert(loader.read<int>("no_spaces") != 1);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "key 'no_spaces' invalid or missing");
  }

  cout << "  Testing many-spaced key..." << endl;
  assert(loader.read<int>("many_spaces") == 4);

  cout << "  Testing spaces in key..." << endl;
  try
  {
    [[maybe_unused]] const int spaces_in_key
        = loader.read<int>("spaces in key");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "key 'spaces in key' invalid or missing");
  }

  cout << "  Testing spaces before key..." << endl;
  assert(loader.read<int>("spaces_before_key") == 8);

  cout << "  Testing spaces after key..." << endl;
  assert(loader.read<int>("spaces_after_key") == 3);

  cout << "  Testing spaces after value..." << endl;
  assert(loader.read<bool>("spaces_after_value"));

  cout << "  Testing spaces after vector..." << endl;
  assert(loader.read<i1t>("spaces_after_vector")
         == i1t({1, 2, 3}));

  cout << "  Testing spaces everywhere table..." << endl;
  assert(
      loader.read<i2t>("spaces_everywhere_table")
      == i2t({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}}));

  cout << "Test completed successfully" << endl;
}
