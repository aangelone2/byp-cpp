#include "test.hpp"

using byp::format;

int main()
{
  cout << "Testing bool formatting..." << endl;
  const bool b = true;
  assert(format(b) == "true");

  cout << "Testing int formatting..." << endl;
  const int i = -1238829929;
  assert(format(i) == "-1238829929");

  cout << "Testing size_t formatting..." << endl;
  const size_t lui = 1030004;
  assert(format(lui) == "1030004");

  cout << "Testing size_t formatting..." << endl;

  const double d1 = 1.0e12;
  assert(format(d1) == "1.000000e+12");

  const double d2 = 1.442e-12;
  assert(format(d2) == "1.442000e-12");

  const double d3 = 1.4788565488e-8;
  assert(format(d3) == "1.478857e-08");

  const double d4 = 1.0e-4;
  assert(format(d4) == "1.000000e-04");

  cout << "Testing string formatting..." << endl;
  const string s = "kkalsjjjdi\"";
  assert(format(s) == s);

  cout << "Testing vector<int> formatting..." << endl;
  const i1t ivec1 = i1t({1, 2, 3, 4});
  assert(format(ivec1) == "[1, 2, 3, 4]");

  cout << "Testing 1-component vector<int>..." << endl;
  const i1t ivec2 = i1t({1});
  assert(format(ivec2) == "[1]");

  cout << "Testing vector<double> formatting..." << endl;
  const d1t dvec = d1t({7.0, 8.0e-8, 1.0e-4, 9});
  assert(
      format(dvec)
      == "[7.000000e+00, 8.000000e-08, 1.000000e-04, "
         "9.000000e+00]"
  );

  cout << "Testing vector<string> formatting..." << endl;
  const s1t svec = s1t({"abc", "def hgi", "jhy jjj "});
  assert(format(svec) == "[abc, def hgi, jhy jjj ]");

  cout << "Testing vector<vector<int>> formatting..."
       << endl;
  const i2t itab1 = i2t({{1, 2, 3, 4}, {5, 6, 7, 8}});
  assert(
      format(itab1) == "[[1, 2, 3, 4], [5, 6, 7, 8]]"
  );

  cout << "Testing 1-component vector<vector<int>>..."
       << endl;
  const i2t itab2 = i2t({{1, 2, 3, 4}});
  assert(format(itab2) == "[[1, 2, 3, 4]]");

  close_test();
}
