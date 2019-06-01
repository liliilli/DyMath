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
#include <Math/Type/Math/DVector3.h>

namespace dy::math
{

/// @struct DRay
/// @tparam TType Real type.
/// @brief Ray type that has origin (position) and direction (normalized)
template <typename TType>
struct MATH_NODISCARD DRay final
{
  static_assert(kIsRealType<TType> == true, "DRay only supports real type.");
  using TValueType = TType;

  DRay(
    const DVector3<TValueType>& origin, 
    const DVector3<TValueType>& direction,
    bool doNormalize = true);

  /// @brief Get ray's origin position.
  const DVector3<TValueType>& GetOrigin() const noexcept; 

  /// @brief Get ray's direction (normalized)
  const DVector3<TValueType>& GetDirection() const noexcept;

  /// @brief Get proceeded position with t. (origin + t * direction)
  DVector3<TValueType> GetPointAtParam(TReal t) const;

  /// @brief Check value has NaN.
  bool HasNaN() const noexcept;

  /// @brief Check value has Infinity.
  bool HasInfinity() const noexcept;

  /// @brief Check values are normal value, neither NaN nor Inf.
  bool HasOnlyNormal() const noexcept;

private:
  DVector3<TValueType> mOrigin;
  DVector3<TValueType> mDirection;
};

} /// ::dy::math namespace
#include <Math/Type/Inline/DRay/DRay.inl>