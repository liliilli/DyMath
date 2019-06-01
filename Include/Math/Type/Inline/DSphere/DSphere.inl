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

#include <Math/Type/Shape/DSphere.h>
#include <cmath>

namespace dy::math
{

template <typename TType> 
DSphere<TType>::DSphere(
  const DVector3<typename DSphere<TType>::TValueType>& origin, 
  typename DSphere<TType>::TValueType radius)
  : mOrigin { origin },
    mRadius { radius }
{ }

template <typename TType> 
const DVector3<typename DSphere<TType>::TValueType>& 
DSphere<TType>::GetOrigin() const noexcept 
{ 
  return this->mOrigin; 
}

template <typename TType> 
typename DSphere<TType>::TValueType 
DSphere<TType>::GetRadius() const noexcept 
{ 
  return this->mRadius; 
}

template <typename TType>
bool DSphere<TType>::HasNaN() const noexcept
{
  return this->mOrigin.HasNaN() || std::isnan(this->mRadius);
}

template <typename TType>
bool DSphere<TType>::HasInfinity() const noexcept
{
  return this->mOrigin.HasInfinity() || std::isinf(this->mRadius);
}

template <typename TType>
bool DSphere<TType>::HasOnlyNormal() const noexcept
{
  return this->mOrigin.HasOnlyNormal() && std::isnormal(this->mRadius);
}

} /// ::dy::math namespace