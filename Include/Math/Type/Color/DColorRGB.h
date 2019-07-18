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
#include <Math/Type/Micellanous/DClamp.h>
#include <Math/Type/Math/DVector3.h>

namespace dy::math
{

/// @class DColorRGB
/// @brief Float color type which stores 3 components (R, G, B)
/// (h, s, v) does not support but can be converted calling HsvToRgb().
template <typename TType>
struct MATH_NODISCARD DColorRGB final
{
private:
  static_assert(
    kCategoryOf<TType> == EValueCategory::Real, 
    "Failed to make DMatrix, DMatrix only supports Real type.");

public:
  using TValueType = TType;
  DClamp<TType, 0, 1> R = 0.0f;
  DClamp<TType, 0, 1> G = 0.0f;
  DClamp<TType, 0, 1> B = 0.0f;

  DColorRGB() = default;
  DColorRGB(TType gray) noexcept;
  DColorRGB(TType r, TType g, TType b) noexcept;

  /// @brief Get values with index. index must be 0, 1 or 2.
  TValueType& operator[](TIndex index);
  /// @brief Get values with index. index must be 0, 1 or 2.
  const TValueType& operator[](TIndex index) const;

  /// @brief Get color's gray scale value following sRGB.
  TType ToGrayValue() const noexcept;

  /// @brief Get Data pointer
  TType* Data() noexcept;
  /// @brief Get Data pointer
  const TType* Data() const noexcept;

  DColorRGB& operator+=(const DColorRGB& value) noexcept;
  DColorRGB& operator-=(const DColorRGB& value) noexcept;
  DColorRGB& operator*=(TValueType value) noexcept;
  DColorRGB& operator*=(const DColorRGB& value) noexcept;
  DColorRGB& operator/=(TValueType value) noexcept;
  DColorRGB& operator/=(const DColorRGB& value) noexcept;

  /// @brief Can be convert DVector3 explicitly, but alpha information passed.
  explicit operator DVector3<TValueType>() const noexcept;

  static const DColorRGB Aqua;
  static const DColorRGB Black;
  static const DColorRGB Blue;
  static const DColorRGB DarkRed;
  static const DColorRGB DarkGray;
  static const DColorRGB DarkGreen;
  static const DColorRGB Gold;
  static const DColorRGB Gray;
  static const DColorRGB Green;
  static const DColorRGB Magenta;
  static const DColorRGB Orange;
  static const DColorRGB Purple;
  static const DColorRGB Red;
  static const DColorRGB White;
  static const DColorRGB Yellow;
};

} /// ::dy::math namespace
#include <Math/Type/Inline/DColor/DColorRGB.inl>
