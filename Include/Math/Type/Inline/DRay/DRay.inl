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

#include <Math/Type/Shape/DRay.h>

namespace dy::math
{

template <typename TType>
DRay<TType>::DRay(
  const DVector3<typename DRay<TType>::TValueType>& origin, 
  const DVector3<typename DRay<TType>::TValueType>& direction,
  bool doNormalize)
  : mOrigin{origin},
    mDirection{doNormalize ? direction.Normalize() : direction}
{ }

template <typename TType>
const DVector3<typename DRay<TType>::TValueType>& 
DRay<TType>::GetOrigin() const noexcept
{
  return this->mOrigin;
} 

template <typename TType>
const DVector3<typename DRay<TType>::TValueType>& 
DRay<TType>::GetDirection() const noexcept
{
  return this->mDirection;
}

template <typename TType>
DVector3<typename DRay<TType>::TValueType> 
DRay<TType>::GetPointAtParam(TReal t) const
{
  return this->mOrigin + (t * this->mDirection);
}

template <typename TType>
bool DRay<TType>::HasNaN() const noexcept
{
  return this->mOrigin.HasNaN() || this->mDirection.HasNaN();
}

template <typename TType>
bool DRay<TType>::HasInfinity() const noexcept
{
  return this->mOrigin.HasInfinity() || this->mDirection.HasInfinity();
}

template <typename TType>
bool DRay<TType>::HasOnlyNormal() const noexcept
{
  return this->mOrigin.HasOnlyNormal() && this->mDirection.HasOnlyNormal();
}

} /// ::dy::math namespace