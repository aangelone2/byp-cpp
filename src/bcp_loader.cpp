#include "bcp.hpp"
#include <regex>

using std::regex;
using std::smatch;
using std::string;
using std::vector;
using iva = std::invalid_argument;

bcp_loader::bcp_loader(const string& filename)
{
  file.open(filename.c_str());
  if (!file)
    throw iva("file '" + filename + "' not found");
}

void bcp_loader::reset_stream()
{
  file.clear();
  file.seekg(0);
}

std::optional<vector<string>>
bcp_loader::match(const string& input, const string& pattern)
{
  const regex r = regex(pattern);
  smatch pieces_match;

  if (!regex_match(input, pieces_match, r))
    return {};

  return vector<string>(pieces_match.begin() + 1,
                        pieces_match.end());
}
