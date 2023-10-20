#include "bcp.hpp"
#include <cassert>
#include <iostream>
#include <limits>

using std::cout;
using std::endl;
using std::string;

using iva = std::invalid_argument;

int main()
{
  const string filename = "../tests/yaml/test-03.yml";
  auto loader = bcp_loader(filename);

  cout << "  Testing invalid bool..." << endl;
  try
  {
    [[maybe_unused]] const bool invalid_bool_1
        = loader.read<bool>("invalid_bool_1");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '1' while expecting bool");
  }
  try
  {
    [[maybe_unused]] const bool invalid_bool_2
        = loader.read<bool>("invalid_bool_2");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read 'abc' while expecting bool");
  }

  cout << "  Testing float parsing for int..." << endl;
  assert(loader.read<int>("float_for_int_1") == 12);
  assert(loader.read<int>("float_for_int_2") == 12);

  cout << "  Testing invalid values for int..." << endl;
  try
  {
    [[maybe_unused]] const int invalid_int
        = loader.read<int>("invalid_int");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read 'cde' while expecting int");
  }

  cout << "  Testing float parsing for size_t..." << endl;
  assert(loader.read<size_t>("float_for_sizet") == 12);
  assert(loader.read<size_t>("float_for_sizet") == 12);

  cout << "  Testing invalid values for size_t..." << endl;
  try
  {
    [[maybe_unused]] const size_t invalid_sizet
        = loader.read<size_t>("invalid_for_sizet");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read 'fgh' while expecting size_t");
  }

  cout << "  Testing int parsing for double..." << endl;
  assert(loader.read<double>("int_for_double") == 7.0);

  cout << "  Testing invalid values for double..." << endl;
  try
  {
    [[maybe_unused]] const double invalid_double
        = loader.read<double>("invalid_for_double");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read 'ilm' while expecting double");
  }

  cout << "  Testing int parsing for string..." << endl;
  assert(loader.read<string>("int_for_string") == "1");

  cout << "  Testing space parsing for string..." << endl;
  assert(loader.read<string>("spaces_in_string") == "a b c");

  cout << "Test completed successfully" << endl;
}
