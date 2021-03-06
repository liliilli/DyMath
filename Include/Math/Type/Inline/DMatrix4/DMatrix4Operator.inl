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

// Column Major

namespace dy::math
{

/// [a b c d] * [v0] = new vector4.
/// [e f g h]   [v1]
/// [i j k l]   [v2]
/// [m n o p]   [v3]
/// https://en.wikibooks.org/wiki/GLSL_Programming/Vector_and_Matrix_Operations
template <typename TLeft, typename TRight>
DVector4<GetBiggerType<TLeft, TRight>> 
operator*(const DMatrix4<TLeft, EMatMajor::Column>& lhs, const DVector4<TRight>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0] + lhs[1][0] * rhs[1] + lhs[2][0] * rhs[2] + lhs[3][0] * rhs[3],
    lhs[0][1] * rhs[0] + lhs[1][1] * rhs[1] + lhs[2][1] * rhs[2] + lhs[3][1] * rhs[3],
    lhs[0][2] * rhs[0] + lhs[1][2] * rhs[1] + lhs[2][2] * rhs[2] + lhs[3][2] * rhs[3],
    lhs[0][3] * rhs[0] + lhs[1][3] * rhs[1] + lhs[2][3] * rhs[2] + lhs[3][3] * rhs[3],
  };
}

template <typename TLeft, typename TRight>
DVector4<GetBiggerType<TLeft, TRight>> 
operator*(const DVector4<TLeft>& lhs, const DMatrix4<TRight, EMatMajor::Column>& rhs) noexcept 
{
  return 
  {
    lhs[0] * rhs[0][0] + lhs[1] * rhs[0][1] + lhs[2] * rhs[0][2] + lhs[3] * rhs[0][3],
    lhs[0] * rhs[1][0] + lhs[1] * rhs[1][1] + lhs[2] * rhs[1][2] + lhs[3] * rhs[1][3],
    lhs[0] * rhs[2][0] + lhs[1] * rhs[2][1] + lhs[2] * rhs[2][2] + lhs[3] * rhs[2][3],
    lhs[0] * rhs[3][0] + lhs[1] * rhs[3][1] + lhs[2] * rhs[3][2] + lhs[3] * rhs[3][3],
  };
}

template <typename TLeft, typename TRight>
DMatrix4<GetBiggerType<TLeft, TRight>, EMatMajor::Column> 
operator*(const DMatrix4<TLeft, EMatMajor::Column>& lhs, const DMatrix4<TRight, EMatMajor::Column>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1] + lhs[2][0] * rhs[0][2] + lhs[3][0] * rhs[0][3],
    lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1] + lhs[2][0] * rhs[1][2] + lhs[3][0] * rhs[1][3],
    lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1] + lhs[2][0] * rhs[2][2] + lhs[3][0] * rhs[2][3],
    lhs[0][0] * rhs[3][0] + lhs[1][0] * rhs[3][1] + lhs[2][0] * rhs[3][2] + lhs[3][0] * rhs[3][3],

    lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] + lhs[2][1] * rhs[0][2] + lhs[3][1] * rhs[0][3],
    lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] + lhs[2][1] * rhs[1][2] + lhs[3][1] * rhs[1][3],
    lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1] + lhs[2][1] * rhs[2][2] + lhs[3][1] * rhs[2][3],
    lhs[0][1] * rhs[3][0] + lhs[1][1] * rhs[3][1] + lhs[2][1] * rhs[3][2] + lhs[3][1] * rhs[3][3],

    lhs[0][2] * rhs[0][0] + lhs[1][2] * rhs[0][1] + lhs[2][2] * rhs[0][2] + lhs[3][2] * rhs[0][3],
    lhs[0][2] * rhs[1][0] + lhs[1][2] * rhs[1][1] + lhs[2][2] * rhs[1][2] + lhs[3][2] * rhs[1][3],
    lhs[0][2] * rhs[2][0] + lhs[1][2] * rhs[2][1] + lhs[2][2] * rhs[2][2] + lhs[3][2] * rhs[2][3],
    lhs[0][2] * rhs[3][0] + lhs[1][2] * rhs[3][1] + lhs[2][2] * rhs[3][2] + lhs[3][2] * rhs[3][3],
    
    lhs[0][3] * rhs[0][0] + lhs[1][3] * rhs[0][1] + lhs[2][3] * rhs[0][2] + lhs[3][3] * rhs[0][3],
    lhs[0][3] * rhs[1][0] + lhs[1][3] * rhs[1][1] + lhs[2][3] * rhs[1][2] + lhs[3][3] * rhs[1][3],
    lhs[0][3] * rhs[2][0] + lhs[1][3] * rhs[2][1] + lhs[2][3] * rhs[2][2] + lhs[3][3] * rhs[2][3],
    lhs[0][3] * rhs[3][0] + lhs[1][3] * rhs[3][1] + lhs[2][3] * rhs[3][2] + lhs[3][3] * rhs[3][3]
  };
}

template <typename TLeft>
DMatrix4<TLeft, EMatMajor::Column>& 
operator*=(DMatrix4<TLeft, EMatMajor::Column>& lhs, const DMatrix4<TLeft, EMatMajor::Column>& rhs) noexcept 
{
  const DVector4<TLeft> _0 = 
  {
    lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1] + lhs[2][0] * rhs[0][2] + lhs[3][0] * rhs[0][3],
    lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] + lhs[2][1] * rhs[0][2] + lhs[3][1] * rhs[0][3],
    lhs[0][2] * rhs[0][0] + lhs[1][2] * rhs[0][1] + lhs[2][2] * rhs[0][2] + lhs[3][2] * rhs[0][3],
    lhs[0][3] * rhs[0][0] + lhs[1][3] * rhs[0][1] + lhs[2][3] * rhs[0][2] + lhs[3][3] * rhs[0][3],
  };

  const DVector4<TLeft> _1 =
  {
    lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1] + lhs[2][0] * rhs[1][2] + lhs[3][0] * rhs[1][3],
    lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] + lhs[2][1] * rhs[1][2] + lhs[3][1] * rhs[1][3],
    lhs[0][2] * rhs[1][0] + lhs[1][2] * rhs[1][1] + lhs[2][2] * rhs[1][2] + lhs[3][2] * rhs[1][3],
    lhs[0][3] * rhs[1][0] + lhs[1][3] * rhs[1][1] + lhs[2][3] * rhs[1][2] + lhs[3][3] * rhs[1][3],
  };

  const DVector4<TLeft> _2 =
  {
    lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1] + lhs[2][0] * rhs[2][2] + lhs[3][0] * rhs[2][3],
    lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1] + lhs[2][1] * rhs[2][2] + lhs[3][1] * rhs[2][3],
    lhs[0][2] * rhs[2][0] + lhs[1][2] * rhs[2][1] + lhs[2][2] * rhs[2][2] + lhs[3][2] * rhs[2][3],
    lhs[0][3] * rhs[2][0] + lhs[1][3] * rhs[2][1] + lhs[2][3] * rhs[2][2] + lhs[3][3] * rhs[2][3],
  };

  const DVector4<TLeft> _3 =
  {
    lhs[0][0] * rhs[3][0] + lhs[1][0] * rhs[3][1] + lhs[2][0] * rhs[3][2] + lhs[3][0] * rhs[3][3],
    lhs[0][1] * rhs[3][0] + lhs[1][1] * rhs[3][1] + lhs[2][1] * rhs[3][2] + lhs[3][1] * rhs[3][3],
    lhs[0][2] * rhs[3][0] + lhs[1][2] * rhs[3][1] + lhs[2][2] * rhs[3][2] + lhs[3][2] * rhs[3][3],
    lhs[0][3] * rhs[3][0] + lhs[1][3] * rhs[3][1] + lhs[2][3] * rhs[3][2] + lhs[3][3] * rhs[3][3],
  };

  lhs[0] = _0; lhs[1] = _1; lhs[2] = _2; lhs[3] = _3;
  return lhs;
}

} /// ::dy::math namespace

// Row Major

namespace dy::math
{

/// [a b c d] * [v0] = new vector4.
/// [e f g h]   [v1]
/// [i j k l]   [v2]
/// [m n o p]   [v3]
/// https://en.wikibooks.org/wiki/GLSL_Programming/Vector_and_Matrix_Operations
template <typename TLeft, typename TRight>
DVector4<GetBiggerType<TLeft, TRight>> 
operator*(const DMatrix4<TLeft, EMatMajor::Row>& lhs, const DVector4<TRight>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0] + lhs[0][1] * rhs[1] + lhs[0][2] * rhs[2] + lhs[0][3] * rhs[3],
    lhs[1][0] * rhs[0] + lhs[1][1] * rhs[1] + lhs[1][2] * rhs[2] + lhs[1][3] * rhs[3],
    lhs[2][0] * rhs[0] + lhs[2][1] * rhs[1] + lhs[2][2] * rhs[2] + lhs[2][3] * rhs[3],
    lhs[3][0] * rhs[0] + lhs[3][1] * rhs[1] + lhs[3][2] * rhs[2] + lhs[3][3] * rhs[3],
  };
}

template <typename TLeft, typename TRight>
DVector4<GetBiggerType<TLeft, TRight>> 
operator*(const DVector4<TLeft>& lhs, const DMatrix4<TRight, EMatMajor::Row>& rhs) noexcept 
{
  return 
  {
    lhs[0] * rhs[0][0] + lhs[1] * rhs[1][0] + lhs[2] * rhs[2][0] + lhs[3] * rhs[3][0],
    lhs[0] * rhs[0][1] + lhs[1] * rhs[1][1] + lhs[2] * rhs[2][1] + lhs[3] * rhs[3][1],
    lhs[0] * rhs[0][2] + lhs[1] * rhs[1][2] + lhs[2] * rhs[2][2] + lhs[3] * rhs[3][2],
    lhs[0] * rhs[0][3] + lhs[1] * rhs[1][3] + lhs[2] * rhs[2][3] + lhs[3] * rhs[3][3],
  };
}

template <typename TLeft, typename TRight>
DMatrix4<GetBiggerType<TLeft, TRight>, EMatMajor::Row> 
operator*(const DMatrix4<TLeft, EMatMajor::Row>& lhs, const DMatrix4<TRight, EMatMajor::Row>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0],
    lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1],
    lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2],
    lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3],

    lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0],
    lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1],
    lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2],
    lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3] + lhs[1][3] * rhs[3][3],

    lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0],
    lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1],
    lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][3] * rhs[3][2],
    lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3] + lhs[2][3] * rhs[3][3],

    lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0] + lhs[3][3] * rhs[3][0],
    lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1] + lhs[3][3] * rhs[3][1],
    lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2] + lhs[3][3] * rhs[3][2],
    lhs[3][0] * rhs[0][3] + lhs[3][1] * rhs[1][3] + lhs[3][2] * rhs[2][3] + lhs[3][3] * rhs[3][3],
  };
}

template <typename TLeft>
DMatrix4<TLeft, EMatMajor::Row>& 
operator*=(DMatrix4<TLeft, EMatMajor::Row>& lhs, const DMatrix4<TLeft, EMatMajor::Row>& rhs) noexcept 
{
  const DVector4<TLeft> _0 = 
  {
    lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0],
    lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1],
    lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2],
    lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3],
  };

  const DVector4<TLeft> _1 =
  {
    lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0],
    lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1],
    lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2],
    lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3] + lhs[1][3] * rhs[3][3],
  };

  const DVector4<TLeft> _2 =
  {
    lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0],
    lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1],
    lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][3] * rhs[3][2],
    lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3] + lhs[2][3] * rhs[3][3],
  };

  const DVector4<TLeft> _3 =
  {
    lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0] + lhs[3][3] * rhs[3][0],
    lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1] + lhs[3][3] * rhs[3][1],
    lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2] + lhs[3][3] * rhs[3][2],
    lhs[3][0] * rhs[0][3] + lhs[3][1] * rhs[1][3] + lhs[3][2] * rhs[2][3] + lhs[3][3] * rhs[3][3],
  };

  lhs[0] = _0; lhs[1] = _1; lhs[2] = _2; lhs[3] = _3;
  return lhs;
}

} /// ::dy::math namespace

// Common

namespace dy::math
{


template <typename TLeft, EMatMajor TMajor>
DMatrix4<TLeft, TMajor>& operator*=(const DMatrix4<TLeft, TMajor>& lhs, TLeft rhs) noexcept 
{
  lhs[0] *= rhs; lhs[1] *= rhs; lhs[2] *= rhs; lhs[3] *= rhs;
  return lhs;
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TRight>>>
DMatrix4<GetBiggerType<TLeft, TRight>, TMajor> 
operator*(const DMatrix4<TLeft, TMajor>& lhs, TRight rhs) noexcept 
{
  return { lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs };
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TLeft>>>
DMatrix4<GetBiggerType<TLeft, TRight>, TMajor> 
operator*(TLeft lhs, const DMatrix4<TRight, TMajor>& rhs) noexcept 
{
  return { lhs * rhs[0], lhs * rhs[1], lhs * rhs[2], lhs * rhs[3] };
}

/// @brief Elementary addition.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix4<GetBiggerType<TLeft, TRight>, TMajor> 
operator+(const DMatrix4<TLeft, TMajor>& lhs, const DMatrix4<TRight, TMajor>& rhs) noexcept 
{
  return { lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2], lhs[3] + rhs[3] };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix4<TLeft, TMajor>& operator+=(DMatrix4<TLeft, TMajor>& lhs, const DMatrix4<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] += rhs[0]; lhs[1] += rhs[1]; lhs[2] += rhs[2]; lhs[3] += rhs[3];
  return lhs;
}

/// @brief Elementary subtraction.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix4<GetBiggerType<TLeft, TRight>, TMajor> 
operator-(const DMatrix4<TLeft, TMajor>& lhs, const DMatrix4<TRight, TMajor>& rhs) noexcept 
{
  return { lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2], lhs[3] - rhs[3] };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix4<TLeft, TMajor>& operator-=(DMatrix4<TLeft, TMajor>& lhs, const DMatrix4<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] -= rhs[0]; lhs[1] -= rhs[1]; lhs[2] -= rhs[2]; lhs[3] -= rhs[3];
  return lhs;
}

/// @brief Elementary multiplication.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix4<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(const DMatrix4<TLeft, TMajor>& lhs, const DMatrix4<TRight, TMajor>& rhs) noexcept 
{
  return { lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2], lhs[3] / rhs[3] };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix4<TLeft, TMajor>& operator/=(DMatrix4<TLeft, TMajor>& lhs, const DMatrix4<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] /= rhs[0]; lhs[1] /= rhs[1]; lhs[2] /= rhs[2]; lhs[3] /= rhs[3];
  return lhs;
}

template <typename TLeft, EMatMajor TMajor>
DMatrix4<TLeft, TMajor>& operator/=(DMatrix4<TLeft, TMajor>& lhs, TLeft rhs) noexcept 
{
  lhs[0] /= rhs; lhs[1] /= rhs; lhs[2] /= rhs; lhs[3] /= rhs;
  return lhs;
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TRight>>>
DMatrix4<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(const DMatrix4<TLeft, TMajor>& lhs, TRight rhs) noexcept 
{
  return { lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs, lhs[3] / rhs };
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TLeft>>>
DMatrix4<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(TLeft lhs, const DMatrix4<TRight, TMajor>& rhs) noexcept 
{
  return { lhs / rhs[0], lhs / rhs[1], lhs / rhs[2], lhs / rhs[3] };
}

template <typename TType, EMatMajor TMajor>
bool operator==(const DMatrix4<TType, TMajor>& lhs, const DMatrix4<TType, TMajor>& rhs) noexcept 
{
  return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] && lhs[3] == rhs[3];
}

template <typename TType, EMatMajor TMajor>
bool operator!=(const DMatrix4<TType, TMajor>& lhs, const DMatrix4<TType, TMajor>& rhs) noexcept 
{
  return !(lhs == rhs);
}

} /// ::dy::math namespace
