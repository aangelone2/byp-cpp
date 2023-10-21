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

using std::regex;
using std::smatch;
using std::string;
using std::vector;
using iva = std::invalid_argument;

byp_loader::byp_loader(const string& filename)
{
  file.open(filename.c_str());
  if (!file)
    throw iva("file '" + filename + "' not found");
}

bool byp_loader::match(const string& input,
                       const string& pattern)
{
  return regex_match(input, regex(pattern));
}

std::optional<vector<string>>
byp_loader::get_groups(const string& input,
                       const string& pattern)
{
  const regex r = regex(pattern);
  smatch pieces_match;

  // Match failed
  if (!regex_match(input, pieces_match, r))
    return {};

  // Removing 0th element (complete string)
  return vector<string>(pieces_match.begin() + 1,
                        pieces_match.end());
}

string byp_loader::trim(const string& input)
{
  // Cannot fail (may return "", expected).
  return get_groups(input, "^\\s*(.*?)\\s*").value()[0];
}
