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

using std::string;
using std::vector;

template <typename T> T byp_loader::read(const string& key)
{
  T res;
  convert(get(key), res);
  return res;
}

// Specializations
template bool byp_loader::read<bool>(const string& key);
template int byp_loader::read<int>(const string& key);
template size_t byp_loader::read<size_t>(const string& key);
template double byp_loader::read<double>(const string& key);
template string byp_loader::read<string>(const string& key);

// vector<bool> and vector<string> disallowed
template vector<int>
byp_loader::read<vector<int>>(const string& key);
template vector<size_t>
byp_loader::read<vector<size_t>>(const string& key);
template vector<double>
byp_loader::read<vector<double>>(const string& key);
template vector<string>
byp_loader::read<vector<string>>(const string& key);

// vector<vector<bool>> and vector<vector<string>> disallowed
template vector<vector<int>>
byp_loader::read<vector<vector<int>>>(const string& key);
template vector<vector<size_t>>
byp_loader::read<vector<vector<size_t>>>(const string& key);
template vector<vector<double>>
byp_loader::read<vector<vector<double>>>(const string& key);
template vector<vector<string>>
byp_loader::read<vector<vector<string>>>(const string& key);
