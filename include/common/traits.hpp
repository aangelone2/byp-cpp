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

#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <type_traits>
#include <string>
#include <vector>

using std::false_type;
using std::string;
using std::true_type;
using std::vector;

// Trait for supported vector types (cannot test on
// value_type, since every container has it)

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

// Trait for supported table (2D vector) types (cannot
// test on value_type, since every container has it)

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

#endif
