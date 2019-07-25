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

#include <Math/Type/Math/DVector4.h>

// Column Major

namespace dy::math
{

template <typename TType>
DMatrix4<TType, EMatMajor::Column>::DMatrix4(
  TValueType _00, TValueType _01, TValueType _02, TValueType _03,
  TValueType _10, TValueType _11, TValueType _12, TValueType _13,
  TValueType _20, TValueType _21, TValueType _22, TValueType _23,
  TValueType _30, TValueType _31, TValueType _32, TValueType _33)
  : __mValues{
    DVector4<TValueType>{_00, _10, _20, _30}, 
    DVector4<TValueType>{_01, _11, _21, _31},
    DVector4<TValueType>{_02, _12, _22, _32},
    DVector4<TValueType>{_03, _13, _23, _33}} 
{ }

template<typename TType>
DMatrix4<TType, EMatMajor::Column>::DMatrix4(
  const DVector4<TValueType>& _0, 
  const DVector4<TValueType>& _1,
  const DVector4<TValueType>& _2,
  const DVector4<TValueType>& _3)
  : __mValues{_0, _1, _2, _3}
{ }

template <typename TType>
DVector4<typename DMatrix4<TType, EMatMajor::Column>::TValueType>& 
DMatrix4<TType, EMatMajor::Column>::operator[](TIndex index) noexcept
{
  return this->__mValues[index];
}

template <typename TType>
const DVector4<typename DMatrix4<TType, EMatMajor::Column>::TValueType>& 
DMatrix4<TType, EMatMajor::Column>::operator[](TIndex index) const noexcept
{
  return this->__mValues[index];
}

template <typename TType>
DMatrix4<TType, EMatMajor::Column> DMatrix4<TType, EMatMajor::Column>::Transpose() const noexcept
{
  return DMatrix4
  {
    this->__mValues[0][0], this->__mValues[0][1], this->__mValues[0][2], this->__mValues[0][3],
    this->__mValues[1][0], this->__mValues[1][1], this->__mValues[1][2], this->__mValues[1][3],
    this->__mValues[2][0], this->__mValues[2][1], this->__mValues[2][2], this->__mValues[2][3],
    this->__mValues[3][0], this->__mValues[3][1], this->__mValues[3][2], this->__mValues[3][3],
  };
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Column>::IsInvertible() const noexcept
{
  return this->GetDeterminant() != TType(0.0);
}

template <typename TType>
TType DMatrix4<TType, EMatMajor::Column>::GetDeterminant() const noexcept
{
  TType SubFactor00 = (*this)[2][2] * (*this)[3][3] - (*this)[3][2] * (*this)[2][3];
  TType SubFactor01 = (*this)[2][1] * (*this)[3][3] - (*this)[3][1] * (*this)[2][3];
  TType SubFactor02 = (*this)[2][1] * (*this)[3][2] - (*this)[3][1] * (*this)[2][2];
  TType SubFactor03 = (*this)[2][0] * (*this)[3][3] - (*this)[3][0] * (*this)[2][3];
  TType SubFactor04 = (*this)[2][0] * (*this)[3][2] - (*this)[3][0] * (*this)[2][2];
  TType SubFactor05 = (*this)[2][0] * (*this)[3][1] - (*this)[3][0] * (*this)[2][1];

  DVector4<TType> DetCof
  {
    + ((*this)[1][1] * SubFactor00 - (*this)[1][2] * SubFactor01 + (*this)[1][3] * SubFactor02),
    - ((*this)[1][0] * SubFactor00 - (*this)[1][2] * SubFactor03 + (*this)[1][3] * SubFactor04),
    + ((*this)[1][0] * SubFactor01 - (*this)[1][1] * SubFactor03 + (*this)[1][3] * SubFactor05),
    - ((*this)[1][0] * SubFactor02 - (*this)[1][1] * SubFactor04 + (*this)[1][2] * SubFactor05)
  };

  return
    (*this)[0][0] * DetCof[0] + (*this)[0][1] * DetCof[1] +
    (*this)[0][2] * DetCof[2] + (*this)[0][3] * DetCof[3];
}

template <typename TType>
DMatrix4<TType, EMatMajor::Column> DMatrix4<TType, EMatMajor::Column>::Inverse() const
{
  TType Coef00 = (*this)[2][2] * (*this)[3][3] - (*this)[3][2] * (*this)[2][3];
  TType Coef02 = (*this)[1][2] * (*this)[3][3] - (*this)[3][2] * (*this)[1][3];
  TType Coef03 = (*this)[1][2] * (*this)[2][3] - (*this)[2][2] * (*this)[1][3];

  TType Coef04 = (*this)[2][1] * (*this)[3][3] - (*this)[3][1] * (*this)[2][3];
  TType Coef06 = (*this)[1][1] * (*this)[3][3] - (*this)[3][1] * (*this)[1][3];
  TType Coef07 = (*this)[1][1] * (*this)[2][3] - (*this)[2][1] * (*this)[1][3];

  TType Coef08 = (*this)[2][1] * (*this)[3][2] - (*this)[3][1] * (*this)[2][2];
  TType Coef10 = (*this)[1][1] * (*this)[3][2] - (*this)[3][1] * (*this)[1][2];
  TType Coef11 = (*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2];

  TType Coef12 = (*this)[2][0] * (*this)[3][3] - (*this)[3][0] * (*this)[2][3];
  TType Coef14 = (*this)[1][0] * (*this)[3][3] - (*this)[3][0] * (*this)[1][3];
  TType Coef15 = (*this)[1][0] * (*this)[2][3] - (*this)[2][0] * (*this)[1][3];

  TType Coef16 = (*this)[2][0] * (*this)[3][2] - (*this)[3][0] * (*this)[2][2];
  TType Coef18 = (*this)[1][0] * (*this)[3][2] - (*this)[3][0] * (*this)[1][2];
  TType Coef19 = (*this)[1][0] * (*this)[2][2] - (*this)[2][0] * (*this)[1][2];

  TType Coef20 = (*this)[2][0] * (*this)[3][1] - (*this)[3][0] * (*this)[2][1];
  TType Coef22 = (*this)[1][0] * (*this)[3][1] - (*this)[3][0] * (*this)[1][1];
  TType Coef23 = (*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1];

  DVector4<TType> fac0(Coef00, Coef00, Coef02, Coef03);
  DVector4<TType> fac1(Coef04, Coef04, Coef06, Coef07);
  DVector4<TType> fac2(Coef08, Coef08, Coef10, Coef11);
  DVector4<TType> fac3(Coef12, Coef12, Coef14, Coef15);
  DVector4<TType> fac4(Coef16, Coef16, Coef18, Coef19);
  DVector4<TType> fac5(Coef20, Coef20, Coef22, Coef23);

  DVector4<TType> vec0((*this)[1][0], (*this)[0][0], (*this)[0][0], (*this)[0][0]);
  DVector4<TType> vec1((*this)[1][1], (*this)[0][1], (*this)[0][1], (*this)[0][1]);
  DVector4<TType> vec2((*this)[1][2], (*this)[0][2], (*this)[0][2], (*this)[0][2]);
  DVector4<TType> vec3((*this)[1][3], (*this)[0][3], (*this)[0][3], (*this)[0][3]);

  DVector4<TType> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
  DVector4<TType> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
  DVector4<TType> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
  DVector4<TType> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

  DVector4<TType> signA(+1, -1, +1, -1);
  DVector4<TType> signB(-1, +1, -1, +1);
  DMatrix4<TType, EMatMajor::Column> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

  DVector4<TType> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

  DVector4<TType> dot0((*this)[0] * row0);
  TType det = (dot0.X + dot0.Y) + (dot0.Z + dot0.W);

  return inverse / det;
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Column>::HasNaN() const noexcept
{
  for (const auto& value : this->__mValues)
  {
    if (value.HasNaN() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Column>::HasInfinity() const noexcept
{
  for (const auto& value : this->__mValues)
  {
    if (value.HasInfinity() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Column>::HasOnlyNormal() const noexcept
{
  for (const auto& value : this->__mValues)
  {
    if (value.HasOnlyNormal() == false) { return false; }
  }

  return true;
}

template <typename TType>
typename DMatrix4<TType, EMatMajor::Column>::TValueType* DMatrix4<TType, EMatMajor::Column>::Data() noexcept
{
  return this->__mValues.front().Data();
}

template <typename TType>
const typename DMatrix4<TType, EMatMajor::Column>::TValueType* DMatrix4<TType, EMatMajor::Column>::Data() const noexcept
{
  return this->__mValues.front().Data();
}

template<typename TType>
std::vector<DVector4<TType>> DMatrix4<TType, EMatMajor::Column>::ToVector() const noexcept
{
  return std::vector<DVector4<TType>>
  {
    (*this)[0], (*this)[1], (*this)[2], (*this)[3]
  };
}

template<typename TType>
DMatrix4<TType,EMatMajor::Row> DMatrix4<TType, EMatMajor::Column>::ConvertToRowMatrix() const
{
  return
  {
    (*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0],
    (*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1],
    (*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2],
    (*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3],
  };
}

template <typename TType>
DMatrix4<TType, EMatMajor::Column> DMatrix4<TType, EMatMajor::Column>::Identity() noexcept
{
  static DMatrix4<TType> identity
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  return identity;
}

} /// ::dy::math namespace

// Row Major

namespace dy::math
{

template <typename TType>
DMatrix4<TType, EMatMajor::Row>::DMatrix4(
  TValueType _00, TValueType _01, TValueType _02, TValueType _03,
  TValueType _10, TValueType _11, TValueType _12, TValueType _13,
  TValueType _20, TValueType _21, TValueType _22, TValueType _23,
  TValueType _30, TValueType _31, TValueType _32, TValueType _33)
  : __mValues{
    DVector4<TValueType>{_00, _01, _02, _03}, 
    DVector4<TValueType>{_10, _11, _12, _13},
    DVector4<TValueType>{_20, _21, _22, _23},
    DVector4<TValueType>{_30, _31, _32, _33}} 
{ }

template<typename TType>
DMatrix4<TType, EMatMajor::Row>::DMatrix4(
  const DVector4<TValueType>& _0, 
  const DVector4<TValueType>& _1,
  const DVector4<TValueType>& _2,
  const DVector4<TValueType>& _3)
  : __mValues{_0, _1, _2, _3}
{ }

template <typename TType>
DVector4<typename DMatrix4<TType, EMatMajor::Row>::TValueType>& 
DMatrix4<TType, EMatMajor::Row>::operator[](TIndex index) noexcept
{
  return this->__mValues[index];
}

template <typename TType>
const DVector4<typename DMatrix4<TType, EMatMajor::Row>::TValueType>& 
DMatrix4<TType, EMatMajor::Row>::operator[](TIndex index) const noexcept
{
  return this->__mValues[index];
}

template <typename TType>
DMatrix4<TType, EMatMajor::Row> DMatrix4<TType, EMatMajor::Row>::Transpose() const noexcept
{
  return DMatrix4
  {
    this->__mValues[0][0], this->__mValues[1][0], this->__mValues[2][0], this->__mValues[3][0],
    this->__mValues[0][1], this->__mValues[1][1], this->__mValues[2][1], this->__mValues[3][1],
    this->__mValues[0][2], this->__mValues[1][2], this->__mValues[2][2], this->__mValues[3][2],
    this->__mValues[0][3], this->__mValues[1][3], this->__mValues[2][3], this->__mValues[3][3],
  };
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Row>::IsInvertible() const noexcept
{
  return this->GetDeterminant() != TType(0.0);
}

template <typename TType>
TType DMatrix4<TType, EMatMajor::Row>::GetDeterminant() const noexcept
{
  TType SubFactor00 = (*this)[2][2] * (*this)[3][3] - (*this)[3][2] * (*this)[2][3];
  TType SubFactor01 = (*this)[2][1] * (*this)[3][3] - (*this)[3][1] * (*this)[2][3];
  TType SubFactor02 = (*this)[2][1] * (*this)[3][2] - (*this)[3][1] * (*this)[2][2];
  TType SubFactor03 = (*this)[2][0] * (*this)[3][3] - (*this)[3][0] * (*this)[2][3];
  TType SubFactor04 = (*this)[2][0] * (*this)[3][2] - (*this)[3][0] * (*this)[2][2];
  TType SubFactor05 = (*this)[2][0] * (*this)[3][1] - (*this)[3][0] * (*this)[2][1];

  DVector4<TType> DetCof
  {
    + ((*this)[1][1] * SubFactor00 - (*this)[1][2] * SubFactor01 + (*this)[1][3] * SubFactor02),
    - ((*this)[1][0] * SubFactor00 - (*this)[1][2] * SubFactor03 + (*this)[1][3] * SubFactor04),
    + ((*this)[1][0] * SubFactor01 - (*this)[1][1] * SubFactor03 + (*this)[1][3] * SubFactor05),
    - ((*this)[1][0] * SubFactor02 - (*this)[1][1] * SubFactor04 + (*this)[1][2] * SubFactor05)
  };

  return
    (*this)[0][0] * DetCof[0] + (*this)[0][1] * DetCof[1] +
    (*this)[0][2] * DetCof[2] + (*this)[0][3] * DetCof[3];
}

template <typename TType>
DMatrix4<TType, EMatMajor::Row> DMatrix4<TType, EMatMajor::Row>::Inverse() const
{
  TType Coef00 = (*this)[2][2] * (*this)[3][3] - (*this)[3][2] * (*this)[2][3];
  TType Coef02 = (*this)[1][2] * (*this)[3][3] - (*this)[3][2] * (*this)[1][3];
  TType Coef03 = (*this)[1][2] * (*this)[2][3] - (*this)[2][2] * (*this)[1][3];

  TType Coef04 = (*this)[2][1] * (*this)[3][3] - (*this)[3][1] * (*this)[2][3];
  TType Coef06 = (*this)[1][1] * (*this)[3][3] - (*this)[3][1] * (*this)[1][3];
  TType Coef07 = (*this)[1][1] * (*this)[2][3] - (*this)[2][1] * (*this)[1][3];

  TType Coef08 = (*this)[2][1] * (*this)[3][2] - (*this)[3][1] * (*this)[2][2];
  TType Coef10 = (*this)[1][1] * (*this)[3][2] - (*this)[3][1] * (*this)[1][2];
  TType Coef11 = (*this)[1][1] * (*this)[2][2] - (*this)[2][1] * (*this)[1][2];

  TType Coef12 = (*this)[2][0] * (*this)[3][3] - (*this)[3][0] * (*this)[2][3];
  TType Coef14 = (*this)[1][0] * (*this)[3][3] - (*this)[3][0] * (*this)[1][3];
  TType Coef15 = (*this)[1][0] * (*this)[2][3] - (*this)[2][0] * (*this)[1][3];

  TType Coef16 = (*this)[2][0] * (*this)[3][2] - (*this)[3][0] * (*this)[2][2];
  TType Coef18 = (*this)[1][0] * (*this)[3][2] - (*this)[3][0] * (*this)[1][2];
  TType Coef19 = (*this)[1][0] * (*this)[2][2] - (*this)[2][0] * (*this)[1][2];

  TType Coef20 = (*this)[2][0] * (*this)[3][1] - (*this)[3][0] * (*this)[2][1];
  TType Coef22 = (*this)[1][0] * (*this)[3][1] - (*this)[3][0] * (*this)[1][1];
  TType Coef23 = (*this)[1][0] * (*this)[2][1] - (*this)[2][0] * (*this)[1][1];

  DVector4<TType> fac0(Coef00, Coef00, Coef02, Coef03);
  DVector4<TType> fac1(Coef04, Coef04, Coef06, Coef07);
  DVector4<TType> fac2(Coef08, Coef08, Coef10, Coef11);
  DVector4<TType> fac3(Coef12, Coef12, Coef14, Coef15);
  DVector4<TType> fac4(Coef16, Coef16, Coef18, Coef19);
  DVector4<TType> fac5(Coef20, Coef20, Coef22, Coef23);

  DVector4<TType> vec0((*this)[1][0], (*this)[0][0], (*this)[0][0], (*this)[0][0]);
  DVector4<TType> vec1((*this)[1][1], (*this)[0][1], (*this)[0][1], (*this)[0][1]);
  DVector4<TType> vec2((*this)[1][2], (*this)[0][2], (*this)[0][2], (*this)[0][2]);
  DVector4<TType> vec3((*this)[1][3], (*this)[0][3], (*this)[0][3], (*this)[0][3]);

  DVector4<TType> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
  DVector4<TType> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
  DVector4<TType> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
  DVector4<TType> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

  DVector4<TType> signA(+1, -1, +1, -1);
  DVector4<TType> signB(-1, +1, -1, +1);
  DMatrix4<TType, EMatMajor::Row> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

  DVector4<TType> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

  DVector4<TType> dot0((*this)[0] * row0);
  TType det = (dot0.X + dot0.Y) + (dot0.Z + dot0.W);

  return inverse / det;
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Row>::HasNaN() const noexcept
{
  for (const auto& value : this->__mValues)
  {
    if (value.HasNaN() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Row>::HasInfinity() const noexcept
{
  for (const auto& value : this->__mValues)
  {
    if (value.HasInfinity() == true) { return true; }
  }

  return false;
}

template <typename TType>
bool DMatrix4<TType, EMatMajor::Row>::HasOnlyNormal() const noexcept
{
  for (const auto& value : this->__mValues)
  {
    if (value.HasOnlyNormal() == false) { return false; }
  }

  return true;
}

template <typename TType>
typename DMatrix4<TType, EMatMajor::Row>::TValueType* DMatrix4<TType, EMatMajor::Row>::Data() noexcept
{
  return this->__mValues.front().Data();
}

template <typename TType>
const typename DMatrix4<TType, EMatMajor::Row>::TValueType* DMatrix4<TType, EMatMajor::Row>::Data() const noexcept
{
  return this->__mValues.front().Data();
}

template<typename TType>
std::vector<DVector4<TType>> DMatrix4<TType, EMatMajor::Row>::ToVector() const noexcept
{
  return std::vector<DVector4<TType>>
  {
    (*this)[0], (*this)[1], (*this)[2], (*this)[3]
  };
}

template<typename TType>
DMatrix4<TType,EMatMajor::Column> DMatrix4<TType, EMatMajor::Row>::ConvertToColumnMatrix() const
{
  return
  {
    (*this)[0][0], (*this)[0][1], (*this)[0][2], (*this)[0][3],
    (*this)[1][0], (*this)[1][1], (*this)[1][2], (*this)[1][3],
    (*this)[2][0], (*this)[2][1], (*this)[2][2], (*this)[2][3],
    (*this)[3][0], (*this)[3][1], (*this)[3][2], (*this)[3][3],
  };
}

template <typename TType>
DMatrix4<TType, EMatMajor::Row> DMatrix4<TType, EMatMajor::Row>::Identity() noexcept
{
  static DMatrix4<TType> identity
  {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  return identity;
}

} /// ::dy::math namespace

