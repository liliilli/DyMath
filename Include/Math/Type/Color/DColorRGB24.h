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

#include <Math/Common/XGlobalMacroes.h>
#include <Math/Common/TGlobalTypes.h>
#include <Math/Type/Color/DColorRGB.h>
#include <Math/Type/Color/DColorRGBA.h>

//!
//! Forward declaration
//!

namespace dy::math
{
struct DColorRGBA32;
} /// ::dy::math namespace

//!
//! Implementation
//!

namespace dy::math
{

/// @class DColorRGB24
/// @brief 8-bit color type which stores 3 components (R, G, B).
/// (h, s, v) does not support but can be converted calling HsvToRgb().
struct MATH_NODISCARD DColorRGB24 final
{
public:
  using TValueType = TU8;
  TU8 R = 0;
  TU8 G = 0;
  TU8 B = 0;

  DColorRGB24() = default;
  DColorRGB24(TU8 gray) noexcept;
  DColorRGB24(TU8 r, TU8 g, TU8 b) noexcept;

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

  DColorRGB24& operator+=(const DColorRGB24 & value) noexcept;
  DColorRGB24& operator-=(const DColorRGB24 & value) noexcept;

   /// @brief Convert to DColorRGB. 
  template <typename TType>
  operator DColorRGB<TType>() const noexcept;
  /// @brief Convert to DColorRGBA. 
  /// When converted to RGBA type, Alpha will be 1.0. (opaque)
  template <typename TType>
  explicit operator DColorRGBA<TType>() const noexcept;
  /// @brief Convert to DColorRGBA.
  /// When converted to RGBA type, Alpha will be 255. (opaque)
  explicit operator DColorRGBA32() const noexcept;

  static const DColorRGB24 Aqua;
  static const DColorRGB24 Black;
  static const DColorRGB24 Blue;
  static const DColorRGB24 DarkRed;
  static const DColorRGB24 DarkGray;
  static const DColorRGB24 DarkGreen;
  static const DColorRGB24 Gold;
  static const DColorRGB24 Gray;
  static const DColorRGB24 Green;
  static const DColorRGB24 Magenta;
  static const DColorRGB24 Orange;
  static const DColorRGB24 Purple;
  static const DColorRGB24 Red;
  static const DColorRGB24 White;
  static const DColorRGB24 Yellow;
};

} /// ::dy::name namespace
#include <Math/Type/Inline/DColor/DColorRGB24.inl>