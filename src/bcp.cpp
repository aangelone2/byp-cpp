/* Copyright (c) 2023 Adriano Angelone
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 *
 * This file is part of bcp-cpp.
 *
 * This file may be used under the terms of the GNU General
 * Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE included in the
 * packaging of this file.  Please review the following
 * information to ensure the GNU General Public License version
 * 3.0 requirements will be met:
 * http://www.gnu.org/copyleft/gpl.html.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "bcp.hpp"

using std::cout;
using std::endl;

using std::getline;
using std::regex;
using std::smatch;
using std::string;
using std::vector;
using iva = std::invalid_argument;

bcp_loader::bcp_loader(const string& filename)
{
  file.open(filename.c_str());
  if (!file)
    throw iva("error :: file '" + filename + "' not found");
}

template <typename T> T bcp_loader::read(const string& key)
{
  string buffer;

  while (!file.eof())
  {
    getline(file, buffer);

    smatch pieces_match;
    const regex pattern = regex("^([^\\s:]*):\\s+(.*)$");

    if (!regex_match(buffer, pieces_match, pattern))
      continue;

    if (pieces_match[1] == key)
    {
      reset_stream();

      T res;
      convert(pieces_match[2], res);
      return res;
    }
    else
      continue;
  }

  throw iva("error :: key '" + key + "' not found");
}

// Specializations
template bool bcp_loader::read<bool>(const string& key);
template int bcp_loader::read<int>(const string& key);
template size_t bcp_loader::read<size_t>(const string& key);
template double bcp_loader::read<double>(const string& key);
template string bcp_loader::read<string>(const string& key);

void bcp_loader::convert(const string& val, bool& res) const
{
  if (val == "true")
    res = true;
  else if (val == "false")
    res = false;
  else
    throw iva("error :: value '" + val
              + "' while expecting bool");
}

void bcp_loader::convert(const string& val, int& res) const
{
  try
  {
    res = std::stoi(val, nullptr, 10);
  }
  catch (const iva& err)
  {
    throw iva("error :: value '" + val
              + "' while expecting int");
  }
}

void bcp_loader::convert(const string& val, size_t& res) const
{
  try
  {
    res = std::stoul(val, nullptr, 10);
  }
  catch (const iva& err)
  {
    throw iva("error :: value '" + val
              + "' while expecting size_t");
  }
}

void bcp_loader::convert(const string& val, double& res) const
{
  try
  {
    res = std::stod(val, nullptr);
  }
  catch (const iva& err)
  {
    throw iva("error :: value '" + val
              + "' while expecting double");
  }
}

void bcp_loader::convert(const string& val, string& res) const
{
  res = val;
}

template <typename T>
void bcp_loader::convert(const string& val,
                         vector<T>& res) const
{
  // Exceptions need not be caught here, they may only be
  // raised by lower-level convert() calls.
  smatch pieces_match;
  const regex pattern = regex("^\\s*\\[(.*)\\]\\s*$");

  if (regex_match(val, pieces_match, pattern))
  {
#ifdef DEBUG
    cout << "in convert_vector" << endl;
    cout << "pieces_match = " << pieces_match[0]
         << " :: " << pieces_match[1] << endl;
#endif

    std::stringstream ss(pieces_match[1]);
    string token;

    while (getline(ss, token, ','))
    {
      res.resize(res.size() + 1);
      convert(token, res.back());
    }
  }
  else
    throw iva("error :: value '" + val
              + "' while expecting vector");
}

// Specializations (vector bool explicitly disabled)
template void bcp_loader::convert(const string& val,
                                  vector<int>& res) const;
template void bcp_loader::convert(const string& val,
                                  vector<size_t>& res) const;
template void bcp_loader::convert(const string& val,
                                  vector<double>& res) const;
template void bcp_loader::convert(const string& val,
                                  vector<string>& res) const;
