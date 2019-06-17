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

} /// ::dy::math namespace