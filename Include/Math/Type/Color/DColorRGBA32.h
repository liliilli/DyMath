#pragma once
///
/// MIT License
/// Copyright (c) 2018-2019 Jongmin Yun
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///

#include <Math/Common/TGlobalTypes.h>
#include <Math/Common/XGlobalMacroes.h>
#include <Math/Type/Color/DColorRGBA.h>

//!
//! Forward declaration
//!

namespace dy::math
{
struct DColorRGB24;
} /// ::dy::math namespace

//!
//! Implementation
//!

namespace dy::math
{

/// @class DColorRGBA32
/// @brief 8-bit color type which stores 4 components (R, G, B, A)
struct MATH_NODISCARD DColorRGBA32 final
{
public:
  using TValueType = TU8;
  TU8 R = 0;
  TU8 G = 0;
  TU8 B = 0;
  TU8 A = 0;

  DColorRGBA32() = default;
  DColorRGBA32(TU8 gray, TU8 alpha) noexcept;
  DColorRGBA32(const DColorRGB24& rgb, TU8 alpha) noexcept;
  DColorRGBA32(TU8 r, TU8 g, TU8 b, TU8 a) noexcept;

  /// @brief Get values with index. index must be 0, 1 or 2.
  TValueType& operator[](TIndex index);
  /// @brief Get values with index. index must be 0, 1 or 2.
  const TValueType& operator[](TIndex index) const;

  /// @brief Get color's gray scale value following sRGB.
  TReal ToGrayValue() const noexcept;

  /// @brief Get Data pointer
  TValueType* Data() noexcept;
  /// @brief Get Data pointer
  const TValueType* Data() const noexcept;

  DColorRGBA32& operator+=(const DColorRGBA32& value) noexcept;
  DColorRGBA32& operator-=(const DColorRGBA32& value) noexcept;

  /// @brief Get color's gray scale value following sRGB.
  TReal GetGrayValue() const noexcept
  {
    return 0.2126f * this->R + 0.7152f * this->G + 0.0722f * this->B;
  }

  /// @brief Can be convert DDyColor explicitly.
  template <typename TType>
  operator DColorRGBA<TType>() const noexcept;

  static const DColorRGBA32 Aqua;
  static const DColorRGBA32 Black;
  static const DColorRGBA32 Blue;
  static const DColorRGBA32 DarkRed;
  static const DColorRGBA32 DarkGray;
  static const DColorRGBA32 DarkGreen;
  static const DColorRGBA32 Gold;
  static const DColorRGBA32 Gray;
  static const DColorRGBA32 Green;
  static const DColorRGBA32 Magenta;
  static const DColorRGBA32 Orange;
  static const DColorRGBA32 Purple;
  static const DColorRGBA32 Red;
  static const DColorRGBA32 White;
  static const DColorRGBA32 Yellow;
};

} /// ::dy::math namespace
#include <Math/Type/Inline/DColor/DColorRGBA32.inl>