#include "test.hpp"

int main()
{
  const string filename = "../tests/yaml/test-02.yml";
  parser prs(filename);

  cout << "  Testing many-spaced key..." << endl;
  assert(prs.get<int>("many_spaces") == 4);

  cout << "  Testing spaces before key..." << endl;
  assert(prs.get<int>("spaces_before_key") == 8);

  cout << "  Testing spaces after key..." << endl;
  assert(prs.get<int>("spaces_after_key") == 3);

  cout << "  Testing spaces after value..." << endl;
  assert(prs.get<bool>("spaces_after_value"));

  cout << "  Testing spaces after vector..." << endl;
  assert(prs.get<i1t>("spaces_after_vector") == i1t({1, 2, 3}));

  cout << "  Testing spaces everywhere table..." << endl;
  assert(
      prs.get<i2t>("spaces_everywhere_table")
      == i2t({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}})
  );

  cout << "  Testing spaces before string..." << endl;
  assert(prs.get<string>("spaces_before_string") == "abc");

  cout << "  Testing spaces inside and after string..." << endl;
  assert(prs.get<string>("spaces_inside_after_string") == "def ghi");

  cout << "  Testing nonexistent key..." << endl;
  assert_fail_get<int, iva>(
      "not_existing", "key 'not_existing' not found", prs
  );

  cout << "  Testing partial comment..." << endl;
  assert(prs.get<int>("partial_comment") == 123);

  cout << "  Testing partial multiple comment..." << endl;
  assert(prs.get<int>("partial_multiple_comment") == 123);

  // If any of the previous tests succeeded, comments and empty lines were
  // successfully ignored
  cout << "  Testing empty and commented lines..." << endl;

  close_test();
}
