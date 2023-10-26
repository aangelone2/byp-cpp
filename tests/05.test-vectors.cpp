#include "test.hpp"

int main()
{
  const string filename = "../tests/yaml/test-05.yml";
  auto parser = byp::parser(filename);

  cout << "  Testing vector<int>..." << endl;
  assert(parser.read<i1t>("i1t") == i1t({1, -2, 3}));

  cout << "  Testing float input for vector<int>..." << endl;
  test_exception<i1t, iva>(
      "float_i1t",
      "read '-2.1' while expecting integral",
      parser
  );

  cout << "  Testing invalid input for vector<int>..." << endl;
  test_exception<i1t, iva>(
      "invalid_i1t",
      "read 'a' while expecting integral",
      parser
  );

  cout << "  Testing empty component for vector<int>..."
       << endl;
  test_exception<i1t, iva>(
      "empty_i1t", "read '' while expecting integral", parser
  );

  cout << "  Testing vector<size_t>..." << endl;
  assert(parser.read<z1t>("z1t") == z1t({4, 5, 6}));

  cout << "  Testing invalid input for vector<size_t>..."
       << endl;
  test_exception<z1t, iva>(
      "invalid_z1t",
      "read 'a' while expecting unsigned",
      parser
  );

  cout << "  Testing vector<double>..." << endl;
  assert(parser.read<d1t>("d1t") == d1t({7.0, 8.1, 9.4}));

  cout << "  Testing invalid input for vector<double>..."
       << endl;
  test_exception<d1t, iva>(
      "invalid_d1t",
      "read 'a' while expecting floating-point",
      parser
  );

  cout << "  Testing bracket inside vector<double>..." << endl;
  test_exception<d1t, iva>(
      "bracket_inside_d1t",
      "read '[7.0, [8.1, 2.0]' while expecting vector<>",
      parser
  );

  cout << "  Testing vector<string>..." << endl;
  assert(
      parser.read<s1t>("s1t")
      == s1t({"abc", "def", "ghi lkm", "ejg"})
  );

  cout << "  Testing incomplete vector..." << endl;
  test_exception<i1t, iva>(
      "incomplete_vector_1",
      "read '[1,2,' while expecting vector<>",
      parser
  );
  test_exception<i1t, iva>(
      "incomplete_vector_2",
      "read '[1,2' while expecting vector<>",
      parser
  );
  test_exception<i1t, iva>(
      "incomplete_vector_3",
      "read '[1,2' while expecting vector<>",
      parser
  );

  cout << "  Trailing comma..." << endl;
  assert(parser.read<i1t>("trailing_comma") == i1t({1, 2}));

  cout << "  Testing valid empty vector..." << endl;
  assert(parser.read<i1t>("empty_1") == i1t({}));

  cout << "  Testing invalid empty vector..." << endl;
  test_exception<i1t, iva>(
      "empty_2", "read '' while expecting integral", parser
  );
  test_exception<i1t, iva>(
      "empty_3", "read '' while expecting integral", parser
  );
  test_exception<i1t, iva>(
      "empty_4", "read '' while expecting integral", parser
  );

  close_test();
}
