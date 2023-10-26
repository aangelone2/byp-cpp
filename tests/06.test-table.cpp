#include "test.hpp"

int main()
{
  const string filename = "../tests/yaml/test-06.yml";
  auto parser = byp::parser(filename);

  cout << "  Testing vector<vector<int>>..." << endl;
  assert(
      parser.read<i2t>("i2t") == i2t({{1, -2, 3}, {4, 5, 6}})
  );

  cout << "  Testing float input for vector<vector<int>>..."
       << endl;
  test_exception<i2t, iva>(
      "float_i2t",
      "read '-4.1' while expecting integral",
      parser
  );

  cout << "  Testing invalid input for vector<vector<int>>..."
       << endl;
  test_exception<i2t, iva>(
      "invalid_i2t",
      "read 'a' while expecting integral",
      parser
  );

  cout
      << "  Testing empty component for vector<vector<int>>..."
      << endl;
  test_exception<i2t, iva>(
      "empty_i2t", "read '' while expecting integral", parser
  );

  cout << "  Testing vector<vector<size_t>>..." << endl;
  assert(
      parser.read<z2t>("z2t") == z2t({{4, 5, 6}, {7, 8, 9}})
  );

  cout << "  Testing vector<vector<double>>..." << endl;
  assert(
      parser.read<d2t>("d2t")
      == d2t({{7.0, 8.1, 9.4}, {1.0, 2.0, 4.1}})
  );

  cout << "  Testing invalid input for "
          "vector<vector<double>>..."
       << endl;
  test_exception<d2t, iva>(
      "invalid_d2t",
      "read 'a' while expecting floating-point",
      parser
  );

  cout << "  Testing bracket inside vector<vector<double>>..."
       << endl;
  test_exception<d2t, iva>(
      "bracket_inside_d2t",
      "read '[[7.0, [8.1, 2.0], [1.0, 2.0, 3.0]]' while "
      "expecting vector<vector<>>",
      parser
  );

  cout << "  Testing vector<vector<string>>..." << endl;
  assert(
      parser.read<s2t>("s2t")
      == s2t({{"abc", "def"}, {"ghi lkm", "ejg"}})
  );

  cout << "  Testing single-component vector<vector<int>>..."
       << endl;
  assert(
      parser.read<i2t>("single_component_ok")
      == i2t({{4, 5, 6}})
  );
  test_exception<i2t, iva>(
      "single_component_wrong",
      "read '[1,2,3]' while expecting vector<vector<>>",
      parser
  );

  cout << "  Testing trailing comma..." << endl;
  assert(
      parser.read<i2t>("trailing_comma")
      == i2t({{1, 2}, {3, 4}, {5, 6}})
  );

  cout << "  Testing incomplete table..." << endl;
  test_exception<i2t, iva>(
      "incomplete_table_1",
      "read '[[1,2]' while expecting vector<vector<>>",
      parser
  );
  test_exception<i2t, iva>(
      "incomplete_table_2",
      "read '[[1,2' while expecting vector<vector<>>",
      parser
  );

  cout << "  Testing valid empty table..." << endl;
  assert(parser.read<i2t>("empty_1") == i2t({{}}));
  test_exception<i2t, iva>(
      "empty_2", "read '' while expecting integral", parser
  );
  test_exception<i2t, iva>(
      "empty_3", "read '' while expecting integral", parser
  );
  test_exception<i2t, iva>(
      "empty_4", "read '' while expecting integral", parser
  );

  close_test();
}
