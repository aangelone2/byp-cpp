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

#include "byp-cpp/common/traits.hpp"
#include "byp-cpp/functions.hpp"
#include <iomanip>
#include <sstream>

// Converts vector<> and vector<vector<>> -> string
// Does not need instantiation (done when compiling
// format<T>)
template <typename T> string format_vector(const T& val)
{
  string buffer = "[";
  for (auto it = val.begin(); it < val.end() - 1; ++it)
    buffer += (byp::format(*it) + ", ");
  buffer += byp::format(val.back()) + "]";

  return buffer;
}

template <typename T> string byp::format(const T& val)
{
  if constexpr (std::is_same<T, bool>::value)
    return (val ? "true" : "false");
  else if constexpr (std::is_same<T, string>::value)
    return val;
  else if constexpr (is_vector<T>::value || is_table<T>::value)
    return format_vector(val);
  else // only numeric types left among the instantiated
  {
    std::stringstream ss;
    // Format locked for reproducibility
    ss << std::setprecision(6) << std::scientific << val;
    return ss.str();
  }
}

/* clang-format off */

template string byp::format(const bool& val);
template string byp::format(const short& val);
template string byp::format(const int& val);
template string byp::format(const long& val);
template string byp::format(const long long& val);
template string byp::format(const unsigned short& val);
template string byp::format(const unsigned int& val);
template string byp::format(const unsigned long& val);
template string byp::format(const unsigned long long& val);
template string byp::format(const float& val);
template string byp::format(const double& val);
template string byp::format(const long double& val);
template string byp::format(const string& val);

template string byp::format(const vector<short>& val);
template string byp::format(const vector<int>& val);
template string byp::format(const vector<long>& val);
template string byp::format(const vector<long long>& val);
template string byp::format(const vector<unsigned short>& val);
template string byp::format(const vector<unsigned int>& val);
template string byp::format(const vector<unsigned long>& val);
template string byp::format(const vector<unsigned long long>& val);
template string byp::format(const vector<float>& val);
template string byp::format(const vector<double>& val);
template string byp::format(const vector<long double>& val);
template string byp::format(const vector<string>& val);

template string byp::format(const vector<vector<short>>& val);
template string byp::format(const vector<vector<int>>& val);
template string byp::format(const vector<vector<long>>& val);
template string byp::format(const vector<vector<long long>>& val);
template string byp::format(const vector<vector<unsigned short>>& val);
template string byp::format(const vector<vector<unsigned int>>& val);
template string byp::format(const vector<vector<unsigned long>>& val);
template string byp::format(const vector<vector<unsigned long long>>& val);
template string byp::format(const vector<vector<float>>& val);
template string byp::format(const vector<vector<double>>& val);
template string byp::format(const vector<vector<long double>>& val);
template string byp::format(const vector<vector<string>>& val);

/* clang-format on */
