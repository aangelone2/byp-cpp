#include "test.hpp"

int main()
{
  logger lgr;

  lgr.set_scientific(true);
  lgr.set_precision(4);
  lgr.set_context("prefix :: ", " :: suffix");

  cout << "  Testing prefix-suffix printing..." << endl;
  const i1t iv = i1t({1, 2, 3, 4});
  lgr.print(lgr.format(iv));

  cout << "  Testing resetting..." << endl;
  lgr.set_context();
  lgr.print(lgr.format(iv));

  cout << "  Testing integration with parser..." << endl;

  parser prs("../tests/yaml/test-05.yml");

  cout << "    Testing logger configuration..." << endl;
  prs.lgr().set_scientific(true);
  prs.lgr().set_precision(4);
  prs.lgr().set_context("prefix :: ", " :: suffix");
  prs.set_logging(true);
  assert(prs.get<d1t>("d1t") == d1t({7.0, 8.1, 9.4}));

  cout << "    Testing logger resetting..." << endl;
  prs.lgr().set_scientific();
  prs.lgr().set_precision();
  prs.lgr().set_context();
  assert(prs.get<d1t>("d1t") == d1t({7.0, 8.1, 9.4}));

  cout << "    Testing logger deactivation..." << endl;
  prs.set_logging(false);
  assert(prs.get<d1t>("d1t") == d1t({7.0, 8.1, 9.4}));

  close_test();
}
