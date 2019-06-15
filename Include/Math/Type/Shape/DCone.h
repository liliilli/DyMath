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
#include <Math/Common/Inline/TGlobalTypes.inl>
#include <Math/Type/Math/DVector3.h>

namespace dy::math
{

/// @class DCone
/// @tparam TType Real type
/// @brief Cone class
template <typename TType> 
struct MATH_NODISCARD DCone
{
public:
  static_assert(
    kCategoryOf<TType> == EValueCategory::Real, 
    "Failed to make DCone, DCone only supports Real type.");
  using TValueType = TType;

  DCone(const DVector3<TValueType>& origin, TValueType height, TValueType radius);
  DCone(const DVector3<TValueType>& origin, TValueType hr);

  /// @brief Get ray's origin position.
  const DVector3<TValueType>& GetOrigin() const noexcept;

  /// @brief Get height value.
  TValueType GetHeight() const noexcept;

  /// @brief Get ray's direction (normalized)
  TValueType GetRadius() const noexcept;

  /// @brief Check value has NaN.
  bool HasNaN() const noexcept;

  /// @brief Check value has Infinity.
  bool HasInfinity() const noexcept;

  /// @brief Check values are normal value, neither NaN nor Inf.
  bool HasOnlyNormal() const noexcept;

protected:
  DVector3<TValueType> mOrigin;
  TValueType mHeight; 
  TValueType mRadius; 
};

} /// ::dy::math namespace
#include <Math/Type/Inline/XShape/DCone.inl>