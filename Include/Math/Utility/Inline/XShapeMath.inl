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

/// @brief Get signed distance value of sphere model from point.
template <typename TType>
TReal GetSDFValueOf(const DVector3<TType>& point, const DSphere<TType>& sphere)
{
  return (point - sphere.GetOrigin()).GetLength() - sphere.GetRadius();
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

} /// ::dy::math namespace