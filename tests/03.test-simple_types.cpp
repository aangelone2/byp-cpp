#include "byp.hpp"
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
  auto loader = byp_loader(filename);



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



  cout << "  Testing (+) parsing for int..." << endl;
  assert(loader.read<int>("positive") == 8);

  cout << "  Testing invalid position for sign for int..." << endl;
  try
  {
    [[maybe_unused]] const int invalid_sign
        = loader.read<int>("invalid_sign");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '1+4' while expecting int");
  }

  cout << "  Testing double sign for int..." << endl;
  try
  {
    [[maybe_unused]] const int double_sign
        = loader.read<int>("double_sign");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '++12' while expecting int");
  }

  cout << "  Testing float parsing for int..." << endl;
  try
  {
    [[maybe_unused]] const int flt
        = loader.read<int>("flt");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '12.4' while expecting int");
  }

  cout << "  Testing scientific parsing for int..." << endl;
  try
  {
    [[maybe_unused]] const int scientific
        = loader.read<int>("scientific");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '1e+6' while expecting int");
  }

  cout << "  Testing invalid values for int..." << endl;
  try
  {
    [[maybe_unused]] const int invalid
        = loader.read<int>("invalid");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read 'cde' while expecting int");
  }


  cout << "  Testing (+) parsing for size_t..." << endl;
  try
  {
    [[maybe_unused]] const size_t positive
        = loader.read<size_t>("positive");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '+8' while expecting size_t");
  }

  cout << "  Testing (-) parsing for size_t..." << endl;
  try
  {
    [[maybe_unused]] const size_t negative
        = loader.read<size_t>("negative");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '-12' while expecting size_t");
  }

  cout << "  Testing float parsing for size_t..." << endl;
  try
  {
    [[maybe_unused]] const size_t flt
        = loader.read<size_t>("flt");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '12.4' while expecting size_t");
  }

  cout << "  Testing scientific parsing for size_t..." << endl;
  try
  {
    [[maybe_unused]] const size_t scientific
        = loader.read<size_t>("scientific");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read '1e+6' while expecting size_t");
  }

  cout << "  Testing invalid values for size_t..." << endl;
  try
  {
    [[maybe_unused]] const size_t invalid
        = loader.read<size_t>("invalid");
    assert(false);
  }
  catch (const iva& err)
  {
    assert(string(err.what())
           == "read 'cde' while expecting size_t");
  }



  cout << "  Testing float parsing for double..." << endl;
  assert(loader.read<double>("flt") == 12.4);

  cout << "  Testing scientific parsing for double..." << endl;
  assert(loader.read<double>("scientific") == 1.0e+6);
  assert(loader.read<double>("scientific_2") == 1.5e-6);

  cout << "  Testing int parsing for double..." << endl;
  assert(loader.read<double>("int_for_double") == 7.0);

  cout << "  Testing (+) parsing for double..." << endl;
  assert(loader.read<double>("positive") == 8.0);

  cout << "  Testing (-) parsing for double..." << endl;
  assert(loader.read<double>("negative") == -12);

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

  cout << "  Testing quote parsing for string..." << endl;
  assert(loader.read<string>("quotes_in_string") == "\"ab\" c\"d ef");

  cout << "Test completed successfully" << endl;
}
