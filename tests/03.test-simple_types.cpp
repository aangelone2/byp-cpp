#include "test.hpp"

int main()
{
  const string filename = "../tests/yaml/test-03.yml";
  auto parser = byp::parser(filename);

  cout << "  Testing invalid bool..." << endl;
  test_exception<bool, iva>(
      "invalid_bool_1", "read '1' while expecting bool", parser
  );
  test_exception<bool, iva>(
      "invalid_bool_2",
      "read 'abc' while expecting bool",
      parser
  );

  cout << "  Testing (+) parsing for int..." << endl;
  assert(parser.read<int>("positive") == 8);

  cout << "  Testing invalid sign position for int..." << endl;
  test_exception<int, iva>(
      "invalid_sign", "read '1+4' while expecting int", parser
  );

  cout << "  Testing double sign for int..." << endl;
  test_exception<int, iva>(
      "double_sign", "read '++12' while expecting int", parser
  );

  cout << "  Testing float parsing for int..." << endl;
  test_exception<int, iva>(
      "flt", "read '12.4' while expecting int", parser
  );

  cout << "  Testing scientific parsing for int..." << endl;
  test_exception<int, iva>(
      "scientific", "read '1e+6' while expecting int", parser
  );

  cout << "  Testing invalid values for int..." << endl;
  test_exception<int, iva>(
      "invalid", "read 'cde' while expecting int", parser
  );

  cout << "  Testing (+) parsing for size_t..." << endl;
  test_exception<size_t, iva>(
      "positive", "read '+8' while expecting size_t", parser
  );

  cout << "  Testing (-) parsing for size_t..." << endl;
  test_exception<size_t, iva>(
      "negative", "read '-12' while expecting size_t", parser
  );

  cout << "  Testing float parsing for size_t..." << endl;
  test_exception<size_t, iva>(
      "flt", "read '12.4' while expecting size_t", parser
  );

  cout << "  Testing scientific parsing for size_t..." << endl;
  test_exception<size_t, iva>(
      "scientific",
      "read '1e+6' while expecting size_t",
      parser
  );

  cout << "  Testing invalid values for size_t..." << endl;
  test_exception<size_t, iva>(
      "invalid", "read 'cde' while expecting size_t", parser
  );

  cout << "  Testing float parsing for double..." << endl;
  assert(parser.read<double>("flt") == 12.4);

  cout << "  Testing scientific parsing for double..." << endl;
  assert(parser.read<double>("scientific") == 1.0e+6);
  assert(parser.read<double>("scientific_2") == 1.5e-6);

  cout << "  Testing int parsing for double..." << endl;
  assert(parser.read<double>("int_for_double") == 7.0);

  cout << "  Testing (+) parsing for double..." << endl;
  assert(parser.read<double>("positive") == 8.0);

  cout << "  Testing (-) parsing for double..." << endl;
  assert(parser.read<double>("negative") == -12);

  cout << "  Testing invalid values for double..." << endl;
  test_exception<double, iva>(
      "invalid_for_double",
      "read 'ilm' while expecting double",
      parser
  );

  cout << "  Testing int parsing for string..." << endl;
  assert(parser.read<string>("int_for_string") == "1");

  cout << "  Testing space parsing for string..." << endl;
  assert(parser.read<string>("spaces_in_string") == "a b c");

  cout << "  Testing quote parsing for string..." << endl;
  assert(
      parser.read<string>("quotes_in_string")
      == "\"ab\" c\"d ef"
  );

  cout << "  Testing colon in string..." << endl;
  assert(
      parser.read<string>("colon_in_string") == "ab:cm:: o"
  );

  cout << "  Testing comma in string..." << endl;
  assert(parser.read<string>("comma_in_string") == "ab,cm");

  cout << "  Testing hash in string..." << endl;
  assert(parser.read<string>("hash_in_string") == "ab");

  close_test();
}
