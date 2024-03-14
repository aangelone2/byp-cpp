/* Copyright (c) 2023 Adriano Angelone
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * This file is part of byp-cpp.
 *
 * This file may be used under the terms of the GNU General Public License
 * version 3.0 as published by the Free Software Foundation and appearing in
 * the file LICENSE included in the packaging of this file. Please review the
 * following information to ensure the GNU General Public License version 3.0
 * requirements will be met: http://www.gnu.org/copyleft/gpl.html.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. */

#ifndef BYPCPP_COMMON_REGEX_HPP
#define BYPCPP_COMMON_REGEX_HPP

#include <optional>
#include <string>
#include <vector>

// Check if a string matches a pattern.
/*
 * @param input The string to analyze.
 * @param pattern A regex pattern against which the string will be checked.
 *
 * @return Whether or not the string matches the pattern.
 */
bool match(const std::string& input, const std::string& pattern);

// Extract groups from string if regex is matched.
/*
 * @param input The string to analyze.
 * @param pattern A regexp pattern against which the string will be checked.
 *
 * @return Non-empty if the string matches. i-th group is element `i-1`.
 */
std::optional<std::vector<std::string>>
get_groups(const std::string& input, const std::string& pattern);

// Extract all repeated instances of a group from a string.
/*
 * If no matches, an empty vector will be returned.
 *
 * @param input The string to analyze.
 * @param pattern A regexp pattern which will be repeatedly extracted from the
 * input string.
 *
 * @return A vector of strings containing all the matched group instances.
 */
std::vector<std::string>
get_repeating_group(const std::string& input, const std::string& pattern);

// Removes trailing comments, then leading and trailing spaces.
/*
 * May return `""` (if no eligible characters remain).
 *
 * @param input The string to de-commented and trim.
 *
 * @return The treated string.
 */
std::string clean(const std::string& input);

#endif
