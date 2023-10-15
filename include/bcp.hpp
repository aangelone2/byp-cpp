#ifndef BCP_HPP
#define BCP_HPP

void test() {}

#include <fstream>
#include <regex>
#include <string>

namespace bcp
{
  template <typename T>
  T read(std::ifstream infile, const std::string &key);
}

template <typename T>
T bcp::read(std::ifstream infile, const std::string &key)
{
  std::string buffer;

  while (!infile.eof())
  {
    std::getline(infile, buffer);

    smatch pieces_match;
    const regex pattern = regex("^([^\\s:]*):\\s+(.*)$");

    if (!regex_match(buffer, pieces_match, pattern))
      continue;

    if (pieces_match[1] == key)
    {
      in.seekg(0, in.beg);

      T res;
      convert(pieces_match[2], res, log);
      return res;
    }
    else
      continue;
  }

  // Reset stream
  infile.seekg(0, infile.beg);
}

#endif
