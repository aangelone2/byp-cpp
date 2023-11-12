#include "test.hpp"

int main()
{
  const string filename = "../tests/yaml/test-01.yml";
  const parser prs(filename);

  cout << "  Testing bool parsing..." << endl;
  assert(prs.get<bool>("bool_p"));

  cout << "  Testing int parsing..." << endl;
  assert(prs.get<int>("int_p") == -12);

  cout << "  Testing size_t parsing..." << endl;
  assert(prs.get<size_t>("uint_p") == 123);

  cout << "  Testing double parsing..." << endl;
  assert(prs.get<double>("double_p") == 45.82);

  cout << "  Testing string parsing..." << endl;
  assert(prs.get<string>("string_p") == "abc");

  cout << "  Testing vector<int> parsing..." << endl;
  assert(prs.get<i1t>("i1t_p") == i1t({1, -2, 3}));

  cout << "  Testing vector<int> parsing, single "
          "component..."
       << endl;
  assert(prs.get<i1t>("i1t_p1") == i1t({1}));

  cout << "  Testing vector<double> parsing..." << endl;
  assert(prs.get<d1t>("d1t_p") == d1t({1.0, -2.45, 77}));

  cout << "  Testing vector<vector<double>> parsing..."
       << endl;
  assert(
      prs.get<d2t>("d2t_p")
      == d2t({{1.0, 2.0}, {3.0, 4.0}})
  );

  close_test();
}
