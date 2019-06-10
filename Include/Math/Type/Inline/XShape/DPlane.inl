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

#include <Math/Utility/XLinearMath.h>

namespace dy::math
{

template <typename TType>
DPlane<TType>::DPlane(TValueType a, TValueType b, TValueType c, TValueType d)
  : mNormal{a, b, c}, mD{d}
{
  const auto len = this->mNormal.GetLength();
  this->mNormal = this->mNormal.Normalize();
  this->mD /= len;
}

template <typename TType>
DPlane<TType>::DPlane(const DVector3<TValueType>& normalizedVector, TValueType d)
  : mNormal{normalizedVector}, mD{d}
{ }

template <typename TType>
DPlane<TType>::DPlane(
  const DVector3<TValueType>& pos1, const DVector3<TValueType>& pos2, const DVector3<TValueType>& pos3)
{
  const auto vec1 = (pos2 - pos1).Normalize();
  const auto vec2 = (pos3 - pos1).Normalize();
  this->mNormal = Cross(vec1, vec2);
  this->mD = Dot(this->mNormal, pos1) * TValueType(-1);
}

template<typename TType>
void DPlane<TType>::SetNormalVector(const DVector3<TValueType>& iNormalVector)
{
  this->mNormal = iNormalVector;
}

template <typename TType>
DVector3<typename DPlane<TType>::TValueType> 
DPlane<TType>::GetNormal() const noexcept
{
  return this->mNormal;
}

template <typename TType>
typename DPlane<TType>::TValueType
DPlane<TType>::GetD() const noexcept
{
  return this->mD;
}

template <typename TType>
EPosPlaneState 
DPlane<TType>::CheckPointStatusOnPlane(const DVector3<TValueType>& iPoint) const noexcept
{
  if (const auto sDist = this->GetSignedDistanceFrom(iPoint); 
      sDist > 0.01f)
  {
    return EPosPlaneState::FrontNormal;
  }
  else if (sDist < -0.01f)
  {
    return EPosPlaneState::BehindNormal;
  }
  else
  {
    return EPosPlaneState::OnPlane;
  }
}

template<typename TType>
TReal DPlane<TType>::GetSignedDistanceFrom(const DVector3<TType>& iPoint) const noexcept
{
  return (Dot(iPoint, this->mNormal) + this->mD) / this->mNormal.GetLength();
}

template<typename TType>
TReal DPlane<TType>::GetUnsignedDistanceFrom(const DVector3<TType>& iPoint) const noexcept
{
  return std::abs(this->GetSignedDistanceFrom(iPoint));
}

template <typename TType>
DVector3<typename DPlane<TType>::TValueType> 
DPlane<TType>::GetClosestPoint(const DVector3<TValueType>& iPoint) const noexcept
{
  return iPoint - this->GetNormal() * this->GetSignedDistanceFrom(iPoint);
}

template<typename TType>
inline bool DPlane<TType>::HasNaN() const noexcept
{
  return this->mNormal.HasNaN() || std::isnan(this->mD);
}

template<typename TType>
inline bool DPlane<TType>::HasInfinity() const noexcept
{
  return this->mNormal.HasInfinity() || std::isinf(this->mD);
}

template<typename TType>
inline bool DPlane<TType>::HasOnlyNormal() const noexcept
{
  return this->mNormal.HasOnlyNormal() || std::isnormal(this->mD);
}

} /// ::dy::math namespace