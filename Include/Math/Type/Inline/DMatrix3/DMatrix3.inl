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

#include <Math/Type/Math/DVector3.h>

// Column Major

namespace dy::math
{

template <typename TType>
DMatrix3<TType, EMatMajor::Column>::DMatrix3(
  TValueType _00, TValueType _01, TValueType _02, 
  TValueType _10, TValueType _11, TValueType _12, 
  TValueType _20, TValueType _21, TValueType _22)
  : mValues{
    DVector3<TValueType>{_00, _10, _20}, 
    DVector3<TValueType>{_01, _11, _21},
    DVector3<TValueType>{_02, _12, _22}} 
{ }

template<typename TType>
DMatrix3<TType, EMatMajor::Column>::DMatrix3(
  const DVector3<TValueType>& _0, 
  const DVector3<TValueType>& _1,
  const DVector3<TValueType>& _2)
  : mValues{_0, _1, _2}
{ }

template <typename TType>
DVector3<typename DMatrix3<TType, EMatMajor::Column>::TValueType>& 
DMatrix3<TType, EMatMajor::Column>::operator[](TIndex index) noexcept
{
  return this->mValues[index];
}

template <typename TType>
const DVector3<typename DMatrix3<TType, EMatMajor::Column>::TValueType>& 
DMatrix3<TType, EMatMajor::Column>::operator[](TIndex index) const noexcept
{
  return this->mValues[index];
}

template <typename TType>
DMatrix3<TType, EMatMajor::Column> DMatrix3<TType, EMatMajor::Column>::Transpose() const noexcept
{
  return DMatrix3
  {
    this->mValues[0][0], this->mValues[0][1], this->mValues[0][2],
    this->mValues[1][0], this->mValues[1][1], this->mValues[1][2],
    this->mValues[2][0], this->mValues[2][1], this->mValues[2][2]
  };
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Column>::IsInvertible() const noexcept
{
  return this->GetDeterminant() != TType(0.0);
}

template <typename TType>
TType DMatrix3<TType, EMatMajor::Column>::GetDeterminant() const noexcept
{
  return 
    + (*this)[0][0] * ((*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2])
    - (*this)[1][0] * ((*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2])
    + (*this)[2][0] * ((*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2]);
}

template <typename TType>
DMatrix3<TType, EMatMajor::Column> DMatrix3<TType, EMatMajor::Column>::Inverse() const
{
  const auto det = this->GetDeterminant();

  DMatrix3<TType, EMatMajor::Column> result{};
  result[0][0] = + ((*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2]);
  result[1][0] = - ((*this)[1][0] * (*this)[2][2] - (*this)[2][0] * (*this)[1][2]);
  result[2][0] = + ((*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1]);
  result[0][1] = - ((*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2]);
  result[1][1] = + ((*this)[0][0] * (*this)[2][2] - (*this)[2][0] * (*this)[0][2]);
  result[2][1] = - ((*this)[0][0] * (*this)[2][1] - (*this)[2][0] * (*this)[0][1]);
  result[0][2] = + ((*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2]);
  result[1][2] = - ((*this)[0][0] * (*this)[1][2] - (*this)[1][0] * (*this)[0][2]);
  result[2][2] = + ((*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1]);
  result /= det;

  return result;
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Column>::HasNaN() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasNaN() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Column>::HasInfinity() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasInfinity() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Column>::HasOnlyNormal() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasOnlyNormal() == false) { return false; }
  }

  return true;
}

template <typename TType>
typename DMatrix3<TType, EMatMajor::Column>::TValueType* DMatrix3<TType, EMatMajor::Column>::Data() noexcept
{
  return this->mValues.front().Data();
}

template <typename TType>
const typename DMatrix3<TType, EMatMajor::Column>::TValueType* DMatrix3<TType, EMatMajor::Column>::Data() const noexcept
{
  return this->mValues.front().Data();
}

template <typename TType>
std::vector<DVector3<TType>> DMatrix3<TType, EMatMajor::Column>::ToVector() const noexcept
{
  return std::vector<DVector3<TType>>
  {
    this->operator[](0),
    this->operator[](1),
    this->operator[](2)
  };
}

template <typename TType>
DMatrix3<TType, EMatMajor::Column> DMatrix3<TType, EMatMajor::Column>::Identity() noexcept
{
  static DMatrix3<TType, EMatMajor::Column> identity
  {
    1, 0, 0, 
    0, 1, 0,
    0, 0, 1
  };
  return identity;
}

template<typename TType>
DMatrix3<TType, EMatMajor::Row> DMatrix3<TType, EMatMajor::Column>::ConvertToRowMatrix() const
{
  return {this->operator[](0), this->operator[](1), this->operator[](2)};
}

} /// ::dy::math namespace

// Row Major

namespace dy::math
{

template <typename TType>
DMatrix3<TType, EMatMajor::Row>::DMatrix3(
  TValueType _00, TValueType _01, TValueType _02, 
  TValueType _10, TValueType _11, TValueType _12, 
  TValueType _20, TValueType _21, TValueType _22)
  : mValues{
    DVector3<TValueType>{_00, _01, _02}, 
    DVector3<TValueType>{_10, _11, _12},
    DVector3<TValueType>{_20, _21, _22}} 
{ }

template<typename TType>
DMatrix3<TType, EMatMajor::Row>::DMatrix3(
  const DVector3<TValueType>& _0, 
  const DVector3<TValueType>& _1,
  const DVector3<TValueType>& _2)
  : mValues{_0, _1, _2}
{ }

template <typename TType>
DVector3<typename DMatrix3<TType, EMatMajor::Row>::TValueType>& 
DMatrix3<TType, EMatMajor::Row>::operator[](TIndex index) noexcept
{
  return this->mValues[index];
}

template <typename TType>
const DVector3<typename DMatrix3<TType, EMatMajor::Row>::TValueType>& 
DMatrix3<TType, EMatMajor::Row>::operator[](TIndex index) const noexcept
{
  return this->mValues[index];
}

template <typename TType>
DMatrix3<TType, EMatMajor::Row> DMatrix3<TType, EMatMajor::Row>::Transpose() const noexcept
{
  return DMatrix3
  {
    this->mValues[0][0], this->mValues[1][0], this->mValues[2][0],
    this->mValues[0][1], this->mValues[1][1], this->mValues[2][1],
    this->mValues[0][2], this->mValues[1][2], this->mValues[2][2]
  };
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Row>::IsInvertible() const noexcept
{
  return this->GetDeterminant() != TType(0.0);
}

template <typename TType>
TType DMatrix3<TType, EMatMajor::Row>::GetDeterminant() const noexcept
{
  return 
    + (*this)[0][0] * ((*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2])
    - (*this)[1][0] * ((*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2])
    + (*this)[2][0] * ((*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2]);
}

template <typename TType>
DMatrix3<TType, EMatMajor::Row> DMatrix3<TType, EMatMajor::Row>::Inverse() const
{
  const auto det = this->GetDeterminant();

  DMatrix3<TType, EMatMajor::Row> result{};
  result[0][0] = + ((*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2]);
  result[1][0] = - ((*this)[1][0] * (*this)[2][2] - (*this)[2][0] * (*this)[1][2]);
  result[2][0] = + ((*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1]);
  result[0][1] = - ((*this)[0][1] * (*this)[2][2] - (*this)[2][1] * (*this)[0][2]);
  result[1][1] = + ((*this)[0][0] * (*this)[2][2] - (*this)[2][0] * (*this)[0][2]);
  result[2][1] = - ((*this)[0][0] * (*this)[2][1] - (*this)[2][0] * (*this)[0][1]);
  result[0][2] = + ((*this)[0][1] * (*this)[1][2] - (*this)[1][1] * (*this)[0][2]);
  result[1][2] = - ((*this)[0][0] * (*this)[1][2] - (*this)[1][0] * (*this)[0][2]);
  result[2][2] = + ((*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1]);
  result /= det;

  return result;
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Row>::HasNaN() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasNaN() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Row>::HasInfinity() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasInfinity() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix3<TType, EMatMajor::Row>::HasOnlyNormal() const noexcept
{
  for (const auto& value : this->mValues)
  {
    if (value.HasOnlyNormal() == false) { return false; }
  }

  return true;
}

template <typename TType>
typename DMatrix3<TType, EMatMajor::Row>::TValueType* DMatrix3<TType, EMatMajor::Row>::Data() noexcept
{
  return this->mValues.front().Data();
}

template <typename TType>
const typename DMatrix3<TType, EMatMajor::Row>::TValueType* DMatrix3<TType, EMatMajor::Row>::Data() const noexcept
{
  return this->mValues.front().Data();
}

template <typename TType>
std::vector<DVector3<TType>> DMatrix3<TType, EMatMajor::Row>::ToVector() const noexcept
{
  return std::vector<DVector3<TType>>
  {
    this->operator[](0),
    this->operator[](1),
    this->operator[](2)
  };
}

template <typename TType>
DMatrix3<TType, EMatMajor::Row> DMatrix3<TType, EMatMajor::Row>::Identity() noexcept
{
  static DMatrix3<TType, EMatMajor::Row> identity
  {
    1, 0, 0, 
    0, 1, 0,
    0, 0, 1
  };
  return identity;
}

template<typename TType>
DMatrix3<TType, EMatMajor::Column> DMatrix3<TType, EMatMajor::Row>::ConvertToColumnMatrix() const
{
  return {this->operator[](0), this->operator[](1), this->operator[](2)};
}


} /// ::dy::math namespace

