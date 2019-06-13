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

/// @brief Check that Ray is intersected into Sphere.
template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DSphere<TType>& sphere)
{
  // Check there is intersection by using quadratic formula.
  const auto alp = ray.GetOrigin() - sphere.GetOrigin();
  const auto dir = ray.GetDirection();

  const auto b = 2 * Dot(alp, dir);
  const auto c = Dot(alp, alp) - (sphere.GetRadius() * sphere.GetRadius());

  const auto result = SolveQuadric(TReal(1), TReal(b), TReal(c));
  if (result.empty() == true) { return false; }

  return std::any_of(result.cbegin(), result.cend(), [](const auto& value) { return value >= 0; });
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box)
{
  const auto tResult = GetTValuesOf(ray, box);
  return tResult.empty() == false;
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot)
{
  // We regards box is symmetrical and origin is located on origin of box space.
  // We need to convert ray of world-space into box-space.
  const auto invRotMat = rot.Transpose();
  const auto localSpaceRayPos = invRotMat * (ray.GetOrigin() - box.GetOrigin());
  const auto localSpaceRayDir = invRotMat * ray.GetDirection();

  return IsRayIntersected(
    DRay<TType>{localSpaceRayPos, localSpaceRayDir}, 
    DBox<TType>{DVector3<TType>{0}, box.GetLengthList()}
  );
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot)
{
  return IsRayIntersected(ray, box, rot.ToMatrix3());
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DPlane<TType>& plane)
{
  // plane is just stretch to infinity, 
  // so we can just only check whether ray direction is forward to plane or not.
  const auto sdfValue = GetSDFValueOf(ray.GetOrigin(), plane);
  if (sdfValue == 0.0f) { return true; }

  // SDF value is positive when ray point is on normal-forwarded region,
  // so need to invert normal when SDF is positive.
  const auto normal = plane.GetNormal() * (sdfValue > TType(0) ? TType(-1) : TType(1));
  return Dot(ray.GetDirection(), normal) > 0.0f;
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DTorus<TType>& torus)
{
  const auto tResult = GetTValuesOf(ray, torus);
  return tResult.empty() == false;
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType>& rot)
{
  // We regards box is symmetrical and origin is located on origin of box space.
  // We need to convert ray of world-space into box-space.
  const auto invRotMat = rot.Transpose();
  const auto localSpaceRayPos = invRotMat * (ray.GetOrigin() - torus.GetOrigin());
  const auto localSpaceRayDir = invRotMat * ray.GetDirection();

  return IsRayIntersected(
    DRay<TType>{localSpaceRayPos, localSpaceRayDir}, 
    DTorus<TType>{DVector3<TType>{0}, torus.GetDistance(), torus.GetOrigin()}
  );
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DTorus<TType>& torus, const DQuaternion<TType>& rot)
{
  return IsRayIntersected(ray, torus, rot.ToMatrix3());
}

//!
//! GetSDFValueOf
//!

/// @brief Get signed distance value of sphere model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DSphere<TType>& sphere)
{
  return (point - sphere.GetOrigin()).GetLength() - sphere.GetRadius();
}

template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DBox<TType>& box)
{
  // If box is not symmetrical, realign box into aligend box that has same axis length,
  // and GetSDFValueOf function once more.
  if (box.IsSymmetrical() == false)
  {
    const auto& origin = box.GetOrigin();
    const auto  offset = DVector3<TType>{
      (box.GetLengthOf(EBoxDir::Right) - box.GetLengthOf(EBoxDir::Left)) / 2, 
      (box.GetLengthOf(EBoxDir::Up) - box.GetLengthOf(EBoxDir::Down)) / 2, 
      (box.GetLengthOf(EBoxDir::Front) - box.GetLengthOf(EBoxDir::Back)) / 2};
    const auto  length = DVector3<TType>{
      (box.GetLengthOf(EBoxDir::Right) + box.GetLengthOf(EBoxDir::Left)) / 2, 
      (box.GetLengthOf(EBoxDir::Up) + box.GetLengthOf(EBoxDir::Down)) / 2, 
      (box.GetLengthOf(EBoxDir::Front) + box.GetLengthOf(EBoxDir::Back)) / 2};

    return GetSDFValueOf(point, DBox<TType>{origin + offset, length});
  }

  // If box is symmetrical, just get SDF value.
  const auto relativePos = point - box.GetOrigin();
  const auto distance = 
      math::Abs(relativePos) 
    - DVector3<TType>{box.GetLengthOf(EBoxDir::Right), box.GetLengthOf(EBoxDir::Up), box.GetLengthOf(EBoxDir::Front)};

  return 
      ExtractMax(distance, DVector3<TType>{0}).GetLength()
    + std::min(std::max(distance.X, std::max(distance.Y, distance.Z)), TType(0));
}

template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DBox<TType>& box, const DMatrix3<TType>& rot)
{
  // We regards box is symmetrical and origin is located on origin of box space.
  // We need to convert ray of world-space into box-space.
  const auto invRotMat = rot.Transpose();
  const auto localSpacePos = invRotMat * (point - box.GetOrigin());
  
  return GetSDFValueOf(localSpacePos, DBox<TType>{DVector3<TType>{0}, box.GetLengthList()});
}

template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DBox<TType>& box, const DQuaternion<TType>& rot)
{
  return GetSDFValueOf(point, box, rot.ToMatrix3());
}

template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DPlane<TType>& plane)
{
  return (Dot(point, plane.GetNormal()) + plane.GetD()) / plane.GetNormal().GetLength();
}

//!
//! GetTValuesOf
//! 

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DSphere<TType>& sphere)
{
  if (IsRayIntersected(ray, sphere) == false) { return {}; }

  const auto alp = ray.GetOrigin() - sphere.GetOrigin();
  const auto dir = ray.GetDirection();

  const auto b = 2 * Dot(alp, dir);
  const auto c = Dot(alp, alp) - (sphere.GetRadius() * sphere.GetRadius());
  const auto sqrtE = std::sqrt((b * b) - c);

  auto result = SolveQuadric(TReal(1), TReal(b), TReal(c));

  result.erase(
    std::remove_if(result.begin(), result.end(), [](const auto& value) { return value < 0.0f; }),
    result.end());
  std::sort(result.begin(), result.end());

  return result;
}

/// @brief Get positive 't' list to the point of given DPlane from given ray.
template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DPlane<TType>& plane)
{
  if (IsRayIntersected(ray, plane) == false) { return {}; }
  
  // Get normal and do. vector `n1` and `n2` length are 1.
  const auto normal = plane.GetNormal().Normalize();
  const auto p1 = Dot(ray.GetDirection(), normal);
  const auto p2 = Dot(ray.GetDirection(), normal * TType(-1));
  
  // Get positive p value and return alpha (a) value.
  const auto cos = std::max(p1, p2);
  return {std::abs(GetSDFValueOf(ray.GetOrigin(), plane)) / cos}; 
}

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box)
{
  // Use 3-dimensional slab method [Kay and Kajyia].
  TType tMin = kMinValueOf<TType>;
  TType tMax = kMaxValueOf<TType>;

  const auto& ro = ray.GetOrigin();
  const auto& rd = ray.GetDirection();
  const auto min = box.GetMinPos();
  const auto max = box.GetMaxPos();

  if (rd.X != TType(0))
  {
    TType tx1 = (min.X - ro.X) / rd.X;
    TType tx2 = (max.X - ro.X) / rd.X;
    tMin = std::max(tMin, std::min(tx1, tx2));
    tMax = std::min(tMax, std::max(tx1, tx2));
  }

  if (rd.Y != TType(0))
  {
    TType ty1 = (min.Y - ro.Y) / rd.Y;
    TType ty2 = (max.Y - ro.Y) / rd.Y;
    tMin = std::max(tMin, std::min(ty1, ty2));
    tMax = std::min(tMax, std::max(ty1, ty2));
  }

  if (rd.Z != TType(0))
  {
    TType tz1 = (min.Z - ro.Z) / rd.Z;
    TType tz2 = (max.Z - ro.Z) / rd.Z;
    tMin = std::max(tMin, std::min(tz1, tz2));
    tMax = std::min(tMax, std::max(tz1, tz2));
  }

  std::vector<TReal> result;
  if (tMax >= tMin && tMax >= 0)
  {
    if (tMin >= 0)    { result.emplace_back(tMin); }
    if (tMax > tMin)  { result.emplace_back(tMax); }
  }

  return result;
}

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot)
{
  // We regards box is symmetrical and origin is located on origin of box space.
  // We need to convert ray of world-space into box-space.
  const auto invRotMat      = rot.Transpose();
  const auto localSpacePos  = invRotMat * (ray.GetOrigin() - box.GetOrigin());
  const auto localSpaceDir  = invRotMat * ray.GetDirection();
  
  return GetTValuesOf(DRay<TType>{localSpacePos, localSpaceDir}, DBox<TType>{DVector3<TType>{0}, box.GetLengthList()});
}

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot)
{
  return GetTValuesOf(ray, box, rot.ToMatrix3());
}

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DTorus<TType>& torus)
{
  // reference https://marcin-chwedczuk.github.io/ray-tracing-torus
  // reference https://en.wikipedia.org/wiki/Quartic_function#Ferrari's_solution

  const auto ro = ray.GetOrigin() - torus.GetOrigin();
  const auto o2_minus_torus2 = 
      std::pow(ro.GetLength(), 2) 
    - (std::pow(torus.GetDistance(), 2) + std::pow(torus.GetRadius(), 2));
  const auto od = Dot(ro, ray.GetDirection());
  const auto d2 = TType(1); // ray.GetDirection().GetLength() always 1. 1^2 = 1.

  // c4t4 + c3t3 + c2t2 + c1t1 + c0 = 0;
  const auto c4 = d2; // Always 1.
  const auto c3 = 4 * d2 * od;
  const auto c2 = 
      2 * d2 * o2_minus_torus2 
    + 4 * std::pow(od, 2)  
    + 4 * std::pow(torus.GetRadius(), 2) * std::pow(ray.GetDirection().Y, 2);
  const auto c1 = 
      4 * o2_minus_torus2 * od
    + 8 * std::pow(torus.GetRadius(), 2) * ro.Y * ray.GetDirection().Y;
  const auto c0 = 
      std::pow(o2_minus_torus2, 2)
    - 4 * std::pow(torus.GetRadius(), 2) * (std::pow(torus.GetRadius(), 2) - std::pow(ro.Y, 2));

  auto result = SolveQuartic(c4, c3, c2, c1, c0);
  result.erase(
    std::remove_if(result.begin(), result.end(), [](const auto& value) { return value < 0.0f; }),
    result.end());
  std::sort(result.begin(), result.end());

  return result;
}

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DMatrix3<TType>& rot)
{
  // We regards box is symmetrical and origin is located on origin of box space.
  // We need to convert ray of world-space into box-space.
  const auto invRotMat      = rot.Transpose();
  const auto localSpacePos  = invRotMat * (ray.GetOrigin() - torus.GetOrigin());
  const auto localSpaceDir  = invRotMat * ray.GetDirection();
  
  return GetTValuesOf(
    DRay<TType>{localSpacePos, localSpaceDir}, 
    DTorus<TType>{DVector3<TType>{0}, torus.GetDistance(), torus.GetRadius()}
  );
}

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DTorus<TType>& torus, const DQuaternion<TType>& rot)
{
  return GetTValuesOf(ray, torus, rot.ToMatrix3());
}

//!
//! GetClosestTValueOf
//!

/// @brief Get positive `t` to the closest point of given sphere from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DSphere<TType>& sphere)
{
  const auto tValueList = GetTValuesOf(ray, sphere);
  if (tValueList.empty() == true) { return std::nullopt; }

  return tValueList.front();
} 

template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box)
{
  const auto tValueList = GetTValuesOf(ray, box);
  if (tValueList.empty() == true) { return std::nullopt; }

  return tValueList.front();
}

template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot)
{
  const auto tValueList = GetTValuesOf(ray, box, rot);
  if (tValueList.empty() == true) { return std::nullopt; }

  return tValueList.front();
}

template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot)
{
  const auto tValueList = GetTValuesOf(ray, box, rot);
  if (tValueList.empty() == true) { return std::nullopt; }

  return tValueList.front();
}

template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DPlane<TType>& plane)
{
  const auto tValueList = GetTValuesOf(ray, plane);
  if (tValueList.empty() == true) { return std::nullopt; }

  return tValueList.front();
}

//!
//! GetNormalOf
//!

/// @brief Try to get normal vector of sphere, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DSphere<TType>& sphere)
{
  // Check
  if (IsRayIntersected(ray, sphere) == false) { return std::nullopt; }

  auto optT = GetClosestTValueOf(ray, sphere);
  if (optT.has_value() == false) { return std::nullopt; }

  DRay<TReal> resultRay = {ray.GetPointAtParam(*optT), ray.GetDirection(), false};

  const TType offset = TType(0.001);
  const auto origin = resultRay.GetOrigin();
  const auto x = GetSDFValueOf<TType>(origin + DVector3<TType>{offset, 0, 0}, sphere) - GetSDFValueOf(origin, sphere);
  const auto y = GetSDFValueOf<TType>(origin + DVector3<TType>{0, offset, 0}, sphere) - GetSDFValueOf(origin, sphere);
  const auto z = GetSDFValueOf<TType>(origin + DVector3<TType>{0, 0, offset}, sphere) - GetSDFValueOf(origin, sphere);

  DVector3<TType> result = DVector3<TType>{x, y, z};
  return result.Normalize();
}

template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box)
{
  // Check
  if (IsRayIntersected(ray, box) == false) { return std::nullopt; }

  auto optT = GetClosestTValueOf(ray, box);
  if (optT.has_value() == false) { return std::nullopt; }

  DRay<TReal> resultRay = {ray.GetPointAtParam(*optT), ray.GetDirection(), false};

  const TType offset = TType(0.001);
  const auto origin = resultRay.GetOrigin();
  const auto x = GetSDFValueOf<TType>(origin + DVector3<TType>{offset, 0, 0}, box) - GetSDFValueOf(origin, box);
  const auto y = GetSDFValueOf<TType>(origin + DVector3<TType>{0, offset, 0}, box) - GetSDFValueOf(origin, box);
  const auto z = GetSDFValueOf<TType>(origin + DVector3<TType>{0, 0, offset}, box) - GetSDFValueOf(origin, box);

  DVector3<TType> result = DVector3<TType>{x, y, z};
  return result.Normalize();
}

template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rot)
{
  // We regards box is symmetrical and origin is located on origin of box space.
  // We need to convert ray of world-space into box-space.
  const auto invRotMat      = rot.Transpose();
  const auto localSpacePos  = invRotMat * (ray.GetOrigin() - box.GetOrigin());
  const auto localSpaceDir  = invRotMat * ray.GetDirection();
  
  const auto normal = GetNormalOf(
    DRay<TType>{localSpacePos, localSpaceDir}, 
    DBox<TType>{DVector3<TType>{0}, box.GetLengthList()}
  );
  if (normal.has_value() == false) { return std::nullopt; }

  return rot * (*normal);
}

template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DBox<TType>& box, const DQuaternion<TType>& rot)
{
  return GetNormalOf(ray, box, rot.ToMatrix3());
}

/// @brief Try to get normal vector of plane, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DPlane<TType>& plane)
{
  // Check
  if (IsRayIntersected(ray, plane) == false) { return std::nullopt; }

  const auto sdfValue = GetSDFValueOf(ray.GetOrigin(), plane);
  return plane.GetNormal() * (sdfValue > TType(0) ? TType(1) : TType(-1));
}

} /// ::dy::math namespace