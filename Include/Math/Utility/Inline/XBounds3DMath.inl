#pragma once
///
/// MIT License
/// Copyright (c) 2019 Jongmin Yun
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
///

#include <utility>
#include <vector>
#include <Math/Common/TGlobalTypes.h>

namespace dy::math
{

template <typename TType>
DBounds3D<TType> GetUnionOf(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs)
{
  return {{lhs.GetMin(), lhs.GetMax(), rhs.GetMin(), rhs.GetMax()}};
}

template <typename TType>
std::optional<DBounds3D<TType>> GetIntersectionOf(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs)
{
  const auto& lhsMin = lhs.GetMin();
  const auto& lhsMax = lhs.GetMax();
  const auto& rhsMin = rhs.GetMin();
  const auto& rhsMax = rhs.GetMax();
  const auto min = ExtractMax(lhsMin, rhsMin);
  const auto max = ExtractMin(lhsMax, rhsMax);

  constexpr TType epsilon = TType(1e-5);
  if (const auto offset = max - min; offset.X <= -epsilon || offset.Y <= -epsilon || offset.Z <= -epsilon)
  {
    return std::nullopt;
  }

  return DBounds3D<TType>{min, max};
}

template <typename TType>
bool IsOverlapped(const DBounds3D<TType>& lhs, const DBounds3D<TType>& rhs)
{
  return GetIntersectionOf(lhs, rhs).has_value();
}

template <typename TType>
DSphere<TType> GetBoundingSphereOf(const DBounds3D<TType>& bounds)
{
  const auto& min = bounds.GetMin();
  const auto& max = bounds.GetMax();
  const auto origin = (min + max) / TType(2);
  const auto length = bounds.GetLength() / TType(2);

  return DSphere<TType>{origin, std::max({length[0], length[1], length[2]})};
}

template <typename TType>
DBounds3D<TType> GetExpandOf(const DBounds3D<TType>& bounds, TType value)
{
  const auto& min = bounds.GetMin();
  const auto& max = bounds.GetMax();
  return {min - DVector3<TType>{value}, max + DVector3<TType>{value}};
}

template <typename TType>
DBounds3D<TType> GetMovedOf(const DBounds3D<TType>& bounds, const DVector3<TType>& offset)
{
  if (bounds.IsInfiniteBound() == true) { return bounds; }
  return {bounds.GetMin() + offset, bounds.GetMax() + offset};
}

//!
//! GetDBounds3DOf
//!

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DSphere<TType>& shape)
{
  const auto& origin  = shape.GetOrigin();
  const auto offset   = DVector3<TType>{shape.GetRadius()};

  return { origin - offset, origin + offset };
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DPlane<TType>&)
{
  // Always return infinite bounds3d.
  return {};
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DBox<TType>& shape)
{
  return {shape.GetMinPos(), shape.GetMaxPos()};
}

template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DBox<TType>& shape, const DMatrix3<TType, TMajor>& rot)
{
  const auto& origin = shape.GetOrigin();
  return  
    GetMovedOf(
      rot * GetMovedOf( // Rotation // Move to origin {0}.
          GetDBounds3DOf(shape) 
        , origin * -1)
      , origin // Move to original position. {origin}
    );
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DBox<TType>& shape, const DQuaternion<TType>& rot)
{
  return GetDBounds3DOf(shape, rot.ToMatrix3<EMatMajor::Column>());
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DTorus<TType>& shape)
{
  const auto dR = shape.GetDistance();
  const auto r  = shape.GetRadius();
  const auto& origin = shape.GetOrigin();
  const auto offset = shape.GetOrigin() + DVector3<TType>{dR + r, dR + r, r};

  return {origin + offset, origin - offset};
}

template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DTorus<TType>& shape, const DMatrix3<TType, TMajor>& rot)
{
  const auto& origin = shape.GetOrigin();
  return  
    GetMovedOf(
      rot * GetMovedOf( // Rotation // Move to origin {0}.
          GetDBounds3DOf(shape) 
        , origin * -1)
      , origin // Move to original position. {origin}
    );
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DTorus<TType>& shape, const DQuaternion<TType>& rot)
{
  return GetDBounds3DOf(shape, rot.ToMatrix3<EMatMajor::Column>());
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCone<TType>& shape)
{
  const auto& origin = shape.GetOrigin();
  const auto y = shape.GetHeight();
  const auto xz = shape.GetRadius();
  
  return {origin + DVector3<TType>{xz, y, xz}, origin - DVector3<TType>{xz, 0, xz}};
}

template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DCone<TType>& shape, const DMatrix3<TType, TMajor>& rot)
{
  const auto& origin = shape.GetOrigin();
  return  
    GetMovedOf(
      rot * GetMovedOf( // Rotation // Move to origin {0}.
          GetDBounds3DOf(shape) 
        , origin * -1)
      , origin // Move to original position. {origin}
    );
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCone<TType>& shape, const DQuaternion<TType>& rot)
{
  return GetDBounds3DOf(shape, rot.ToMatrix3<EMatMajor::Column>());
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCapsule<TType>& shape)
{
  const auto& origin = shape.GetOrigin();
  const auto h = shape.GetHeight();
  const auto r = shape.GetRadius();

  return {origin + DVector3<TType>{r, h + r, r}, origin - DVector3<TType>{r}};
}

template <typename TType, EMatMajor TMajor>
DBounds3D<TType> GetDBounds3DOf(const DCapsule<TType>& shape, const DMatrix3<TType, TMajor>& rot)
{
  const auto& origin = shape.GetOrigin();
  return  
    GetMovedOf(
      rot * GetMovedOf( // Rotation // Move to origin {0}.
          GetDBounds3DOf(shape) 
        , origin * -1)
      , origin // Move to original position. {origin}
    );
}

template <typename TType>
DBounds3D<TType> GetDBounds3DOf(const DCapsule<TType>& shape, const DQuaternion<TType>& rot)
{
  return GetDBounds3DOf(shape, rot.ToMatrix3<EMatMajor::Column>());
}

} /// ::dy::math namespace