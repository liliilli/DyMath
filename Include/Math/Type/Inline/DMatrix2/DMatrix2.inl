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

#include <Math/Type/Math/DMatrix2.h>

// Column Major

namespace dy::math
{

template <typename TType>
DMatrix2<TType, EMatMajor::Column>::DMatrix2(TValueType _00, TValueType _01, TValueType _10, TValueType _11)
  : mValues{DVector2<TValueType>{_00, _10}, DVector2<TValueType>{_01, _11}} 
{ }

template<typename TType>
DMatrix2<TType, EMatMajor::Column>::DMatrix2(const DVector2<TValueType>& _0, const DVector2<TValueType>& _1)
  : mValues{_0, _1}
{ }

template <typename TType>
DVector2<typename DMatrix2<TType, EMatMajor::Column>::TValueType>& 
DMatrix2<TType, EMatMajor::Column>::operator[](TIndex index) noexcept
{
  return this->mValues[index];
}

template <typename TType>
const DVector2<typename DMatrix2<TType, EMatMajor::Column>::TValueType>& 
DMatrix2<TType, EMatMajor::Column>::operator[](TIndex index) const noexcept
{
  return this->mValues[index];
}

template <typename TType>
DMatrix2<TType, EMatMajor::Column> DMatrix2<TType, EMatMajor::Column>::Transpose() const noexcept
{
  return DMatrix2
  {
    this->mValues[0][0], 
    this->mValues[0][1],
    this->mValues[1][0], 
    this->mValues[1][1]
  };
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Column>::IsInvertible() const noexcept
{
  return this->GetDeterminant() != TType(0.0);
}

template <typename TType>
TType DMatrix2<TType, EMatMajor::Column>::GetDeterminant() const noexcept
{
  return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
}

template <typename TType>
DMatrix2<TType, EMatMajor::Column> DMatrix2<TType, EMatMajor::Column>::Inverse() const
{
  const auto det = this->GetDeterminant();

  DMatrix2<TType, EMatMajor::Column> result;
  result[0][0] =  (*this)[1][1];
  result[1][1] =  (*this)[0][0];
  result[1][0] = -(*this)[1][0];
  result[0][1] = -(*this)[0][1];

  result /= det;
  return result;
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Column>::HasNaN() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasNaN() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Column>::HasInfinity() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasInfinity() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Column>::HasOnlyNormal() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasOnlyNormal() == false) { return false; }
  }

  return true;
}

template <typename TType>
typename DMatrix2<TType, EMatMajor::Column>::TValueType* DMatrix2<TType, EMatMajor::Column>::Data() noexcept
{
  return this->mValues.front().Data();
}

template <typename TType>
const typename DMatrix2<TType, EMatMajor::Column>::TValueType* DMatrix2<TType, EMatMajor::Column>::Data() const noexcept
{
  return this->mValues.front().Data();
}

template<typename TType>
std::vector<DVector2<TType>> DMatrix2<TType, EMatMajor::Column>::ToVector() const noexcept
{
  return std::vector<DVector2<TType, EMatMajor::Column>>{this->operator[](0), this->operator[](1)};
}

template <typename TType>
DMatrix2<TType, EMatMajor::Column> DMatrix2<TType, EMatMajor::Column>::Identity() noexcept
{
  // 1 0
  // 0 1
  static DMatrix2<TType, EMatMajor::Column> identity{1, 0, 0, 1};
  return identity;
}

template<typename TType>
DMatrix2<TType,EMatMajor::Row> DMatrix2<TType, EMatMajor::Column>::ConvertToRowMatrix() const
{
  const auto transposedMatrix = this->Transpose();
  return {transposedMatrix[0], transposedMatrix[1]};
}

} /// ::dy::math namespace

// Row Major

namespace dy::math
{

template <typename TType>
DMatrix2<TType, EMatMajor::Row>::DMatrix2(TValueType _00, TValueType _01, TValueType _10, TValueType _11)
  : mValues{DVector2<TValueType>{_00, _01}, DVector2<TValueType>{_10, _11}} 
{ }

template<typename TType>
DMatrix2<TType, EMatMajor::Row>::DMatrix2(const DVector2<TValueType>& _0, const DVector2<TValueType>& _1)
  : mValues{_0, _1}
{ }

template <typename TType>
DVector2<typename DMatrix2<TType, EMatMajor::Row>::TValueType>& 
DMatrix2<TType, EMatMajor::Row>::operator[](TIndex index) noexcept
{
  return this->mValues[index];
}

template <typename TType>
const DVector2<typename DMatrix2<TType, EMatMajor::Row>::TValueType>& 
DMatrix2<TType, EMatMajor::Row>::operator[](TIndex index) const noexcept
{
  return this->mValues[index];
}

template <typename TType>
DMatrix2<TType, EMatMajor::Row> DMatrix2<TType, EMatMajor::Row>::Transpose() const noexcept
{
  return DMatrix2
  {
    this->mValues[0][0], 
    this->mValues[1][0], 
    this->mValues[0][1],
    this->mValues[1][1]
  };
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Row>::IsInvertible() const noexcept
{
  return this->GetDeterminant() != TType(0.0);
}

template <typename TType>
TType DMatrix2<TType, EMatMajor::Row>::GetDeterminant() const noexcept
{
  return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
}

template <typename TType>
DMatrix2<TType, EMatMajor::Row> DMatrix2<TType, EMatMajor::Row>::Inverse() const
{
  const auto det = this->GetDeterminant();

  DMatrix2<TType, EMatMajor::Row> result;
  result[0][0] =  (*this)[1][1];
  result[1][1] =  (*this)[0][0];
  result[1][0] = -(*this)[1][0];
  result[0][1] = -(*this)[0][1];

  result /= det;
  return result;
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Row>::HasNaN() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasNaN() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Row>::HasInfinity() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasInfinity() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix2<TType, EMatMajor::Row>::HasOnlyNormal() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasOnlyNormal() == false) { return false; }
  }

  return true;
}

template <typename TType>
typename DMatrix2<TType, EMatMajor::Row>::TValueType* DMatrix2<TType, EMatMajor::Row>::Data() noexcept
{
  return this->mValues.front().Data();
}

template <typename TType>
const typename DMatrix2<TType, EMatMajor::Row>::TValueType* DMatrix2<TType, EMatMajor::Row>::Data() const noexcept
{
  return this->mValues.front().Data();
}

template<typename TType>
std::vector<DVector2<TType>> DMatrix2<TType, EMatMajor::Row>::ToVector() const noexcept
{
  return std::vector<DVector2<TType, EMatMajor::Row>>{this->operator[](0), this->operator[](1)};
}

template<typename TType>
DMatrix2<TType, EMatMajor::Column> DMatrix2<TType, EMatMajor::Row>::ConvertToColumnMatrix() const
{
  return {this->operator[](0), this->operator[](1)};
}

template <typename TType>
DMatrix2<TType, EMatMajor::Row> DMatrix2<TType, EMatMajor::Row>::Identity() noexcept
{
  // 1 0
  // 0 1
  static DMatrix2<TType, EMatMajor::Row> identity{1, 0, 0, 1};
  return identity;
}

} /// ::dy::math namespace

