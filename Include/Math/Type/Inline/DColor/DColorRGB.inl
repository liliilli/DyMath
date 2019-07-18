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

#include <Math/Type/Color/DColorRGB.h>

namespace dy::math
{

template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Aqua = {0, 1, 1};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Black = {0};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Blue = {0, TType(0), TType(1)};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB DarkRed = {TType(0.5), 0, 0};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB DarkGray  = {0, TType(0.5), 0};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB DarkGreen = {0, 0, TType(0.5)};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Gold      = {1, 0.843, 0};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Gray      = {TType(0.5)};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Green     = {0, 1, 0};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Magenta   = {1, 0, 1};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Orange    = {1, 0.549, 0};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Purple    = {0.5, 0, 0.5};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Red       = {1, 0, 0};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB White     = {1};
template <typename TType>
inline static const typename DColorRGB<TType>::DColorRGB Yellow    = {1, 1, 0};

template <typename TType>
DColorRGB<TType>::DColorRGB(TType gray) noexcept
  : R{gray}, G{gray}, B{gray}
{ }

template <typename TType>
DColorRGB<TType>::DColorRGB(TType r, TType g, TType b) noexcept 
  : R{r}, G{g}, B{b}
{ };

template <typename TType>
typename DColorRGB<TType>::TValueType& DColorRGB<TType>::operator[](TIndex index)
{
  switch (index)
  {
  case 0: return this->R;
  case 1: return this->G;
  case 2: return this->B;
  default: M_ASSERT_OR_THROW(false, "index must be 0, 1 and 2.");
  }
}

template <typename TType>
const typename DColorRGB<TType>::TValueType& DColorRGB<TType>::operator[](TIndex index) const
{
  switch (index)
  {
  case 0: return this->R;
  case 1: return this->G;
  case 2: return this->B;
  default: M_ASSERT_OR_THROW(false, "index must be 0, 1 and 2.");
  }
}

template <typename TType>
TType DColorRGB<TType>::ToGrayValue() const noexcept
{
  return TType(0.2126) * this->R + TType(0.7152) * this->G + TType(0.0722) * this->B;
}

template <typename TType>
TType* DColorRGB<TType>::Data() noexcept
{
  return &this->R;
}

template <typename TType>
const TType* DColorRGB<TType>::Data() const noexcept
{
  return &this->R;
}

template <typename TType>
DColorRGB<TType>& DColorRGB<TType>::operator+=(const DColorRGB& value) noexcept
{
  this->R += value.R;
  this->G += value.G;
  this->B += value.B;

  return *this;
}

template <typename TType>
DColorRGB<TType>& DColorRGB<TType>::operator-=(const DColorRGB& value) noexcept
{
  this->R -= value.R;
  this->G -= value.G;
  this->B -= value.B;

  return *this;
}

template <typename TType>
DColorRGB<TType>& DColorRGB<TType>::operator*=(TValueType value) noexcept
{
  this->R *= value;
  this->G *= value;
  this->B *= value;

  return *this;
}

template <typename TType>
DColorRGB<TType>& DColorRGB<TType>::operator*=(const DColorRGB& value) noexcept
{
  this->R *= value.R;
  this->G *= value.G;
  this->B *= value.B;

  return *this;
}

template <typename TType>
DColorRGB<TType>& DColorRGB<TType>::operator/=(TValueType value) noexcept
{
  this->R /= value;
  this->G /= value;
  this->B /= value;

  return *this;
}

template <typename TType>
DColorRGB<TType>& DColorRGB<TType>::operator/=(const DColorRGB& value) noexcept
{
  this->R /= value.R;
  this->G /= value.G;
  this->B /= value.B;

  return *this;
}

template <typename TType>
DColorRGB<TType>::operator DVector3<TType>() const noexcept
{
  return DVector3<TValueType>{this->R, this->G, this->B};
}

} /// ::dy::math namespace

