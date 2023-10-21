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

#ifndef BCP_HPP
#define BCP_HPP

#include <fstream>
#include <optional>
#include <string>
#include <vector>

//! Basic loader class.
class byp_loader
{
  public:
    //! Public constructor.
    /*!
     * \param filename The path to the filename to parse.
     */
    byp_loader(const std::string& filename);

    //! Main parsing function.
    /*!
     * Call to parse a value of the specified type.
     *
     * Explicitly instantiated in the source files.
     *
     * \param key The key associated to the value.
     *
     * \return The parsed value of the specified type.
     */
    template <typename T> T read(const std::string& key);

  private:
    // File object to be parsed for key-value pairs.
    std::ifstream file;

    // Value parsing function.
    /*
     * Returns the value associated to a key as a string.
     * Does not trim spaces before and after value.
     *
     * \param key The key associated to the value.
     *
     * \return The parsed value as a string.
     */
    std::string get(const std::string& key);

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
     * \param val The string to convert.
     * \param res The inout parameter in which the return value
     *            will be stored.
     */
    static void convert(const std::string& val, bool& res);
    static void convert(const std::string& val, int& res);
    static void convert(const std::string& val, size_t& res);
    static void convert(const std::string& val, double& res);
    static void convert(const std::string& val,
                        std::string& res);
    template <typename T>
    static void convert(const std::string& val,
                        std::vector<T>& res);
    template <typename T>
    static void convert(const std::string& val,
                        std::vector<std::vector<T>>& res);

    // Check if a string matches a pattern.
    /*
     * \param input The string to analyze.
     * \param pattern A regex pattern against which the string
     *                will be checked.
     *
     * \return bool, whether or not the string matches the
     *               pattern.
     */
    static bool match(const std::string& input,
                      const std::string& pattern);

    // Extract groups from string if regex is matched.
    /*
     * \param input The string to analyze.
     * \param pattern A regexp pattern against which the string
     *                will be checked.
     *
     * \return optional<vector<string>>, non-empty if the
     *         string matches. i-th group is element `i-1`.
     */
    static std::optional<std::vector<std::string>>
    get_groups(const std::string& input,
               const std::string& pattern);
};

#endif
