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

#include <vector>
#include <Math/Common/Inline/TGlobalTypes.inl>
#include <Math/Type/Math/DVector3.h>

namespace dy::math
{

/// @enum EBounds3D
/// @brief Special value type of points of DBounds3D 
enum class EBounds3D
{
  LDB = 0, // Left Down Backward
  LDF, // Left Down Forward
  LUB, // Left Up Backward
  LUF, // Left Up Forward
  RDB, // Right Down Backward
  RDF, // Right Down Forward
  RUB, // Right Up Backward
  RUF, // Right Up Forward
};

/// @struct DBounds3D
/// @brief 3-element area struct type that has min, max point (DVector3) as axis aligned bounding box.
template <typename TType> 
struct MATH_NODISCARD DBounds3D
{
public:
  static_assert(
    kCategoryOf<TType> == EValueCategory::Real, 
    "Failed to make DBounds3D, DBounds3D only supports Real type.");
  using TValueType = TType;
  using TItem = DVector3<TValueType>;

  DBounds3D() = default;
  DBounds3D(const DVector3<TValueType>& point);
  DBounds3D(const DVector3<TValueType>& point1, const DVector3<TValueType>& point2);
  DBounds3D(const std::vector<DVector3<TValueType>>& list);

  template <typename TAnotherType>
  explicit operator DBounds3D<TAnotherType>() const noexcept;

  /// @brief [[deprecated]] Get area of bounding box. 
  TReal GetArea() const noexcept;
  /// @brief Get surface area of bounding box.
  TReal GetSurfaceArea() const noexcept;
  /// @brief Get volume of DBounds.
  TReal GetVolume() const noexcept;
  
  /// @brief Get length vector from min to max.
  DVector3<TValueType> GetLength() const noexcept; 
  /// @brief Get diagonal vector from min to max.
  DVector3<TValueType> GetDiagonal() const noexcept;

  /// @brief [[deprecated]] Get minimum point of bounding box.
  const DVector3<TValueType>& GetMinimumPoint() const noexcept;
  /// @brief [[deprecated]] Get maximum point of bounding box.
  const DVector3<TValueType>& GetMaximumPoint() const noexcept;
  /// @brief Get minimum point of bounding box.
  const DVector3<TValueType>& GetMin() const noexcept;
  /// @brief Get maximum point of bounding box.
  const DVector3<TValueType>& GetMax() const noexcept;
  /// @brief Get given EBounds3D's point from instance.
  DVector3<TValueType> GetPointOf(EBounds3D type) const noexcept;
  
  /// @brief Check value has NaN.
  bool HasNaN() const noexcept;
  /// @brief Check value has Infinity.
  bool HasInfinity() const noexcept;
  /// @brief Check values are normal value, neither NaN nor Inf.
  bool HasOnlyNormal() const noexcept;

protected:
  DVector3<TValueType> mMin = kMinValueOf<TValueType>;
  DVector3<TValueType> mMax = kMaxValueOf<TValueType>;
};

} /// ::dy::math namespace
#include <Math/Type/Inline/DBounds3D/DBounds3D.inl>
