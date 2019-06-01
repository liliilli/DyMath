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
#include <Math/Type/Color/DColorRGB.h>
#include <Math/Type/Math/DVector4.h>

namespace dy::math
{

/// @class DColorRGBA
/// @brief Float color type which stores 3 components (R, G, B)
/// (h, s, v) does not support but can be converted calling HsvToRgb().
template <typename TType>
struct MATH_NODISCARD DColorRGBA final
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
  DClamp<TType, 0, 1> A = 0.0f;

  DColorRGBA() = default;
  DColorRGBA(TType gray, TType alpha) noexcept;
  DColorRGBA(const DColorRGB<TType>& color, TType alpha) noexcept;
  DColorRGBA(TType r, TType g, TType b, TType a) noexcept;

  /// @brief Get values with index. index must be 0, 1 or 2.
  TValueType& operator[](TIndex index);
  /// @brief Get values with index. index must be 0, 1 or 2.
  const TValueType& operator[](TIndex index) const;

  /// @brief Get color's gray scale value following sRGB.
  TType ToGrayScale() const noexcept;

  /// @brief Get Data pointer
  TType* Data() noexcept;
  /// @brief Get Data pointer
  const TType* Data() const noexcept;

  DColorRGBA& operator+=(const DColorRGBA& value) noexcept;
  DColorRGBA& operator-=(const DColorRGBA& value) noexcept;
  DColorRGBA& operator*=(TValueType value) noexcept;
  DColorRGBA& operator*=(const DColorRGBA& value) noexcept;
  DColorRGBA& operator/=(TValueType value) noexcept;
  DColorRGBA& operator/=(const DColorRGBA& value) noexcept;

  /// @brief Cconvert it to DVector4 explicitly.
  explicit operator DVector4<TValueType>() const noexcept;

  inline static const DColorRGBA Aqua;
  inline static const DColorRGBA Black;
  inline static const DColorRGBA Blue;
  inline static const DColorRGBA DarkRed;
  inline static const DColorRGBA DarkGray;
  inline static const DColorRGBA DarkGreen;
  inline static const DColorRGBA Gold;
  inline static const DColorRGBA Gray = { 0.5f };
  inline static const DColorRGBA Green;
  inline static const DColorRGBA Magenta;
  inline static const DColorRGBA Orange;
  inline static const DColorRGBA Purple;
  inline static const DColorRGBA Red;
  inline static const DColorRGBA White = { 1.0f };
  inline static const DColorRGBA Yellow;
};

} /// ::dy::math namespace
#include <Math/Type/Inline/DColor/DColorRGBA.inl>
