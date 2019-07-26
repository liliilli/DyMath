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

#include <Math/Utility/XMath.h>
#include <Math/Utility/XLinearMath.h>
#include <Math/Type/Math/DMatrix3.h>
#include <Math/Type/Math/DQuat.h>

namespace dy::math
{

template <typename TLeft, typename TRight, EMatMajor TMajor> 
DBounds3D<GetBiggerType<TLeft, TRight>>
operator*(const DMatrix3<TLeft, TMajor>& lhs, const DBounds3D<TRight>& rhs) noexcept
{
  // Get Point list of rhs AABB.
  using TBiggerType = GetBiggerType<TLeft, TRight>;
  std::vector<DVector3<typename DBounds3D<TRight>::TValueType>> pointList = rhs.GetPointList();
  for (auto& item : pointList)
  {
    item = lhs * item;
  }

  // If TBiggerType and TRigth is not matched, create new point list and convert them.
  if constexpr (std::is_same_v<TBiggerType, TRight> == true)
  {
    return {pointList};
  }
  else
  {
    const std::vector<DVector3<TBiggerType>> result;
    for (const auto& item : pointList)
    {
      result.emplace_back(static_cast<DVector3<TBiggerType>>(item));
    }
    return {result};
  }
}
 
template <typename TLeft, typename TRight> 
DBounds3D<GetBiggerType<TLeft, TRight>>
operator*(const DQuaternion<TLeft>& lhs, const DBounds3D<TRight>& rhs) noexcept
{
  return lhs.ToMatrix3<EMatMajor::Column>() * rhs;
}
   
template <typename TLeft, typename TRight>
DBounds3D<GetBiggerType<TLeft, TRight>> 
operator+(const DBounds3D<TLeft>& lhs, const DBounds3D<TRight>& rhs) noexcept 
{
  using TBiggerType = GetBiggerType<TLeft, TRight>;
  return DBounds3D<TBiggerType>{
    ExtractMin(lhs.GetMinimumPoint(), rhs.GetMinimumPoint()), 
    ExtractMax(lhs.GetMaximumPoint(), rhs.GetMaximumPoint())
  };
}

template <typename TType>
bool operator==(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs) noexcept
{
  return 
      lhs.GetMinimumPoint() == rhs.GetMinimumPoint()
  &&  lhs.GetMaximumPoint() == rhs.GetMaximumPoint();
}

template <typename TType>
bool operator!=(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs) noexcept
{
  return !(lhs == rhs);
}
  
template <typename TType>
DBounds3D<TType>::DBounds3D(const DVector3<TValueType>& point)
  : __mMin{point}, __mMax{point}
{ }

template <typename TType>
DBounds3D<TType>::DBounds3D(const DVector3<TValueType>& point1, const DVector3<TValueType>& point2)
  : __mMin{ExtractMin(point1, point2)},
    __mMax{ExtractMax(point1, point2)}
{ }

template <typename TType>
DBounds3D<TType>::DBounds3D(const std::vector<DVector3<TValueType>>& list)
  : __mMin { kMaxValueOf<TValueType> },
    __mMax { kMinValueOf<TValueType> }
{
  for (auto& point : list)
  {
    this->__mMin = ExtractMin(this->__mMin, point);
    this->__mMax = ExtractMax(this->__mMax, point);
  }
}

template <typename TType>
template <typename TAnotherType>
DBounds3D<TType>::operator DBounds3D<TAnotherType>() const noexcept
{
  return {
    static_cast<DVector3<TAnotherType>>(this->GetMinimumPoint()), 
    static_cast<DVector3<TAnotherType>>(this->GetMaximumPoint())
  };
}

template <typename TType>
TReal DBounds3D<TType>::GetArea() const noexcept
{
  return this->GetSurfaceArea();
}

template <typename TType>
TReal DBounds3D<TType>::GetSurfaceArea() const noexcept
{
  const auto diagonal   = this->GetDiagonal();
  const auto plane3Area = Dot(diagonal, diagonal);

  return static_cast<TReal>(plane3Area) * TReal(2);
}

template<typename TType>
TReal DBounds3D<TType>::GetVolume() const noexcept
{
  const auto diagonal = this->GetDiagonal();
  return static_cast<TReal>(diagonal.X * diagonal.Y * diagonal.Z);
}

template<typename TType>
DVector3<typename DBounds3D<TType>::TValueType> DBounds3D<TType>::GetLength() const noexcept
{
  return this->GetDiagonal();
}

template <typename TType>
DVector3<typename DBounds3D<TType>::TValueType> DBounds3D<TType>::GetDiagonal() const noexcept
{
  return this->__mMax - this->__mMin;
}

template <typename TType>
const DVector3<TType>& DBounds3D<TType>::GetMinimumPoint() const noexcept
{
  return this->GetMin();
}

template <typename TType>
const DVector3<typename DBounds3D<TType>::TValueType>& DBounds3D<TType>::GetMin() const noexcept
{
  return this->__mMin;
}

template <typename TType>
const DVector3<typename DBounds3D<TType>::TValueType>& DBounds3D<TType>::GetMaximumPoint() const noexcept
{
  return this->GetMax();
}

template <typename TType>
const DVector3<typename DBounds3D<TType>::TValueType>& DBounds3D<TType>::GetMax() const noexcept
{
  return this->__mMax;
}

template <typename TType>
DVector3<typename DBounds3D<TType>::TValueType> DBounds3D<TType>::GetPointOf(EBounds3D type) const noexcept
{
  const auto v = static_cast<std::underlying_type_t<EBounds3D>>(type);
  return DVector3<TValueType>
  {
    (v >> 2) ? this->__mMax.X : this->__mMin.X,
    (v & 0b10) >> 1 ? this->__mMax.Y : this->__mMin.Y,
    (v & 0b1) ? this->__mMax.Z : this->__mMin.Z
  };
}

template <typename TType>
std::vector<DVector3<typename DBounds3D<TType>::TValueType>> DBounds3D<TType>::GetPointList() const
{
  std::vector<DVector3<TValueType>> result;
  result.reserve(8);
  for (TIndex i = 0; i < 8; ++i)
  {
    result.emplace_back(this->GetPointOf(static_cast<EBounds3D>(i)));
  }

  return result;
}

template<typename TType>
bool DBounds3D<TType>::IsInfiniteBound() const noexcept
{
  return 
      this->__mMin == DVector3<TValueType>{kMinValueOf<TValueType>}
  &&  this->__mMax == DVector3<TValueType>{kMaxValueOf<TValueType>};
}

template<typename TType>
bool DBounds3D<TType>::HasNaN() const noexcept
{
  return 
      this->__mMin.HasNan() == true
  ||  this->__mMax.HasNan() == true; 
}

template<typename TType>
bool DBounds3D<TType>::HasInfinity() const noexcept
{
  return 
      this->__mMin.HasInfinity() == true
  ||  this->__mMax.HasInfinity() == true;
}

template<typename TType>
bool DBounds3D<TType>::HasOnlyNormal() const noexcept
{
  return 
      this->__mMin.HasOnlyNormal() == true
  &&  this->__mMax.HasOnlyNormal() == true;
}

} /// ::dy::math namespace