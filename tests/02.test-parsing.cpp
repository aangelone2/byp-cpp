#include "byp.hpp"
#include <cassert>
#include <iostream>
#include <vector>

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
  auto loader = byp::parser(filename);

  cout << "  Testing many-spaced key..." << endl;
  assert(loader.read<int>("many_spaces") == 4);

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

  cout << "  Testing spaces before string..." << endl;
  assert(loader.read<string>("spaces_before_string") == "abc");

  cout << "  Testing spaces inside and after string..."
       << endl;
  assert(loader.read<string>("spaces_inside_after_string")
         == "def ghi");

  cout << "  Testing nonexistent key..." << endl;
  try
  {
    [[maybe_unused]] const int no_spaces
        = loader.read<int>("not_existing");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "key 'not_existing' invalid or missing");
  }

  cout << "  Testing partial comment..." << endl;
  assert(loader.read<int>("partial_comment") == 123);

  cout << "  Testing partial multiple comment..." << endl;
  assert(loader.read<int>("partial_multiple_comment") == 123);

  // If any of the previous tests succeeded,
  // comments and empty lines were successfully ignored
  cout << "  Testing empty and commented lines..." << endl;

  cout << "Test completed successfully" << endl;
}
