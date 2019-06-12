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

/// @enum EBoxDir
/// @brief Box Direction helping enum type.
enum class EBoxDir
{
  Right = 0,
  Left,
  Up,
  Down,
  Front,
  Back
};

/// @class DBox
/// @tparam TType Real type
/// @brief Box (Rectangle, Square, and Rectangle that not have centered barycentric position) class
template <typename TType> 
struct MATH_NODISCARD DBox
{
public:
  static_assert(
    kCategoryOf<TType> == EValueCategory::Real, 
    "Failed to make DBox, DBox only supports Real type.");
  using TValueType = TType;

  DBox(const DVector3<TValueType>& origin, 
    TValueType right, TValueType left, TValueType up, 
    TValueType down, TValueType front, TValueType back);
  DBox(const DVector3<TValueType>& origin, const std::array<TValueType, 6>& lengthList);
  DBox(const DVector3<TValueType>& origin, const DVector3<TValueType>& length);
  DBox(const DVector3<TValueType>& origin, TValueType right, TValueType up, TValueType down);
  DBox(const DVector3<TValueType>& origin, TValueType length);

  /// @brief Get positive length of direction.
  TValueType GetLengthOf(EBoxDir direction) const noexcept;

  /// @brief Get ray's origin position.
  const DVector3<TValueType>& GetOrigin() const noexcept;

  /// @brief Get min pos of box in local space.
  DVector3<TValueType> GetMinPos() const noexcept;

  /// @brief Get max pos of box in local space.
  DVector3<TValueType> GetMaxPos() const noexcept;

  /// @brief Get length list of box.
  std::array<TValueType, 6> GetLengthList() const noexcept;

  /// @brief Check this box is symmetrical, 
  /// so right and left are same, up and down are same, and front and back are same length to each other.
  bool IsSymmetrical() const noexcept;

  /// @brief Check this box is squared.
  /// IsSymmetrical() is true and right, up and front are same length.
  bool IsSquare() const noexcept;

  /// @brief Check value has NaN.
  bool HasNaN() const noexcept;

  /// @brief Check value has Infinity.
  bool HasInfinity() const noexcept;

  /// @brief Check values are normal value, neither NaN nor Inf.
  bool HasOnlyNormal() const noexcept;

protected:
  DVector3<TValueType> mOrigin;
  std::array<TValueType, 6> mLength;
};

} /// ::dy::math namespace
#include <Math/Type/Inline/XShape/DBox.inl>