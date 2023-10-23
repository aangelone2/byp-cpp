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

#ifndef COMMON_HPP
#define COMMON_HPP

#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::getline;
using std::optional;
using std::regex;
using std::regex_match;
using std::sregex_iterator;
using std::string;
using std::vector;

using iva = std::invalid_argument;

// Check if a string matches a pattern.
/*
 * @param input The string to analyze.
 * @param pattern A regex pattern against which the string
 *                will be checked.
 *
 * @return Whether or not the string matches the pattern.
 */
bool match(const string& input, const string& pattern);

// Extract groups from string if regex is matched.
/*
 * @param input The string to analyze.
 * @param pattern A regexp pattern against which the string
 *                will be checked.
 *
 * @return Non-empty if the string matches. i-th group is
 *         element `i-1`.
 */
std::optional<vector<string>> get_groups(const string& input, const string& pattern);

// Removes trailing comments, then leading and trailing spaces.
/*
 * @param input The string to de-commented and trim.
 *
 * @return The treated string.
 */
string clean(const string& input);

// Conversion functions, string -> specified type
/*
 * Required to trim leading and trailing spaces from value
 * before conversion, or at least to ignore them. This is
 * simpler than letting get() deal with it, since convert()
 * can be called by other convert() calls.
 *
 * The templated vector<> and vector<vector<>> functions
 * are explicitly instantiated in the source files.
 *
 * @param val The string to convert.
 * @param res The inout parameter in which the return value
 *            will be stored.
 *
 * @throws invalid_argument If invalid value passed.
 */
void convert(const string& val, bool& res);
void convert(const string& val, int& res);
void convert(const string& val, size_t& res);
void convert(const string& val, double& res);
void convert(const string& val, string& res);
template <typename T> void convert(const string& val, vector<T>& res);
template <typename T> void convert(const string& val, vector<vector<T>>& res);

#endif
