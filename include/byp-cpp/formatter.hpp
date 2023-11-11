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

#ifndef BYPCPP_FORMATTER_HPP
#define BYPCPP_FORMATTER_HPP

/*! @file include/byp-cpp/formatter.hpp
 *
 *  @brief Formatter class definition
 */

#include <iomanip>
#include <sstream>
#include <string>

//! Namespace for `byp` library.
namespace byp
{
  class formatter
  {
    public:
      //! Public constructor.
      /*!
       * Does not specify floating-point formatting,
       * left to system default.
       */
      formatter() {}

      //! Public constructor.
      /*!
       * Sets scientific notation with the specified
       * number of floating-point part digits.
       *
       * @param digits Set floating-point digit number.
       *
       * @throws invalid_argument If `digits < 0`.
       */
      formatter(const int digits)
      {
        set_scientific(digits);
      }

      //! Set number of digits post-construction.
      /*!
       * Sets scientific notation with the specified
       * number of floating-point part digits.
       *
       * @param digits Set floating-point digit number.
       *
       * @throws invalid_argument If `digits < 0`.
       */
      void set_scientific(const int digits);

      //! Formatting functions, specified type -> string
      /*!
       * Uses the same conventions expected when parsing
       * parameter files (+ no trailing commas for
       * vectors).
       *
       * @param val The value to convert.
       *
       * @return The converted string.
       */
      template <typename T>
      std::string format(const T& val);

    private:
      // Stringstream object used for type-safe printing
      std::stringstream ss{};
  };
} // namespace byp

#endif
