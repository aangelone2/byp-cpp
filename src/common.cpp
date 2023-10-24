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

bool match(const string& input, const string& pattern)
{
  return regex_match(input, regex(pattern));
}

optional<vector<string>>
get_groups(const string& input, const string& pattern)
{
  const auto r = regex(pattern);
  std::smatch pieces_match;

  // Match failed
  if (!regex_match(input, pieces_match, r))
    return {};

  // Removing 0th element (complete string)
  return vector<string>(
      pieces_match.begin() + 1, pieces_match.end()
  );
}

string clean(const string& input)
{
  // Cannot fail (may return "", expected).

  // Greedy match to leave no pre-commented chars.
  const string buffer
      = get_groups(input, "^([^#]*).*$").value()[0];
  // Non-greedy match to leave all trailing spaces.
  return get_groups(buffer, "^\\s*(.*?)\\s*$").value()[0];
}
