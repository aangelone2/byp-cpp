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

#ifndef BYPCPP_FUNCTIONS_HPP
#define BYPCPP_FUNCTIONS_HPP

#include <string>

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
   * @return The parsed value of the specified type.
   *
   * @throws invalid_argument If invalid value passed.
   */
  template <typename T>
  T convert(const std::string& val);
} // namespace byp

#endif
