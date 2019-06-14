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

#include <cassert>

namespace dy::math
{

template<typename TType>
inline DCone<TType>::DCone(const DVector3<TValueType>& origin, TValueType height, TValueType radius)
  : mOrigin { origin },
    mHeight { height },
    mRadius { radius }
{
#if !defined(NDEBUG)
  assert(this->mHeight > 0);
  assert(this->mRadius > 0);
  assert(this->HasInfinity() == false);
  assert(this->HasNaN() == false);
  assert(this->HasOnlyNormal() == true);
#endif
}

template<typename TType>
inline DCone<TType>::DCone(const DVector3<TValueType>& origin, TValueType hr)
  : DCone<TType>{origin, hr, hr}
{ }

template<typename TType>
inline const DVector3<typename DCone<TType>::TValueType>& DCone<TType>::GetOrigin() const noexcept
{
  return this->mOrigin;
}

template<typename TType>
inline typename DCone<TType>::TValueType DCone<TType>::GetHeight() const noexcept
{
  return this->mHeight;
}

template<typename TType>
inline typename DCone<TType>::TValueType DCone<TType>::GetRadius() const noexcept
{
  return this->mRadius;
}

template<typename TType>
inline bool DCone<TType>::HasNaN() const noexcept
{
  return 
      this->mOrigin.HasNaN()
    || std::isnan(this->mHeight)
    || std::isnan(this->mRadius);
}

template<typename TType>
inline bool DCone<TType>::HasInfinity() const noexcept
{
  return 
      this->mOrigin.HasInfinity() == true
    || std::isinf(this->mHeight)
    || std::isinf(this->mRadius);
}

template<typename TType>
inline bool DCone<TType>::HasOnlyNormal() const noexcept
{
  return 
      this->mOrigin.HasOnlyNormal() == true
    && std::isnormal(this->mHeight)
    && std::isnormal(this->mRadius);
}

} /// ::dy::math namespace