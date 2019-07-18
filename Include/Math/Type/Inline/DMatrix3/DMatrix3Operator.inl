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

// Column

namespace dy::math
{

/// [a b c] * [v0] = new vector3.
/// [d e f]   [v1]
/// [g h i]   [v2]
/// https://en.wikibooks.org/wiki/GLSL_Programming/Vector_and_Matrix_Operations
template <typename TLeft, typename TRight>
DVector3<GetBiggerType<TLeft, TRight>> 
operator*(const DMatrix3<TLeft, EMatMajor::Column>& lhs, const DVector3<TRight>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0] + lhs[1][0] * rhs[1] + lhs[2][0] * rhs[2],
    lhs[0][1] * rhs[0] + lhs[1][1] * rhs[1] + lhs[2][1] * rhs[2],
    lhs[0][2] * rhs[0] + lhs[1][2] * rhs[1] + lhs[2][2] * rhs[2]
  };
}

template <typename TLeft, typename TRight>
DVector3<GetBiggerType<TLeft, TRight>> 
operator*(const DVector3<TLeft>& lhs, const DMatrix3<TRight, EMatMajor::Column>& rhs) noexcept 
{
  return 
  {
    lhs[0] * rhs[0][0] + lhs[1] * rhs[0][1] + lhs[2] * rhs[0][2],
    lhs[0] * rhs[1][0] + lhs[1] * rhs[1][1] + lhs[2] * rhs[1][2],
    lhs[0] * rhs[2][0] + lhs[1] * rhs[2][1] + lhs[2] * rhs[2][2]
  };
}

template <typename TLeft, typename TRight>
DMatrix3<GetBiggerType<TLeft, TRight>, EMatMajor::Column> 
operator*(const DMatrix3<TLeft, EMatMajor::Column>& lhs, const DMatrix3<TRight, EMatMajor::Column>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1] + lhs[2][0] * rhs[0][2],
    lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1] + lhs[2][0] * rhs[1][2],
    lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1] + lhs[2][0] * rhs[2][2],

    lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] + lhs[2][1] * rhs[0][2],
    lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] + lhs[2][1] * rhs[1][2],
    lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1] + lhs[2][1] * rhs[2][2],

    lhs[0][2] * rhs[0][0] + lhs[1][2] * rhs[0][1] + lhs[2][2] * rhs[0][2],
    lhs[0][2] * rhs[1][0] + lhs[1][2] * rhs[1][1] + lhs[2][2] * rhs[1][2],
    lhs[0][2] * rhs[2][0] + lhs[1][2] * rhs[2][1] + lhs[2][2] * rhs[2][2]
  };
}

template <typename TLeft>
DMatrix3<TLeft, EMatMajor::Column>& 
operator*=(DMatrix3<TLeft, EMatMajor::Column>& lhs, const DMatrix3<TLeft, EMatMajor::Column>& rhs) noexcept 
{
  const DVector3<TLeft> _0 = 
  {
    lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1] + lhs[2][0] * rhs[0][2],
    lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] + lhs[2][1] * rhs[0][2],
    lhs[0][2] * rhs[0][0] + lhs[1][2] * rhs[0][1] + lhs[2][2] * rhs[0][2],
  };

  const DVector3<TLeft> _1 =
  {
    lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1] + lhs[2][0] * rhs[1][2],
    lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] + lhs[2][1] * rhs[1][2],
    lhs[0][2] * rhs[1][0] + lhs[1][2] * rhs[1][1] + lhs[2][2] * rhs[1][2],
  };

  const DVector3<TLeft> _2 =
  {
    lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1] + lhs[2][0] * rhs[2][2],
    lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1] + lhs[2][1] * rhs[2][2],
    lhs[0][2] * rhs[2][0] + lhs[1][2] * rhs[2][1] + lhs[2][2] * rhs[2][2]
  };

  lhs[0] = _0; lhs[1] = _1; lhs[2] = _2;
  return lhs;
}

} /// ::dy::math namespace

// Row

namespace dy::math
{

/// [a b c] * [v0] = new vector3.
/// [d e f]   [v1]
/// [g h i]   [v2]
template <typename TLeft, typename TRight>
DVector3<GetBiggerType<TLeft, TRight>> 
operator*(const DMatrix3<TLeft, EMatMajor::Row>& lhs, const DVector3<TRight>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0] + lhs[0][1] * rhs[1] + lhs[0][2] * rhs[2],
    lhs[1][0] * rhs[0] + lhs[1][1] * rhs[1] + lhs[1][2] * rhs[2],
    lhs[2][0] * rhs[0] + lhs[2][1] * rhs[1] + lhs[2][2] * rhs[2]
  };
}

template <typename TLeft, typename TRight>
DVector3<GetBiggerType<TLeft, TRight>> 
operator*(const DVector3<TLeft>& lhs, const DMatrix3<TRight, EMatMajor::Row>& rhs) noexcept 
{
  return 
  {
    lhs[0] * rhs[0][0] + lhs[1] * rhs[1][0] + lhs[2] * rhs[2][0],
    lhs[0] * rhs[0][1] + lhs[1] * rhs[1][1] + lhs[2] * rhs[2][1],
    lhs[0] * rhs[0][2] + lhs[1] * rhs[1][2] + lhs[2] * rhs[2][2]
  };
}

template <typename TLeft, typename TRight>
DMatrix3<GetBiggerType<TLeft, TRight>, EMatMajor::Row> 
operator*(const DMatrix3<TLeft, EMatMajor::Row>& lhs, const DMatrix3<TRight, EMatMajor::Row>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0],
    lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1],
    lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2],

    lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0],
    lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1],
    lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2],

    lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0],
    lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1],
    lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2]
  };
}

template <typename TLeft>
DMatrix3<TLeft, EMatMajor::Row>& 
operator*=(DMatrix3<TLeft, EMatMajor::Row>& lhs, const DMatrix3<TLeft, EMatMajor::Row>& rhs) noexcept 
{
  const DVector3<TLeft> _0 = 
  {
    lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0],
    lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1],
    lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2]
  };

  const DVector3<TLeft> _1 =
  {
    lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0],
    lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1],
    lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2],
  };

  const DVector3<TLeft> _2 =
  {
    lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0],
    lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1],
    lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2]
  };

  lhs[0] = _0; lhs[1] = _1; lhs[2] = _2;
  return lhs;
}

} /// ::dy::math namespace

// Common

namespace dy::math
{

template <typename TLeft, EMatMajor TMajor>
DMatrix3<TLeft, TMajor>& operator*=(const DMatrix3<TLeft, TMajor>& lhs, TLeft rhs) noexcept 
{
  lhs[0] *= rhs; lhs[1] *= rhs; lhs[2] *= rhs;
  return lhs;
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TRight>>>
DMatrix3<GetBiggerType<TLeft, TRight>, TMajor> 
operator*(const DMatrix3<TLeft, TMajor>& lhs, TRight rhs) noexcept 
{
  return { lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs };
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TLeft>>>
DMatrix3<GetBiggerType<TLeft, TRight>, TMajor> 
operator*(TLeft lhs, const DMatrix3<TRight, TMajor>& rhs) noexcept 
{
  return { lhs * rhs[0], lhs * rhs[1], lhs * rhs[2] };
}

/// @brief Elementary addition.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix3<GetBiggerType<TLeft, TRight>, TMajor> 
operator+(const DMatrix3<TLeft, TMajor>& lhs, const DMatrix3<TRight, TMajor>& rhs) noexcept 
{
  return { lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2] };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix3<TLeft, TMajor>& operator+=(DMatrix3<TLeft, TMajor>& lhs, const DMatrix3<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] += rhs[0]; lhs[1] += rhs[1]; lhs[2] += rhs[2];
  return lhs;
}

/// @brief Elementary subtraction.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix3<GetBiggerType<TLeft, TRight>, TMajor> 
operator-(const DMatrix3<TLeft, TMajor>& lhs, const DMatrix3<TRight, TMajor>& rhs) noexcept 
{
  return { lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2] };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix3<TLeft, TMajor>& operator-=(DMatrix3<TLeft, TMajor>& lhs, const DMatrix3<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] -= rhs[0]; lhs[1] -= rhs[1]; lhs[2] -= rhs[2];
  return lhs;
}

/// @brief Elementary multiplication.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix3<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(const DMatrix3<TLeft, TMajor>& lhs, const DMatrix3<TRight, TMajor>& rhs) noexcept 
{
  return { lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2] };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix3<TLeft, TMajor>& operator/=(DMatrix3<TLeft, TMajor>& lhs, const DMatrix3<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] /= rhs[0]; lhs[1] /= rhs[1]; lhs[2] /= rhs[2];
  return lhs;
}

template <typename TLeft, EMatMajor TMajor>
DMatrix3<TLeft, TMajor>& operator/=(DMatrix3<TLeft, TMajor>& lhs, TLeft rhs) noexcept 
{
  lhs[0] /= rhs; lhs[1] /= rhs; lhs[2] /= rhs;
  return lhs;
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TRight>>>
DMatrix3<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(const DMatrix3<TLeft, TMajor>& lhs, TRight rhs) noexcept 
{
  return { lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs };
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TLeft>>>
DMatrix3<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(TLeft lhs, const DMatrix3<TRight, TMajor>& rhs) noexcept 
{
  return { lhs / rhs[0], lhs / rhs[1], lhs / rhs[2] };
}

template <typename TType, EMatMajor TMajor>
bool operator==(const DMatrix3<TType, TMajor>& lhs, const DMatrix3<TType, TMajor>& rhs) noexcept 
{
  return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
}

template <typename TType, EMatMajor TMajor>
bool operator!=(const DMatrix3<TType, TMajor>& lhs, const DMatrix3<TType, TMajor>& rhs) noexcept 
{
  return !(lhs == rhs);
}

} /// ::dy::math namespace
