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

#include <Math/Type/Color/DColorRGB24.h>
#include <Math/Type/Color/DColorRGBA32.h>
#include <algorithm>

namespace dy::math
{

inline DColorRGBA32::DColorRGBA32(TU8 gray, TU8 alpha) noexcept
  : R{ gray }, G{ gray }, B{ gray }, A{ alpha }
{ }

inline DColorRGBA32(const DColorRGB24& rgb, TU8 alpha) noexcept
  : R{ rgb.R }, G { rgb.G }, B { rgb.B }, A { alpha }
{ }

inline DColorRGBA32::DColorRGBA32(TU8 r, TU8 g, TU8 b, TU8 a) noexcept
  : R{ r }, G{ g }, B{ b }, A{ a } 
{ }

inline DColorRGBA32::TValueType& DColorRGBA32::operator[](TIndex index)
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

inline const DColorRGBA32::TValueType& DColorRGBA32::operator[](TIndex index) const
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

inline TReal DColorRGBA32::ToGrayValue() const noexcept
{
  const TReal r = static_cast<TReal>(this->R) / TReal(255.0);
  const TReal g = static_cast<TReal>(this->G) / TReal(255.0);
  const TReal b = static_cast<TReal>(this->B) / TReal(255.0);

  return TType(0.2126)* r + TType(0.7152) * g + TType(0.0722) * b;
}

inline DColorRGBA32::TValueType* DColorRGBA32::Data() noexcept
{
  return &this->R;
}

inline const DColorRGBA32::TValueType* DColorRGBA32::Data() const noexcept
{
  return &this->R;
}

inline DColorRGBA32& DColorRGBA32::operator+=(const DColorRGBA32& value) noexcept
{
  const TU16 r = std::clamp(static_cast<TU16>(this->R + value.R), 0, 255);
  const TU16 g = std::clamp(static_cast<TU16>(this->G + value.G), 0, 255);
  const TU16 b = std::clamp(static_cast<TU16>(this->B + value.B), 0, 255);
  const TU16 a = std::clamp(static_cast<TU16>(this->A + value.A), 0, 255);

  this->R = static_cast<TU8>(r);
  this->G = static_cast<TU8>(g);
  this->B = static_cast<TU8>(b);
  this->A = static_cast<TU8>(a);
  return *this;
}

inline DColorRGBA32 & DColorRGBA32::operator-=(const DColorRGBA32 & value) noexcept
{
  const TU16 r = std::clamp(static_cast<TU16>(this->R - value.R), 0, 255);
  const TU16 g = std::clamp(static_cast<TU16>(this->G - value.G), 0, 255);
  const TU16 b = std::clamp(static_cast<TU16>(this->B - value.B), 0, 255);
  const TU16 a = std::clamp(static_cast<TU16>(this->A + value.A), 0, 255);

  this->R = static_cast<TU8>(r);
  this->G = static_cast<TU8>(g);
  this->B = static_cast<TU8>(b);
  this->A = static_cast<TU8>(a);
  return *this;
}

template <typename TType>
DColorRGBA32::operator DColorRGBA<TType>() const noexcept
{
  const TType r = TType(this->R) / TType(255.0);
  const TType g = TType(this->G) / TType(255.0);
  const TType b = TType(this->B) / TType(255.0);
  const TType a = TType(this->A) / TType(255.0);

  return DColorRGBA<TType>{r, g, b, a};
}

} /// ::dy::math namespace
