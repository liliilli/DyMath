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

} /// ::dy::math namespace