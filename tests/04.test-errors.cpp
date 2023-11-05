#include "test.hpp"

int main()
{
  cout << "  Testing missing file..." << endl;
  assert_fail_build<iva>(
      "../tests/yaml/not-existent.yml",
      "file '../tests/yaml/not-existent.yml' not found"
  );

  cout << "  Testing spaces in key..." << endl;
  assert_fail_build<iva>(
      "../tests/yaml/test-04-1.yml",
      "invalid key-value pair at row 4"
  );

  cout << "  Testing no-space key..." << endl;
  assert_fail_build<iva>(
      "../tests/yaml/test-04-2.yml",
      "invalid key-value pair at row 4"
  );

  cout << "  Testing colon in key..." << endl;
  assert_fail_build<iva>(
      "../tests/yaml/test-04-3.yml",
      "invalid key 'colon:in:key' at row 4"
  );

  cout << "  Testing duplicate key..." << endl;
  assert_fail_build<iva>(
      "../tests/yaml/test-04-4.yml",
      "duplicate key 'test_2' at row 4"
  );

  close_test();
}
