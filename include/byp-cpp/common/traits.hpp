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

#ifndef BYPCPP_COMMON_TRAITS_HPP
#define BYPCPP_COMMON_TRAITS_HPP

#include <type_traits>
#include <string>
#include <vector>

// Trait for supported vector types (cannot test on
// value_type, since every container has it)

template <typename T> struct is_vector : std::false_type {};
template <> struct is_vector<std::vector<short>> : std::true_type {};
template <> struct is_vector<std::vector<int>> : std::true_type {};
template <> struct is_vector<std::vector<long>> : std::true_type {};
template <> struct is_vector<std::vector<long long>> : std::true_type {};
template <> struct is_vector<std::vector<unsigned short>> : std::true_type {};
template <> struct is_vector<std::vector<unsigned int>> : std::true_type {};
template <> struct is_vector<std::vector<unsigned long>> : std::true_type {};
template <> struct is_vector<std::vector<unsigned long long>> : std::true_type {};
template <> struct is_vector<std::vector<float>> : std::true_type {};
template <> struct is_vector<std::vector<double>> : std::true_type {};
template <> struct is_vector<std::vector<long double>> : std::true_type {};
template <> struct is_vector<std::vector<std::string>> : std::true_type {};

// Trait for supported table (2D vector) types (cannot
// test on value_type, since every container has it)

template <typename T> struct is_table : std::false_type {};
template <> struct is_table<std::vector<std::vector<short>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<int>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<long>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<long long>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<unsigned short>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<unsigned int>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<unsigned long>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<unsigned long long>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<float>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<double>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<long double>>> : std::true_type {};
template <> struct is_table<std::vector<std::vector<std::string>>> : std::true_type {};

#endif
