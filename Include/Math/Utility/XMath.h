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

#include <algorithm>
#include <utility>
#include <vector>
#include <Math/Common/TGlobalTypes.h>
#include <Math/Type/Math/DVector2.h>
#include <Math/Type/Math/DVector3.h>
#include <Math/Type/Math/DVector4.h>

namespace dy::math
{

/// @brief Pi(π)
template <typename TType>
constexpr TType kPi = TType(3.1415926535897932385L);

/// @brief 2*Pi (2π)
template <typename TType>
constexpr TType k2Pi = TType(3.1415926535897932385L) * TType(2);

/// @brief E (e)
template <typename TType>
constexpr TType kExp = TType(2.71828182845904523536L);

/// @brief Convert degree value to radian value.
template <typename TType>
constexpr TType kToRadian = kPi<TType> / TType(180);

/// @brief Convert radian value to degree value.
template <typename TType>
constexpr TType kToDegree = TType(180) / kPi<TType>;

/// @brief Map given value to [start, end).
template <typename TType>
constexpr TType MapValue(TType value, TType start, TType end) noexcept;

/// @brief Check float lhs is nearly equal to rhs.
/// floating-point number type like a float and double has a natural problem like
/// a floating-error such as 0.1 but 0.10000007, so you have to use this function
/// if you want to compare two floating points.
constexpr bool IsNearlyEqual(TF32 lhs, TF32 rhs, TF32 tolerance = 0.001f) noexcept;

/// @brief Check double lhs is nearly equal to rhs.
/// floating-point number type like a float and double has a natural problem like
/// a floating-error such as 0.1 but 0.10000007, so you have to use this function
/// if you want to compare two double points.
constexpr bool IsNearlyEqual(TF64 lhs, TF64 rhs, TF64 tolerance = 0.001) noexcept;

/// @brief Check given two vector values are equal within given tolerance value. 
/// 
/// floating-point number type like a float and double has a natural problem like 
/// a floating-error such as 0.1 but 0.10000007, so you have to use this function 
/// if you want to compare two double points.
template <typename TLeft, typename TRight>
bool IsNearlyEqual(const DVector2<TLeft>& lhs, const DVector2<TRight>& rhs, TReal tolerance = 0.001f);

/// @brief Check given two vector values are equal within given tolerance value. 
/// 
/// floating-point number type like a float and double has a natural problem like 
/// a floating-error such as 0.1 but 0.10000007, so you have to use this function 
/// if you want to compare two double points.
template <typename TLeft, typename TRight>
bool IsNearlyEqual(const DVector3<TLeft>& lhs, const DVector3<TRight>& rhs, TReal tolerance = 0.001f);

/// @brief Check given two vector values are equal within given tolerance value. 
/// 
/// floating-point number type like a float and double has a natural problem like 
/// a floating-error such as 0.1 but 0.10000007, so you have to use this function 
/// if you want to compare two double points.
template <typename TLeft, typename TRight>
bool IsNearlyEqual(const DVector4<TLeft>& lhs, const DVector4<TRight>& rhs, TReal tolerance = 0.001f);

/// @brief Check float '0' is nearly equal to real actual 0.
constexpr bool IsNearlyZero(TF32 lhs, TF32 errorTolerance = 0.001f) noexcept;

/// @brief Check float '0' is nearly equal to real actual 0.
constexpr bool IsNearlyZero(TF64 lhs, TF64 errorTolerance = 0.001) noexcept;

/// @brief Normalize radian value to [-pi, pi).
template <typename TType, typename = std::enable_if_t<kIsRealType<TType>>>
constexpr TType ToNormalizedRadian(TType radian);

/// @brief Normalize degree value to [-180, 180).
template <typename TType, typename = std::enable_if_t<kIsRealType<TType>>>
constexpr TType ToNormalizedDegree(TType degree);

/// @brief Do linear interpolation with float type.
/// If something wrong has been happened, return lowest value of float.
TF32 Lerp(TF32 lhs, TF32 rhs, TReal offset);

/// @brief Do linear interpolation with double type.
/// If something wrong has been happened, return lowest value of double.
TF64 Lerp(TF64 lhs, TF64 rhs, TReal offset);

/// @brief Extract only fractional part.
template <typename TType>
TType Frac(TType realValue) noexcept
{
  return realValue - static_cast<TI32>(realValue);
}

/// @brief Clamp vector's all elements to [0, 1].
/// @param vector Vector value.
/// @return Saturated vector instance.
template <typename TType>
DVector2<TType> Saturate(const DVector2<TType>& vector)
{
  return
  {
    std::clamp(vector.X, static_cast<TType>(0), static_cast<TType>(1)),
    std::clamp(vector.Y, static_cast<TType>(0), static_cast<TType>(1)),
  };
}

/// @brief Clamp vector's all elements to [0, 1].
/// @param vector Vector value.
/// @return Saturated vector instance.
template <typename TType>
DVector3<TType> Saturate(const DVector3<TType>& vector)
{
  return
  {
    std::clamp(vector.X, static_cast<TType>(0), static_cast<TType>(1)),
    std::clamp(vector.Y, static_cast<TType>(0), static_cast<TType>(1)),
    std::clamp(vector.Z, static_cast<TType>(0), static_cast<TType>(1)),
  };
}

/// @brief Clamp vector's all elements to [0, 1].
/// @param vector Vector value.
/// @return Saturated vector instance.
template <typename TType>
DVector4<TType> Saturate(const DVector4<TType>& vector)
{
  return
  {
    std::clamp(vector.X, static_cast<TType>(0), static_cast<TType>(1)),
    std::clamp(vector.Y, static_cast<TType>(0), static_cast<TType>(1)),
    std::clamp(vector.Z, static_cast<TType>(0), static_cast<TType>(1)),
    std::clamp(vector.W, static_cast<TType>(0), static_cast<TType>(1)),
  };
}

/// @brief Get minimum value vector (x, y)
template <typename TLeft, typename TRight>
DVector2<GetBiggerType<TLeft, TRight>>
ExtractMin(const DVector2<TLeft>& lhs, const DVector2<TRight>& rhs) noexcept;

/// @brief Get minimum value vector (x, y, z)
template <typename TLeft, typename TRight>
DVector3<GetBiggerType<TLeft, TRight>>
ExtractMin(const DVector3<TLeft>& lhs, const DVector3<TRight>& rhs) noexcept;

/// @brief Get minimum value vector (x, y, z, w)
template <typename TLeft, typename TRight>
DVector4<GetBiggerType<TLeft, TRight>>
ExtractMin(const DVector4<TLeft>& lhs, const DVector4<TRight>& rhs) noexcept;

/// @brief Get maximum value vector (x, y)
template <typename TLeft, typename TRight>
DVector2<GetBiggerType<TLeft, TRight>>
ExtractMax(const DVector2<TLeft>& lhs, const DVector2<TRight>& rhs) noexcept;

/// @brief Get maximum value vector (x, y, z)
template <typename TLeft, typename TRight>
DVector3<GetBiggerType<TLeft, TRight>>
ExtractMax(const DVector3<TLeft>& lhs, const DVector3<TRight>& rhs) noexcept;

/// @brief Get maximum value vector (x, y, z, w)
template <typename TLeft, typename TRight>
DVector4<GetBiggerType<TLeft, TRight>>
ExtractMax(const DVector4<TLeft>& lhs, const DVector4<TRight>& rhs) noexcept;

/// @brief Absolutize vector values.
/// @param vector input vector.
/// @tparam TType The type of vector.
/// @return Absolutized vector value.
template <typename TType>
DVector2<TType> Abs(const DVector2<TType>& vector) noexcept;

/// @brief Absolutize vector values.
/// @param vector input vector.
/// @tparam TType The type of vector.
/// @return Absolutized vector value.
template <typename TType>
DVector3<TType> Abs(const DVector3<TType>& vector) noexcept;

/// @brief Absolutize vector values.
/// @param vector input vector.
/// @tparam TType The type of vector.
/// @return Absolutized vector value.
template <typename TType>
DVector4<TType> Abs(const DVector4<TType>& vector) noexcept;

/// @brief Solve quadric (highest order term is 2) equation and get only real values.
/// c2x2 + c1x + c0 = 0.
/// @param c2 coefficient of second-order term.
/// @param c1 coefficient of first-order term.
/// @param c0 constant value.
/// @return Sorted root values.
std::vector<TReal> SolveQuadric(TReal c2, TReal c1, TReal c0);

/// @brief Solve cubic (highest order term is 3) equation and get only real values.
/// c3x3 + c2x2 + c1x + c0 = 0.
/// @param c3 coefficient of third-order term.
/// @param c2 coefficient of second-order term.
/// @param c1 coefficient of first-order term.
/// @param c0 constant value.
/// @return Sorted root values.
std::vector<TReal> SolveCubic(TReal c3, TReal c2, TReal c1, TReal c0);

/// @brief Solve quartic (highest order term is 4) equation and get only real values.
/// c4x4 + c3x3 + c2x2 + c1x + c0 = 0.
/// @param c4 coefficient of fourth-order term.
/// @param c3 coefficient of third-order term.
/// @param c2 coefficient of second-order term.
/// @param c1 coefficient of first-order term.
/// @param c0 constant value.
/// @return Sorted root values.
std::vector<TReal> SolveQuartic(TReal c4, TReal c3, TReal c2, TReal c1, TReal c0);

} /// ::dy::math namespace
#include <Math/Utility/Inline/XMath/MapValue.inl>
#include <Math/Utility/Inline/XMath/IsNearlyEqual.inl>
#include <Math/Utility/Inline/XMath/Lerp.inl>
#include <Math/Utility/Inline/XMath/ToNormalized.inl>
#include <Math/Utility/Inline/XMath/MinMax.inl>
#include <Math/Utility/Inline/XMath/Abs.inl>