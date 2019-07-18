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

/// [a b] * [v0] = new vector2.
/// [c d]   [v1]
/// https://en.wikibooks.org/wiki/GLSL_Programming/Vector_and_Matrix_Operations
template <typename TLeft, typename TRight>
DVector2<GetBiggerType<TLeft, TRight>> 
operator*(const DMatrix2<TLeft, EMatMajor::Column>& lhs, const DVector2<TRight>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0] + lhs[1][0] * rhs[1],
    lhs[0][1] * rhs[0] + lhs[1][1] * rhs[1]
  };
}

template <typename TLeft, typename TRight>
DVector2<GetBiggerType<TLeft, TRight>> 
operator*(const DVector2<TLeft>& lhs, const DMatrix2<TRight, EMatMajor::Column>& rhs) noexcept 
{
  return 
  {
    lhs[0] * rhs[0][0] + lhs[1] * rhs[0][1],
    lhs[0] * rhs[1][0] + lhs[1] * rhs[1][1]
  };
}

template <typename TLeft, typename TRight>
DMatrix2<GetBiggerType<TLeft, TRight>, EMatMajor::Column> 
operator*(const DMatrix2<TLeft, EMatMajor::Column>& lhs, const DMatrix2<TRight, EMatMajor::Column>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
    lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
    lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
    lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1],
  };
}

template <typename TLeft>
DMatrix2<TLeft, EMatMajor::Column>& 
operator*=(DMatrix2<TLeft, EMatMajor::Column>& lhs, const DMatrix2<TLeft, EMatMajor::Column>& rhs) noexcept 
{
  const DVector2<TLeft> _0 = 
  {
    lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1],
    lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1],
  };

  const DVector2<TLeft> _1 =
  {
    lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1],
    lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1],
  };

  lhs[0] = _0; lhs[1] = _1;
  return lhs;
}

} /// ::dy::math namespace

// Row Major

namespace dy::math
{

/// [a b] * [v0] = new vector2.
/// [c d]   [v1]
/// https://en.wikibooks.org/wiki/GLSL_Programming/Vector_and_Matrix_Operations
template <typename TLeft, typename TRight>
DVector2<GetBiggerType<TLeft, TRight>> 
operator*(const DMatrix2<TLeft, EMatMajor::Row>& lhs, const DVector2<TRight>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0] + lhs[0][1] * rhs[1],
    lhs[1][0] * rhs[0] + lhs[1][1] * rhs[1]
  };
}

template <typename TLeft, typename TRight>
DVector2<GetBiggerType<TLeft, TRight>> 
operator*(const DVector2<TLeft>& lhs, const DMatrix2<TRight, EMatMajor::Row>& rhs) noexcept 
{
  return 
  {
    lhs[0] * rhs[0][0] + lhs[1] * rhs[1][0],
    lhs[0] * rhs[0][1] + lhs[1] * rhs[1][1]
  };
}

template <typename TLeft, typename TRight>
DMatrix2<GetBiggerType<TLeft, TRight>, EMatMajor::Row> 
operator*(const DMatrix2<TLeft, EMatMajor::Row>& lhs, const DMatrix2<TRight, EMatMajor::Row>& rhs) noexcept 
{
  return 
  {
    lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0],
    lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1],
    lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0],
    lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1],
  };
}

template <typename TLeft>
DMatrix2<TLeft, EMatMajor::Row>& 
operator*=(DMatrix2<TLeft, EMatMajor::Row>& lhs, const DMatrix2<TLeft, EMatMajor::Row>& rhs) noexcept 
{
  const DVector2<TLeft> _0 = 
  {
    lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0],
    lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1]
  };

  const DVector2<TLeft> _1 =
  {
    lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0],
    lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1],
  };

  lhs[0] = _0; lhs[1] = _1;
  return lhs;
}

} /// ::dy::math namespace

namespace dy::math
{

template <typename TLeft, EMatMajor TMajor>
DMatrix2<TLeft, TMajor>& operator*=(const DMatrix2<TLeft, TMajor>& lhs, TLeft rhs) noexcept 
{
  lhs[0] *= rhs;
  lhs[1] *= rhs;
  return lhs;
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TRight>>>
DMatrix2<GetBiggerType<TLeft, TRight>, TMajor> 
operator*(const DMatrix2<TLeft, TMajor>& lhs, TRight rhs) noexcept 
{
  return 
  {
    lhs[0] * rhs,
    lhs[1] * rhs
  };
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TLeft>>>
DMatrix2<GetBiggerType<TLeft, TRight>, TMajor> 
operator*(TLeft lhs, const DMatrix2<TRight, TMajor>& rhs) noexcept 
{
  return 
  {
    lhs * rhs[0],
    lhs * rhs[1]
  };
}

/// @brief Elementary addition.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix2<GetBiggerType<TLeft, TRight>, TMajor> 
operator+(const DMatrix2<TLeft, TMajor>& lhs, const DMatrix2<TRight, TMajor>& rhs) noexcept 
{
  return 
  {
    lhs[0] + rhs[0],
    lhs[1] + rhs[1],
  };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix2<TLeft, TMajor>& 
operator+=(DMatrix2<TLeft, TMajor>& lhs, const DMatrix2<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] += rhs[0]; 
  lhs[1] += rhs[1];
  return lhs;
}

/// @brief Elementary subtraction.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix2<GetBiggerType<TLeft, TRight>, TMajor> 
operator-(const DMatrix2<TLeft, TMajor>& lhs, const DMatrix2<TRight, TMajor>& rhs) noexcept 
{
  return 
  {
    lhs[0] - rhs[0],
    lhs[1] - rhs[1],
  };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix2<TLeft, TMajor>& 
operator-=(DMatrix2<TLeft, TMajor>& lhs, const DMatrix2<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] -= rhs[0]; 
  lhs[1] -= rhs[1];
  return lhs;
}

/// @brief Elementary multiplication.
template <typename TLeft, typename TRight, EMatMajor TMajor>
DMatrix2<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(const DMatrix2<TLeft, TMajor>& lhs, const DMatrix2<TRight, TMajor>& rhs) noexcept 
{
  return 
  {
    lhs[0] / rhs[0],
    lhs[1] / rhs[1],
  };
}

template <typename TLeft, EMatMajor TMajor>
DMatrix2<TLeft, TMajor>& 
operator/=(DMatrix2<TLeft, TMajor>& lhs, const DMatrix2<TLeft, TMajor>& rhs) noexcept 
{
  lhs[0] /= rhs[0]; 
  lhs[1] /= rhs[1];
  return lhs;
}

template <typename TLeft, EMatMajor TMajor>
DMatrix2<TLeft, TMajor>& operator/=(DMatrix2<TLeft, TMajor>& lhs, TLeft rhs) noexcept 
{
  lhs[0] /= rhs;
  lhs[1] /= rhs;

  return lhs;
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TRight>>>
DMatrix2<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(const DMatrix2<TLeft, TMajor>& lhs, TRight rhs) noexcept 
{
  return 
  {
    lhs[0] / rhs,
    lhs[1] / rhs
  };
}

template <typename TLeft, typename TRight, EMatMajor TMajor, typename = std::enable_if_t<std::is_arithmetic_v<TLeft>>>
DMatrix2<GetBiggerType<TLeft, TRight>, TMajor> 
operator/(TLeft lhs, const DMatrix2<TRight, TMajor>& rhs) noexcept 
{
  return 
  {
    lhs / rhs[0],
    lhs / rhs[1]
  };
}

template <typename TType, EMatMajor TMajor>
bool operator==(const DMatrix2<TType, TMajor>& lhs, const DMatrix2<TType, TMajor>& rhs) noexcept 
{
  return lhs[0] == rhs[0] && lhs[1] == rhs[1];
}

template <typename TType, EMatMajor TMajor>
bool operator!=(const DMatrix2<TType, TMajor>& lhs, const DMatrix2<TType, TMajor>& rhs) noexcept 
{
  return !(lhs == rhs);
}

} /// ::dy::math namespace
