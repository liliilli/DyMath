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

/// @enum EPosPlaneState
/// @brief Point's state for comparing status of position with plane.
enum class EPosPlaneState
{
  FrontNormal,  // Point is in front of plane normal.
  BehindNormal, // Point is bahind of plane normal.
  OnPlane       // Point is on plane.
};

/// @struct DPlane
/// @brief Plane type.
/// Plane type just can only store real number type. \n
///
///          . <= Normal (A, B, C) \n
///     /----|----\ \n
///    /     |     \ \n
///   /      '      \ \n
///  /---------------\ <= Plane \n
/// \n
template <typename TType>
struct MATH_NODISCARD DPlane 
{
  static_assert(kIsRealType<TType> == true, "DPlane only supports real type.");
  using TValueType = TType;

  DPlane() = default;
  /// @brief a, b, c will be normalized values as |a, b, c| == 1
  DPlane(TValueType a, TValueType b, TValueType c, TValueType d);
  /// @brief Construct DPlane with normalized vector and just d.
  DPlane(const DVector3<TValueType>& normalizedVector, TValueType d);
  /// @brief Construt DPlane with (pos2 - pos1) and (pos3 - pos1) vector.
  DPlane(const DVector3<TValueType>& pos1, const DVector3<TValueType>& pos2, const DVector3<TValueType>& pos3);

  /// @brief Set new normal vector to plane.
  /// Vector must be normalized when input.
  void SetNormalVector(const DVector3<TValueType>& iNormalVector);

  /// @brief Get normal vector.
  /// Returned normal vector does not guarantees that length is 1.
  DVector3<TValueType> GetNormal() const noexcept;

  /// @brief Get D value.
  TValueType GetD() const noexcept;

  /// @brief Check given point is on plane, on front (pos), on behind (neg).
  EPosPlaneState CheckPointStatusOnPlane(const DVector3<TValueType>& iPoint) const noexcept;
  
  /// @brief Get given point's signed distance from plane.
  TReal GetSignedDistanceFrom(const DVector3<TType>& iPoint) const noexcept;

  /// @brief Get given point's signed distance from plane.
  TReal GetUnsignedDistanceFrom(const DVector3<TType>& iPoint) const noexcept;

  /// @brief Get closest on-plane point of given point.
  DVector3<TValueType> GetClosestPoint(const DVector3<TValueType>& iPoint) const noexcept;

  /// @brief Check value has NaN.
  bool HasNaN() const noexcept;

  /// @brief Check value has Infinity.
  bool HasInfinity() const noexcept;

  /// @brief Check values are normal value, neither NaN nor Inf.
  bool HasOnlyNormal() const noexcept;

private:
  /// @brief Normal value.
  DVector3<TValueType> mNormal = DVector3<TValueType>::UnitY(); 
  /// @brief D value.
  TValueType mD = TValueType{};
};

} /// ::dy::math namespace
#include <Math/Type/Inline/XShape/DPlane.inl>
