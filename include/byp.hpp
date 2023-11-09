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

#ifndef BYP_HPP
#define BYP_HPP

#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

//! Namespace for `byp` library.
namespace byp
{
  //! Conversion functions, string -> specified type
  /*!
   * Trims leading and trailing spaces from value before
   * conversion, or at least to ignore them.
   *
   * @param val The string to convert.
   *
   * @throws invalid_argument If invalid value passed.
   */
  template <typename T>
  T convert(const std::string& val);

  //! Loader class for parsing values.
  class parser
  {
    public:
      //! Public constructor.
      /*!
       * Populates the internal dictionary with the
       * key-value pairs parsed from the file.
       *
       * @param filename The path to the filename to
       * parse.
       *
       * @throws invalid_argument If file does not exist
       * or invalid key and/or value found.
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
       * @throws invalid_argument If key not found.
       */
      template <typename T>
      inline T get(const std::string& key) const
      {
        try
        {
          return convert<T>(values.at(key));
        }
        catch (const std::out_of_range& err)
        {
          throw std::invalid_argument(
              "key '" + key + "' not found"
          );
        }
      }

    private:
      // Map containing string values, accessed by key.
      std::unordered_map<std::string, std::string>
          values;

      // Parsing function.
      /*
       * Populates the internal dictionary with key-value
       * pairs. Trims spaces before/after key, but not
       * value.
       *
       * @param file The ifstream to parse.
       *
       * @throws invalid_argument If invalid row,
       * or invalid or duplicate key found while parsing.
       */
      void populate_values(std::ifstream& file);
  };
} // namespace byp

#endif
