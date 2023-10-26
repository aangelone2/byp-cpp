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
#include <sstream>
#include <type_traits>

using byp::convert;
using std::false_type;
using std::stringstream;
using std::true_type;

/* clang-format off */

// Trait for supported vector types
// (cannot test on value_type, since every container has it)
template <typename T> struct is_vector : false_type {};
template <> struct is_vector<vector<short>> : true_type {};
template <> struct is_vector<vector<int>> : true_type {};
template <> struct is_vector<vector<long>> : true_type {};
template <> struct is_vector<vector<long long>> : true_type {};
template <> struct is_vector<vector<unsigned short>> : true_type {};
template <> struct is_vector<vector<unsigned int>> : true_type {};
template <> struct is_vector<vector<unsigned long>> : true_type {};
template <> struct is_vector<vector<unsigned long long>> : true_type {};
template <> struct is_vector<vector<float>> : true_type {};
template <> struct is_vector<vector<double>> : true_type {};
template <> struct is_vector<vector<long double>> : true_type {};
template <> struct is_vector<vector<string>> : true_type {};

// Trait for supported table (2D vector) types
// (cannot test on value_type, since every container has it)
template <typename T> struct is_table : false_type {};
template <> struct is_table<vector<vector<short>>> : true_type {};
template <> struct is_table<vector<vector<int>>> : true_type {};
template <> struct is_table<vector<vector<long>>> : true_type {};
template <> struct is_table<vector<vector<long long>>> : true_type {};
template <> struct is_table<vector<vector<unsigned short>>> : true_type {};
template <> struct is_table<vector<vector<unsigned int>>> : true_type {};
template <> struct is_table<vector<vector<unsigned long>>> : true_type {};
template <> struct is_table<vector<vector<unsigned long long>>> : true_type {};
template <> struct is_table<vector<vector<float>>> : true_type {};
template <> struct is_table<vector<vector<double>>> : true_type {};
template <> struct is_table<vector<vector<long double>>> : true_type {};
template <> struct is_table<vector<vector<string>>> : true_type {};

/* clang-format on */

// Converts string -> bool
bool convert_bool(const string& val)
{
  if (val == "true")
    return true;
  else if (val == "false")
    return false;
  else
    throw iva("read '" + val + "' while expecting bool");
}

// Converts string -> vector<...>
// Does not need instantiation (done when compiling convert<T>)
template <typename T> T convert_vector(const string& val)
{
  typedef typename T::value_type element_type;

  // Only vector content, no bounding []
  const string vregex = "[^\\[\\]]*";

  // Filtering bounding [], not allowed in content
  // Exceptions need not be caught here, they may only be
  // raised by lower-level convert() calls.
  const auto vec_string
      = get_groups(val, "^\\[(" + vregex + ")\\]$");

  if (vec_string.has_value())
  {
    // Simpler than using sregex_iterator,
    // allows trailing comma
    stringstream ss(vec_string.value()[0]);
    string token;

    T res;
    while (getline(ss, token, ','))
      res.push_back(convert<element_type>(token));

    return res;
  }
  else
    throw iva("read '" + val + "' while expecting vector<>");
}

// Converts string -> vector<vector<...>>
// Does not need instantiation (done when compiling convert<T>)
template <typename T> T convert_table(const string& val)
{
  typedef typename T::value_type row_type;

  // Vector + bounding []
  const string bvregex = "\\[[^\\[\\]]*\\]";

  // Filtering bounding [], allowed in content (vectors)
  // Exceptions need not be caught here, they may only be
  // raised by lower-level convert() calls.
  // Non-capturing groups to avoid duplication issues
  // Trailing comma is allowed.
  const string global = "\\[(?:\\s*" + bvregex
                        + "\\s*,)*(?:\\s*" + bvregex
                        + "\\s*,?\\s*)\\]";

  if (!match(val, global))
    throw iva(
        "read '" + val + "' while expecting vector<vector<>>"
    );

  // Match cannot fail (the one above succeeded)
  // Cannot join with previous command, using get_groups() to
  // extract the single components, due to general repeated
  // capture group issues in regexs.
  const string table_str
      = get_groups(val, "^\\[(.*)\\]$").value()[0];

  // Iterating over matches (subvectors)
  // Will ignore trailing comma and leading/trailing spaces
  const vector<string> elements
      = get_repeating_group(table_str, bvregex);

  T res;
  for (const auto& el : elements)
    res.push_back(convert<row_type>(el));

  return res;
}

// Converts string -> arithmetic type
template <typename T> T convert_numeric(const string& val)
{
  string type, pattern;

  if constexpr (std::is_integral<T>::value && std::is_signed<T>::value)
  {
    // stoi() accepts floats, stricter filtering
    pattern = "^[\\+\\-]?[0-9]+$";
    type = "integral";
  }
  else if constexpr (std::is_unsigned<T>::value)
  {
    // stoul() accepts floats and negatives, stricter filtering
    pattern = "^[0-9]+$";
    type = "unsigned";
  }
  else // if constexpr(std::is_floating_point<T>::value)
  {
    // Essentially same filters as in stod(), but 1. disallowed
    pattern = "^[\\+\\-]?[0-9]+(?:\\.[0-9]+)?(?:[Ee][\\+\\-]?["
              "0-9]+)?$";
    type = "floating-point";
  }

  if (!match(val, pattern))
    throw iva("read '" + val + "' while expecting " + type);

  // Default, type-unaware conversion
  stringstream ss(val);
  T res;
  ss >> res;

  return res;
}

template <typename T> T byp::convert(const string& val)
{
  const string buffer = clean(val);

  if constexpr (std::is_same<T, bool>::value)
    return convert_bool(buffer);
  else if constexpr (std::is_same<T, string>::value)
    return buffer;
  else if constexpr (is_vector<T>::value)
    return convert_vector<T>(buffer);
  else if constexpr (is_table<T>::value)
    return convert_table<T>(buffer);
  else // only numeric types left among the instantiated
    return convert_numeric<T>(buffer);
}

/* clang-format off */

template bool byp::convert(const string& val);
template short byp::convert(const string& val);
template int byp::convert(const string& val);
template long byp::convert(const string& val);
template long long byp::convert(const string& val);
template unsigned short byp::convert(const string& val);
template unsigned int byp::convert(const string& val);
template unsigned long byp::convert(const string& val);
template unsigned long long byp::convert(const string& val);
template float byp::convert(const string& val);
template double byp::convert(const string& val);
template long double byp::convert(const string& val);
template string byp::convert(const string& val);

template vector<short> byp::convert(const string& val);
template vector<int> byp::convert(const string& val);
template vector<long> byp::convert(const string& val);
template vector<long long> byp::convert(const string& val);
template vector<unsigned short> byp::convert(const string& val);
template vector<unsigned int> byp::convert(const string& val);
template vector<unsigned long> byp::convert(const string& val);
template vector<unsigned long long> byp::convert(const string& val);
template vector<float> byp::convert(const string& val);
template vector<double> byp::convert(const string& val);
template vector<long double> byp::convert(const string& val);
template vector<string> byp::convert(const string& val);

template vector<vector<short>> byp::convert(const string& val);
template vector<vector<int>> byp::convert(const string& val);
template vector<vector<long>> byp::convert(const string& val);
template vector<vector<long long>> byp::convert(const string& val);
template vector<vector<unsigned short>> byp::convert(const string& val);
template vector<vector<unsigned int>> byp::convert(const string& val);
template vector<vector<unsigned long>> byp::convert(const string& val);
template vector<vector<unsigned long long>> byp::convert(const string& val);
template vector<vector<float>> byp::convert(const string& val);
template vector<vector<double>> byp::convert(const string& val);
template vector<vector<long double>> byp::convert(const string& val);
template vector<vector<string>> byp::convert(const string& val);

/* clang-format on */
