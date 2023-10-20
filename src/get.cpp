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
#include <regex>

using std::string;
using iva = std::invalid_argument;

string bcp_loader::get(const string& key)
{
  reset_stream();

  string buffer;
  while (std::getline(file, buffer))
  {
    // We cannot properly filter spaces *after* the value:
    // we'd need (.*) -> ([^\\s]*) => problems with vectors.
    // Only 1st ' ' is hard-coded, the rest goes in the block.
    const auto matches
        = match(buffer, "^\\s*([^\\s]*)\\s*: (.*)$");

    // Skipping non-key-value-pair lines
    if (!matches.has_value())
      continue;

    if (matches.value()[0] == key)
      return matches.value()[1];
  }

  throw iva("key '" + key + "' invalid or missing");
}
