#include "test.hpp"

int main()
{
  logger lgr;

  lgr.set_scientific(true);
  lgr.set_precision(5);

  cout << "  Testing bool formatting..." << endl;
  const bool b = true;
  assert(lgr.format(b) == "true");

  cout << "  Testing int formatting..." << endl;
  const int i = -1238829929;
  assert(lgr.format(i) == "-1238829929");

  cout << "  Testing size_t formatting..." << endl;
  const size_t lui = 1030004;
  assert(lgr.format(lui) == "1030004");

  cout << "  Testing double formatting..." << endl;

  const double d1 = 1.0e12;
  assert(lgr.format(d1) == "1.00000e+12");

  const double d2 = 1.442e-12;
  assert(lgr.format(d2) == "1.44200e-12");

  const double d3 = 1.4788565488e-8;
  assert(lgr.format(d3) == "1.47886e-08");

  const double d4 = 1.0e-4;
  assert(lgr.format(d4) == "1.00000e-04");

  const double d5 = 11234.5678;
  assert(lgr.format(d5) == "1.12346e+04");

  cout << "  Testing string formatting..." << endl;
  const string s = "kkalsjjjdi\"";
  assert(lgr.format(s) == s);

  cout << "  Testing vector<int> formatting..." << endl;
  const i1t ivec1 = i1t({1, 2, 3, 4});
  assert(lgr.format(ivec1) == "[1, 2, 3, 4]");

  cout << "  Testing 1-component vector<int>..." << endl;
  const i1t ivec2 = i1t({1});
  assert(lgr.format(ivec2) == "[1]");

  cout << "  Testing vector<double> formatting..."
       << endl;
  const d1t dvec
      = d1t({7.000006, 8.000003e-8, 1.000005e-4, 9});
  assert(
      lgr.format(dvec)
      == "[7.00001e+00, 8.00000e-08, 1.00000e-04, "
         "9.00000e+00]"
  );

  cout << "  Testing vector<string> formatting..."
       << endl;
  const s1t svec = s1t({"abc", "def hgi", "jhy jjj "});
  assert(lgr.format(svec) == "[abc, def hgi, jhy jjj ]");

  cout << "  Testing vector<vector<int>> formatting..."
       << endl;
  const i2t itab1 = i2t({{1, 2, 3, 4}, {5, 6, 7, 8}});
  assert(
      lgr.format(itab1) == "[[1, 2, 3, 4], [5, 6, 7, 8]]"
  );

  cout << "  Testing 1-component vector<vector<int>>..."
       << endl;
  const i2t itab2 = i2t({{1, 2, 3, 4}});
  assert(lgr.format(itab2) == "[[1, 2, 3, 4]]");

  cout << "  Testing resetting..." << endl;

  lgr.set_scientific();
  lgr.set_precision();

  const double d6 = 1889.72689;
  assert(lgr.format(d6) == "1889.73");

  const double d7 = 11234.5678;
  assert(lgr.format(d7) == "11234.6");

  close_test();
}
