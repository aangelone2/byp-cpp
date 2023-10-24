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

#include "common.hpp"

void convert(const string& val, bool& res)
{
  const string buffer = clean(val);

  if (buffer == "true")
    res = true;
  else if (buffer == "false")
    res = false;
  else
    throw iva("read '" + buffer + "' while expecting bool");
}

void convert(const string& val, int& res)
{
  const string buffer = clean(val);

  // stoi() accepts floats, additional filtering required
  if (!match(buffer, "^[\\+\\-]?[0-9]+$"))
    throw iva("read '" + buffer + "' while expecting int");

  res = std::stoi(buffer, nullptr, 10);
}

void convert(const string& val, size_t& res)
{
  const string buffer = clean(val);

  // stoul() accepts floats and negatives,
  // additional filtering required
  if (!match(buffer, "^[0-9]+$"))
    throw iva("read '" + buffer + "' while expecting size_t");

  res = std::stoul(buffer, nullptr, 10);
}

void convert(const string& val, double& res)
{
  const string buffer = clean(val);

  // Builtin filters in stod() should be enough
  try
  {
    res = std::stod(buffer, nullptr);
  }
  catch (const iva& err)
  {
    throw iva("read '" + buffer + "' while expecting double");
  }
}

void convert(const string& val, string& res)
{
  res = clean(val);
}

template <typename T>
void convert(const string& val, vector<T>& res)
{
  const string buffer = clean(val);

  // Only vector content, no bounding []
  const string vregex = "[^\\[\\]]*";

  // Filtering bounding [], not allowed in content
  // Exceptions need not be caught here, they may only be
  // raised by lower-level convert() calls.
  const auto vec_string
      = get_groups(buffer, "^\\[(" + vregex + ")\\]$");

  if (vec_string.has_value())
  {
    // Simpler than using sregex_iterator
    std::stringstream ss(vec_string.value()[0]);
    string token;

    while (getline(ss, token, ','))
    {
      res.resize(res.size() + 1);
      convert(token, res.back());
    }
  }
  else
    throw iva("read '" + buffer + "' while expecting vector");
}

// Specializations (vector<bool> disallowed)
template void convert(const string& val, vector<int>& res);
template void convert(const string& val, vector<size_t>& res);
template void convert(const string& val, vector<double>& res);
template void convert(const string& val, vector<string>& res);

template <typename T>
void convert(const string& val, vector<vector<T>>& res)
{
  const string buffer = clean(val);

  // Vector + bounding []
  const string bvregex = "\\[[^\\[\\]]*\\]";

  // Filtering bounding [], allowed in content (vectors)
  // Exceptions need not be caught here, they may only be
  // raised by lower-level convert() calls.
  // Note repeated group (()*), regex gotcha to match all
  // vectors except the last.
  const string global = "\\[((\\s*" + bvregex + "\\s*,)*)(\\s*"
                        + bvregex + "\\s*)\\]";

  if (!match(buffer, global))
    throw iva(
        "read '" + buffer
        + "' while expecting vector<vector<>>"
    );

  const auto table_string = get_groups(buffer, "^\\[(.*)\\]$");

  if (table_string.has_value())
  {
    const string vec_str = table_string.value()[0];
    // Filtering bounding [] in subvectors, not allowed within
    // Not catching leading/trailing spaces within subvectors
    const auto el_pattern = std::regex(bvregex);

    const auto begin = sregex_iterator(
        vec_str.begin(), vec_str.end(), el_pattern
    );
    const auto end = sregex_iterator();

    // Iterating over matches (subvectors)
    for (auto el = begin; el != end; ++el)
    {
      res.resize(res.size() + 1);
      convert(el->str(), res.back());
    }
  }
  else
    throw iva(
        "read '" + buffer
        + "' while expecting vector<vector<>>"
    );
}

// Specializations (vector<vector<bool>> disallowed)
template void
convert(const string& val, vector<vector<int>>& res);
template void
convert(const string& val, vector<vector<size_t>>& res);
template void
convert(const string& val, vector<vector<double>>& res);
template void
convert(const string& val, vector<vector<string>>& res);
