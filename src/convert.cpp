/* Copyright (c) 2023 Adriano Angelone
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the
 * Software.
 *
 * This file is part of byp-cpp.
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

#include "byp.hpp"
#include <regex>
#include <sstream>

using std::regex;
using std::sregex_iterator;
using std::string;
using std::vector;
using iva = std::invalid_argument;

void byp_loader::convert(const string& val, bool& res)
{
  if (val == "true")
    res = true;
  else if (val == "false")
    res = false;
  else
    throw iva("read '" + val + "' while expecting bool");
}

void byp_loader::convert(const string& val, int& res)
{
  try
  {
    res = std::stoi(val, nullptr, 10);
  }
  catch (const iva& err)
  {
    throw iva("read '" + val + "' while expecting int");
  }
}

void byp_loader::convert(const string& val, size_t& res)
{
  try
  {
    res = std::stoul(val, nullptr, 10);
  }
  catch (const iva& err)
  {
    throw iva("read '" + val + "' while expecting size_t");
  }
}

void byp_loader::convert(const string& val, double& res)
{
  try
  {
    res = std::stod(val, nullptr);
  }
  catch (const iva& err)
  {
    throw iva("read '" + val + "' while expecting double");
  }
}

void byp_loader::convert(const string& val, string& res)
{
  res = val;
}

template <typename T>
void byp_loader::convert(const string& val, vector<T>& res)
{
  // Filtering bounding [], not allowed in content
  // Exceptions need not be caught here, they may only be
  // raised by lower-level convert() calls.
  const auto vec_string
      = get_groups(val, "^\\[([^\\[\\]]*)\\]$");

  if (vec_string.has_value())
  {
    // Code is simpler than with sregex_iterator
    std::stringstream ss(vec_string.value()[0]);
    string token;

    while (std::getline(ss, token, ','))
    {
      res.resize(res.size() + 1);
      convert(token, res.back());
    }
  }
  else
    throw iva("read '" + val + "' while expecting vector");
}

// Specializations (vector<bool> and vector<string> disallowed)
template void byp_loader::convert(const string& val,
                                  vector<int>& res);
template void byp_loader::convert(const string& val,
                                  vector<size_t>& res);
template void byp_loader::convert(const string& val,
                                  vector<double>& res);

template <typename T>
void byp_loader::convert(const string& val,
                         vector<vector<T>>& res)
{
  // Filtering bounding [], allowed in content (vectors)
  // Exceptions need not be caught here, they may only be
  // raised by lower-level convert() calls.
  const auto table_string = get_groups(val, "^\\[(.*)\\]$");

  if (table_string.has_value())
  {
    const string vec_str = table_string.value()[0];
    // Filtering bounding [] in subvectors, not allowed within
    const regex el_pattern = regex("\\[[^\\[\\]]*\\]");

    const auto begin = sregex_iterator(
        vec_str.begin(), vec_str.end(), el_pattern);
    const auto end = sregex_iterator();

    // Iterating over matches (subvectors)
    for (auto el = begin; el != end; ++el)
    {
      res.resize(res.size() + 1);
      convert(el->str(), res.back());
    }
  }
  else
    throw iva("read '" + val
              + "' while expecting vector<vector>");
}

// Specializations (vector<vector<bool>> and
// vector<vector<string>> disallowed)
template void byp_loader::convert(const string& val,
                                  vector<vector<int>>& res);
template void byp_loader::convert(const string& val,
                                  vector<vector<size_t>>& res);
template void byp_loader::convert(const string& val,
                                  vector<vector<double>>& res);
