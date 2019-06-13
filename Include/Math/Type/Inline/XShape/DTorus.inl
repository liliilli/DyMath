#include "..\..\Shape\DTorus.h"
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

namespace dy::math
{

template<typename TType>
inline DTorus<TType>::DTorus(const DVector3<TValueType>& origin, TValueType distance, TValueType radius)
  : mOrigin { origin },
    mDistanceFromOrigin { distance },
    mRadiusOfTube { radius }
{ 
#if !defined(NDEBUG)
  assert(this->mDistanceFromOrigin != TType(0));
  assert(this->mRadiusOfTube != TType(0));
#endif
}

template<typename TType>
inline const DVector3<typename DTorus<TType>::TValueType>& DTorus<TType>::GetOrigin() const noexcept
{
  return this->mOrigin;
}

template<typename TType>
inline typename DTorus<TType>::TValueType DTorus<TType>::GetRadius() const noexcept
{
  return this->mRadiusOfTube;
}

template<typename TType>
inline typename DTorus<TType>::TValueType DTorus<TType>::GetDistance() const noexcept
{
  return this->mDistanceFromOrigin;
}

template<typename TType>
inline bool DTorus<TType>::HasNaN() const noexcept
{
  return this->mOrigin.HasNaN() 
    || std::isnan(this->mDistanceFromOrigin) 
    || std::isnan(this->mRadiusOfTube);
}

template<typename TType>
inline bool DTorus<TType>::HasInfinity() const noexcept
{
  return this->mOrigin.HasInfinity() 
    || std::isinf(this->mDistanceFromOrigin) 
    || std::isinf(this->mRadiusOfTube);
}

template<typename TType>
inline bool DTorus<TType>::HasOnlyNormal() const noexcept
{
  return this->mOrigin.HasOnlyNormal() 
    && std::isnormal(this->mDistanceFromOrigin) 
    && std::isnormal(this->mRadiusOfTube);
}

} /// ::dy::math namespace