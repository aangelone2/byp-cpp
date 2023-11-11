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

#ifndef BYPCPP_LOGGER_HPP
#define BYPCPP_LOGGER_HPP

/*! @file include/byp-cpp/logger.hpp
 *
 *  @brief Logger class definition
 */

#include <string>

//! Namespace for `byp` library.
namespace byp
{
  //! Logger class to log key-value parsings.
  class logger
  {
    public:
      //! Public constructor.
      /*!
       * Sets default value parameters calling setters
       * with no arguments (see below).
       */
      logger();

      //! Sets scientific/fixed-point notation.
      /*!
       * Call without argument to reset to C++ default.
       *
       * @param scientific Sets scientific/fixed-point
       * notation if true/false.
       */
      void set_scientific(const bool scientific = false)
      {
        m_scientific = scientific;
      }

      //! Set floating-point precision.
      /*!
       * Call without argument to set to C++ default.
       *
       * @param precision Desired decimal digit number.
       *
       * @throws invalid_argument If `digits < 0`.
       */
      void set_precision(const int precision = 6);

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
      // Scientific/fixed-point notation if true/false.
      bool m_scientific;
      // Scientific/fixed-point precision (default C++
      // value, set by `std::basic_ios::init()`).
      int m_precision;
  };
} // namespace byp

#endif
