/* Copyright (c) 2023 Adriano Angelone
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial
 * portions of the Software.
 *
 * This file is part of byp-cpp.
 *
 * This file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the
 * Free Software Foundation and appearing in the file
 * LICENSE included in the packaging of this file. Please
 * review the following information to ensure the GNU
 * General Public License version 3.0 requirements will
 * be met: http://www.gnu.org/copyleft/gpl.html.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
 * EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "byp-cpp/parser.hpp"
#include "byp-cpp/common/regex.hpp"

using std::ifstream;
using std::string;
using std::to_string;
using iva = std::invalid_argument;

byp::parser::parser(const string& filename)
{
  ifstream file(filename.c_str());
  if (!file)
    throw iva("file '" + filename + "' not found");

  populate_values(file);
}

void byp::parser::populate_values(ifstream& file)
{
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
    const auto key_val = get_groups(
        buffer, "^\\s*([^\\s]*)\\s*: (.*)$"
    );

    // Skipping non-key-value-pair lines
    if (!key_val.has_value())
      throw iva(
          "invalid key-value pair at row "
          + to_string(counter)
      );

    const string key = key_val.value()[0];

    if (match(key, "^.*\\s.*$") || match(key, "^.*:.*$"))
      throw iva(
          "invalid key '" + key + "' at row "
          + to_string(counter)
      );

    if (m_values.find(key) != m_values.end())
      throw iva(
          "duplicate key '" + key + "' at row "
          + to_string(counter)
      );

    m_values.insert({key, key_val.value()[1]});
  }
}
