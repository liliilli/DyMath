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

#include <array>
#include <Math/Common/XGlobalMacroes.h>
#include <Math/Common/Inline/TGlobalTypes.inl>
#include <Math/Type/Math/DVector3.h>

namespace dy::math
{

/// @class DTorus
/// @tparam TType Real type
/// @brief Torus class
template <typename TType> 
struct MATH_NODISCARD DTorus
{
public:
  static_assert(
    kCategoryOf<TType> == EValueCategory::Real, 
    "Failed to make DTorus, DTorus only supports Real type.");
  using TValueType = TType;

  DTorus() = default;
  DTorus(const DVector3<TValueType>& origin, TValueType distance, TValueType radius);

  /// @brief Get Center Origin of torus.
  const DVector3<TValueType>& GetOrigin() const noexcept;

  /// @brief Get radius of tube.
  TValueType GetRadius() const noexcept;

  /// @brief Get distance from origin.
  TValueType GetDistance() const noexcept;

  /// @brief Check value has NaN.
  bool HasNaN() const noexcept;

  /// @brief Check value has Infinity.
  bool HasInfinity() const noexcept;

  /// @brief Check values are normal value, neither NaN nor Inf.
  bool HasOnlyNormal() const noexcept;

protected:
  DVector3<TValueType> mOrigin = {};
  TValueType mDistanceFromOrigin = TValueType{};
  TValueType mRadiusOfTube = TValueType{};
};

} /// ::dy::math namespace
#include <Math/Type/Inline/XShape/DTorus.inl>