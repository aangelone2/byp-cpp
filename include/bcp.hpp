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

#ifndef BCP_HPP
#define BCP_HPP

#include <fstream>
#include <optional>
#include <string>
#include <vector>

class bcp_loader
{
  public:
    bcp_loader(const std::string& filename);

    template <typename T> T read(const std::string& key);

  private:
    std::ifstream file;

    // Is guaranteed to trim spaces before and after value
    std::string get(const std::string& key);

    void reset_stream();

    // Cannot simply have a different return type:
    // overload by return type alone does not work
    // Not required to be robust against spaces
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

    static std::optional<std::vector<std::string>>
    match(const std::string& input,
          const std::string& pattern);
};

#endif
