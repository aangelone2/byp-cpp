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

#include "byp-cpp/logger.hpp"
#include "byp-cpp/common/traits.hpp"
#include <iomanip>
#include <stdexcept>

using std::string;
using std::stringstream;
using std::vector;

byp::logger::logger()
{
  set_scientific();
  set_precision();
  set_context();
}

void byp::logger::set_precision(const int precision)
{
  if (precision < 0)
    throw std::invalid_argument(
        "invalid precision in logger::set_precision()"
    );

  m_precision = precision;
}

template <typename T>
string byp::logger::format(const T& val) const
{
  if constexpr (std::is_same<T, bool>::value)
    return (val ? "true" : "false");
  else if constexpr (std::is_same<T, string>::value)
    return val;
  else if constexpr (is_vector<T>::value || is_table<T>::value)
  {
    string buffer = "[";
    for (auto it = val.begin(); it < val.end() - 1; ++it)
      buffer += (format(*it) + ", ");
    buffer += format(val.back()) + "]";

    return buffer;
  }
  else // only numeric types left among the instantiated
  {
    stringstream ss;

    if (m_scientific)
      ss << std::scientific;
    ss.precision(m_precision);

    ss << val;
    return ss.str();
  }
}

/* clang-format off */

template string byp::logger::format(const bool& val) const;
template string byp::logger::format(const short& val) const;
template string byp::logger::format(const int& val) const;
template string byp::logger::format(const long& val) const;
template string byp::logger::format(const long long& val) const;
template string byp::logger::format(const unsigned short& val) const;
template string byp::logger::format(const unsigned int& val) const;
template string byp::logger::format(const unsigned long& val) const;
template string byp::logger::format(const unsigned long long& val) const;
template string byp::logger::format(const float& val) const;
template string byp::logger::format(const double& val) const;
template string byp::logger::format(const long double& val) const;
template string byp::logger::format(const string& val) const;

template string byp::logger::format(const vector<short>& val) const;
template string byp::logger::format(const vector<int>& val) const;
template string byp::logger::format(const vector<long>& val) const;
template string byp::logger::format(const vector<long long>& val) const;
template string byp::logger::format(const vector<unsigned short>& val) const;
template string byp::logger::format(const vector<unsigned int>& val) const;
template string byp::logger::format(const vector<unsigned long>& val) const;
template string byp::logger::format(const vector<unsigned long long>& val) const;
template string byp::logger::format(const vector<float>& val) const;
template string byp::logger::format(const vector<double>& val) const;
template string byp::logger::format(const vector<long double>& val) const;
template string byp::logger::format(const vector<string>& val) const;

template string byp::logger::format(const vector<vector<short>>& val) const;
template string byp::logger::format(const vector<vector<int>>& val) const;
template string byp::logger::format(const vector<vector<long>>& val) const;
template string byp::logger::format(const vector<vector<long long>>& val) const;
template string byp::logger::format(const vector<vector<unsigned short>>& val) const;
template string byp::logger::format(const vector<vector<unsigned int>>& val) const;
template string byp::logger::format(const vector<vector<unsigned long>>& val) const;
template string byp::logger::format(const vector<vector<unsigned long long>>& val) const;
template string byp::logger::format(const vector<vector<float>>& val) const;
template string byp::logger::format(const vector<vector<double>>& val) const;
template string byp::logger::format(const vector<vector<long double>>& val) const;
template string byp::logger::format(const vector<vector<string>>& val) const;

/* clang-format on */
