#include "byp.hpp"
#include <cassert>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using i1t = vector<int>;
using z1t = vector<size_t>;
using d1t = vector<double>;
using s1t = vector<string>;
using iva = std::invalid_argument;

int main()
{
  const string filename = "../tests/yaml/test-05.yml";
  auto loader = byp_loader(filename);

  cout << "  Testing vector<int>..." << endl;
  assert(loader.read<i1t>("i1t") == i1t({1,-2,3}));

  cout << "  Testing float input for vector<int>..." << endl;
  try
  {
    [[maybe_unused]] const i1t float_i1t
        = loader.read<i1t>("float_i1t");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read '-2.1' while expecting int");
  }

  cout << "  Testing invalid input for vector<int>..." << endl;
  try
  {
    [[maybe_unused]] const i1t invalid_i1t
        = loader.read<i1t>("invalid_i1t");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read 'a' while expecting int");
  }

  cout << "  Testing empty component for vector<int>..." << endl;
  try
  {
    [[maybe_unused]] const i1t empty_i1t
        = loader.read<i1t>("empty_i1t");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read '' while expecting int");
  }

  cout << "  Testing vector<size_t>..." << endl;
  assert(loader.read<z1t>("z1t") == z1t({4,5,6}));

  cout << "  Testing invalid input for vector<size_t>..." << endl;
  try
  {
    [[maybe_unused]] const z1t invalid_z1t
        = loader.read<z1t>("invalid_z1t");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read 'a' while expecting size_t");
  }

  cout << "  Testing vector<double>..." << endl;
  assert(loader.read<d1t>("d1t") == d1t({7.0, 8.1, 9.4}));

  cout << "  Testing invalid input for vector<double>..." << endl;
  try
  {
    [[maybe_unused]] const d1t invalid_d1t
        = loader.read<d1t>("invalid_d1t");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read 'a' while expecting double");
  }

  cout << "  Testing bracket inside vector<double>..." << endl;
  try
  {
    [[maybe_unused]] const d1t bracket_inside_d1t
        = loader.read<d1t>("bracket_inside_d1t");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read '[7.0, [8.1, 2.0]' while expecting vector");
  }

  cout << "  Testing vector<string>..." << endl;
  assert(loader.read<s1t>("s1t") == s1t({"abc", "def", "ghi lkm", "ejg"}));

  cout << "  Testing incomplete vector..." << endl;
  try
  {
    [[maybe_unused]] const i1t incomplete_vector_1
        = loader.read<i1t>("incomplete_vector_1");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read '[1,2,' while expecting vector");
  }
  try
  {
    [[maybe_unused]] const i1t incomplete_vector_2
        = loader.read<i1t>("incomplete_vector_2");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read '[1,2' while expecting vector");
  }
  try
  {
    [[maybe_unused]] const i1t incomplete_vector_3
        = loader.read<i1t>("incomplete_vector_3");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
        == "read '[1,2' while expecting vector");
  }

  cout << "Test completed successfully" << endl;
}
