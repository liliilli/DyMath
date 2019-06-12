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

  const auto b = Dot(alp, dir);
  const auto c = Dot(alp, alp) - (sphere.GetRadius() * sphere.GetRadius());
  const auto sqrtE = std::sqrt((b * b) - c);

  const auto result1 = -b + sqrtE;
  const auto result2 = -b - sqrtE;
  return result1 >= 0 || result2 >= 0;
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box)
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

  return tMax >= tMin && tMax >= 0;
}

template <typename TType>
bool IsRayIntersected(const DRay<TType>& ray, const DBox<TType>& box, const DMatrix3<TType>& rotMatrix)
{
  // We regards box is symmetrical and origin is located on origin of box space.
  // We need to convert ray of world-space into box-space.
  const auto invRotMat = rotMatrix.Transpose();
  const auto localSpaceRayDir = invRotMat * ray.GetDirection();

  return IsRayIntersected(DRay<TType>{ray.GetOrigin(), localSpaceRayDir}, box);
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

/// @brief Get signed distance value of sphere model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DSphere<TType>& sphere)
{
  return (point - sphere.GetOrigin()).GetLength() - sphere.GetRadius();
}

template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DPlane<TType>& plane)
{
  return (Dot(point, plane.GetNormal()) + plane.GetD()) / plane.GetNormal().GetLength();
}

template <typename TType>
std::vector<TReal> GetTValuesOf(const DRay<TType>& ray, const DSphere<TType>& sphere)
{
  if (IsRayIntersected(ray, sphere) == false) { return {}; }

  const auto alp = ray.GetOrigin() - sphere.GetOrigin();
  const auto dir = ray.GetDirection();

  const auto b = Dot(alp, dir);
  const auto c = Dot(alp, alp) - (sphere.GetRadius() * sphere.GetRadius());
  const auto sqrtE = std::sqrt((b * b) - c);

  const auto result1 = -b + sqrtE;
  const auto result2 = -b - sqrtE;

  // Insert values into result list.
  std::vector<TReal> result = {result1, result2};
  result.erase(
    std::remove_if(result.begin(), result.end(), [](const auto& value) { return value < 0.0f; }),
    result.end());
  std::sort(result.begin(), result.end(), [](const auto& lhs, const auto& rhs) { return lhs < rhs; });

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

/// @brief Get positive `t` to the closest point of given sphere from given ray.
/// If not found, just return nullopt value.
template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DSphere<TType>& sphere)
{
  const auto tValueList = GetTValuesOf(ray, sphere);
  if (tValueList.empty() == true) 
  { 
    return std::nullopt; 
  }

  return tValueList.front();
} 

template <typename TType>
std::optional<TReal> GetClosestTValueOf(const DRay<TType>& ray, const DPlane<TType>& plane)
{
  const auto tValueList = GetTValuesOf(ray, plane);
  if (tValueList.empty() == true) { return std::nullopt; }

  return tValueList.front();
}

/// @brief Try to get normal vector of sphere, when ray is intersected.
template <typename TType>
std::optional<DVector3<TType>> GetNormalOf(const DRay<TType>& ray, const DSphere<TType>& sphere)
{
  // Check
  if (IsRayIntersected(ray, sphere) == false) { return std::nullopt; }

  auto optT = GetClosestTValueOf(ray, sphere);
  if (optT.has_value() == false) 
  { 
    return std::nullopt; 
  }

  DRay<TReal> resultRay = {ray.GetPointAtParam(*optT), ray.GetDirection(), false};

  const TType offset = TType(0.001);
  const auto origin = resultRay.GetOrigin();
  const auto x = GetSDFValueOf<TType>(origin + DVector3<TType>{offset, 0, 0}, sphere) - GetSDFValueOf(origin, sphere);
  const auto y = GetSDFValueOf<TType>(origin + DVector3<TType>{0, offset, 0}, sphere) - GetSDFValueOf(origin, sphere);
  const auto z = GetSDFValueOf<TType>(origin + DVector3<TType>{0, 0, offset}, sphere) - GetSDFValueOf(origin, sphere);

  DVector3<TType> result = DVector3<TType>{x, y, z};
  return result.Normalize();
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