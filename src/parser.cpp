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
#include "common.hpp"

byp::parser::parser(const string& filename)
{
  file.open(filename.c_str());
  if (!file)
    throw iva("file '" + filename + "' not found");
}

// Helper function, resets stream to the beginning
void reset_stream(std::ifstream& file)
{
  file.clear();
  file.seekg(0);
}

string byp::parser::get(const string& key)
{
  reset_stream(file);

  int counter = 0;
  string buffer;
  while (getline(file, buffer))
  {
    ++counter;

    const bool is_comment = match(buffer, "^\\s*#.*");
    if (is_comment || buffer.empty())
      continue;

    // Leading and trailing spaces for val not removed,
    // managed by convert() (1st, "dialect" space kept)
    const auto key_val
        = get_groups(buffer, "^\\s*([^\\s]*)\\s*: (.*)$");

    // Skipping non-key-value-pair lines
    if (!key_val.has_value())
      throw iva("invalid key-value pair at row "
                + std::to_string(counter));

    if (key_val.value()[0] == key)
      return key_val.value()[1];
  }

  throw iva("key '" + key + "' invalid or missing");
}

template <typename T> T byp::parser::read(const string& key)
{
  T res;
  convert(get(key), res);
  return res;
}

// Specializations
template bool byp::parser::read<bool>(const string& key);
template int byp::parser::read<int>(const string& key);
template size_t byp::parser::read<size_t>(const string& key);
template double byp::parser::read<double>(const string& key);
template string byp::parser::read<string>(const string& key);

// vector<bool> and vector<string> disallowed
template vector<int>
byp::parser::read<vector<int>>(const string& key);
template vector<size_t>
byp::parser::read<vector<size_t>>(const string& key);
template vector<double>
byp::parser::read<vector<double>>(const string& key);
template vector<string>
byp::parser::read<vector<string>>(const string& key);

// vector<vector<bool>> and vector<vector<string>> disallowed
template vector<vector<int>>
byp::parser::read<vector<vector<int>>>(const string& key);
template vector<vector<size_t>>
byp::parser::read<vector<vector<size_t>>>(const string& key);
template vector<vector<double>>
byp::parser::read<vector<vector<double>>>(const string& key);
template vector<vector<string>>
byp::parser::read<vector<vector<string>>>(const string& key);
