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
  auto l1 = bcp_loader("../tests/yaml/test-04-1.yml");

  cout << "  Testing spaces in key..." << endl;
  try
  {
    [[maybe_unused]] const int spaces_in_key
        = l1.read<int>("spaces in key");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "invalid key-value pair at row 4");
  }

  auto l2 = bcp_loader("../tests/yaml/test-04-2.yml");

  cout << "  Testing no-space key..." << endl;
  try
  {
    [[maybe_unused]] const int no_spaces
        = l2.read<int>("no_spaces");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "invalid key-value pair at row 4");
  }

  cout << "Test completed successfully" << endl;
}
