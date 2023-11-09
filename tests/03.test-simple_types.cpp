#include "test.hpp"

int main()
{
  const string filename = "../tests/yaml/test-03.yml";
  const byp::parser parser(filename);

  cout << "  Testing invalid bool..." << endl;
  assert_fail_get<bool, iva>(
      "invalid_bool_1",
      "read '1' while expecting bool",
      parser
  );
  assert_fail_get<bool, iva>(
      "invalid_bool_2",
      "read 'abc' while expecting bool",
      parser
  );

  cout << "  Testing (+) parsing for int..." << endl;
  assert(parser.get<int>("positive") == 8);

  cout << "  Testing invalid sign position for int..."
       << endl;
  assert_fail_get<int, iva>(
      "invalid_sign",
      "read '1+4' while expecting integral",
      parser
  );

  cout << "  Testing double sign for int..." << endl;
  assert_fail_get<int, iva>(
      "double_sign",
      "read '++12' while expecting integral",
      parser
  );

  cout << "  Testing float parsing for int..." << endl;
  assert_fail_get<int, iva>(
      "flt",
      "read '12.4' while expecting integral",
      parser
  );

  cout << "  Testing scientific parsing for int..."
       << endl;
  assert_fail_get<int, iva>(
      "scientific",
      "read '1e+6' while expecting integral",
      parser
  );

  cout << "  Testing invalid values for int..." << endl;
  assert_fail_get<int, iva>(
      "invalid",
      "read 'cde' while expecting integral",
      parser
  );

  cout << "  Testing (+) parsing for size_t..." << endl;
  assert_fail_get<size_t, iva>(
      "positive",
      "read '+8' while expecting unsigned",
      parser
  );

  cout << "  Testing (-) parsing for size_t..." << endl;
  assert_fail_get<size_t, iva>(
      "negative",
      "read '-12' while expecting unsigned",
      parser
  );

  cout << "  Testing float parsing for size_t..."
       << endl;
  assert_fail_get<size_t, iva>(
      "flt",
      "read '12.4' while expecting unsigned",
      parser
  );

  cout << "  Testing scientific parsing for size_t..."
       << endl;
  assert_fail_get<size_t, iva>(
      "scientific",
      "read '1e+6' while expecting unsigned",
      parser
  );

  cout << "  Testing invalid values for size_t..."
       << endl;
  assert_fail_get<size_t, iva>(
      "invalid",
      "read 'cde' while expecting unsigned",
      parser
  );

  cout << "  Testing float parsing for double..."
       << endl;
  assert(parser.get<double>("flt") == 12.4);

  cout << "  Testing scientific parsing for double..."
       << endl;
  assert(parser.get<double>("scientific") == 1.0e+6);
  assert(parser.get<double>("scientific_2") == 1.5e-6);

  cout << "  Testing int parsing for double..." << endl;
  assert(parser.get<double>("int_for_double") == 7.0);

  cout << "  Testing (+) parsing for double..." << endl;
  assert(parser.get<double>("positive") == 8.0);

  cout << "  Testing (-) parsing for double..." << endl;
  assert(parser.get<double>("negative") == -12);

  cout << "  Testing invalid values for double..."
       << endl;
  assert_fail_get<double, iva>(
      "invalid_for_double",
      "read 'ilm' while expecting floating-point",
      parser
  );

  cout << "  Testing valid double formats..." << endl;
  assert(parser.get<double>("flt_1") == 1.0);
  assert(parser.get<double>("flt_2") == 1.0e+06);
  assert(parser.get<double>("flt_3") == 1.0e+06);
  assert(parser.get<double>("flt_4") == 1.0e+06);
  assert(parser.get<double>("flt_5") == 1.0);
  assert(parser.get<double>("flt_6") == 1.0e+06);
  assert(parser.get<double>("flt_7") == 1.0e+06);
  assert(parser.get<double>("flt_8") == 1.0e+06);

  cout << "  Testing invalid double formats..." << endl;
  assert_fail_get<double, iva>(
      "invalid_flt_1",
      "read '1.' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_2",
      "read '1.e6' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_3",
      "read '1.e06' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_4",
      "read '1.e+06' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_5",
      "read '.345' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_6",
      "read '.345e+06' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_7",
      "read '.345+06' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_8",
      "read '.345e+' while expecting floating-point",
      parser
  );
  assert_fail_get<double, iva>(
      "invalid_flt_9",
      "read '.345e' while expecting floating-point",
      parser
  );

  cout << "  Testing int parsing for string..." << endl;
  assert(parser.get<string>("int_for_string") == "1");

  cout << "  Testing space parsing for string..."
       << endl;
  assert(
      parser.get<string>("spaces_in_string") == "a b c"
  );

  cout << "  Testing quote parsing for string..."
       << endl;
  assert(
      parser.get<string>("quotes_in_string")
      == "\"ab\" c\"d ef"
  );

  cout << "  Testing colon in string..." << endl;
  assert(
      parser.get<string>("colon_in_string")
      == "ab:cm:: o"
  );

  cout << "  Testing comma in string..." << endl;
  assert(
      parser.get<string>("comma_in_string") == "ab,cm"
  );

  cout << "  Testing hash in string..." << endl;
  assert(parser.get<string>("hash_in_string") == "ab");

  close_test();
}
