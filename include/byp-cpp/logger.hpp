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

#include <fstream>
#include <iostream>
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
      void set_precision(const int precision = 6)
      {
        if (precision < 0)
          throw std::invalid_argument(
              "invalid arg in logger::set_precision()"
          );

        m_precision = precision;
      }

      //! Set prefix/suffix strings.
      /*!
       * Call without argument to set to empty.
       *
       * @param prefix Desired prefix string.
       * @param suffix Desired suffix string.
       */
      void set_context(
          const std::string prefix = "",
          const std::string suffix = ""
      )
      {
        m_prefix = prefix;
        m_suffix = suffix;
      }

      //! Set file to contain logging messages.
      /*!
       * Call without argument to set to std::cout.
       * File will be appended to if existing.
       *
       * @param logfile Path to the desired logfile.
       */
      void set_logfile(const std::string path = "")
      {
        if (m_ofs.is_open())
          m_ofs.close();

        if (!path.empty())
          m_ofs.open(path);
      }

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
      std::string format(const T& val) const;

      //! Prints keeping prefix/suffix into account.
      /*!
       * Uses the internal ofstream if open, std::cout
       * otherwise.
       *
       * @param content The string to print.
       */
      void print(const std::string content)
      {
        std::ostream& out
            = (m_ofs.is_open() ? m_ofs : std::cout);

        out << m_prefix << content << m_suffix
            << std::endl;
      }

    private:
      // Private parameters are left uninitialized here,
      // default constructor will set defaults.

      // Scientific/fixed-point notation if true/false.
      bool m_scientific;

      // Scientific/fixed-point precision (default C++
      // value, set by `std::basic_ios::init()`).
      int m_precision;

      // Prepended/appended when calling `print()`.
      std::string m_prefix, m_suffix;

      // Logfile for print().
      std::ofstream m_ofs;
  };
} // namespace byp

#endif
