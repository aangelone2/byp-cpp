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

using std::string;
using iva = std::invalid_argument;

// Helper function, resets stream to the beginning
void reset_stream(std::ifstream& file)
{
  file.clear();
  file.seekg(0);
}

string bcp_loader::get(const string& key)
{
  reset_stream(file);

  int counter = 0;
  string buffer;
  while (std::getline(file, buffer))
  {
    ++counter;

    const bool is_comment = match(buffer, "^\\s*#.*");
    if (is_comment || buffer.empty())
      continue;

    const auto key_val = get_groups(
        buffer, "^\\s*([^\\s]*)\\s*:\\s+(.*?)\\s*$");

    // Skipping non-key-value-pair lines
    if (!key_val.has_value())
      throw iva("invalid key-value pair at row "
                + std::to_string(counter));

    if (key_val.value()[0] == key)
      return key_val.value()[1];
  }

  throw iva("key '" + key + "' invalid or missing");
}
