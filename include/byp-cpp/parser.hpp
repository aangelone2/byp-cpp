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

#ifndef BYPCPP_PARSER_HPP
#define BYPCPP_PARSER_HPP

#include "byp-cpp/functions.hpp"
#include "byp-cpp/logger.hpp"
#include <fstream>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>

//! Namespace for `byp` library.
namespace byp
{
  //! Loader class for parsing values.
  // Chosen unused members + flags rather than
  // inheritance due to get<>() being a template (double
  // instantiation, for base and derived class).
  class parser
  {
    public:
      //! Public constructor.
      /*!
       * Populates the internal dictionary with the
       * key-value pairs parsed from the file. Unsets
       * logging (default).
       *
       * @param filename The path to the filename to
       * parse.
       *
       * @throws invalid_argument If file does not exist
       * or invalid key and/or value found.
       */
      parser(const std::string& filename);

      //! Toggles logging.
      /*!
       * @param value `true` to activate logging, `false`
       * otherwise.
       */
      void set_logging(const bool value)
      {
        m_logging = value;
      }

      //! Reference to internal logger for setup.
      /*!
       * Will return reference even if logger not in use
       * (for setup). The logger will still not be used
       * when parsing, in this case.
       *
       * @return A reference to the internal logger.
       */
      logger& lgr() { return m_lgr; }

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
      inline T get(const std::string& key)
      {
        try
        {
          const T val = convert<T>(m_values.at(key));

          // string -> T -> string useful to have
          // uniform syntax and test valid conversion
          if (m_logging)
            m_lgr.print(key + ": " + m_lgr.format(val));

          return val;
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
          m_values {{}};

      // True if logging is active, false otherwise.
      bool m_logging {false};

      // Logger for key-value parsing. Always present
      // even if not used, but waste deemed negligible.
      // Could have used unique_ptr<logger>, but then
      // checks were required to avoid dereferencing null
      // in lgr().
      // Default-initialized unless set up.
      logger m_lgr {};

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
