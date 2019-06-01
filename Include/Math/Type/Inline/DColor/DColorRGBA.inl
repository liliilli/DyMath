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

#include <Math/Type/Color/DColorRGBA.h>

namespace dy::math
{

template <typename TType>
DColorRGBA<TType>::DColorRGBA(TType gray, TType alpha) noexcept
  : R{ gray }, G{ gray }, B{ gray }, A{ alpha }
{ }

template <typename TType>
DColorRGBA<TType>::DColorRGBA(const DColorRGB<TType>& color, TType alpha) noexcept
  : R{ color.R }, G{ color.G }, B{ color.B }, A{ alpha }
{ }

template <typename TType>
DColorRGBA<TType>::DColorRGBA(TType r, TType g, TType b, TType a) noexcept
  : R{ r }, G{ g }, B{ b }, A{ a }
{ };

template <typename TType>
typename DColorRGBA<TType>::TValueType& DColorRGBA<TType>::operator[](TIndex index)
{
  switch (index)
  {
  case 0: return this->R;
  case 1: return this->G;
  case 2: return this->B;
  case 3: return this->A;
  default: M_ASSERT_OR_THROW(false, "index must be 0, 1 and 2.");
  }
}

template <typename TType>
const typename DColorRGBA<TType>::TValueType& DColorRGBA<TType>::operator[](TIndex index) const
{
  switch (index)
  {
  case 0: return this->R;
  case 1: return this->G;
  case 2: return this->B;
  case 3: return this->A;
  default: M_ASSERT_OR_THROW(false, "index must be 0, 1 and 2.");
  }
}

template <typename TType>
TType DColorRGBA<TType>::ToGrayScale() const noexcept
{
  return TType(0.2126)* this->R + TType(0.7152) * this->G + TType(0.0722) * this->B;
}

template <typename TType>
TType* DColorRGBA<TType>::Data() noexcept
{
  return &this->R;
}

template <typename TType>
const TType* DColorRGBA<TType>::Data() const noexcept
{
  return &this->R;
}

template <typename TType>
DColorRGBA<TType>& DColorRGBA<TType>::operator+=(const DColorRGBA& value) noexcept
{
  this->R += value.R;
  this->G += value.G;
  this->B += value.B;
  this->A += value.A;

  return *this;
}

template <typename TType>
DColorRGBA<TType>& DColorRGBA<TType>::operator-=(const DColorRGBA& value) noexcept
{
  this->R -= value.R;
  this->G -= value.G;
  this->B -= value.B;
  this->A -= value.A;

  return *this;
}

template <typename TType>
DColorRGBA<TType>& DColorRGBA<TType>::operator*=(TValueType value) noexcept
{
  this->R *= value;
  this->G *= value;
  this->B *= value;
  this->A *= value;

  return *this;
}

template <typename TType>
DColorRGBA<TType>& DColorRGBA<TType>::operator*=(const DColorRGBA& value) noexcept
{
  this->R *= value.R;
  this->G *= value.G;
  this->B *= value.B;
  this->A *= value.A;

  return *this;
}

template <typename TType>
DColorRGBA<TType>& DColorRGBA<TType>::operator/=(TValueType value) noexcept
{
  this->R /= value;
  this->G /= value;
  this->B /= value;
  this->A /= value;

  return *this;
}

template <typename TType>
DColorRGBA<TType>& DColorRGBA<TType>::operator/=(const DColorRGBA& value) noexcept
{
  this->R /= value.R;
  this->G /= value.G;
  this->B /= value.B;
  this->A /= value.A;

  return *this;
}

template <typename TType>
DColorRGBA<TType>::operator DVector4<TType>() const noexcept
{
  return DVector4<TValueType>{this->R, this->G, this->B, this->A};
}

} /// ::dy::math namespace

