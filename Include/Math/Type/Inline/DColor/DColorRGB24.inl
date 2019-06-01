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

inline DColorRGB24::DColorRGB24(TU8 gray) noexcept
  : R{ gray }, G{ gray }, B{ gray }
{ }

inline DColorRGB24::DColorRGB24(TU8 r, TU8 g, TU8 b) noexcept
  : R{ r }, G{ g }, B{ b }
{ }

inline DColorRGB24::TValueType& DColorRGB24::operator[](TIndex index)
{
  switch (index)
  {
  case 0: return this->R;
  case 1: return this->G;
  case 2: return this->B;
  default: M_ASSERT_OR_THROW(false, "index must be 0, 1 and 2.");
  }
}

inline const DColorRGB24::TValueType& DColorRGB24::operator[](TIndex index) const
{
  switch (index)
  {
  case 0: return this->R;
  case 1: return this->G;
  case 2: return this->B;
  default: M_ASSERT_OR_THROW(false, "index must be 0, 1 and 2.");
  }
}

inline TReal DColorRGB24::ToGrayValue() const noexcept
{
  const TReal r = static_cast<TReal>(this->R) / TReal(255.0);
  const TReal g = static_cast<TReal>(this->G) / TReal(255.0);
  const TReal b = static_cast<TReal>(this->B) / TReal(255.0);

  return TReal(0.2126)* r + TReal(0.7152) * g + TReal(0.0722) * b;
}

inline DColorRGB24::TValueType* DColorRGB24::Data() noexcept
{
  return &this->R;
}

inline const DColorRGB24::TValueType* DColorRGB24::Data() const noexcept
{
  return &this->R;
}

inline DColorRGB24& DColorRGB24::operator+=(const DColorRGB24& value) noexcept
{
  const TU16 r = std::clamp<TU16>(static_cast<TU16>(this->R + value.R), 0, 255);
  const TU16 g = std::clamp<TU16>(static_cast<TU16>(this->G + value.G), 0, 255);
  const TU16 b = std::clamp<TU16>(static_cast<TU16>(this->B + value.B), 0, 255);

  this->R = static_cast<TU8>(r);
  this->G = static_cast<TU8>(g);
  this->B = static_cast<TU8>(b);
  return *this;
}

inline DColorRGB24& DColorRGB24::operator-=(const DColorRGB24& value) noexcept
{
  const TU16 r = std::clamp<TU16>(static_cast<TU16>(this->R - value.R), 0, 255);
  const TU16 g = std::clamp<TU16>(static_cast<TU16>(this->G - value.G), 0, 255);
  const TU16 b = std::clamp<TU16>(static_cast<TU16>(this->B - value.B), 0, 255);

  this->R = static_cast<TU8>(r);
  this->G = static_cast<TU8>(g);
  this->B = static_cast<TU8>(b);
  return *this;
}

template <typename TType>
DColorRGB24::operator DColorRGB<TType>() const noexcept
{
  const TType r = TType(this->R) / TType(255.0);
  const TType g = TType(this->G) / TType(255.0);
  const TType b = TType(this->B) / TType(255.0);

  return DColorRGB<TType>{r, g, b};
}

template <typename TType>
DColorRGB24::operator DColorRGBA<TType>() const noexcept
{
  const TType r = TType(this->R) / TType(255.0);
  const TType g = TType(this->G) / TType(255.0);
  const TType b = TType(this->B) / TType(255.0);

  return DColorRGBA<TType>{r, g, b, TType(1.0)};
}

inline DColorRGB24::operator DColorRGBA32() const noexcept
{
  return DColorRGBA32{ this->R, this->G, this->B, TU8(255) };
};

} /// ::dy::math namespace

