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
#include <string>
#include <vector>

using std::regex;
using std::smatch;
using std::string;
using std::vector;
using iva = std::invalid_argument;

bcp_loader::bcp_loader(const string& filename)
{
  file.open(filename.c_str());
  if (!file)
    throw iva("file '" + filename + "' not found");
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

  throw iva("key '" + key + "' not found");
}

// Specializations (vector<bool> and vector<string> disallowed)
template bool bcp_loader::read<bool>(const string& key);
template int bcp_loader::read<int>(const string& key);
template size_t bcp_loader::read<size_t>(const string& key);
template double bcp_loader::read<double>(const string& key);
template string bcp_loader::read<string>(const string& key);
template vector<int>
bcp_loader::read<vector<int>>(const string& key);
template vector<size_t>
bcp_loader::read<vector<size_t>>(const string& key);
template vector<double>
bcp_loader::read<vector<double>>(const string& key);
