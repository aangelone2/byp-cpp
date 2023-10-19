#include "bcp.hpp"

using std::string;
using iva = std::invalid_argument;

bcp_loader::bcp_loader(const string& filename)
{
  file.open(filename.c_str());
  if (!file)
    throw iva("file '" + filename + "' not found");
}
