#include "test.hpp"

int main()
{
  cout << "  Testing missing file..." << endl;
  try
  {
    [[maybe_unused]] auto p0 = byp::parser("../tests/yaml/not-existent.yaml");
    assert(false);
  }
  catch(const iva& err)
  {
    assert(string(err.what()) == "file '../tests/yaml/not-existent.yaml' not found");
  }

  auto p1 = byp::parser("../tests/yaml/test-04-1.yml");

  cout << "  Testing spaces in key..." << endl;
  test_exception<int, iva>(
      "spaces in key", "invalid key-value pair at row 4", p1);

  auto p2 = byp::parser("../tests/yaml/test-04-2.yml");

  cout << "  Testing no-space key..." << endl;
  test_exception<int, iva>(
      "no_spaces", "invalid key-value pair at row 4", p2);

  close_test();
}
