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

namespace byp
{
  //! Loader class for parsing values.
  class parser
  {
    public:
      //! Public constructor.
      /*!
       * @param filename The path to the filename to parse.
       *
       * @throws invalid_argument If file does not exist.
       */
      parser(const std::string& filename);

      //! Main parsing function.
      /*!
       * Call to parse a value of the specified type.
       *
       * Explicitly instantiated in the source files.
       *
       * @param key The key associated to the value.
       *
       * @return The parsed value of the specified type.
       *
       * @throws invalid_argument If key-value pair missing or
       *                          invalid, or invalid row found
       *                          while parsing.
       */
      template <typename T> T read(const std::string& key);

    private:
      // File object to be parsed for key-value pairs.
      std::ifstream file;

      // Value parsing function.
      /*
       * Returns the value associated to a key as a string.
       * Stops and attempts parsing at the first matching key
       * from the top of the file.
       * Does not trim spaces before and after value.
       *
       * @param key The key associated to the value.
       *
       * @return The parsed value as a string.
       *
       * @throws invalid_argument If missing key, invalid row,
       * or invalid value found while parsing the file.
       */
      std::string get(const std::string& key);
  };
} // namespace byp

#endif
